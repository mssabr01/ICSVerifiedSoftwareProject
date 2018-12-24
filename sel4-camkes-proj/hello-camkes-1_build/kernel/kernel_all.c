#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/api/faults.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <types.h>
#include <api/faults.h>
#include <api/syscall.h>
#include <kernel/thread.h>
#include <arch/kernel/thread.h>
#include <machine/debug.h>

/* consistency with libsel4 */
compile_assert(InvalidRoot, lookup_fault_invalid_root + 1 == seL4_InvalidRoot)
compile_assert(MissingCapability, lookup_fault_missing_capability + 1 == seL4_MissingCapability)
compile_assert(DepthMismatch, lookup_fault_depth_mismatch + 1 == seL4_DepthMismatch)
compile_assert(GuardMismatch, lookup_fault_guard_mismatch + 1 == seL4_GuardMismatch)
compile_assert(seL4_UnknownSyscall_Syscall, (word_t) n_syscallMessage == seL4_UnknownSyscall_Syscall)
compile_assert(seL4_UserException_Number, (word_t) n_exceptionMessage == seL4_UserException_Number)
compile_assert(seL4_UserException_Code, (word_t) n_exceptionMessage + 1 == seL4_UserException_Code)

static inline unsigned int
setMRs_lookup_failure(tcb_t *receiver, word_t* receiveIPCBuffer,
                      lookup_fault_t luf, unsigned int offset)
{
    word_t lufType = lookup_fault_get_lufType(luf);
    word_t i;

    i = setMR(receiver, receiveIPCBuffer, offset, lufType + 1);

    /* check constants match libsel4 */
    if (offset == seL4_CapFault_LookupFailureType) {
        assert(offset + 1 == seL4_CapFault_BitsLeft);
        assert(offset + 2 == seL4_CapFault_DepthMismatch_BitsFound);
        assert(offset + 2 == seL4_CapFault_GuardMismatch_GuardFound);
        assert(offset + 3 == seL4_CapFault_GuardMismatch_BitsFound);
    } else {
        assert(offset == 1);
    }

    switch (lufType) {
    case lookup_fault_invalid_root:
        return i;

    case lookup_fault_missing_capability:
        return setMR(receiver, receiveIPCBuffer, offset + 1,
                     lookup_fault_missing_capability_get_bitsLeft(luf));

    case lookup_fault_depth_mismatch:
        setMR(receiver, receiveIPCBuffer, offset + 1,
              lookup_fault_depth_mismatch_get_bitsLeft(luf));
        return setMR(receiver, receiveIPCBuffer, offset + 2,
                     lookup_fault_depth_mismatch_get_bitsFound(luf));

    case lookup_fault_guard_mismatch:
        setMR(receiver, receiveIPCBuffer, offset + 1,
              lookup_fault_guard_mismatch_get_bitsLeft(luf));
        setMR(receiver, receiveIPCBuffer, offset + 2,
              lookup_fault_guard_mismatch_get_guardFound(luf));
        return setMR(receiver, receiveIPCBuffer, offset + 3,
                     lookup_fault_guard_mismatch_get_bitsFound(luf));

    default:
        fail("Invalid lookup failure");
    }
}

static inline void
copyMRsFaultReply(tcb_t *sender, tcb_t *receiver, MessageID_t id, word_t length)
{
    word_t i;
    bool_t archInfo;

    archInfo = Arch_getSanitiseRegisterInfo(receiver);

    for (i = 0; i < MIN(length, n_msgRegisters); i++) {
        register_t r = fault_messages[id][i];
        word_t v = getRegister(sender, msgRegisters[i]);
        setRegister(receiver, r, sanitiseRegister(r, v, archInfo));
    }

    if (i < length) {
        word_t *sendBuf = lookupIPCBuffer(false, sender);
        if (sendBuf) {
            for (; i < length; i++) {
                register_t r = fault_messages[id][i];
                word_t v = sendBuf[i + 1];
                setRegister(receiver, r, sanitiseRegister(r, v, archInfo));
            }
        }
    }
}

static inline void
copyMRsFault(tcb_t *sender, tcb_t *receiver, MessageID_t id,
             word_t length, word_t *receiveIPCBuffer)
{
    word_t i;
    for (i = 0; i < MIN(length, n_msgRegisters); i++) {
        setRegister(receiver, msgRegisters[i], getRegister(sender, fault_messages[id][i]));
    }

    if (receiveIPCBuffer) {
        for (; i < length; i++) {
            receiveIPCBuffer[i + 1] = getRegister(sender, fault_messages[id][i]);
        }
    }
}

bool_t
handleFaultReply(tcb_t *receiver, tcb_t *sender)
{
    /* These lookups are moved inward from doReplyTransfer */
    seL4_MessageInfo_t tag = messageInfoFromWord(getRegister(sender, msgInfoRegister));
    word_t label = seL4_MessageInfo_get_label(tag);
    word_t length = seL4_MessageInfo_get_length(tag);
    seL4_Fault_t fault = receiver->tcbFault;

    switch (seL4_Fault_get_seL4_FaultType(fault)) {
    case seL4_Fault_CapFault:
        return true;

    case seL4_Fault_UnknownSyscall:
        copyMRsFaultReply(sender, receiver, MessageID_Syscall, MIN(length, n_syscallMessage));
        return (label == 0);

    case seL4_Fault_UserException:
        copyMRsFaultReply(sender, receiver, MessageID_Exception, MIN(length, n_exceptionMessage));
        return (label == 0);

#ifdef CONFIG_HARDWARE_DEBUG_API
    case seL4_Fault_DebugException: {
        word_t n_instrs;

        if (seL4_Fault_DebugException_get_exceptionReason(fault) != seL4_SingleStep) {
            /* Only single-step replies are required to set message registers.
             */
            return (label == 0);
        }

        if (length < DEBUG_REPLY_N_EXPECTED_REGISTERS) {
            /* A single-step reply doesn't mean much if it isn't composed of the bp
             * number and number of instructions to skip. But even if both aren't
             * set, we can still allow the thread to continue because replying
             * should uniformly resume thread execution, based on the general seL4
             * API model.
             *
             * If it was single-step, but no reply registers were set, just
             * default to skipping 1 and continuing.
             *
             * On x86, bp_num actually doesn't matter for single-stepping
             * because single-stepping doesn't use a hardware register -- it
             * uses EFLAGS.TF.
             */
            n_instrs = 1;
        } else {
            /* If the reply had all expected registers set, proceed as normal */
            n_instrs = getRegister(sender, msgRegisters[0]);
        }

        syscall_error_t res;

        res = Arch_decodeConfigureSingleStepping(receiver, 0, n_instrs, true);
        if (res.type != seL4_NoError) {
            return false;
        };

        configureSingleStepping(receiver, 0, n_instrs, true);

        /* Replying will always resume the thread: the only variant behaviour
         * is whether or not the thread will be resumed with stepping still
         * enabled.
         */
        return (label == 0);
    }
#endif

    default:
        return Arch_handleFaultReply(receiver, sender, seL4_Fault_get_seL4_FaultType(fault));
    }
}

word_t
setMRs_fault(tcb_t *sender, tcb_t* receiver, word_t *receiveIPCBuffer)
{
    switch (seL4_Fault_get_seL4_FaultType(sender->tcbFault)) {
    case seL4_Fault_CapFault:
        setMR(receiver, receiveIPCBuffer, seL4_CapFault_IP, getRestartPC(sender));
        setMR(receiver, receiveIPCBuffer, seL4_CapFault_Addr,
              seL4_Fault_CapFault_get_address(sender->tcbFault));
        setMR(receiver, receiveIPCBuffer, seL4_CapFault_InRecvPhase,
              seL4_Fault_CapFault_get_inReceivePhase(sender->tcbFault));
        return setMRs_lookup_failure(receiver, receiveIPCBuffer,
                                     sender->tcbLookupFailure, seL4_CapFault_LookupFailureType);

    case seL4_Fault_UnknownSyscall: {
        copyMRsFault(sender, receiver, MessageID_Syscall, n_syscallMessage,
                     receiveIPCBuffer);

        return setMR(receiver, receiveIPCBuffer, n_syscallMessage,
                     seL4_Fault_UnknownSyscall_get_syscallNumber(sender->tcbFault));
    }

    case seL4_Fault_UserException: {
        copyMRsFault(sender, receiver, MessageID_Exception,
                     n_exceptionMessage, receiveIPCBuffer);
        setMR(receiver, receiveIPCBuffer, n_exceptionMessage,
              seL4_Fault_UserException_get_number(sender->tcbFault));
        return setMR(receiver, receiveIPCBuffer, n_exceptionMessage + 1u,
                     seL4_Fault_UserException_get_code(sender->tcbFault));
    }

#ifdef CONFIG_HARDWARE_DEBUG_API
    case seL4_Fault_DebugException: {
        word_t reason = seL4_Fault_DebugException_get_exceptionReason(sender->tcbFault);

        setMR(receiver, receiveIPCBuffer,
              seL4_DebugException_FaultIP, getRestartPC(sender));
        unsigned int ret = setMR(receiver, receiveIPCBuffer,
                                 seL4_DebugException_ExceptionReason, reason);

        if (reason != seL4_SingleStep && reason != seL4_SoftwareBreakRequest) {
            ret = setMR(receiver, receiveIPCBuffer,
                        seL4_DebugException_TriggerAddress,
                        seL4_Fault_DebugException_get_breakpointAddress(sender->tcbFault));

            /* Breakpoint messages also set a "breakpoint number" register. */
            ret = setMR(receiver, receiveIPCBuffer,
                        seL4_DebugException_BreakpointNumber,
                        seL4_Fault_DebugException_get_breakpointNumber(sender->tcbFault));
        }
        return ret;
    }
#endif /* CONFIG_HARDWARE_DEBUG_API */

    default:
        return Arch_setMRs_fault(sender, receiver, receiveIPCBuffer,
                                 seL4_Fault_get_seL4_FaultType(sender->tcbFault));
    }
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/api/syscall.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <types.h>
#include <benchmark/benchmark.h>
#include <arch/benchmark.h>
#include <benchmark/benchmark_track.h>
#include <benchmark/benchmark_utilisation.h>
#include <api/syscall.h>
#include <api/failures.h>
#include <api/faults.h>
#include <kernel/cspace.h>
#include <kernel/faulthandler.h>
#include <kernel/thread.h>
#include <kernel/vspace.h>
#include <machine/io.h>
#include <plat/machine/hardware.h>
#include <object/interrupt.h>
#include <model/statedata.h>
#include <string.h>
#include <kernel/traps.h>
#include <arch/machine.h>

#ifdef CONFIG_DEBUG_BUILD
#include <arch/machine/capdl.h>
#endif

/* The haskell function 'handleEvent' is split into 'handleXXX' variants
 * for each event causing a kernel entry */

exception_t
handleInterruptEntry(void)
{
    irq_t irq;

    irq = getActiveIRQ();

    if (irq != irqInvalid) {
        handleInterrupt(irq);
        Arch_finaliseInterrupt();
    } else {
#ifdef CONFIG_IRQ_REPORTING
        userError("Spurious interrupt!");
#endif
        handleSpuriousIRQ();
    }

    schedule();
    activateThread();

    return EXCEPTION_NONE;
}

exception_t
handleUnknownSyscall(word_t w)
{
#ifdef CONFIG_PRINTING
    if (w == SysDebugPutChar) {
        kernel_putchar(getRegister(NODE_STATE(ksCurThread), capRegister));
        return EXCEPTION_NONE;
    }
    if (w == SysDebugDumpScheduler) {
#ifdef CONFIG_DEBUG_BUILD
        debug_dumpScheduler();
#endif
        return EXCEPTION_NONE;
    }
#endif
#ifdef CONFIG_DEBUG_BUILD
    if (w == SysDebugHalt) {
        tcb_t * UNUSED tptr = NODE_STATE(ksCurThread);
        printf("Debug halt syscall from user thread %p \"%s\"\n", tptr, tptr->tcbName);
        halt();
    }
    if (w == SysDebugSnapshot) {
        tcb_t * UNUSED tptr = NODE_STATE(ksCurThread);
        printf("Debug snapshot syscall from user thread %p \"%s\"\n", tptr, tptr->tcbName);
        capDL();
        return EXCEPTION_NONE;
    }
    if (w == SysDebugCapIdentify) {
        word_t cptr = getRegister(NODE_STATE(ksCurThread), capRegister);
        lookupCapAndSlot_ret_t lu_ret = lookupCapAndSlot(NODE_STATE(ksCurThread), cptr);
        word_t cap_type = cap_get_capType(lu_ret.cap);
        setRegister(NODE_STATE(ksCurThread), capRegister, cap_type);
        return EXCEPTION_NONE;
    }

    if (w == SysDebugNameThread) {
        /* This is a syscall meant to aid debugging, so if anything goes wrong
         * then assume the system is completely misconfigured and halt */
        const char *name;
        word_t len;
        word_t cptr = getRegister(NODE_STATE(ksCurThread), capRegister);
        lookupCapAndSlot_ret_t lu_ret = lookupCapAndSlot(NODE_STATE(ksCurThread), cptr);
        /* ensure we got a TCB cap */
        word_t cap_type = cap_get_capType(lu_ret.cap);
        if (cap_type != cap_thread_cap) {
            userError("SysDebugNameThread: cap is not a TCB, halting");
            halt();
        }
        /* Add 1 to the IPC buffer to skip the message info word */
        name = (const char*)(lookupIPCBuffer(true, NODE_STATE(ksCurThread)) + 1);
        if (!name) {
            userError("SysDebugNameThread: Failed to lookup IPC buffer, halting");
            halt();
        }
        /* ensure the name isn't too long */
        len = strnlen(name, seL4_MsgMaxLength * sizeof(word_t));
        if (len == seL4_MsgMaxLength * sizeof(word_t)) {
            userError("SysDebugNameThread: Name too long, halting");
            halt();
        }
        setThreadName(TCB_PTR(cap_thread_cap_get_capTCBPtr(lu_ret.cap)), name);
        return EXCEPTION_NONE;
    }
#endif /* CONFIG_DEBUG_BUILD */

#ifdef CONFIG_DANGEROUS_CODE_INJECTION
    if (w == SysDebugRun) {
        ((void (*) (void *))getRegister(NODE_STATE(ksCurThread), capRegister))((void*)getRegister(NODE_STATE(ksCurThread), msgInfoRegister));
        return EXCEPTION_NONE;
    }
#endif

#ifdef CONFIG_KERNEL_X86_DANGEROUS_MSR
    if (w == SysX86DangerousWRMSR) {
        uint64_t val;
        uint32_t reg = getRegister(NODE_STATE(ksCurThread), capRegister);
        if (CONFIG_WORD_SIZE == 32) {
            val = (uint64_t)getSyscallArg(0, NULL) | ((uint64_t)getSyscallArg(1, NULL) << 32);
        } else {
            val = getSyscallArg(0, NULL);
        }
        x86_wrmsr(reg, val);
        return EXCEPTION_NONE;
    } else if (w == SysX86DangerousRDMSR) {
        uint64_t val;
        uint32_t reg = getRegister(NODE_STATE(ksCurThread), capRegister);
        val = x86_rdmsr(reg);
        int num = 1;
        if (CONFIG_WORD_SIZE == 32) {
            setMR(NODE_STATE(ksCurThread), NULL, 0, val & 0xffffffff);
            setMR(NODE_STATE(ksCurThread), NULL, 1, val >> 32);
            num++;
        } else {
            setMR(NODE_STATE(ksCurThread), NULL, 0, val);
        }
        setRegister(NODE_STATE(ksCurThread), msgInfoRegister, wordFromMessageInfo(seL4_MessageInfo_new(0, 0, 0, num)));
        return EXCEPTION_NONE;
    }
#endif

#ifdef CONFIG_ENABLE_BENCHMARKS
    if (w == SysBenchmarkFlushCaches) {
        arch_clean_invalidate_caches();
        return EXCEPTION_NONE;
    } else if (w == SysBenchmarkResetLog) {
#ifdef CONFIG_BENCHMARK_USE_KERNEL_LOG_BUFFER
        if (ksUserLogBuffer == 0) {
            userError("A user-level buffer has to be set before resetting benchmark.\
                    Use seL4_BenchmarkSetLogBuffer\n");
            setRegister(NODE_STATE(ksCurThread), capRegister, seL4_IllegalOperation);
            return EXCEPTION_SYSCALL_ERROR;
        }

        ksLogIndex = 0;
#endif /* CONFIG_BENCHMARK_USE_KERNEL_LOG_BUFFER */
#ifdef CONFIG_BENCHMARK_TRACK_UTILISATION
        benchmark_log_utilisation_enabled = true;
        NODE_STATE(ksIdleThread)->benchmark.utilisation = 0;
        NODE_STATE(ksCurThread)->benchmark.schedule_start_time = ksEnter;
        benchmark_start_time = ksEnter;
        benchmark_arch_utilisation_reset();
#endif /* CONFIG_BENCHMARK_TRACK_UTILISATION */
        setRegister(NODE_STATE(ksCurThread), capRegister, seL4_NoError);
        return EXCEPTION_NONE;
    } else if (w == SysBenchmarkFinalizeLog) {
#ifdef CONFIG_BENCHMARK_USE_KERNEL_LOG_BUFFER
        ksLogIndexFinalized = ksLogIndex;
        setRegister(NODE_STATE(ksCurThread), capRegister, ksLogIndexFinalized);
#endif /* CONFIG_BENCHMARK_USE_KERNEL_LOG_BUFFER */
#ifdef CONFIG_BENCHMARK_TRACK_UTILISATION
        benchmark_utilisation_finalise();
#endif /* CONFIG_BENCHMARK_TRACK_UTILISATION */
        return EXCEPTION_NONE;
    } else if (w == SysBenchmarkSetLogBuffer) {
#ifdef CONFIG_BENCHMARK_USE_KERNEL_LOG_BUFFER
        word_t cptr_userFrame = getRegister(NODE_STATE(ksCurThread), capRegister);

        if (benchmark_arch_map_logBuffer(cptr_userFrame) != EXCEPTION_NONE) {
            setRegister(NODE_STATE(ksCurThread), capRegister, seL4_IllegalOperation);
            return EXCEPTION_SYSCALL_ERROR;
        }

        setRegister(NODE_STATE(ksCurThread), capRegister, seL4_NoError);
        return EXCEPTION_NONE;
#endif /* CONFIG_BENCHMARK_USE_KERNEL_LOG_BUFFER */
    }

#ifdef CONFIG_BENCHMARK_TRACK_UTILISATION
    else if (w == SysBenchmarkGetThreadUtilisation) {
        benchmark_track_utilisation_dump();
        return EXCEPTION_NONE;
    } else if (w == SysBenchmarkResetThreadUtilisation) {
        benchmark_track_reset_utilisation();
        return EXCEPTION_NONE;
    }
#endif /* CONFIG_BENCHMARK_TRACK_UTILISATION */

    else if (w == SysBenchmarkNullSyscall) {
        return EXCEPTION_NONE;
    }
#endif /* CONFIG_ENABLE_BENCHMARKS */

    current_fault = seL4_Fault_UnknownSyscall_new(w);
    handleFault(NODE_STATE(ksCurThread));

    schedule();
    activateThread();

    return EXCEPTION_NONE;
}

exception_t
handleUserLevelFault(word_t w_a, word_t w_b)
{
    current_fault = seL4_Fault_UserException_new(w_a, w_b);
    handleFault(NODE_STATE(ksCurThread));

    schedule();
    activateThread();

    return EXCEPTION_NONE;
}

exception_t
handleVMFaultEvent(vm_fault_type_t vm_faultType)
{
    exception_t status;

    status = handleVMFault(NODE_STATE(ksCurThread), vm_faultType);
    if (status != EXCEPTION_NONE) {
        handleFault(NODE_STATE(ksCurThread));
    }

    schedule();
    activateThread();

    return EXCEPTION_NONE;
}


static exception_t
handleInvocation(bool_t isCall, bool_t isBlocking)
{
    seL4_MessageInfo_t info;
    cptr_t cptr;
    lookupCapAndSlot_ret_t lu_ret;
    word_t *buffer;
    exception_t status;
    word_t length;
    tcb_t *thread;

    thread = NODE_STATE(ksCurThread);

    info = messageInfoFromWord(getRegister(thread, msgInfoRegister));
    cptr = getRegister(thread, capRegister);

    /* faulting section */
    lu_ret = lookupCapAndSlot(thread, cptr);

    if (unlikely(lu_ret.status != EXCEPTION_NONE)) {
        userError("Invocation of invalid cap #%lu.", cptr);
        current_fault = seL4_Fault_CapFault_new(cptr, false);

        if (isBlocking) {
            handleFault(thread);
        }

        return EXCEPTION_NONE;
    }

    buffer = lookupIPCBuffer(false, thread);

    status = lookupExtraCaps(thread, buffer, info);

    if (unlikely(status != EXCEPTION_NONE)) {
        userError("Lookup of extra caps failed.");
        if (isBlocking) {
            handleFault(thread);
        }
        return EXCEPTION_NONE;
    }

    /* Syscall error/Preemptible section */
    length = seL4_MessageInfo_get_length(info);
    if (unlikely(length > n_msgRegisters && !buffer)) {
        length = n_msgRegisters;
    }
    status = decodeInvocation(seL4_MessageInfo_get_label(info), length,
                              cptr, lu_ret.slot, lu_ret.cap,
                              current_extra_caps, isBlocking, isCall,
                              buffer);

    if (unlikely(status == EXCEPTION_PREEMPTED)) {
        return status;
    }

    if (unlikely(status == EXCEPTION_SYSCALL_ERROR)) {
        if (isCall) {
            replyFromKernel_error(thread);
        }
        return EXCEPTION_NONE;
    }

    if (unlikely(
                thread_state_get_tsType(thread->tcbState) == ThreadState_Restart)) {
        if (isCall) {
            replyFromKernel_success_empty(thread);
        }
        setThreadState(thread, ThreadState_Running);
    }

    return EXCEPTION_NONE;
}

static void
handleReply(void)
{
    cte_t *callerSlot;
    cap_t callerCap;

    callerSlot = TCB_PTR_CTE_PTR(NODE_STATE(ksCurThread), tcbCaller);
    callerCap = callerSlot->cap;

    switch (cap_get_capType(callerCap)) {
    case cap_reply_cap: {
        tcb_t *caller;

        if (cap_reply_cap_get_capReplyMaster(callerCap)) {
            break;
        }
        caller = TCB_PTR(cap_reply_cap_get_capTCBPtr(callerCap));
        /* Haskell error:
         * "handleReply: caller must not be the current thread" */
        assert(caller != NODE_STATE(ksCurThread));
        doReplyTransfer(NODE_STATE(ksCurThread), caller, callerSlot);
        return;
    }

    case cap_null_cap:
        userError("Attempted reply operation when no reply cap present.");
        return;

    default:
        break;
    }

    fail("handleReply: invalid caller cap");
}

static void
handleRecv(bool_t isBlocking)
{
    word_t epCPtr;
    lookupCap_ret_t lu_ret;

    epCPtr = getRegister(NODE_STATE(ksCurThread), capRegister);

    lu_ret = lookupCap(NODE_STATE(ksCurThread), epCPtr);

    if (unlikely(lu_ret.status != EXCEPTION_NONE)) {
        /* current_lookup_fault has been set by lookupCap */
        current_fault = seL4_Fault_CapFault_new(epCPtr, true);
        handleFault(NODE_STATE(ksCurThread));
        return;
    }

    switch (cap_get_capType(lu_ret.cap)) {
    case cap_endpoint_cap:
        if (unlikely(!cap_endpoint_cap_get_capCanReceive(lu_ret.cap))) {
            current_lookup_fault = lookup_fault_missing_capability_new(0);
            current_fault = seL4_Fault_CapFault_new(epCPtr, true);
            handleFault(NODE_STATE(ksCurThread));
            break;
        }

        deleteCallerCap(NODE_STATE(ksCurThread));
        receiveIPC(NODE_STATE(ksCurThread), lu_ret.cap, isBlocking);
        break;

    case cap_notification_cap: {
        notification_t *ntfnPtr;
        tcb_t *boundTCB;
        ntfnPtr = NTFN_PTR(cap_notification_cap_get_capNtfnPtr(lu_ret.cap));
        boundTCB = (tcb_t*)notification_ptr_get_ntfnBoundTCB(ntfnPtr);
        if (unlikely(!cap_notification_cap_get_capNtfnCanReceive(lu_ret.cap)
                     || (boundTCB && boundTCB != NODE_STATE(ksCurThread)))) {
            current_lookup_fault = lookup_fault_missing_capability_new(0);
            current_fault = seL4_Fault_CapFault_new(epCPtr, true);
            handleFault(NODE_STATE(ksCurThread));
            break;
        }

        receiveSignal(NODE_STATE(ksCurThread), lu_ret.cap, isBlocking);
        break;
    }
    default:
        current_lookup_fault = lookup_fault_missing_capability_new(0);
        current_fault = seL4_Fault_CapFault_new(epCPtr, true);
        handleFault(NODE_STATE(ksCurThread));
        break;
    }
}

static void
handleYield(void)
{
    tcbSchedDequeue(NODE_STATE(ksCurThread));
    SCHED_APPEND_CURRENT_TCB;
    rescheduleRequired();
}

exception_t
handleSyscall(syscall_t syscall)
{
    exception_t ret;
    irq_t irq;

    switch (syscall) {
    case SysSend:
        ret = handleInvocation(false, true);
        if (unlikely(ret != EXCEPTION_NONE)) {
            irq = getActiveIRQ();
            if (irq != irqInvalid) {
                handleInterrupt(irq);
                Arch_finaliseInterrupt();
            }
        }
        break;

    case SysNBSend:
        ret = handleInvocation(false, false);
        if (unlikely(ret != EXCEPTION_NONE)) {
            irq = getActiveIRQ();
            if (irq != irqInvalid) {
                handleInterrupt(irq);
                Arch_finaliseInterrupt();
            }
        }
        break;

    case SysCall:
        ret = handleInvocation(true, true);
        if (unlikely(ret != EXCEPTION_NONE)) {
            irq = getActiveIRQ();
            if (irq != irqInvalid) {
                handleInterrupt(irq);
                Arch_finaliseInterrupt();
            }
        }
        break;

    case SysRecv:
        handleRecv(true);
        break;

    case SysReply:
        handleReply();
        break;

    case SysReplyRecv:
        handleReply();
        handleRecv(true);
        break;

    case SysNBRecv:
        handleRecv(false);
        break;

    case SysYield:
        handleYield();
        break;

    default:
        fail("Invalid syscall");
    }

    schedule();
    activateThread();

    return EXCEPTION_NONE;
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/64/c_traps.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <model/statedata.h>
#include <machine/fpu.h>
#include <kernel/traps.h>
#include <arch/machine/debug.h>
#include <kernel/stack.h>

#include <api/syscall.h>

#ifdef CONFIG_VTX
static void NORETURN vmlaunch_failed(word_t failInvalid, word_t failValid)
{
    NODE_LOCK_SYS;

    c_entry_hook();

    if (failInvalid) {
        userError("current VMCS pointer is not valid");
    }
    if (failValid) {
        userError("vmlaunch/vmresume error %d", (int)vmread(VMX_DATA_INSTRUCTION_ERROR));
    }

    handleVmEntryFail();
    restore_user_context();
}

static void NORETURN restore_vmx(void)
{
    restoreVMCS();
    tcb_t *cur_thread = NODE_STATE(ksCurThread);
#ifdef CONFIG_HARDWARE_DEBUG_API
    /* Do not support breakpoints in VMs, so just disable all breakpoints */
    loadAllDisabledBreakpointState(cur_thread);
#endif
    if (cur_thread->tcbArch.tcbVCPU->launched) {
        /* attempt to do a vmresume */
        asm volatile(
            // Set our stack pointer to the top of the tcb so we can efficiently pop
            "movq %[reg], %%rsp\n"
            "popq %%rax\n"
            "popq %%rbx\n"
            "popq %%rcx\n"
            "popq %%rdx\n"
            "popq %%rsi\n"
            "popq %%rdi\n"
            "popq %%rbp\n"
#ifdef ENABLE_SMP_SUPPORT
            "swapgs\n"
#endif
            // Now do the vmresume
            "vmresume\n"
            "setb %%al\n"
            "sete %%bl\n"
            "movzx %%al, %%rdi\n"
            "movzx %%bl, %%rsi\n"
            // if we get here we failed
#ifdef ENABLE_SMP_SUPPORT
            "swapgs\n"
            "movq %%gs:%c[stack_offset], %%rsp\n"
#else
            "leaq kernel_stack_alloc + %c[stack_size], %%rsp\n"
#endif
            "leaq %[failed], %%rax\n"
            "jmp *%%rax\n"
            :
            : [reg]"r"(&cur_thread->tcbArch.tcbVCPU->gp_registers[VCPU_EAX]),
            [failed]"m"(vmlaunch_failed),
            [stack_size]"i"(BIT(CONFIG_KERNEL_STACK_BITS))
#ifdef ENABLE_SMP_SUPPORT
            , [stack_offset]"i"(OFFSETOF(nodeInfo_t, stackTop))
#endif
            // Clobber memory so the compiler is forced to complete all stores
            // before running this assembler
            : "memory"
        );
    } else {
        /* attempt to do a vmlaunch */
        asm volatile(
            // Set our stack pointer to the top of the tcb so we can efficiently pop
            "movq %[reg], %%rsp\n"
            "popq %%rax\n"
            "popq %%rbx\n"
            "popq %%rcx\n"
            "popq %%rdx\n"
            "popq %%rsi\n"
            "popq %%rdi\n"
            "popq %%rbp\n"
#ifdef ENABLE_SMP_SUPPORT
            "swapgs\n"
#endif
            // Now do the vmresume
            "vmlaunch\n"
            // if we get here we failed
            "setb %%al\n"
            "sete %%bl\n"
            "movzx %%al, %%rdi\n"
            "movzx %%bl, %%rsi\n"
#ifdef ENABLE_SMP_SUPPORT
            "swapgs\n"
            "movq %%gs:%c[stack_offset], %%rsp\n"
#else
            "leaq kernel_stack_alloc + %c[stack_size], %%rsp\n"
#endif
            "leaq %[failed], %%rax\n"
            "jmp *%%rax\n"
            :
            : [reg]"r"(&cur_thread->tcbArch.tcbVCPU->gp_registers[VCPU_EAX]),
            [failed]"m"(vmlaunch_failed),
            [stack_size]"i"(BIT(CONFIG_KERNEL_STACK_BITS))
#ifdef ENABLE_SMP_SUPPORT
            , [stack_offset]"i"(OFFSETOF(nodeInfo_t, stackTop))
#endif
            // Clobber memory so the compiler is forced to complete all stores
            // before running this assembler
            : "memory"
        );
    }
    UNREACHABLE();
}
#endif

void VISIBLE NORETURN restore_user_context(void)
{
    NODE_UNLOCK_IF_HELD;
    c_exit_hook();

    /* we've now 'exited' the kernel. If we have a pending interrupt
     * we should 'enter' it again */
    if (ARCH_NODE_STATE(x86KSPendingInterrupt) != int_invalid) {
        interrupt_t irq = servicePendingIRQ();
        /* reset our stack and jmp to the IRQ entry point */
        asm volatile(
            "movq %[stack_top], %%rsp\n"
            "movq %[syscall], %%rsi\n"
            "movq %[irq], %%rdi\n"
            "call c_handle_interrupt"
            :
            : [stack_top] "r"(&(kernel_stack_alloc[CURRENT_CPU_INDEX()][BIT(CONFIG_KERNEL_STACK_BITS)])),
            [syscall] "i"(0), /* syscall is unused for irq path */
            [irq] "r"((seL4_Word)irq)
            : "memory");
        UNREACHABLE();
    }

    tcb_t *cur_thread = NODE_STATE(ksCurThread);
    word_t *irqstack = x64KSIRQStack[CURRENT_CPU_INDEX()];
#ifdef CONFIG_VTX
    if (thread_state_ptr_get_tsType(&cur_thread->tcbState) == ThreadState_RunningVM) {
        restore_vmx();
    }
#endif
    lazyFPURestore(cur_thread);

#ifdef CONFIG_HARDWARE_DEBUG_API
    restore_user_debug_context(cur_thread);
#endif

#ifdef ENABLE_SMP_SUPPORT
    cpu_id_t cpu = getCurrentCPUIndex();
#ifdef CONFIG_KERNEL_SKIM_WINDOW
    word_t user_cr3 = MODE_NODE_STATE(x64KSCurrentUserCR3);
#endif /* CONFIG_KERNEL_SKIM_WINDOW */
    swapgs();
#endif /* ENABLE_SMP_SUPPORT */

    /* Now that we have swapped back to the user gs we can safely
     * update the GS base. We must *not* use any kernel functions
     * that rely on having a kernel GS though. Most notably uses
     * of NODE_STATE etc cannot be used beyond this point */
    word_t base = getRegister(cur_thread, TLS_BASE);
    x86_write_fs_base(base, SMP_TERNARY(cpu, 0));

    base = cur_thread->tcbIPCBuffer;
    x86_write_gs_base(base, SMP_TERNARY(cpu, 0));

    if (config_set(CONFIG_KERNEL_X86_IBRS_BASIC)) {
        x86_disable_ibrs();
    }

    // Check if we are returning from a syscall/sysenter or from an interrupt
    // There is a special case where if we would be returning from a sysenter,
    // but are current singlestepping, do a full return like an interrupt
    if (likely(cur_thread->tcbArch.tcbContext.registers[Error] == -1) &&
            (!config_set(CONFIG_SYSENTER) || !config_set(CONFIG_HARDWARE_DEBUG_API) || ((cur_thread->tcbArch.tcbContext.registers[FLAGS] & FLAGS_TF) == 0))) {
        if (config_set(CONFIG_KERNEL_SKIM_WINDOW)) {
            /* if we are using the SKIM window then we are trying to hide kernel state from
             * the user in the case of Meltdown where the kernel region is effectively readable
             * by the user. To prevent a storage channel across threads through the irq stack,
             * which is idirectly controlled by the user, we need to clear the stack. We perform
             * this here since when we return *from* an interrupt we must use this stack and
             * cannot clear it. This means if we restore from interrupt, then enter from a syscall
             * and switch to a different thread we must either on syscall entry, or before leaving
             * the kernel, clear the irq stack. */
            irqstack[0] = 0;
            irqstack[1] = 0;
            irqstack[2] = 0;
            irqstack[3] = 0;
            irqstack[4] = 0;
            irqstack[5] = 0;
        }
        if (config_set(CONFIG_SYSENTER)) {
            cur_thread->tcbArch.tcbContext.registers[FLAGS] &= ~FLAGS_IF;
#if defined(ENABLE_SMP_SUPPORT) && defined(CONFIG_KERNEL_SKIM_WINDOW)
            register word_t user_cr3_r11 asm("r11") = user_cr3;
#endif
            asm volatile(
                // Set our stack pointer to the top of the tcb so we can efficiently pop
                "movq %0, %%rsp\n"
                "popq %%rdi\n"
                "popq %%rsi\n"
                "popq %%rax\n"
                "popq %%rbx\n"
                "popq %%rbp\n"
                "popq %%r12\n"
                "popq %%r13\n"
                "popq %%r14\n"
                // skip RDX
                "addq $8, %%rsp\n"
                "popq %%r10\n"
                "popq %%r8\n"
                "popq %%r9\n"
                "popq %%r15\n"
                //restore RFLAGS
                "popfq\n"
                // reset interrupt bit
                "orq %[IF], -8(%%rsp)\n"
                // Restore NextIP
                "popq %%rdx\n"
                // Skip ERROR
                "addq $8, %%rsp\n"
                // Restore RSP
                "popq %%rcx\n"
                // Skip TLS_BASE, FaultIP
                "addq $16, %%rsp\n"
#if defined(ENABLE_SMP_SUPPORT) && defined(CONFIG_KERNEL_SKIM_WINDOW)
                "popq %%rsp\n"
                "movq %%r11, %%cr3\n"
                "movq %%rsp, %%r11\n"
#else
                "popq %%r11\n"
#ifdef CONFIG_KERNEL_SKIM_WINDOW
                "movq (x64KSCurrentUserCR3), %%rsp\n"
                "movq %%rsp, %%cr3\n"
#endif /* CONFIG_KERNEL_SKIM_WINDOW */
#endif /* defined(ENABLE_SMP_SUPPORT) && defined(CONFIG_KERNEL_SKIM_WINDOW) */
                // More register but we can ignore and are done restoring
                // enable interrupt disabled by sysenter
                "sti\n"
                /* return to user
                 * sysexit with rex.w user code = cs + 32, user data = cs + 40.
                 * without rex.w user code = cs + 16, user data = cs + 24
                 * */
                "rex.w sysexit\n"
                :
                : "r"(&cur_thread->tcbArch.tcbContext.registers[RDI]),
#if defined(ENABLE_SMP_SUPPORT) && defined(CONFIG_KERNEL_SKIM_WINDOW)
                "r"(user_cr3_r11),
#endif
                [IF] "i" (FLAGS_IF)
                // Clobber memory so the compiler is forced to complete all stores
                // before running this assembler
                : "memory"
            );
        } else {
            asm volatile(
                // Set our stack pointer to the top of the tcb so we can efficiently pop
                "movq %0, %%rsp\n"
                "popq %%rdi\n"
                "popq %%rsi\n"
                "popq %%rax\n"
                "popq %%rbx\n"
                "popq %%rbp\n"
                "popq %%r12\n"
                "popq %%r13\n"
                "popq %%r14\n"
                "popq %%rdx\n"
                "popq %%r10\n"
                "popq %%r8\n"
                "popq %%r9\n"
                "popq %%r15\n"
                //restore RFLAGS
                "popq %%r11\n"
                // Restore NextIP
#if defined(ENABLE_SMP_SUPPORT) && defined(CONFIG_KERNEL_SKIM_WINDOW)
                "popq %%rsp\n"
                "movq %%rcx, %%cr3\n"
                "movq %%rsp, %%rcx\n"
#else
                "popq %%rcx\n"
#ifdef CONFIG_KERNEL_SKIM_WINDOW
                "movq (x64KSCurrentUserCR3), %%rsp\n"
                "movq %%rsp, %%cr3\n"
#endif /* CONFIG_KERNEL_SKIM_WINDOW */
#endif /* defined(ENABLE_SMP_SUPPORT) && defined(CONFIG_KERNEL_SKIM_WINDOW) */
                // clear RSP to not leak information to the user
                "xor %%rsp, %%rsp\n"
                // More register but we can ignore and are done restoring
                // enable interrupt disabled by sysenter
                "rex.w sysret\n"
                :
                : "r"(&cur_thread->tcbArch.tcbContext.registers[RDI])
#if defined(ENABLE_SMP_SUPPORT) && defined(CONFIG_KERNEL_SKIM_WINDOW)
                , "c" (user_cr3)
#endif
                // Clobber memory so the compiler is forced to complete all stores
                // before running this assembler
                : "memory"
            );
        }
    } else {
        /* construct our return from interrupt frame */
#ifdef CONFIG_KERNEL_SKIM_WINDOW
        /* Have to zero this to prevent storage channel */
        irqstack[0] = 0;
#endif
        irqstack[1] = getRegister(cur_thread, NextIP);
        irqstack[2] = getRegister(cur_thread, CS);
        irqstack[3] = getRegister(cur_thread, FLAGS);
        irqstack[4] = getRegister(cur_thread, RSP);
        irqstack[5] = getRegister(cur_thread, SS);
        asm volatile(
            // Set our stack pointer to the top of the tcb so we can efficiently pop
            "movq %0, %%rsp\n"
            "popq %%rdi\n"
            "popq %%rsi\n"
            "popq %%rax\n"
            "popq %%rbx\n"
            "popq %%rbp\n"
            "popq %%r12\n"
            "popq %%r13\n"
            "popq %%r14\n"
            "popq %%rdx\n"
            "popq %%r10\n"
            "popq %%r8\n"
            "popq %%r9\n"
            "popq %%r15\n"
            /* skip RFLAGS, Error NextIP RSP, TLS_BASE, FaultIP */
            "addq $48, %%rsp\n"
            "popq %%r11\n"

#if defined(ENABLE_SMP_SUPPORT) && defined(CONFIG_KERNEL_SKIM_WINDOW)
            /* pop into rsp as we're done with the stack for now and we need to
             * preserve our rcx value as it has our next cr3 value */
            "popq %%rsp\n"
#else
            "popq %%rcx\n"
#endif /* defined(ENABLE_SMP_SUPPORT) && defined(CONFIG_KERNEL_SKIM_WINDOW) */

#ifdef ENABLE_SMP_SUPPORT
            // Swapping gs twice here is worth it as it allows us to efficiently
            // set the user gs base previously
            "swapgs\n"
#ifdef CONFIG_KERNEL_SKIM_WINDOW
            /* now we stash rcx in the scratch space that we can access once we've
             * loaded the user cr3 */
            "movq %%rsp, %%gs:%c[scratch_offset]\n"
#endif /* CONFIG_KERNEL_SKIM_WINDOW */
            "movq %%gs:8, %%rsp\n"
#ifdef CONFIG_KERNEL_SKIM_WINDOW
            /* change to the user address space and then load the value of rcx that
             * we stashed */
            "movq %%rcx, %%cr3\n"
            "movq %%gs:%c[scratch_offset], %%rcx\n"
#endif /* CONFIG_KERNEL_SKIM_WINDOW */
            "addq $8, %%rsp\n"
            // Switch to the user GS value
            "swapgs\n"
#else /* !ENABLE_SMP_SUPPORT */
#ifdef CONFIG_KERNEL_SKIM_WINDOW
            "movq (x64KSCurrentUserCR3), %%rsp\n"
            "movq %%rsp, %%cr3\n"
#endif /* CONFIG_KERNEL_SKIM_WINDOW */
            "leaq x64KSIRQStack + 8, %%rsp\n"
#endif /* ENABLE_SMP_SUPPORT */
            "iretq\n"
            :
            : "r"(&cur_thread->tcbArch.tcbContext.registers[RDI])
#if defined(ENABLE_SMP_SUPPORT) && defined(CONFIG_KERNEL_SKIM_WINDOW)
            , "c" (user_cr3)
            , [scratch_offset] "i" (nodeSkimScratchOffset)
#endif
            // Clobber memory so the compiler is forced to complete all stores
            // before running this assembler
            : "memory"
        );
    }
    UNREACHABLE();
}

void VISIBLE NORETURN c_x64_handle_interrupt(int irq, int syscall);
void VISIBLE NORETURN c_x64_handle_interrupt(int irq, int syscall)
{
    if (config_set(CONFIG_KERNEL_X86_IBRS_BASIC)) {
        x86_enable_ibrs();
    }
    word_t *irq_stack = x64KSIRQStack[CURRENT_CPU_INDEX()];
    setRegister(NODE_STATE(ksCurThread), Error, irq_stack[0]);
    /* In the case of an interrupt the NextIP and the FaultIP should be the same value,
     * i.e. the address of the instruction the CPU was about to execute before the
     * interrupt. This is the 5th value pushed on by the hardware, so indexing from
     * the bottom is x64KSIRQStack[1] */
    setRegister(NODE_STATE(ksCurThread), NextIP, irq_stack[1]);
    setRegister(NODE_STATE(ksCurThread), FaultIP, irq_stack[1]);
    setRegister(NODE_STATE(ksCurThread), FLAGS, irq_stack[3]);
    setRegister(NODE_STATE(ksCurThread), RSP, irq_stack[4]);
    c_handle_interrupt(irq, syscall);
    UNREACHABLE();
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/64/kernel/elf.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <arch/kernel/elf.h>
#include <linker.h>

BOOT_CODE bool_t
elf_checkFile(Elf64_Header_t *elf)
{
    return (
               elf->e_ident[0] == '\177' &&
               elf->e_ident[1] == 'E'    &&
               elf->e_ident[2] == 'L'    &&
               elf->e_ident[3] == 'F'    &&
               elf->e_ident[4] == 2
           );
}


BOOT_CODE v_region_t
elf_getMemoryBounds(Elf64_Header_t *elf)
{
    v_region_t  elf_reg;
    vptr_t      sect_start;
    vptr_t      sect_end;
    uint32_t    i;
    Elf64_Phdr_t *phdr = (Elf64_Phdr_t *)((paddr_t)elf + elf->e_phoff);

    elf_reg.start = 0x7fffffffffffffffUL;
    elf_reg.end = 0;

    for (i = 0; i < elf->e_phnum; i++) {
        if (phdr[i].p_memsz > 0) {
            sect_start = phdr[i].p_vaddr;
            sect_end = sect_start + phdr[i].p_memsz;
            if (sect_start < elf_reg.start) {
                elf_reg.start = sect_start;
            }
            if (sect_end > elf_reg.end) {
                elf_reg.end = sect_end;
            }
        }
    }

    return elf_reg;
}

BOOT_CODE void
elf_load(Elf64_Header_t *elf, seL4_Word offset)
{
    paddr_t     src;
    paddr_t     dst;
    uint64_t    len;
    uint32_t    i;
    Elf64_Phdr_t *phdr = (Elf64_Phdr_t *)((paddr_t)elf + elf->e_phoff);

    for (i = 0; i < elf->e_phnum; i++) {
        src = (paddr_t)elf + phdr[i].p_offset;
        dst = phdr[i].p_vaddr + offset;
        len = phdr[i].p_filesz;
        memcpy((void *)dst, (char *)src, len);
        dst += len;
        memset((void *)dst, 0, phdr[i].p_memsz - len);
    }
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/64/kernel/thread.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <object.h>
#include <machine.h>
#include <arch/model/statedata.h>
#include <arch/kernel/vspace.h>
#include <arch/kernel/thread.h>
#include <linker.h>

void
Arch_switchToThread(tcb_t* tcb)
{
    /* set PD */
    setVMRoot(tcb);
#ifdef ENABLE_SMP_SUPPORT
    asm volatile("movq %[value], %%gs:%c[offset]"
                 :
                 : [value] "r" (&tcb->tcbArch.tcbContext.registers[Error + 1]),
                 [offset] "i" (OFFSETOF(nodeInfo_t, currentThreadUserContext)));
#endif
    if (config_set(CONFIG_KERNEL_X86_IBPB_ON_CONTEXT_SWITCH)) {
        x86_ibpb();
    }

    if (config_set(CONFIG_KERNEL_X86_RSB_ON_CONTEXT_SWITCH)) {
        x86_flush_rsb();
    }
}

BOOT_CODE void
Arch_configureIdleThread(tcb_t* tcb)
{
    setRegister(tcb, FLAGS, FLAGS_USER_DEFAULT);
    setRegister(tcb, NextIP, (uint64_t)idleThreadStart);
    setRegister(tcb, CS, SEL_CS_0);
    setRegister(tcb, SS, SEL_DS_0);
    /* We set the RSP to 0, even though the idle thread will never touch it, as it
     * allows us to distinguish an interrupt from the idle thread from an interrupt
     * from kernel execution, just by examining the saved RSP value (since the kernel
     * thread will have a valid RSP, and never 0). See traps.S for the other side of this
     */
    setRegister(tcb, RSP, 0);
}

void
Arch_switchToIdleThread(void)
{
    tcb_t *tcb = NODE_STATE(ksIdleThread);
    /* Force the idle thread to run on kernel page table */
    setVMRoot(tcb);
#ifdef ENABLE_SMP_SUPPORT
    asm volatile("movq %[value], %%gs:%c[offset]"
                 :
                 : [value] "r"(&tcb->tcbArch.tcbContext.registers[Error + 1]),
                 [offset] "i" (OFFSETOF(nodeInfo_t, currentThreadUserContext)));
#endif
}

void
Arch_activateIdleThread(tcb_t* tcb)
{
    /* Don't need to do anything */
}

void
Mode_postModifyRegisters(tcb_t *tptr)
{
    /* Setting Error to 0 will force a return by the interrupt path, which
     * does a full restore. Unless we're the current thread, in which case
     * we still have to go back out via a sysret */
    if (tptr != NODE_STATE(ksCurThread)) {
        setRegister(tptr, Error, 0);
    }
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/64/kernel/vspace.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <api/syscall.h>
#include <machine/io.h>
#include <kernel/boot.h>
#include <model/statedata.h>
#include <arch/kernel/vspace.h>
#include <arch/kernel/boot.h>
#include <arch/api/invocation.h>
#include <mode/kernel/tlb.h>
#include <arch/kernel/tlb_bitmap.h>

/* When using the SKIM window to isolate the kernel from the user we also need to
 * not use global mappings as having global mappings and entries in the TLB is
 * equivalent, for the purpose of exploitation, to having the mappings in the
 * kernel window */
#define KERNEL_IS_GLOBAL() (config_set(CONFIG_KERNEL_SKIM_WINDOW) ? 0 : 1)

/* For the boot code we create two windows into the physical address space
 * One is at the same location as the kernel window, and is placed up high
 * The other is a 1-to-1 mapping of the first 512gb of memory. The purpose
 * of this is to have a 1-to-1 mapping for the low parts of memory, so that
 * when we switch paging on, and are still running at physical addresses,
 * we don't explode. Then we also want the high mappings so we can start
 * running at proper kernel virtual addresses */
pml4e_t boot_pml4[BIT(PML4_INDEX_BITS)] ALIGN(BIT(seL4_PageBits)) VISIBLE PHYS_BSS;
pdpte_t boot_pdpt[BIT(PDPT_INDEX_BITS)] ALIGN(BIT(seL4_PageBits)) VISIBLE PHYS_BSS;

/* 'gdt_idt_ptr' is declared globally because of a C-subset restriction.
 * It is only used in init_drts(), which therefore is non-reentrant.
 */
gdt_idt_ptr_t gdt_idt_ptr;

BOOT_CODE bool_t
map_kernel_window(
    uint32_t num_ioapic,
    paddr_t*   ioapic_paddrs,
    uint32_t   num_drhu,
    paddr_t*   drhu_list
)
{

    uint64_t paddr;
    uint64_t vaddr;

#ifdef CONFIG_HUGE_PAGE
    /* using 1 GiB page size */

    /* verify that the kernel window as at the last entry of the PML4 */
    assert(GET_PML4_INDEX(PPTR_BASE) == BIT(PML4_INDEX_BITS) - 1);
    /* verify that the kernel_base is located in the last entry of the PML4,
     * the second last entry of the PDPT, is 1gb aligned and 1gb in size */
    assert(GET_PML4_INDEX(KERNEL_BASE) == BIT(PML4_INDEX_BITS) - 1);
    assert(GET_PDPT_INDEX(KERNEL_BASE) == BIT(PML4_INDEX_BITS) - 2);
    assert(GET_PDPT_INDEX(PPTR_KDEV) == BIT(PML4_INDEX_BITS) - 1);
    assert(IS_ALIGNED(KERNEL_BASE, seL4_HugePageBits));
    assert(IS_ALIGNED(PPTR_KDEV, seL4_HugePageBits));
    /* place the PDPT into the PML4 */
    x64KSKernelPML4[GET_PML4_INDEX(PPTR_BASE)] = pml4e_new(
                                                     0, /* xd */
                                                     kpptr_to_paddr(x64KSKernelPDPT),
                                                     0, /* accessed */
                                                     0, /* cache_disabled */
                                                     0, /* write_through */
                                                     0, /* super_user */
                                                     1, /* read_write */
                                                     1  /* present */
                                                 );
    /* put the 1GB kernel_base mapping into the PDPT */
    x64KSKernelPDPT[GET_PDPT_INDEX(KERNEL_BASE)] = pdpte_pdpte_1g_new(
                                                       0, /* xd */
                                                       PADDR_BASE,
                                                       0, /* PAT */
                                                       KERNEL_IS_GLOBAL(), /* global */
                                                       0, /* dirty */
                                                       0, /* accessed */
                                                       0, /* cache_disabled */
                                                       0, /* write_through */
                                                       0, /* super_user */
                                                       1, /* read_write */
                                                       1  /* present */
                                                   );
    /* also map the physical memory into the big kernel window */
    paddr = 0;
    vaddr = PPTR_BASE;
    for (paddr = 0; paddr < PADDR_TOP;
            paddr += BIT(seL4_HugePageBits)) {

        int pdpte_index = GET_PDPT_INDEX(vaddr);
        x64KSKernelPDPT[pdpte_index] = pdpte_pdpte_1g_new(
                                           0,          /* xd               */
                                           paddr,      /* physical address */
                                           0,          /* PAT              */
                                           KERNEL_IS_GLOBAL(), /* global   */
                                           0,          /* dirty            */
                                           0,          /* accessed         */
                                           0,          /* cache_disabled   */
                                           0,          /* write_through    */
                                           0,          /* super_user       */
                                           1,          /* read_write       */
                                           1           /* present          */
                                       );

        vaddr += BIT(seL4_HugePageBits);
    }

    /* put the PD into the PDPT */
    x64KSKernelPDPT[GET_PDPT_INDEX(PPTR_KDEV)] = pdpte_pdpte_pd_new(
                                                     0, /* xd */
                                                     kpptr_to_paddr(x64KSKernelPD),
                                                     0, /* accessed */
                                                     0, /* cache_disabled */
                                                     0, /* write_through */
                                                     0, /* super_user */
                                                     1, /* read_write */
                                                     1  /* present */
                                                 );
    /* put the PT into the PD */
    x64KSKernelPD[0] = pde_pde_pt_new(
                           0, /* xd */
                           kpptr_to_paddr(x64KSKernelPT),
                           0, /* accessed */
                           0, /* cache_disabled */
                           0, /* write_through */
                           0, /* super_user */
                           1, /* read_write */
                           1  /* present */
                       );
#else

    int pd_index = 0;
    /* use 2 MiB page size */
    /* verify that the kernel window as at the last entry of the PML4 */
    assert(GET_PML4_INDEX(PPTR_BASE) == BIT(PML4_INDEX_BITS) - 1);
    /* verify that the kernel_base is located in the last entry of the PML4,
     * the second last entry of the PDPT, is 1gb aligned and 1gb in size */
    assert(GET_PML4_INDEX(KERNEL_BASE) == BIT(PML4_INDEX_BITS) - 1);
    assert(GET_PDPT_INDEX(KERNEL_BASE) == BIT(PML4_INDEX_BITS) - 2);
    assert(GET_PDPT_INDEX(PPTR_KDEV) == BIT(PML4_INDEX_BITS) - 1);
    assert(IS_ALIGNED(KERNEL_BASE, seL4_HugePageBits));
    assert(IS_ALIGNED(PPTR_KDEV, seL4_HugePageBits));

    /* place the PDPT into the PML4 */
    x64KSKernelPML4[GET_PML4_INDEX(PPTR_BASE)] = pml4e_new(
                                                     0, /* xd */
                                                     kpptr_to_paddr(x64KSKernelPDPT),
                                                     0, /* accessed */
                                                     0, /* cache_disabled */
                                                     0, /* write_through */
                                                     0, /* super_user */
                                                     1, /* read_write */
                                                     1  /* present */
                                                 );

    for (pd_index = 0; pd_index < PADDR_TOP >> seL4_HugePageBits; pd_index++) {
        /* put the 1GB kernel_base mapping into the PDPT */
        x64KSKernelPDPT[GET_PDPT_INDEX(PPTR_BASE) + pd_index] = pdpte_pdpte_pd_new(
                                                                    0, /* xd */
                                                                    kpptr_to_paddr(&x64KSKernelPDs[pd_index][0]),
                                                                    0, /* accessed */
                                                                    0, /* cache disabled */
                                                                    0, /* write through */
                                                                    0, /* super user */
                                                                    1, /* read write */
                                                                    1 /* present */
                                                                );
    }

    x64KSKernelPDPT[GET_PDPT_INDEX(KERNEL_BASE)] = pdpte_pdpte_pd_new(
                                                       0, /* xd */
                                                       kpptr_to_paddr(&x64KSKernelPDs[0][0]),
                                                       0, /* accessed */
                                                       0, /* cache disable */
                                                       1, /* write through */
                                                       0, /* super user */
                                                       1, /* read write */
                                                       1  /* present */
                                                   );

    paddr = 0;
    vaddr = PPTR_BASE;

    for (paddr = 0; paddr < PADDR_TOP;
            paddr += 0x200000) {

        int pd_index = GET_PDPT_INDEX(vaddr) - GET_PDPT_INDEX(PPTR_BASE);
        int pde_index = GET_PD_INDEX(vaddr);

        x64KSKernelPDs[pd_index][pde_index] = pde_pde_large_new(
                                                  0, /* xd */
                                                  paddr,
                                                  0, /* pat */
                                                  KERNEL_IS_GLOBAL(), /* global */
                                                  0, /* dirty */
                                                  0, /* accessed */
                                                  0, /* cache disabled */
                                                  0, /* write through */
                                                  0, /* super user */
                                                  1, /* read write */
                                                  1  /* present */
                                              );
        vaddr += 0x200000;
    }

    /* put the PD into the PDPT */
    x64KSKernelPDPT[GET_PDPT_INDEX(PPTR_KDEV)] = pdpte_pdpte_pd_new(
                                                     0, /* xd */
                                                     kpptr_to_paddr(&x64KSKernelPDs[BIT(PDPT_INDEX_BITS) - 1][0]),
                                                     0, /* accessed */
                                                     0, /* cache_disabled */
                                                     0, /* write_through */
                                                     0, /* super_user */
                                                     1, /* read_write */
                                                     1  /* present */
                                                 );

    /* put the PT into the PD */
    x64KSKernelPDs[BIT(PDPT_INDEX_BITS) - 1][0] = pde_pde_pt_new(
                                                      0, /* xd */
                                                      kpptr_to_paddr(x64KSKernelPT),
                                                      0, /* accessed */
                                                      0, /* cache_disabled */
                                                      0, /* write_through */
                                                      0, /* super_user */
                                                      1, /* read_write */
                                                      1  /* present */
                                                  );
#endif

#if CONFIG_MAX_NUM_TRACE_POINTS > 0
    /* use the last PD entry as the benchmark log storage.
     * the actual backing physical memory will be filled
     * later by using alloc_region */
    ksLog = (ks_log_entry_t *)(PPTR_KDEV + 0x200000 * (BIT(PD_INDEX_BITS) - 1));
#endif

    /* now map in the kernel devices */
    if (!map_kernel_window_devices(x64KSKernelPT, num_ioapic, ioapic_paddrs, num_drhu, drhu_list)) {
        return false;
    }

#ifdef ENABLE_SMP_SUPPORT
    /* initialize the TLB bitmap */
    tlb_bitmap_init(x64KSKernelPML4);
#endif /* ENABLE_SMP_SUPPORT */

    /* In boot code, so fine to just trash everything here */
    invalidateLocalTranslationAll();
    printf("Mapping kernel window is done\n");
    return true;
}

#ifdef CONFIG_KERNEL_SKIM_WINDOW
BOOT_CODE bool_t
map_skim_window(vptr_t skim_start, vptr_t skim_end)
{
    /* place the PDPT into the PML4 */
    x64KSSKIMPML4[GET_PML4_INDEX(PPTR_BASE)] = pml4e_new(
                                                   0, /* xd */
                                                   kpptr_to_paddr(x64KSSKIMPDPT),
                                                   0, /* accessed */
                                                   0, /* cache_disabled */
                                                   0, /* write_through */
                                                   0, /* super_user */
                                                   1, /* read_write */
                                                   1  /* present */
                                               );
    /* place the PD into the kernel_base slot of the PDPT */
    x64KSSKIMPDPT[GET_PDPT_INDEX(KERNEL_BASE)] = pdpte_pdpte_pd_new(
                                                     0, /* xd */
                                                     kpptr_to_paddr(x64KSSKIMPD),
                                                     0, /* accessed */
                                                     0, /* cache_disabled */
                                                     0, /* write_through */
                                                     0, /* super_user */
                                                     1, /* read_write */
                                                     1  /* present */
                                                 );
    /* map the skim portion into the PD. we expect it to be 2M aligned */
    assert((skim_start % BIT(seL4_LargePageBits)) == 0);
    assert((skim_end % BIT(seL4_LargePageBits)) == 0);
    uint64_t paddr = kpptr_to_paddr((void*)skim_start);
    for (int i = GET_PD_INDEX(skim_start); i < GET_PD_INDEX(skim_end); i++) {
        x64KSSKIMPD[i] = pde_pde_large_new(
                             0, /* xd */
                             paddr,
                             0, /* pat */
                             KERNEL_IS_GLOBAL(), /* global */
                             0, /* dirty */
                             0, /* accessed */
                             0, /* cache_disabled */
                             0, /* write_through */
                             0, /* super_user */
                             1, /* read_write */
                             1  /* present */
                         );
        paddr += BIT(seL4_LargePageBits);
    }
    return true;
}
#endif

BOOT_CODE void
init_tss(tss_t *tss)
{
    word_t base = (word_t)&x64KSIRQStack[CURRENT_CPU_INDEX()][IRQ_STACK_SIZE];
    *tss = tss_new(
               sizeof(*tss),   /* io map base */
               0, 0,       /* ist 7 */
               0, 0,
               0, 0,
               0, 0,
               0, 0,
               0, 0,
               /* ist 1 is the stack frame we use for interrupts */
               base >> 32, base & 0xffffffff,  /* ist 1 */
               0, 0,       /* rsp 2 */
               0, 0,       /* rsp 1 */
               0, 0        /* rsp 0 */
           );
    /* set the IO map to all 1 to block user IN/OUT instructions */
    memset(&x86KSGlobalState[CURRENT_CPU_INDEX()].x86KStss.io_map[0], 0xff, sizeof(x86KSGlobalState[CURRENT_CPU_INDEX()].x86KStss.io_map));
}

BOOT_CODE void
init_syscall_msrs(void)
{
    x86_wrmsr(IA32_LSTAR_MSR, (uint64_t)&handle_fastsyscall);
    // mask bit 9 in the kernel (which is the interrupt enable bit)
    // also mask bit 8, which is the Trap Flag, to prevent the kernel
    // from single stepping
    x86_wrmsr(IA32_FMASK_MSR, FLAGS_TF | FLAGS_IF);
    x86_wrmsr(IA32_STAR_MSR, ((uint64_t)SEL_CS_0 << 32) | ((uint64_t)SEL_CS_3 << 48));
}

BOOT_CODE void
init_gdt(gdt_entry_t *gdt, tss_t *tss)
{

    uint64_t tss_base = (uint64_t)tss;
    gdt_tss_t gdt_tss;

    gdt[GDT_NULL] = gdt_entry_gdt_null_new();

    gdt[GDT_CS_0] = gdt_entry_gdt_code_new(
                        0,                  /* base high */
                        1,                  /* granularity */
                        0,                  /* operation size, must be 0 when 64-bit is set */
                        1,                  /* long mode */
                        0,                  /* avl */
                        0xf,                /* limit high */
                        1,                  /* present */
                        0,                  /* dpl */
                        1,                  /* always 1 for segment */
                        0,                  /* base middle */
                        0,                  /* base low */
                        0xffff              /* limit low */
                    );

    gdt[GDT_DS_0] = gdt_entry_gdt_data_new(
                        0,                  /* base high */
                        1,                  /* granularity */
                        1,                  /* operation size */
                        0,                  /* avl */
                        0xf,                /* seg limit high */
                        1,                  /* present */
                        0,                  /* dpl */
                        1,                  /* always 1 */
                        0,                  /* base mid */
                        0,                  /* base low */
                        0xffff              /* seg limit low */
                    );

    gdt[GDT_CS_3] = gdt_entry_gdt_code_new(
                        0,                  /* base high */
                        1,                  /* granularity */
                        0,                  /* operation size, must be 0 when 64-bit is set */
                        1,                  /* long mode */
                        0,                  /* avl */
                        0xf,                /* limit high */
                        1,                  /* present */
                        3,                  /* dpl */
                        1,                  /* always 1 */
                        0,                  /* base middle */
                        0,                  /* base low */
                        0xffff              /* limit low */
                    );

    gdt[GDT_DS_3] = gdt_entry_gdt_data_new(
                        0,
                        1,
                        1,
                        0,
                        0xf,
                        1,
                        3,
                        1,
                        0,
                        0,
                        0xffff
                    );

    gdt[GDT_TLS] = gdt_entry_gdt_data_new(
                       0,
                       1,
                       1,
                       0,
                       0xf,
                       1,
                       3,
                       1,
                       0,
                       0,
                       0xffff
                   );

    gdt[GDT_IPCBUF] = gdt_entry_gdt_data_new(
                          0,
                          1,
                          1,
                          0,
                          0xf,
                          1,
                          3,
                          1,
                          0,
                          0,
                          0xffff
                      );

    gdt_tss = gdt_tss_new(
                  tss_base >> 32,                     /* base 63 - 32 */
                  (tss_base & 0xff000000UL) >> 24,    /* base 31 - 24 */
                  1,                                  /* granularity */
                  0,                                  /* avl */
                  0,                                  /* limit high */
                  1,                                  /* present */
                  0,                                  /* dpl */
                  9,                                  /* desc type */
                  (tss_base & 0xff0000UL) >> 16,      /* base 23-16 */
                  (tss_base & 0xffffUL),              /* base 15 - 0 */
                  sizeof(tss_io_t) - 1
              );

    gdt[GDT_TSS].words[0] = gdt_tss.words[0];
    gdt[GDT_TSS + 1].words[0] = gdt_tss.words[1];
}

BOOT_CODE void
init_idt_entry(idt_entry_t *idt, interrupt_t interrupt, void(*handler)(void))
{
    uint64_t handler_addr = (uint64_t)handler;
    uint64_t dpl = 3;

    if (interrupt < int_trap_min && interrupt != int_software_break_request) {
        dpl = 0;
    }

    idt[interrupt] = idt_entry_interrupt_gate_new(
                         handler_addr >> 32,                 /* offset 63 - 32 */
                         ((handler_addr >> 16) & 0xffff),
                         1,                                  /* present */
                         dpl,                                /* dpl */
                         1,                                  /* ist */
                         SEL_CS_0,                           /* segment selector */
                         (handler_addr & 0xffff)               /* offset 15 - 0 */
                     );
}

void setVMRoot(tcb_t *tcb)
{
    cap_t threadRoot;
    asid_t asid;
    pml4e_t *pml4;
    findVSpaceForASID_ret_t find_ret;
    cr3_t cr3;

    threadRoot = TCB_PTR_CTE_PTR(tcb, tcbVTable)->cap;

    if (cap_get_capType(threadRoot) != cap_pml4_cap ||
            !cap_pml4_cap_get_capPML4IsMapped(threadRoot)) {
        setCurrentUserVSpaceRoot(kpptr_to_paddr(X86_GLOBAL_VSPACE_ROOT), 0);
        return;
    }

    pml4 = PML4E_PTR(cap_pml4_cap_get_capPML4BasePtr(threadRoot));
    asid = cap_pml4_cap_get_capPML4MappedASID(threadRoot);
    find_ret = findVSpaceForASID(asid);
    if (unlikely(find_ret.status != EXCEPTION_NONE || find_ret.vspace_root != pml4)) {
        setCurrentUserVSpaceRoot(kpptr_to_paddr(X86_GLOBAL_VSPACE_ROOT), 0);
        return;
    }
    cr3 = makeCR3(pptr_to_paddr(pml4), asid);
    if (getCurrentUserCR3().words[0] != cr3.words[0]) {
        SMP_COND_STATEMENT(tlb_bitmap_set(pml4, getCurrentCPUIndex());)
        setCurrentUserCR3(cr3);
    }
}


BOOT_CODE void
init_dtrs(void)
{
    gdt_idt_ptr.limit = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1;
    gdt_idt_ptr.base = (uint64_t)x86KSGlobalState[CURRENT_CPU_INDEX()].x86KSgdt;

    /* When we install the gdt it will clobber any value of gs that
     * we have. Since we might be using it for TLS we can stash
     * and unstash any gs value using swapgs
     */
    swapgs();
    x64_install_gdt(&gdt_idt_ptr);
    swapgs();

    gdt_idt_ptr.limit = (sizeof(idt_entry_t) * (int_max + 1 )) - 1;
    gdt_idt_ptr.base = (uint64_t)x86KSGlobalState[CURRENT_CPU_INDEX()].x86KSidt;
    x64_install_idt(&gdt_idt_ptr);

    x64_install_ldt(SEL_NULL);

    x64_install_tss(SEL_TSS);
}

BOOT_CODE void
map_it_frame_cap(cap_t pd_cap, cap_t frame_cap)
{
    pml4e_t *pml4 = PML4_PTR(pptr_of_cap(pd_cap));
    pdpte_t *pdpt;
    pde_t *pd;
    pte_t *pt;
    vptr_t vptr = cap_frame_cap_get_capFMappedAddress(frame_cap);
    void *pptr = (void*)cap_frame_cap_get_capFBasePtr(frame_cap);

    assert(cap_frame_cap_get_capFMapType(frame_cap) == X86_MappingVSpace);
    assert(cap_frame_cap_get_capFMappedASID(frame_cap) != asidInvalid);
    pml4 += GET_PML4_INDEX(vptr);
    assert(pml4e_ptr_get_present(pml4));
    pdpt = paddr_to_pptr(pml4e_ptr_get_pdpt_base_address(pml4));
    pdpt += GET_PDPT_INDEX(vptr);
    assert(pdpte_pdpte_pd_ptr_get_present(pdpt));
    pd = paddr_to_pptr(pdpte_pdpte_pd_ptr_get_pd_base_address(pdpt));
    pd += GET_PD_INDEX(vptr);
    assert(pde_pde_pt_ptr_get_present(pd));
    pt = paddr_to_pptr(pde_pde_pt_ptr_get_pt_base_address(pd));
    *(pt + GET_PT_INDEX(vptr)) = pte_new(
                                     0,                      /* xd                   */
                                     pptr_to_paddr(pptr),    /* page_base_address    */
                                     0,                      /* global               */
                                     0,                      /* pat                  */
                                     0,                      /* dirty                */
                                     0,                      /* accessed             */
                                     0,                      /* cache_disabled       */
                                     0,                      /* write_through        */
                                     1,                      /* super_user           */
                                     1,                      /* read_write           */
                                     1                       /* present              */
                                 );
}

static BOOT_CODE void
map_it_pdpt_cap(cap_t vspace_cap, cap_t pdpt_cap)
{
    pml4e_t *pml4 = PML4_PTR(pptr_of_cap(vspace_cap));
    pdpte_t *pdpt = PDPT_PTR(cap_pdpt_cap_get_capPDPTBasePtr(pdpt_cap));
    vptr_t vptr = cap_pdpt_cap_get_capPDPTMappedAddress(pdpt_cap);

    assert(cap_pdpt_cap_get_capPDPTIsMapped(pdpt_cap));
    *(pml4 + GET_PML4_INDEX(vptr)) = pml4e_new(
                                         0,                      /* xd                   */
                                         pptr_to_paddr(pdpt),    /* pdpt_base_address    */
                                         0,                      /* accessed             */
                                         0,                      /* cache_disabled       */
                                         0,                      /* write_through        */
                                         1,                      /* super_user           */
                                         1,                      /* read_write           */
                                         1                       /* present              */
                                     );
}

BOOT_CODE void
map_it_pd_cap(cap_t vspace_cap, cap_t pd_cap)
{
    pml4e_t *pml4 = PML4_PTR(pptr_of_cap(vspace_cap));
    pdpte_t *pdpt;
    pde_t *pd = PD_PTR(cap_page_directory_cap_get_capPDBasePtr(pd_cap));
    vptr_t vptr = cap_page_directory_cap_get_capPDMappedAddress(pd_cap);

    assert(cap_page_directory_cap_get_capPDIsMapped(pd_cap));
    pml4 += GET_PML4_INDEX(vptr);
    assert(pml4e_ptr_get_present(pml4));
    pdpt = paddr_to_pptr(pml4e_ptr_get_pdpt_base_address(pml4));
    *(pdpt + GET_PDPT_INDEX(vptr)) = pdpte_pdpte_pd_new(
                                         0,                      /* xd                   */
                                         pptr_to_paddr(pd),      /* pd_base_address      */
                                         0,                      /* accessed             */
                                         0,                      /* cache_disabled       */
                                         0,                      /* write_through        */
                                         1,                      /* super_user           */
                                         1,                      /* read_write           */
                                         1                       /* present              */
                                     );
}

BOOT_CODE void
map_it_pt_cap(cap_t vspace_cap, cap_t pt_cap)
{
    pml4e_t *pml4 = PML4_PTR(pptr_of_cap(vspace_cap));
    pdpte_t *pdpt;
    pde_t *pd;
    pte_t *pt = PT_PTR(cap_page_table_cap_get_capPTBasePtr(pt_cap));
    vptr_t vptr = cap_page_table_cap_get_capPTMappedAddress(pt_cap);

    assert(cap_page_table_cap_get_capPTIsMapped(pt_cap));
    pml4 += GET_PML4_INDEX(vptr);
    assert(pml4e_ptr_get_present(pml4));
    pdpt = paddr_to_pptr(pml4e_ptr_get_pdpt_base_address(pml4));
    pdpt += GET_PDPT_INDEX(vptr);
    assert(pdpte_pdpte_pd_ptr_get_present(pdpt));
    pd = paddr_to_pptr(pdpte_pdpte_pd_ptr_get_pd_base_address(pdpt));
    *(pd + GET_PD_INDEX(vptr)) = pde_pde_pt_new(
                                     0,                      /* xd                   */
                                     pptr_to_paddr(pt),      /* pt_base_address      */
                                     0,                      /* accessed             */
                                     0,                      /* cache_disabled       */
                                     0,                      /* write_through        */
                                     1,                      /* super_user           */
                                     1,                      /* read_write           */
                                     1                       /* present              */
                                 );
}

BOOT_CODE void*
map_temp_boot_page(void* entry, uint32_t large_pages)
{
    /* this function is for legacy 32-bit systems where the ACPI tables might
     * collide with the kernel window. Here we just assert that the table is
     * in fact in the lower 4GiB region (which is already 1-to-1 mapped) and
     * continue */
    assert((word_t)entry < BIT(32));
    return entry;
}

static BOOT_CODE cap_t
create_it_pdpt_cap(cap_t vspace_cap, pptr_t pptr, vptr_t vptr, asid_t asid)
{
    cap_t cap;
    cap = cap_pdpt_cap_new(
              asid,   /* capPDPTMappedASID    */
              pptr,   /* capPDPTBasePtr       */
              1,      /* capPDPTIsMapped      */
              vptr    /* capPDPTMappedAddress */
          );
    map_it_pdpt_cap(vspace_cap, cap);
    return cap;
}

static BOOT_CODE cap_t
create_it_pd_cap(cap_t vspace_cap, pptr_t pptr, vptr_t vptr, asid_t asid)
{
    cap_t cap;
    cap = cap_page_directory_cap_new(
              asid,   /* capPDMappedASID      */
              pptr,   /* capPDBasePtr         */
              1,      /* capPDIsMapped        */
              vptr    /* capPDMappedAddress   */
          );
    map_it_pd_cap(vspace_cap, cap);
    return cap;
}

static BOOT_CODE cap_t
create_it_pt_cap(cap_t vspace_cap, pptr_t pptr, vptr_t vptr, asid_t asid)
{
    cap_t cap;
    cap = cap_page_table_cap_new(
              asid,   /* capPTMappedASID      */
              pptr,   /* capPTBasePtr         */
              1,      /* capPTIsMapped        */
              vptr    /* capPTMappedAddress   */
          );
    map_it_pt_cap(vspace_cap, cap);
    return cap;
}

BOOT_CODE cap_t
create_it_address_space(cap_t root_cnode_cap, v_region_t it_v_reg)
{
    cap_t      vspace_cap;
    vptr_t     vptr;
    pptr_t     pptr;
    seL4_SlotPos slot_pos_before;
    seL4_SlotPos slot_pos_after;

    slot_pos_before = ndks_boot.slot_pos_cur;
    /* create the PML4 */
    pptr = alloc_region(seL4_PML4Bits);
    if (!pptr) {
        return cap_null_cap_new();
    }
    memzero(PML4_PTR(pptr), BIT(seL4_PML4Bits));
    copyGlobalMappings(PML4_PTR(pptr));
    vspace_cap = cap_pml4_cap_new(
                     IT_ASID,        /* capPML4MappedASID */
                     pptr,           /* capPML4BasePtr   */
                     1               /* capPML4IsMapped   */
                 );


    write_slot(SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapInitThreadVSpace), vspace_cap);

    /* Create any PDPTs needed for the user land image */
    for (vptr = ROUND_DOWN(it_v_reg.start, PML4_INDEX_OFFSET);
            vptr < it_v_reg.end;
            vptr += BIT(PML4_INDEX_OFFSET)) {
        pptr = alloc_region(seL4_PDPTBits);
        if (!pptr) {
            return cap_null_cap_new();
        }
        memzero(PDPT_PTR(pptr), BIT(seL4_PDPTBits));
        if (!provide_cap(root_cnode_cap,
                         create_it_pdpt_cap(vspace_cap, pptr, vptr, IT_ASID))
           ) {
            return cap_null_cap_new();
        }
    }

    /* Create any PDs needed for the user land image */
    for (vptr = ROUND_DOWN(it_v_reg.start, PDPT_INDEX_OFFSET);
            vptr < it_v_reg.end;
            vptr += BIT(PDPT_INDEX_OFFSET)) {
        pptr = alloc_region(seL4_PageDirBits);
        if (!pptr) {
            return cap_null_cap_new();
        }
        memzero(PD_PTR(pptr), BIT(seL4_PageDirBits));
        if (!provide_cap(root_cnode_cap,
                         create_it_pd_cap(vspace_cap, pptr, vptr, IT_ASID))
           ) {
            return cap_null_cap_new();
        }
    }

    /* Create any PTs needed for the user land image */
    for (vptr = ROUND_DOWN(it_v_reg.start, PD_INDEX_OFFSET);
            vptr < it_v_reg.end;
            vptr += BIT(PD_INDEX_OFFSET)) {
        pptr = alloc_region(seL4_PageTableBits);
        if (!pptr) {
            return cap_null_cap_new();
        }
        memzero(PT_PTR(pptr), BIT(seL4_PageTableBits));
        if (!provide_cap(root_cnode_cap,
                         create_it_pt_cap(vspace_cap, pptr, vptr, IT_ASID))
           ) {
            return cap_null_cap_new();
        }
    }

    slot_pos_after = ndks_boot.slot_pos_cur;
    ndks_boot.bi_frame->userImagePaging = (seL4_SlotRegion) {
        slot_pos_before, slot_pos_after
    };
    return vspace_cap;
}

void copyGlobalMappings(vspace_root_t *new_vspace)
{
    unsigned long i;
    pml4e_t *vspace = (pml4e_t *)new_vspace;

    /* Copy from the tlbbitmap_pptr so that we copy the default entries of the
     * tlb bitmap (if it exists). If it doesn't exist then this loop
     * will be equivalent to copying from PPTR_BASE
     */
    for (i = GET_PML4_INDEX(TLBBITMAP_PPTR); i < BIT(PML4_INDEX_BITS); i++) {
        vspace[i] = X86_GLOBAL_VSPACE_ROOT[i];
    }
}

static BOOT_CODE cap_t
create_it_frame_cap(pptr_t pptr, vptr_t vptr, asid_t asid, bool_t use_large, seL4_Word map_type)
{
    vm_page_size_t frame_size;

    if (use_large) {
        frame_size = X86_LargePage;
    } else {
        frame_size = X86_SmallPage;
    }

    return
        cap_frame_cap_new(
            asid,                          /* capFMappedASID     */
            pptr,                          /* capFBasePtr        */
            frame_size,                    /* capFSize           */
            map_type,                      /* capFMapType        */
            vptr,                          /* capFMappedAddress  */
            wordFromVMRights(VMReadWrite), /* capFVMRights       */
            0                              /* capFIsDevice       */
        );
}

BOOT_CODE cap_t
create_unmapped_it_frame_cap(pptr_t pptr, bool_t use_large)
{
    return create_it_frame_cap(pptr, 0, asidInvalid, use_large, X86_MappingNone);
}

BOOT_CODE cap_t
create_mapped_it_frame_cap(cap_t vspace_cap, pptr_t pptr, vptr_t vptr, asid_t asid, bool_t use_large, bool_t executable UNUSED)
{
    cap_t cap = create_it_frame_cap(pptr, vptr, asid, use_large, X86_MappingVSpace);
    map_it_frame_cap(vspace_cap, cap);
    return cap;
}

/* ====================== BOOT CODE FINISHES HERE ======================== */



exception_t
performASIDPoolInvocation(asid_t asid, asid_pool_t *poolPtr, cte_t *vspaceCapSlot)
{
    asid_map_t asid_map;
#ifdef CONFIG_VTX
    if (cap_get_capType(vspaceCapSlot->cap) == cap_ept_pml4_cap) {
        cap_ept_pml4_cap_ptr_set_capPML4MappedASID(&vspaceCapSlot->cap, asid);
        cap_ept_pml4_cap_ptr_set_capPML4IsMapped(&vspaceCapSlot->cap, 1);
        asid_map = asid_map_asid_map_ept_new(cap_ept_pml4_cap_get_capPML4BasePtr(vspaceCapSlot->cap));
    } else
#endif
    {
        assert(cap_get_capType(vspaceCapSlot->cap) == cap_pml4_cap);
        cap_pml4_cap_ptr_set_capPML4MappedASID(&vspaceCapSlot->cap, asid);
        cap_pml4_cap_ptr_set_capPML4IsMapped(&vspaceCapSlot->cap, 1);
        asid_map = asid_map_asid_map_vspace_new(cap_pml4_cap_get_capPML4BasePtr(vspaceCapSlot->cap));
    }
    poolPtr->array[asid & MASK(asidLowBits)] = asid_map;
    return EXCEPTION_NONE;
}

bool_t CONST
isVTableRoot(cap_t cap)
{
    return cap_get_capType(cap) == cap_pml4_cap;
}

bool_t CONST
isValidNativeRoot(cap_t cap)
{
    return isVTableRoot(cap) &&
           cap_pml4_cap_get_capPML4IsMapped(cap);
}

static pml4e_t CONST
makeUserPML4E(paddr_t paddr, vm_attributes_t vm_attr)
{
    return pml4e_new(
               0,
               paddr,
               0,
               vm_attributes_get_x86PCDBit(vm_attr),
               vm_attributes_get_x86PWTBit(vm_attr),
               1,
               1,
               1
           );
}

static pml4e_t CONST
makeUserPML4EInvalid(void)
{
    return pml4e_new(
               0,                  /* xd               */
               0,                  /* pdpt_base_addr   */
               0,                  /* accessed         */
               0,                  /* cache_disabled   */
               0,                  /* write through    */
               0,                  /* super user       */
               0,                  /* read_write       */
               0                   /* present          */
           );
}

static pdpte_t CONST
makeUserPDPTEHugePage(paddr_t paddr, vm_attributes_t vm_attr, vm_rights_t vm_rights)
{
    return pdpte_pdpte_1g_new(
               0,          /* xd               */
               paddr,      /* physical address */
               0,          /* PAT              */
               0,          /* global           */
               0,          /* dirty            */
               0,          /* accessed         */
               vm_attributes_get_x86PCDBit(vm_attr),  /* cache disabled */
               vm_attributes_get_x86PWTBit(vm_attr),  /* write through  */
               SuperUserFromVMRights(vm_rights),       /* super user     */
               WritableFromVMRights(vm_rights),        /* read write     */
               1                                       /* present        */
           );
}

static pdpte_t CONST
makeUserPDPTEPageDirectory(paddr_t paddr, vm_attributes_t vm_attr)
{
    return pdpte_pdpte_pd_new(
               0,                      /* xd       */
               paddr,                  /* paddr    */
               0,                      /* accessed */
               vm_attributes_get_x86PCDBit(vm_attr),  /* cache disabled */
               vm_attributes_get_x86PWTBit(vm_attr),  /* write through  */
               1,                      /* super user */
               1,                      /* read write */
               1                       /* present    */
           );
}

static pdpte_t CONST
makeUserPDPTEInvalid(void)
{
    return pdpte_pdpte_pd_new(
               0,          /* xd               */
               0,          /* physical address */
               0,          /* accessed         */
               0,          /* cache disabled */
               0,          /* write through  */
               0,          /* super user     */
               0,          /* read write     */
               0           /* present        */
           );
}

pde_t CONST
makeUserPDELargePage(paddr_t paddr, vm_attributes_t vm_attr, vm_rights_t vm_rights)
{
    return pde_pde_large_new(
               0,                                              /* xd                   */
               paddr,                                          /* page_base_address    */
               vm_attributes_get_x86PATBit(vm_attr),          /* pat                  */
               0,                                              /* global               */
               0,                                              /* dirty                */
               0,                                              /* accessed             */
               vm_attributes_get_x86PCDBit(vm_attr),          /* cache_disabled       */
               vm_attributes_get_x86PWTBit(vm_attr),          /* write_through        */
               SuperUserFromVMRights(vm_rights),               /* super_user           */
               WritableFromVMRights(vm_rights),                /* read_write           */
               1                                               /* present              */
           );
}

pde_t CONST
makeUserPDEPageTable(paddr_t paddr, vm_attributes_t vm_attr)
{

    return  pde_pde_pt_new(
                0,                                  /* xd               */
                paddr,                              /* pt_base_address  */
                0,                                  /* accessed         */
                vm_attributes_get_x86PCDBit(vm_attr), /* cache_disabled   */
                vm_attributes_get_x86PWTBit(vm_attr), /* write_through    */
                1,                                  /* super_user       */
                1,                                  /* read_write       */
                1                                   /* present          */
            );
}

pde_t CONST
makeUserPDEInvalid(void)
{
    /* The bitfield only declares two kinds of PDE entries (page tables or large pages)
     * and an invalid entry should really be a third type, but we can simulate it by
     * creating an invalid (present bit 0) entry of either of the defined types */
    return pde_pde_pt_new(
               0,      /* xd               */
               0,      /* pt_base_addr     */
               0,      /* accessed         */
               0,      /* cache_disabled   */
               0,      /* write_through    */
               0,      /* super_user       */
               0,      /* read_write       */
               0       /* present          */
           );
}

pte_t CONST
makeUserPTE(paddr_t paddr, vm_attributes_t vm_attr, vm_rights_t vm_rights)
{
    return pte_new(
               0,                                              /* xd                   */
               paddr,                                          /* page_base_address    */
               0,                                              /* global               */
               vm_attributes_get_x86PATBit(vm_attr),          /* pat                  */
               0,                                              /* dirty                */
               0,                                              /* accessed             */
               vm_attributes_get_x86PCDBit(vm_attr),          /* cache_disabled       */
               vm_attributes_get_x86PWTBit(vm_attr),          /* write_through        */
               SuperUserFromVMRights(vm_rights),               /* super_user           */
               WritableFromVMRights(vm_rights),                /* read_write           */
               1                                               /* present              */
           );
}

pte_t CONST
makeUserPTEInvalid(void)
{
    return pte_new(
               0,                   /* xd                   */
               0,                   /* page_base_address    */
               0,                   /* global               */
               0,                   /* pat                  */
               0,                   /* dirty                */
               0,                   /* accessed             */
               0,                   /* cache_disabled       */
               0,                   /* write_through        */
               0,                   /* super_user           */
               0,                   /* read_write           */
               0                    /* present              */
           );
}


static pml4e_t*
lookupPML4Slot(vspace_root_t*pml4, vptr_t vptr)
{
    pml4e_t *pml4e = PML4E_PTR(pml4);
    word_t pml4Index = GET_PML4_INDEX(vptr);
    return pml4e + pml4Index;
}

static lookupPDPTSlot_ret_t
lookupPDPTSlot(vspace_root_t *pml4, vptr_t vptr)
{
    pml4e_t *pml4Slot = lookupPML4Slot(pml4, vptr);
    lookupPDPTSlot_ret_t ret;

    if (!pml4e_ptr_get_present(pml4Slot)) {
        current_lookup_fault = lookup_fault_missing_capability_new(PML4_INDEX_OFFSET);

        ret.pdptSlot = NULL;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    } else {
        pdpte_t *pdpt;
        pdpte_t *pdptSlot;
        word_t pdptIndex = GET_PDPT_INDEX(vptr);
        pdpt = paddr_to_pptr(pml4e_ptr_get_pdpt_base_address(pml4Slot));
        pdptSlot = pdpt + pdptIndex;

        ret.status = EXCEPTION_NONE;
        ret.pdptSlot = pdptSlot;
        return ret;
    }
}

lookupPDSlot_ret_t
lookupPDSlot(vspace_root_t *pml4, vptr_t vptr)
{
    lookupPDPTSlot_ret_t pdptSlot;
    lookupPDSlot_ret_t ret;

    pdptSlot = lookupPDPTSlot(pml4, vptr);

    if (pdptSlot.status != EXCEPTION_NONE) {
        ret.pdSlot = NULL;
        ret.status = pdptSlot.status;
        return ret;
    }
    if ((pdpte_ptr_get_page_size(pdptSlot.pdptSlot) != pdpte_pdpte_pd) ||
            !pdpte_pdpte_pd_ptr_get_present(pdptSlot.pdptSlot)) {
        current_lookup_fault = lookup_fault_missing_capability_new(PDPT_INDEX_OFFSET);

        ret.pdSlot = NULL;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    } else {
        pde_t *pd;
        pde_t *pdSlot;
        word_t pdIndex = GET_PD_INDEX(vptr);
        pd = paddr_to_pptr(pdpte_pdpte_pd_ptr_get_pd_base_address(pdptSlot.pdptSlot));
        pdSlot = pd + pdIndex;

        ret.status = EXCEPTION_NONE;
        ret.pdSlot = pdSlot;
        return ret;
    }
}

static void
flushPD(vspace_root_t *vspace, word_t vptr, pde_t *pd, asid_t asid)
{
    /* clearing the entire PCID vs flushing the virtual addresses
     * one by one using invplg.
     * choose the easy way, invalidate the PCID
     */
    invalidateASID(vspace, asid, SMP_TERNARY(tlb_bitmap_get(vspace), 0));

}

static void
flushPDPT(vspace_root_t *vspace, word_t vptr, pdpte_t *pdpt, asid_t asid)
{
    /* similar here */
    invalidateASID(vspace, asid, SMP_TERNARY(tlb_bitmap_get(vspace), 0));
    return;
}

void
hwASIDInvalidate(asid_t asid, vspace_root_t *vspace)
{
    invalidateASID(vspace, asid, SMP_TERNARY(tlb_bitmap_get(vspace), 0));
}

void
unmapPageDirectory(asid_t asid, vptr_t vaddr, pde_t *pd)
{
    findVSpaceForASID_ret_t find_ret;
    lookupPDPTSlot_ret_t    lu_ret;

    find_ret = findVSpaceForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        return;
    }

    lu_ret = lookupPDPTSlot(find_ret.vspace_root, vaddr);
    if (lu_ret.status != EXCEPTION_NONE) {
        return;
    }

    /* check if the PDPT has the PD */
    if (! (pdpte_ptr_get_page_size(lu_ret.pdptSlot) == pdpte_pdpte_pd &&
            pdpte_pdpte_pd_ptr_get_present(lu_ret.pdptSlot) &&
            (pdpte_pdpte_pd_ptr_get_pd_base_address(lu_ret.pdptSlot) == pptr_to_paddr(pd)))) {
        return;
    }

    flushPD(find_ret.vspace_root, vaddr, pd, asid);

    *lu_ret.pdptSlot = makeUserPDPTEInvalid();

    invalidatePageStructureCacheASID(pptr_to_paddr(find_ret.vspace_root), asid,
                                     SMP_TERNARY(tlb_bitmap_get(find_ret.vspace_root), 0));
}


static exception_t
performX64PageDirectoryInvocationUnmap(cap_t cap, cte_t *ctSlot)
{

    if (cap_page_directory_cap_get_capPDIsMapped(cap)) {
        pde_t *pd = PDE_PTR(cap_page_directory_cap_get_capPDBasePtr(cap));
        unmapPageDirectory(
            cap_page_directory_cap_get_capPDMappedASID(cap),
            cap_page_directory_cap_get_capPDMappedAddress(cap),
            pd
        );
        clearMemory((void *)pd, cap_get_capSizeBits(cap));
    }

    cap_page_directory_cap_ptr_set_capPDIsMapped(&(ctSlot->cap), 0);

    return EXCEPTION_NONE;
}

static exception_t
performX64PageDirectoryInvocationMap(cap_t cap, cte_t *ctSlot, pdpte_t pdpte, pdpte_t *pdptSlot, vspace_root_t *vspace)
{
    ctSlot->cap = cap;
    *pdptSlot = pdpte;
    invalidatePageStructureCacheASID(pptr_to_paddr(vspace), cap_page_directory_cap_get_capPDMappedASID(cap),
                                     SMP_TERNARY(tlb_bitmap_get(vspace), 0));
    return EXCEPTION_NONE;
}


static exception_t
decodeX64PageDirectoryInvocation(
    word_t label,
    word_t length,
    cte_t* cte,
    cap_t cap,
    extra_caps_t extraCaps,
    word_t* buffer
)
{
    word_t              vaddr;
    vm_attributes_t     vm_attr;
    cap_t               vspaceCap;
    vspace_root_t      *vspace;
    pdpte_t             pdpte;
    paddr_t             paddr;
    asid_t              asid;
    lookupPDPTSlot_ret_t pdptSlot;

    if (label == X86PageDirectoryUnmap) {
        if (!isFinalCapability(cte)) {
            current_syscall_error.type = seL4_RevokeFirst;
            userError("X86PageDirectory: Cannot unmap if more than one cap exist.");
            return EXCEPTION_SYSCALL_ERROR;
        }
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);

        return performX64PageDirectoryInvocationUnmap(cap, cte);
    }

    if (label != X86PageDirectoryMap) {
        userError("X64Directory: Illegal operation.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (length < 2 || extraCaps.excaprefs[0] == NULL) {
        userError("X64PageDirectory: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (cap_page_directory_cap_get_capPDIsMapped(cap)) {
        userError("X64PageDirectory: PD is already mapped to a PML4.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;

        return EXCEPTION_SYSCALL_ERROR;
    }

    vaddr = getSyscallArg(0, buffer) & (~MASK(PDPT_INDEX_OFFSET));
    vm_attr = vmAttributesFromWord(getSyscallArg(1, buffer));
    vspaceCap = extraCaps.excaprefs[0]->cap;

    if (!isValidNativeRoot(vspaceCap)) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;

        return EXCEPTION_SYSCALL_ERROR;
    }

    vspace = (vspace_root_t *)pptr_of_cap(vspaceCap);
    asid = cap_get_capMappedASID(vspaceCap);

    if (vaddr > PPTR_USER_TOP) {
        userError("X64PageDirectory: Mapping address too high.");
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 0;

        return EXCEPTION_SYSCALL_ERROR;
    }

    findVSpaceForASID_ret_t find_ret;

    find_ret = findVSpaceForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;

        return EXCEPTION_SYSCALL_ERROR;
    }

    if (find_ret.vspace_root != vspace) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;

        return EXCEPTION_SYSCALL_ERROR;
    }

    pdptSlot = lookupPDPTSlot(vspace, vaddr);
    if (pdptSlot.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;

        return EXCEPTION_SYSCALL_ERROR;
    }

    if ((pdpte_ptr_get_page_size(pdptSlot.pdptSlot) == pdpte_pdpte_pd &&
            pdpte_pdpte_pd_ptr_get_present(pdptSlot.pdptSlot)) ||
            (pdpte_ptr_get_page_size(pdptSlot.pdptSlot) == pdpte_pdpte_1g
             && pdpte_pdpte_1g_ptr_get_present(pdptSlot.pdptSlot))) {
        current_syscall_error.type = seL4_DeleteFirst;

        return EXCEPTION_SYSCALL_ERROR;
    }

    paddr = pptr_to_paddr(PDE_PTR(cap_page_directory_cap_get_capPDBasePtr(cap)));
    pdpte = makeUserPDPTEPageDirectory(paddr, vm_attr);

    cap = cap_page_directory_cap_set_capPDIsMapped(cap, 1);
    cap = cap_page_directory_cap_set_capPDMappedASID(cap, asid);
    cap = cap_page_directory_cap_set_capPDMappedAddress(cap, vaddr);

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return performX64PageDirectoryInvocationMap(cap, cte, pdpte, pdptSlot.pdptSlot, vspace);
}

static void unmapPDPT(asid_t asid, vptr_t vaddr, pdpte_t *pdpt)
{
    findVSpaceForASID_ret_t find_ret;
    pml4e_t *pml4Slot;

    find_ret = findVSpaceForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        return;
    }

    pml4Slot = lookupPML4Slot(find_ret.vspace_root, vaddr);

    /* check if the PML4 has the PDPT */
    if (! (pml4e_ptr_get_present(pml4Slot) &&
            pml4e_ptr_get_pdpt_base_address(pml4Slot) == pptr_to_paddr(pdpt))) {
        return;
    }

    flushPDPT(find_ret.vspace_root, vaddr, pdpt, asid);

    *pml4Slot = makeUserPML4EInvalid();
}

static exception_t
performX64PDPTInvocationUnmap(cap_t cap, cte_t *ctSlot)
{
    if (cap_pdpt_cap_get_capPDPTIsMapped(cap)) {
        pdpte_t *pdpt = PDPTE_PTR(cap_pdpt_cap_get_capPDPTBasePtr(cap));
        unmapPDPT(cap_pdpt_cap_get_capPDPTMappedASID(cap),
                  cap_pdpt_cap_get_capPDPTMappedAddress(cap),
                  pdpt);
        clearMemory((void *)pdpt, cap_get_capSizeBits(cap));
    }

    cap_pdpt_cap_ptr_set_capPDPTIsMapped(&(ctSlot->cap), 0);

    return EXCEPTION_NONE;
}

static exception_t
performX64PDPTInvocationMap(cap_t cap, cte_t *ctSlot, pml4e_t pml4e, pml4e_t *pml4Slot, vspace_root_t *vspace)
{
    ctSlot->cap = cap;
    *pml4Slot = pml4e;
    invalidatePageStructureCacheASID(pptr_to_paddr(vspace), cap_pdpt_cap_get_capPDPTMappedASID(cap),
                                     SMP_TERNARY(tlb_bitmap_get(vspace), 0));

    return EXCEPTION_NONE;
}

static exception_t
decodeX64PDPTInvocation(
    word_t  label,
    word_t length,
    cte_t   *cte,
    cap_t   cap,
    extra_caps_t extraCaps,
    word_t  *buffer)
{
    word_t                  vaddr;
    vm_attributes_t         attr;
    pml4e_t                *pml4Slot;
    cap_t                   vspaceCap;
    vspace_root_t          *vspace;
    pml4e_t                 pml4e;
    paddr_t                 paddr;
    asid_t                  asid;

    if (label == X86PDPTUnmap) {
        if (!isFinalCapability(cte)) {
            current_syscall_error.type = seL4_RevokeFirst;
            userError("X86PDPT: Cannot unmap if more than one cap exist.");
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);

        return performX64PDPTInvocationUnmap(cap, cte);
    }

    if (label != X86PDPTMap) {
        userError("X86PDPT: Illegal operation.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (length < 2 || extraCaps.excaprefs[0] == NULL) {
        userError("X64PDPT: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (cap_pdpt_cap_get_capPDPTIsMapped(cap)) {
        userError("X64PDPT: PDPT is already mapped to a PML4.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;

        return EXCEPTION_SYSCALL_ERROR;
    }

    vaddr = getSyscallArg(0, buffer) & (~MASK(PML4_INDEX_OFFSET));
    attr = vmAttributesFromWord(getSyscallArg(1, buffer));
    vspaceCap = extraCaps.excaprefs[0]->cap;

    if (!isValidNativeRoot(vspaceCap)) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;

        return EXCEPTION_SYSCALL_ERROR;
    }

    vspace = (vspace_root_t *)pptr_of_cap(vspaceCap);
    asid = cap_get_capMappedASID(vspaceCap);

    if (vaddr > PPTR_USER_TOP) {
        userError("X64PDPT: Mapping address too high.");
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 0;

        return EXCEPTION_SYSCALL_ERROR;
    }

    findVSpaceForASID_ret_t find_ret;

    find_ret = findVSpaceForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;

        return EXCEPTION_SYSCALL_ERROR;
    }

    if (find_ret.vspace_root != vspace) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;

        return EXCEPTION_SYSCALL_ERROR;
    }

    pml4Slot = lookupPML4Slot(vspace, vaddr);

    if (pml4e_ptr_get_present(pml4Slot)) {
        current_syscall_error.type = seL4_DeleteFirst;

        return EXCEPTION_SYSCALL_ERROR;
    }

    paddr = pptr_to_paddr(PDPTE_PTR((cap_pdpt_cap_get_capPDPTBasePtr(cap))));
    pml4e = makeUserPML4E(paddr, attr);

    cap = cap_pdpt_cap_set_capPDPTIsMapped(cap, 1);
    cap = cap_pdpt_cap_set_capPDPTMappedASID(cap, asid);
    cap = cap_pdpt_cap_set_capPDPTMappedAddress(cap, vaddr);

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return performX64PDPTInvocationMap(cap, cte, pml4e, pml4Slot, vspace);
}

exception_t
decodeX86ModeMMUInvocation(
    word_t label,
    word_t length,
    cptr_t cptr,
    cte_t* cte,
    cap_t cap,
    extra_caps_t extraCaps,
    word_t* buffer
)
{
    switch (cap_get_capType(cap)) {

    case cap_pml4_cap:
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;

    case cap_pdpt_cap:
        return decodeX64PDPTInvocation(label, length, cte, cap, extraCaps, buffer);

    case cap_page_directory_cap:
        return decodeX64PageDirectoryInvocation(label, length, cte, cap, extraCaps, buffer);

    default:
        fail("Invalid arch cap type");
    }
}

bool_t modeUnmapPage(vm_page_size_t page_size, vspace_root_t *vroot, vptr_t vaddr, void *pptr)
{
    if (config_set(CONFIG_HUGE_PAGE) && page_size == X64_HugePage) {
        pdpte_t     *pdpte;
        lookupPDPTSlot_ret_t pdpt_ret = lookupPDPTSlot(vroot, vaddr);
        if (pdpt_ret.status != EXCEPTION_NONE) {
            return false;
        }
        pdpte = pdpt_ret.pdptSlot;


        if (! (pdpte_ptr_get_page_size(pdpte) == pdpte_pdpte_1g
                && pdpte_pdpte_1g_ptr_get_present(pdpte)
                &&  (pdpte_pdpte_1g_ptr_get_page_base_address(pdpte)
                     == pptr_to_paddr(pptr)))) {
            return false;
        }

        *pdpte = makeUserPDPTEInvalid();
        return true;
    }
    fail("Invalid page type");
    return false;
}

static exception_t updatePDPTE(asid_t asid, pdpte_t pdpte, pdpte_t *pdptSlot, vspace_root_t *vspace)
{
    *pdptSlot = pdpte;
    invalidatePageStructureCacheASID(pptr_to_paddr(vspace), asid,
                                     SMP_TERNARY(tlb_bitmap_get(vspace), 0));
    return EXCEPTION_NONE;
}

static exception_t
performX64ModeRemap(asid_t asid, pdpte_t pdpte, pdpte_t *pdptSlot, vspace_root_t *vspace)
{
    return updatePDPTE(asid, pdpte, pdptSlot, vspace);
}


static exception_t
performX64ModeMap(cap_t cap, cte_t *ctSlot, pdpte_t pdpte, pdpte_t *pdptSlot, vspace_root_t *vspace)
{
    ctSlot->cap = cap;
    return updatePDPTE(cap_frame_cap_get_capFMappedASID(cap), pdpte, pdptSlot, vspace);
}

struct create_mapping_pdpte_return {
    exception_t status;
    pdpte_t pdpte;
    pdpte_t *pdptSlot;
};
typedef struct create_mapping_pdpte_return create_mapping_pdpte_return_t;

static create_mapping_pdpte_return_t
createSafeMappingEntries_PDPTE(paddr_t base, word_t vaddr, vm_rights_t vmRights, vm_attributes_t attr,
                               vspace_root_t *vspace)
{
    create_mapping_pdpte_return_t ret;
    lookupPDPTSlot_ret_t          lu_ret;

    lu_ret = lookupPDPTSlot(vspace, vaddr);
    if (lu_ret.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        ret.status = EXCEPTION_SYSCALL_ERROR;
        /* current_lookup_fault will have been set by lookupPDSlot */
        return ret;
    }
    ret.pdptSlot = lu_ret.pdptSlot;

    /* check for existing page directory */
    if ((pdpte_ptr_get_page_size(ret.pdptSlot) == pdpte_pdpte_pd) &&
            (pdpte_pdpte_pd_ptr_get_present(ret.pdptSlot))) {
        current_syscall_error.type = seL4_DeleteFirst;
        ret.status = EXCEPTION_SYSCALL_ERROR;
        return ret;
    }


    ret.pdpte = makeUserPDPTEHugePage(base, attr, vmRights);
    ret.status = EXCEPTION_NONE;
    return ret;
}

exception_t
decodeX86ModeMapRemapPage(word_t label, vm_page_size_t page_size, cte_t *cte, cap_t cap, vspace_root_t *vroot, vptr_t vaddr, paddr_t paddr, vm_rights_t vm_rights, vm_attributes_t vm_attr)
{
    if (config_set(CONFIG_HUGE_PAGE) && page_size == X64_HugePage) {
        create_mapping_pdpte_return_t map_ret;

        map_ret = createSafeMappingEntries_PDPTE(paddr, vaddr, vm_rights, vm_attr, vroot);
        if (map_ret.status != EXCEPTION_NONE) {
            return map_ret.status;
        }

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);

        switch (label) {
        case X86PageMap: {
            return performX64ModeMap(cap, cte, map_ret.pdpte, map_ret.pdptSlot, vroot);
        }

        case X86PageRemap: {
            return performX64ModeRemap(cap_frame_cap_get_capFMappedASID(cap), map_ret.pdpte, map_ret.pdptSlot, vroot);
        }

        default: {
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }
        }
    }
    fail("Invalid Page type");
}

#ifdef CONFIG_PRINTING
typedef struct readWordFromVSpace_ret {
    exception_t status;
    word_t value;
} readWordFromVSpace_ret_t;

static readWordFromVSpace_ret_t
readWordFromVSpace(vspace_root_t *vspace, word_t vaddr)
{
    readWordFromVSpace_ret_t ret;
    lookupPTSlot_ret_t ptSlot;
    lookupPDSlot_ret_t pdSlot;
    lookupPDPTSlot_ret_t pdptSlot;
    paddr_t paddr;
    word_t offset;
    pptr_t kernel_vaddr;
    word_t *value;

    pdptSlot = lookupPDPTSlot(vspace, vaddr);
    if (pdptSlot.status == EXCEPTION_NONE &&
            pdpte_ptr_get_page_size(pdptSlot.pdptSlot) == pdpte_pdpte_1g &&
            pdpte_pdpte_1g_ptr_get_present(pdptSlot.pdptSlot)) {

        paddr = pdpte_pdpte_1g_ptr_get_page_base_address(pdptSlot.pdptSlot);
        offset = vaddr & MASK(seL4_HugePageBits);
    } else {
        pdSlot = lookupPDSlot(vspace, vaddr);
        if (pdSlot.status == EXCEPTION_NONE &&
                ((pde_ptr_get_page_size(pdSlot.pdSlot) == pde_pde_large) &&
                 pde_pde_large_ptr_get_present(pdSlot.pdSlot))) {

            paddr = pde_pde_large_ptr_get_page_base_address(pdSlot.pdSlot);
            offset = vaddr & MASK(seL4_LargePageBits);
        } else {
            ptSlot = lookupPTSlot(vspace, vaddr);
            if (ptSlot.status == EXCEPTION_NONE && pte_ptr_get_present(ptSlot.ptSlot)) {
                paddr = pte_ptr_get_page_base_address(ptSlot.ptSlot);
                offset = vaddr & MASK(seL4_PageBits);
            } else {
                ret.status = EXCEPTION_LOOKUP_FAULT;
                return ret;
            }
        }
    }


    kernel_vaddr = (word_t)paddr_to_pptr(paddr);
    value = (word_t*)(kernel_vaddr + offset);
    ret.status = EXCEPTION_NONE;
    ret.value = *value;
    return ret;
}

void
Arch_userStackTrace(tcb_t *tptr)
{
    cap_t threadRoot;
    vspace_root_t *vspace_root;
    word_t sp;
    int i;

    threadRoot = TCB_PTR_CTE_PTR(tptr, tcbVTable)->cap;

    /* lookup the PD */
    if (cap_get_capType(threadRoot) != cap_pml4_cap) {
        printf("Invalid vspace\n");
        return;
    }

    vspace_root = (vspace_root_t*)pptr_of_cap(threadRoot);

    sp = getRegister(tptr, RSP);
    /* check for alignment so we don't have to worry about accessing
     * words that might be on two different pages */
    if (!IS_ALIGNED(sp, seL4_WordSizeBits)) {
        printf("RSP not aligned\n");
        return;
    }

    for (i = 0; i < CONFIG_USER_STACK_TRACE_LENGTH; i++) {
        word_t address = sp + (i * sizeof(word_t));
        readWordFromVSpace_ret_t result;
        result = readWordFromVSpace(vspace_root, address);
        if (result.status == EXCEPTION_NONE) {
            printf("0x%lx: 0x%lx\n", (long)address, (long)result.value);
        } else {
            printf("0x%lx: INVALID\n", (long)address);
        }
    }
}
#endif /* CONFIG_PRINTING */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/64/machine/registerset.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <arch/machine/registerset.h>
#include <machine/fpu.h>
#include <arch/object/structures.h>

const register_t msgRegisters[] = {
    R10, R8, R9, R15
};

const register_t frameRegisters[] = {
    FaultIP, RSP, FLAGS, RAX, RBX, RCX, RDX, RSI, RDI, RBP,
    R8, R9, R10, R11, R12, R13, R14, R15
};

const register_t gpRegisters[] = {
    TLS_BASE
};

void Mode_initContext(user_context_t* context)
{
    context->registers[RAX] = 0;
    context->registers[RBX] = 0;
    context->registers[RCX] = 0;
    context->registers[RDX] = 0;
    context->registers[RSI] = 0;
    context->registers[RDI] = 0;
    context->registers[RBP] = 0;
    context->registers[R8]  = 0;
    context->registers[R9]  = 0;
    context->registers[R10] = 0;
    context->registers[R11] = 0;
    context->registers[R12] = 0;
    context->registers[R13] = 0;
    context->registers[R14] = 0;
    context->registers[R15] = 0;
    context->registers[RSP] = 0;
}

word_t Mode_sanitiseRegister(register_t reg, word_t v)
{
    if (reg == FaultIP || reg == NextIP) {
        /* ensure instruction address is canonical */
        if (v > 0x00007fffffffffff && v < 0xffff800000000000) {
            /* no way to guess what the user wanted so give them zero */
            v = 0;
        }
    }
    return v;
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/64/model/smp.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <mode/model/smp.h>

#ifdef ENABLE_SMP_SUPPORT

nodeInfo_t node_info[CONFIG_MAX_NUM_NODES] ALIGN(L1_CACHE_LINE_SIZE) VISIBLE;
char nodeSkimScratch[CONFIG_MAX_NUM_NODES][sizeof(nodeInfo_t)] ALIGN(L1_CACHE_LINE_SIZE);
extern char kernel_stack_alloc[CONFIG_MAX_NUM_NODES][BIT(CONFIG_KERNEL_STACK_BITS)];

BOOT_CODE void
mode_init_tls(cpu_id_t cpu_index)
{
    node_info[cpu_index].stackTop = kernel_stack_alloc[cpu_index + 1];
    node_info[cpu_index].irqStack = &x64KSIRQStack[cpu_index][0];
    node_info[cpu_index].index = cpu_index;
    x86_wrmsr(IA32_KERNEL_GS_BASE_MSR, (word_t)&node_info[cpu_index]);
    swapgs();
}

#endif /* ENABLE_SMP_SUPPORT */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/64/model/statedata.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <arch/model/statedata.h>

/* The privileged kernel mapping PD & PT */
pml4e_t x64KSKernelPML4[BIT(PML4_INDEX_BITS)] ALIGN(BIT(seL4_PML4Bits)) VISIBLE;
pdpte_t x64KSKernelPDPT[BIT(PDPT_INDEX_BITS)] ALIGN(BIT(seL4_PDPTBits));
#ifdef CONFIG_HUGE_PAGE
pde_t x64KSKernelPD[BIT(PD_INDEX_BITS)] ALIGN(BIT(seL4_PageDirBits));
#else
pde_t x64KSKernelPDs[BIT(PDPT_INDEX_BITS)][BIT(PD_INDEX_BITS)] ALIGN(BIT(seL4_PageDirBits));
#endif
pte_t x64KSKernelPT[BIT(PT_INDEX_BITS)] ALIGN(BIT(seL4_PageTableBits));

#ifdef CONFIG_KERNEL_SKIM_WINDOW
pml4e_t x64KSSKIMPML4[BIT(PML4_INDEX_BITS)] ALIGN(BIT(seL4_PML4Bits));
pdpte_t x64KSSKIMPDPT[BIT(PDPT_INDEX_BITS)] ALIGN(BIT(seL4_PDPTBits));
pde_t x64KSSKIMPD[BIT(PD_INDEX_BITS)] ALIGN(BIT(seL4_PageDirBits));
#endif

#ifdef CONFIG_KERNEL_SKIM_WINDOW
UP_STATE_DEFINE(word_t, x64KSCurrentUserCR3);
#else
UP_STATE_DEFINE(cr3_t, x64KSCurrentCR3);
#endif

word_t x64KSIRQStack[CONFIG_MAX_NUM_NODES][IRQ_STACK_SIZE + 2] ALIGN(64) VISIBLE SKIM_BSS;
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/64/object/objecttype.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <types.h>
#include <api/failures.h>
#include <kernel/vspace.h>
#include <object/structures.h>
#include <arch/machine.h>
#include <arch/model/statedata.h>
#include <machine/fpu.h>
#include <arch/object/objecttype.h>
#include <arch/object/ioport.h>
#include <arch/kernel/ept.h>

#include <arch/object/iospace.h>
#include <plat/machine/intel-vtd.h>


bool_t
Arch_isFrameType(word_t type)
{
    switch (type) {
    case seL4_X86_4K:
        return true;
    case seL4_X86_LargePageObject:
        return true;
    case seL4_X64_HugePageObject:
        return true;
    default:
        return false;
    }
}

deriveCap_ret_t
Mode_deriveCap(cte_t* slot, cap_t cap)
{
    deriveCap_ret_t ret;

    switch (cap_get_capType(cap)) {
    case cap_pml4_cap:
        if (cap_pml4_cap_get_capPML4IsMapped(cap)) {
            ret.cap = cap;
            ret.status = EXCEPTION_NONE;
        } else {
            userError("Deriving a PML4 cap without an assigned ASID");
            current_syscall_error.type = seL4_IllegalOperation;
            ret.cap = cap_null_cap_new();
            ret.status = EXCEPTION_SYSCALL_ERROR;
        }
        return ret;

    case cap_pdpt_cap:
        if (cap_pdpt_cap_get_capPDPTIsMapped(cap)) {
            ret.cap = cap;
            ret.status = EXCEPTION_NONE;
        } else {
            userError("Deriving an unmapped PTPD cap");
            current_syscall_error.type = seL4_IllegalOperation;
            ret.cap = cap_null_cap_new();
            ret.status = EXCEPTION_SYSCALL_ERROR;
        }
        return ret;

    case cap_frame_cap:
        cap = cap_frame_cap_set_capFMapType(cap, X86_MappingNone);
        ret.cap = cap_frame_cap_set_capFMappedASID(cap, asidInvalid);
        ret.status = EXCEPTION_NONE;
        return ret;

    default:
        fail("Invalid arch cap type");
    }
}

finaliseCap_ret_t Mode_finaliseCap(cap_t cap, bool_t final)
{
    finaliseCap_ret_t fc_ret;

    switch (cap_get_capType(cap)) {

    case cap_pml4_cap:
        if (final && cap_pml4_cap_get_capPML4IsMapped(cap)) {
            deleteASID(
                cap_pml4_cap_get_capPML4MappedASID(cap),
                PML4E_PTR(cap_pml4_cap_get_capPML4BasePtr(cap))
            );
        }
        break;

    case cap_pdpt_cap:
        if (final && cap_pdpt_cap_get_capPDPTIsMapped(cap)) {
            unmapPDPT(
                cap_pdpt_cap_get_capPDPTMappedASID(cap),
                cap_pdpt_cap_get_capPDPTMappedAddress(cap),
                PDPTE_PTR(cap_pdpt_cap_get_capPDPTBasePtr(cap))
            );
        }
        break;

    case cap_frame_cap:
        if (cap_frame_cap_get_capFMappedASID(cap)) {
            switch (cap_frame_cap_get_capFMapType(cap)) {
#ifdef CONFIG_VTX
            case X86_MappingEPT:
                unmapEPTPage(
                    cap_frame_cap_get_capFSize(cap),
                    cap_frame_cap_get_capFMappedASID(cap),
                    cap_frame_cap_get_capFMappedAddress(cap),
                    (void *)cap_frame_cap_get_capFBasePtr(cap)
                );
                break;
#endif
#ifdef CONFIG_IOMMU
            case X86_MappingIOSpace:
                unmapIOPage(cap);
                break;
#endif
            case X86_MappingVSpace:
                unmapPage(
                    cap_frame_cap_get_capFSize(cap),
                    cap_frame_cap_get_capFMappedASID(cap),
                    cap_frame_cap_get_capFMappedAddress(cap),
                    (void *)cap_frame_cap_get_capFBasePtr(cap)
                );
                break;
            default:
                fail("Invalid map type");
            }
        }
        break;

    default:
        fail("Invalid arch cap type");
    }

    fc_ret.remainder = cap_null_cap_new();
    fc_ret.cleanupInfo = cap_null_cap_new();
    return fc_ret;
}

bool_t CONST Mode_sameRegionAs(cap_t cap_a, cap_t cap_b)
{
    switch (cap_get_capType(cap_a)) {

    case cap_pdpt_cap:
        if (cap_get_capType(cap_b) == cap_pdpt_cap) {
            return cap_pdpt_cap_get_capPDPTBasePtr(cap_a) ==
                   cap_pdpt_cap_get_capPDPTBasePtr(cap_b);
        }
        return false;

    case cap_pml4_cap:
        if (cap_get_capType(cap_b) == cap_pml4_cap) {
            return cap_pml4_cap_get_capPML4BasePtr(cap_a) ==
                   cap_pml4_cap_get_capPML4BasePtr(cap_b);
        }
        return false;
    default:
        return false;
    }
}

word_t
Mode_getObjectSize(word_t t)
{
    switch (t) {
    case seL4_X64_PML4Object:
        return seL4_PML4Bits;

    case seL4_X64_HugePageObject:
        return pageBitsForSize(X64_HugePage);

    default:
        fail("Invalid object type");
        return 0;
    }
}

cap_t
Mode_createObject(object_t t, void *regionBase, word_t userSize, bool_t deviceMemory)
{
    switch (t) {

    case seL4_X86_4K:
        if (deviceMemory) {
            /** AUXUPD: "(True, ptr_retyps 1
                     (Ptr (ptr_val \<acute>regionBase) :: user_data_device_C ptr))" */
            /** GHOSTUPD: "(True, gs_new_frames vmpage_size.X64SmallPage
                                                    (ptr_val \<acute>regionBase)
                                                    (unat X64SmallPageBits))" */
        } else {
            /** AUXUPD: "(True, ptr_retyps 1
                     (Ptr (ptr_val \<acute>regionBase) :: user_data_C ptr))" */
            /** GHOSTUPD: "(True, gs_new_frames vmpage_size.X64SmallPage
                                                    (ptr_val \<acute>regionBase)
                                                    (unat X64SmallPageBits))" */
        }
        return cap_frame_cap_new(
                   asidInvalid,        /* capFMappedASID           */
                   (word_t)regionBase, /* capFBasePtr              */
                   X86_SmallPage,      /* capFSize                 */
                   X86_MappingNone,    /* capFMapType              */
                   0,                  /* capFMappedAddress        */
                   VMReadWrite,        /* capFVMRights             */
                   deviceMemory        /* capFIsDevice             */
               );

    case seL4_X86_LargePageObject:
        if (deviceMemory) {
            /** AUXUPD: "(True, ptr_retyps 512
                     (Ptr (ptr_val \<acute>regionBase) :: user_data_device_C ptr))" */
            /** GHOSTUPD: "(True, gs_new_frames vmpage_size.X64LargePage
                                                    (ptr_val \<acute>regionBase)
                                                    (unat X64LargePageBits))" */
        } else {
            /** AUXUPD: "(True, ptr_retyps 512
                     (Ptr (ptr_val \<acute>regionBase) :: user_data_C ptr))" */
            /** GHOSTUPD: "(True, gs_new_frames vmpage_size.X64LargePage
                                                    (ptr_val \<acute>regionBase)
                                                    (unat X64LargePageBits))" */
        }
        return cap_frame_cap_new(
                   asidInvalid,        /* capFMappedASID           */
                   (word_t)regionBase, /* capFBasePtr              */
                   X86_LargePage,      /* capFSize                 */
                   X86_MappingNone,    /* capFMapType              */
                   0,                  /* capFMappedAddress        */
                   VMReadWrite,        /* capFVMRights             */
                   deviceMemory        /* capFIsDevice             */
               );

    case seL4_X64_HugePageObject:
        if (deviceMemory) {
            /** AUXUPD: "(True, ptr_retyps 262144
                     (Ptr (ptr_val \<acute>regionBase) :: user_data_device_C ptr))" */
            /** GHOSTUPD: "(True, gs_new_frames vmpage_size.X64HugePage
                                                    (ptr_val \<acute>regionBase)
                                                    (unat X64HugePageBits))" */
        } else {
            /** AUXUPD: "(True, ptr_retyps 262144
                     (Ptr (ptr_val \<acute>regionBase) :: user_data_C ptr))" */
            /** GHOSTUPD: "(True, gs_new_frames vmpage_size.X64HugePage
                                                    (ptr_val \<acute>regionBase)
                                                    (unat X64HugePageBits))" */
        }
        return cap_frame_cap_new(
                   asidInvalid,        /* capFMappedASID           */
                   (word_t)regionBase, /* capFBasePtr              */
                   X64_HugePage,       /* capFSize                 */
                   X86_MappingNone,    /* capFMapType              */
                   0,                  /* capFMappedAddress        */
                   VMReadWrite,        /* capFVMRights             */
                   deviceMemory        /* capFIsDevice             */
               );

    case seL4_X86_PageTableObject:
        /** AUXUPD: "(True, ptr_retyps 1
              (Ptr (ptr_val \<acute>regionBase) :: (pte_C[512]) ptr))" */
        return cap_page_table_cap_new(
                   asidInvalid,            /* capPTMappedASID    */
                   (word_t)regionBase,     /* capPTBasePtr       */
                   0,                      /* capPTIsMapped      */
                   0                       /* capPTMappedAddress */
               );

    case seL4_X86_PageDirectoryObject:
        /** AUXUPD: "(True, ptr_retyps 1
              (Ptr (ptr_val \<acute>regionBase) :: (pde_C[512]) ptr))" */
        return cap_page_directory_cap_new(
                   asidInvalid,                /* capPDMappedASID      */
                   (word_t)regionBase,         /* capPDBasePtr         */
                   0,                          /* capPDIsMapped        */
                   0                           /* capPDMappedAddress   */
               );

    case seL4_X86_PDPTObject:
        /** AUXUPD: "(True, ptr_retyps 1
              (Ptr (ptr_val \<acute>regionBase) :: (pdpte_C[512]) ptr))" */
        return cap_pdpt_cap_new(
                   asidInvalid,                /* capPDPTMappedASID    */
                   (word_t)regionBase,         /* capPDPTBasePtr       */
                   0,                          /* capPDPTIsMapped      */
                   0                           /* capPDPTMappedAddress */
               );

    case seL4_X64_PML4Object:
        /** AUXUPD: "(True, ptr_retyps 1
              (Ptr (ptr_val \<acute>regionBase) :: (pml4e_C[512]) ptr))" */
        copyGlobalMappings(PML4_PTR(regionBase));
        return cap_pml4_cap_new(
                   asidInvalid,                /* capPML4MappedASID   */
                   (word_t)regionBase,         /* capPML4BasePtr      */
                   0                           /* capPML4IsMapped     */
               );

#ifdef CONFIG_IOMMU
    case seL4_X86_IOPageTableObject:
        return cap_io_page_table_cap_new(
                   0,
                   0,
                   0,
                   asidInvalid,
                   (word_t)regionBase
               );
#endif

    default:
        /*
         * This is a conflation of the haskell error: "Arch.createNewCaps
         * got an API type" and the case where an invalid object type is
         * passed (which is impossible in haskell).
         */
        fail("Arch_createObject got an API type or invalid object type");
    }
}

exception_t
Mode_decodeInvocation(
    word_t label,
    word_t length,
    cptr_t cptr,
    cte_t* slot,
    cap_t cap,
    extra_caps_t extraCaps,
    word_t* buffer
)
{
    switch (cap_get_capType(cap)) {
    case cap_pml4_cap:
    case cap_pdpt_cap:
    case cap_page_directory_cap:
    case cap_page_table_cap:
    case cap_frame_cap:
        return decodeX86MMUInvocation(label, length, cptr, slot, cap, extraCaps, buffer);

    default:
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/64/smp/ipi.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <mode/smp/ipi.h>
#include <mode/kernel/tlb.h>

#ifdef ENABLE_SMP_SUPPORT

void Mode_handleRemoteCall(IpiModeRemoteCall_t call, word_t arg0, word_t arg1, word_t arg2)
{
    switch (call) {
    case IpiRemoteCall_InvalidatePCID:
        invalidateLocalPCID(arg0, (void*)arg1, arg2);
        break;

    case IpiRemoteCall_InvalidateASID:
        invalidateLocalASID((vspace_root_t*)arg0, arg1);
        break;

    default:
        fail("Invalid remote call");
    }
}

#endif /* ENABLE_SMP_SUPPORT */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/api/faults.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <types.h>
#include <machine/io.h>
#include <api/faults.h>
#include <api/syscall.h>
#include <util.h>

bool_t Arch_handleFaultReply(tcb_t *receiver, tcb_t *sender, word_t faultType)
{
    switch (faultType) {
    case seL4_Fault_VMFault:
        return true;

    default:
        fail("Invalid fault");
    }
}

word_t
Arch_setMRs_fault(tcb_t *sender, tcb_t* receiver, word_t *receiveIPCBuffer, word_t faultType)
{
    switch (faultType) {
    case seL4_Fault_VMFault: {
        setMR(receiver, receiveIPCBuffer, seL4_VMFault_IP, getRestartPC(sender));
        setMR(receiver, receiveIPCBuffer, seL4_VMFault_Addr,
              seL4_Fault_VMFault_get_address(sender->tcbFault));
        setMR(receiver, receiveIPCBuffer, seL4_VMFault_PrefetchFault,
              seL4_Fault_VMFault_get_instructionFault(sender->tcbFault));
        return setMR(receiver, receiveIPCBuffer, seL4_VMFault_FSR,
                     seL4_Fault_VMFault_get_FSR(sender->tcbFault));
    }
    default:
        fail("Invalid fault");
    }
}

word_t handleKernelException(
    word_t vector,
    word_t errcode,
    word_t ip,
    word_t sp,
    word_t flags,
    word_t cr0,
    word_t cr2,
    word_t cr3,
    word_t cr4
);

VISIBLE
word_t handleKernelException(
    word_t vector,
    word_t errcode,
    word_t ip,
    word_t sp,
    word_t flags,
    word_t cr0,
    word_t cr2,
    word_t cr3,
    word_t cr4
)
{
    word_t i;

    /* Check if we are in a state where we expect a GP fault, if so record it and return */
    if (vector == int_gp_fault && ARCH_NODE_STATE(x86KSGPExceptReturnTo) != 0) {
        word_t ret = ARCH_NODE_STATE(x86KSGPExceptReturnTo);
        ARCH_NODE_STATE(x86KSGPExceptReturnTo) = 0;
        return ret;
    }
    printf("\n========== KERNEL EXCEPTION ==========\n");
    printf("Vector:  0x%lx\n", vector);
    printf("ErrCode: 0x%lx\n", errcode);
    printf("IP:      0x%lx\n", ip);
    printf("SP:      0x%lx\n", sp);
    printf("FLAGS:   0x%lx\n", flags);
    printf("CR0:     0x%lx\n", cr0);
    printf("CR2:     0x%lx (page-fault address)\n", cr2);
    printf("CR3:     0x%lx (page-directory physical address)\n", cr3);
    printf("CR4:     0x%lx\n", cr4);
    printf("\nStack Dump:\n");
    for (i = 0; i < 20; i++) {
        word_t UNUSED stack = sp + i * sizeof(word_t);
        printf("*0x%lx == 0x%lx\n", stack, *(word_t*)stack);
    }
    printf("\nHalting...\n");
    halt();
    UNREACHABLE();
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/benchmark/benchmark.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#if CONFIG_MAX_NUM_TRACE_POINTS > 0

#include <benchmark/benchmark.h>
#include <arch/benchmark.h>
#include <arch/machine/hardware.h>

timestamp_t ksEntries[CONFIG_MAX_NUM_TRACE_POINTS];
bool_t ksStarted[CONFIG_MAX_NUM_TRACE_POINTS];
timestamp_t ksExit;
seL4_Word ksLogIndex = 0;
seL4_Word ksLogIndexFinalized = 0;

#endif /* CONFIG_MAX_NUM_TRACE_POINTS > 0 */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/c_traps.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <model/statedata.h>
#include <machine/fpu.h>
#include <arch/fastpath/fastpath.h>
#include <arch/kernel/traps.h>
#include <machine/debug.h>
#include <arch/object/vcpu.h>
#include <api/syscall.h>
#include <arch/api/vmenter.h>

#include <benchmark/benchmark_track.h>
#include <benchmark/benchmark_utilisation.h>

void VISIBLE
c_nested_interrupt(int irq)
{
    /* This is not a real entry point, so we do not grab locks or
     * run c_entry/exit_hooks, since this occurs only if we're already
     * running inside the kernel. Just record the irq and return */
    assert(ARCH_NODE_STATE(x86KSPendingInterrupt) == int_invalid);
    ARCH_NODE_STATE(x86KSPendingInterrupt) = irq;
}

void VISIBLE NORETURN
c_handle_interrupt(int irq, int syscall)
{
    /* need to run this first as the NODE_LOCK code might end up as a function call
     * with a return, and we need to make sure returns are not exploitable yet
     * on x64 this code ran already */
    if (config_set(CONFIG_ARCH_IA32) && config_set(CONFIG_KERNEL_X86_IBRS_BASIC)) {
        x86_enable_ibrs();
    }

    /* Only grab the lock if we are not handeling 'int_remote_call_ipi' interrupt
     * also flag this lock as IRQ lock if handling the irq interrupts. */
    NODE_LOCK_IF(irq != int_remote_call_ipi,
                 irq >= int_irq_min && irq <= int_irq_max);

    c_entry_hook();

    if (irq == int_unimpl_dev) {
        handleFPUFault();
#ifdef TRACK_KERNEL_ENTRIES
        ksKernelEntry.path = Entry_UnimplementedDevice;
        ksKernelEntry.word = irq;
#endif
    } else if (irq == int_page_fault) {
        /* Error code is in Error. Pull out bit 5, which is whether it was instruction or data */
        vm_fault_type_t type = (NODE_STATE(ksCurThread)->tcbArch.tcbContext.registers[Error] >> 4u) & 1u;
#ifdef TRACK_KERNEL_ENTRIES
        ksKernelEntry.path = Entry_VMFault;
        ksKernelEntry.word = type;
#endif
        handleVMFaultEvent(type);
#ifdef CONFIG_HARDWARE_DEBUG_API
    } else if (irq == int_debug || irq == int_software_break_request) {
        /* Debug exception */
#ifdef TRACK_KERNEL_ENTRIES
        ksKernelEntry.path = Entry_DebugFault;
        ksKernelEntry.word = NODE_STATE(ksCurThread)->tcbArch.tcbContext.registers[FaultIP];
#endif
        handleUserLevelDebugException(irq);
#endif /* CONFIG_HARDWARE_DEBUG_API */
    } else if (irq < int_irq_min) {
#ifdef TRACK_KERNEL_ENTRIES
        ksKernelEntry.path = Entry_UserLevelFault;
        ksKernelEntry.word = irq;
#endif
        handleUserLevelFault(irq, NODE_STATE(ksCurThread)->tcbArch.tcbContext.registers[Error]);
    } else if (likely(irq < int_trap_min)) {
        ARCH_NODE_STATE(x86KScurInterrupt) = irq;
#ifdef TRACK_KERNEL_ENTRIES
        ksKernelEntry.path = Entry_Interrupt;
        ksKernelEntry.word = irq;
#endif
        handleInterruptEntry();
        /* check for other pending interrupts */
        receivePendingIRQ();
    } else if (irq == int_spurious) {
        /* fall through to restore_user_context and do nothing */
    } else {
        /* Interpret a trap as an unknown syscall */
        /* Adjust FaultIP to point to trapping INT
         * instruction by subtracting 2 */
        int sys_num;
        NODE_STATE(ksCurThread)->tcbArch.tcbContext.registers[FaultIP] -= 2;
        /* trap number is MSBs of the syscall number and the LSBS of EAX */
        sys_num = (irq << 24) | (syscall & 0x00ffffff);
#ifdef TRACK_KERNEL_ENTRIES
        ksKernelEntry.path = Entry_UnknownSyscall;
        ksKernelEntry.word = sys_num;
#endif
        handleUnknownSyscall(sys_num);
    }
    restore_user_context();
    UNREACHABLE();
}

void NORETURN
slowpath(syscall_t syscall)
{

#ifdef CONFIG_VTX
    if (syscall == SysVMEnter) {
        vcpu_update_state_sysvmenter(NODE_STATE(ksCurThread)->tcbArch.tcbVCPU);
        if (NODE_STATE(ksCurThread)->tcbBoundNotification && notification_ptr_get_state(NODE_STATE(ksCurThread)->tcbBoundNotification) == NtfnState_Active) {
            completeSignal(NODE_STATE(ksCurThread)->tcbBoundNotification, NODE_STATE(ksCurThread));
            setRegister(NODE_STATE(ksCurThread), msgInfoRegister, SEL4_VMENTER_RESULT_NOTIF);
            /* Any guest state that we should return is in the same
             * register position as sent to us, so we can just return
             * and let the user pick up the values they put in */
            restore_user_context();
        } else {
            setThreadState(NODE_STATE(ksCurThread), ThreadState_RunningVM);
            restore_user_context();
        }
    }
#endif
    /* check for undefined syscall */
    if (unlikely(syscall < SYSCALL_MIN || syscall > SYSCALL_MAX)) {
#ifdef TRACK_KERNEL_ENTRIES
        ksKernelEntry.path = Entry_UnknownSyscall;
        /* ksKernelEntry.word word is already set to syscall */
#endif /* TRACK_KERNEL_ENTRIES */
        handleUnknownSyscall(syscall);
    } else {
#ifdef TRACK_KERNEL_ENTRIES
        ksKernelEntry.is_fastpath = 0;
#endif /* TRACK KERNEL ENTRIES */
        handleSyscall(syscall);
    }

    restore_user_context();
    UNREACHABLE();
}

void VISIBLE NORETURN
c_handle_syscall(word_t cptr, word_t msgInfo, syscall_t syscall)
{
    /* need to run this first as the NODE_LOCK code might end up as a function call
     * with a return, and we need to make sure returns are not exploitable yet */
    if (config_set(CONFIG_KERNEL_X86_IBRS_BASIC)) {
        x86_enable_ibrs();
    }

    NODE_LOCK_SYS;

    c_entry_hook();

#ifdef TRACK_KERNEL_ENTRIES
    benchmark_debug_syscall_start(cptr, msgInfo, syscall);
    ksKernelEntry.is_fastpath = 1;
#endif /* TRACK_KERNEL_ENTRIES */

    if (config_set(CONFIG_SYSENTER)) {
        /* increment NextIP to skip sysenter */
        NODE_STATE(ksCurThread)->tcbArch.tcbContext.registers[NextIP] += 2;
    } else {
        /* set FaultIP */
        setRegister(NODE_STATE(ksCurThread), FaultIP, getRegister(NODE_STATE(ksCurThread), NextIP) - 2);
    }

#ifdef CONFIG_FASTPATH
    if (syscall == (syscall_t)SysCall) {
        fastpath_call(cptr, msgInfo);
        UNREACHABLE();
    } else if (syscall == (syscall_t)SysReplyRecv) {
        fastpath_reply_recv(cptr, msgInfo);
        UNREACHABLE();
    }
#endif /* CONFIG_FASTPATH */
    slowpath(syscall);
    UNREACHABLE();
}

#ifdef CONFIG_VTX
void VISIBLE NORETURN c_handle_vmexit(void)
{
#ifdef TRACK_KERNEL_ENTRIES
    ksKernelEntry.path = Entry_VMExit;
#endif

    /* We *always* need to flush the rsb as a guest may have been able to train the rsb with kernel addresses */
    x86_flush_rsb();

    c_entry_hook();
    /* NODE_LOCK will get called in handleVmexit */
    handleVmexit();
    /* When we switched out of VMX mode the FS and GS registers were clobbered
     * and set to potentially undefined values. If we are going to switch back
     * to VMX mode then this is fine, but if we are switching to user mode we
     * need to make sure we reload the correct values of FS and GS. Unfortunately
     * our cached values in x86KSCurrent[FG]SBase now mismatch what is in the
     * hardware. To force a reload to happen we set the cached value to something
     * that is guaranteed to not be the target threads value, ensuring both
     * the cache and the hardware get updated */
    tcb_t *cur_thread = NODE_STATE(ksCurThread);
    if (thread_state_ptr_get_tsType(&cur_thread->tcbState) != ThreadState_RunningVM) {
        ARCH_NODE_STATE(x86KSCurrentGSBase) = -(word_t)1;
        ARCH_NODE_STATE(x86KSCurrentFSBase) = -(word_t)1;
    }
    restore_user_context();
    UNREACHABLE();
}
#endif
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/idle.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <api/debug.h>

void idle_thread(void)
{
    while (1) {
        asm volatile("hlt");
    }
}

/** DONT_TRANSLATE */
void VISIBLE halt(void)
{
    /* halt is actually, idle thread without the interrupts */
    asm volatile("cli");

#ifdef CONFIG_PRINTING
    printf("halting...");
#ifdef CONFIG_DEBUG_BUILD
    debug_printKernelEntryReason();
#endif
#endif
    idle_thread();
    UNREACHABLE();
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/kernel/apic.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <machine/io.h>
#include <arch/machine.h>
#include <arch/kernel/apic.h>
#include <linker.h>
#include <plat/machine/devices.h>
#include <plat/machine/pit.h>

static BOOT_CODE uint32_t
apic_measure_freq(void)
{
    pit_init();
    /* wait for 1st PIT wraparound */
    pit_wait_wraparound();

    /* start APIC timer countdown */
    apic_write_reg(APIC_TIMER_DIVIDE, 0xb); /* divisor = 1 */
    apic_write_reg(APIC_TIMER_COUNT, 0xffffffff);

    /* wait for 2nd PIT wraparound */
    pit_wait_wraparound();

    /* calculate APIC/bus cycles per ms = frequency in kHz */
    return (0xffffffff - apic_read_reg(APIC_TIMER_CURRENT)) / PIT_WRAPAROUND_MS;
}

BOOT_CODE paddr_t
apic_get_base_paddr(void)
{
    apic_base_msr_t apic_base_msr;

    apic_base_msr.words[0] = x86_rdmsr_low(IA32_APIC_BASE_MSR);
    return apic_base_msr_get_base_addr(apic_base_msr);
}

BOOT_CODE bool_t
apic_init(bool_t mask_legacy_irqs)
{
    apic_version_t apic_version;
    uint32_t num_lvt_entries;
    uint32_t apic_khz;

    if (!apic_enable()) {
        return false;
    }

    apic_khz = apic_measure_freq();

    apic_version.words[0] = apic_read_reg(APIC_VERSION);

    /* check for correct version (both APIC and x2APIC): 0x1X */
    if (apic_version_get_version(apic_version) >> 4 != 1) {
        printf("APIC: apic_version must be 0x1X\n");
        return false;
    }

    /* check for correct number of LVT entries */
    num_lvt_entries = apic_version_get_max_lvt_entry(apic_version) + 1;
    if (num_lvt_entries < 3) {
        printf("APIC: number of LVT entries: %d\n", num_lvt_entries);
        printf("APIC: number of LVT entries must be >= 3\n");
        return false;
    }

    /* initialise APIC timer */
    apic_write_reg(APIC_TIMER_DIVIDE, 0xb); /* divisor = 1 */
    apic_write_reg(APIC_TIMER_COUNT, apic_khz * CONFIG_TIMER_TICK_MS);

    /* enable APIC using SVR register */
    apic_write_reg(
        APIC_SVR,
        apic_svr_new(
            0,           /* focus_processor_chk */
            1,           /* enabled             */
            int_spurious /* spurious_vector     */
        ).words[0]
    );

    /* mask/unmask LINT0 (used for legacy IRQ delivery) */
    apic_write_reg(
        APIC_LVT_LINT0,
        apic_lvt_new(
            0,                /* timer_mode      */
            mask_legacy_irqs, /* masked          */
            0,                /* trigger_mode    */
            0,                /* remote_irr      */
            0,                /* pin_polarity    */
            0,                /* delivery_status */
            7,                /* delivery_mode   */
            0                 /* vector          */
        ).words[0]
    );

    /* mask LINT1 (used for NMI delivery) */
    apic_write_reg(
        APIC_LVT_LINT1,
        apic_lvt_new(
            0,  /* timer_mode      */
            1,  /* masked          */
            0,  /* trigger_mode    */
            0,  /* remote_irr      */
            0,  /* pin_polarity    */
            0,  /* delivery_status */
            0,  /* delivery_mode   */
            0   /* vector          */
        ).words[0]
    );

    /* initialise timer */
    apic_write_reg(
        APIC_LVT_TIMER,
        apic_lvt_new(
            1,        /* timer_mode      */
            0,        /* masked          */
            0,        /* trigger_mode    */
            0,        /* remote_irr      */
            0,        /* pin_polarity    */
            0,        /* delivery_status */
            0,        /* delivery_mode   */
            int_timer /* vector          */
        ).words[0]
    );

    /*
    printf("APIC: ID=0x%x\n", apic_read_reg(APIC_ID) >> 24);
    printf("APIC: SVR=0x%x\n", apic_read_reg(APIC_SVR));
    printf("APIC: LVT_TIMER=0x%x\n", apic_read_reg(APIC_LVT_TIMER));
    printf("APIC: LVT_LINT0=0x%x\n", apic_read_reg(APIC_LVT_LINT0));
    printf("APIC: LVT_LINT1=0x%x\n", apic_read_reg(APIC_LVT_LINT1));
    printf("APIC: LVT_ERROR=0x%x\n", apic_read_reg(APIC_LVT_ERROR));
    printf("APIC: LVT_PERF_CNTR=0x%x\n", apic_read_reg(APIC_LVT_PERF_CNTR));
    printf("APIC: LVT_THERMAL=0x%x\n", apic_read_reg(APIC_LVT_THERMAL));
    */
    return true;
}

void apic_ack_active_interrupt(void)
{
    apic_write_reg(APIC_EOI, 0);
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/kernel/boot.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <kernel/boot.h>
#include <machine/io.h>
#include <model/statedata.h>
#include <object/interrupt.h>
#include <arch/object/interrupt.h>
#include <arch/machine.h>
#include <arch/kernel/apic.h>
#include <arch/kernel/boot.h>
#include <arch/kernel/boot_sys.h>
#include <arch/kernel/vspace.h>
#include <machine/fpu.h>
#include <arch/machine/timer.h>
#include <arch/object/ioport.h>
#include <linker.h>
#include <util.h>

#include <plat/machine/intel-vtd.h>

/* functions exactly corresponding to abstract specification */

BOOT_CODE static void
init_irqs(cap_t root_cnode_cap)
{
    irq_t i;

    for (i = 0; i <= maxIRQ; i++) {
        if (i == irq_timer) {
            setIRQState(IRQTimer, i);
#ifdef ENABLE_SMP_SUPPORT
        } else if (i == irq_remote_call_ipi || i == irq_reschedule_ipi) {
            setIRQState(IRQIPI, i);
#endif /* ENABLE_SMP_SUPPORT */
#ifdef CONFIG_IOMMU
        } else if (i == irq_iommu) {
            setIRQState(IRQReserved, i);
#endif
        } else if (i == 2 && config_set(CONFIG_IRQ_PIC)) {
            /* cascaded legacy PIC */
            setIRQState(IRQReserved, i);
        } else if (i >= irq_isa_min && i <= irq_isa_max) {
            if (config_set(CONFIG_IRQ_PIC)) {
                setIRQState(IRQInactive, i);
            } else {
                setIRQState(IRQReserved, i);
            }
        } else if (i >= irq_user_min && i <= irq_user_max) {
            if (config_set(CONFIG_IRQ_IOAPIC)) {
                setIRQState(IRQInactive, i);
            } else {
                setIRQState(IRQReserved, i);
            }
        } else {
            setIRQState(IRQReserved, i);
        }
    }
    Arch_irqStateInit();
    /* provide the IRQ control cap */
    write_slot(SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapIRQControl), cap_irq_control_cap_new());
}

/* The maximum number of reserved regions we have is 1 for each physical memory region (+ MAX_NUM_FREEMEM_REG)
 * plus 1 for each kernel device. For kernel devices we have the ioapics (+ CONFIG_MAX_NUM_IOAPIC),
 * iommus (+ MAX_NUM_DRHU), apic (+ 1) and the reserved MSI region (+ 1) */
#define NUM_RESERVED_REGIONS    (MAX_NUM_FREEMEM_REG + CONFIG_MAX_NUM_IOAPIC + MAX_NUM_DRHU + 2)
typedef struct allocated_p_region {
    p_region_t  regs[NUM_RESERVED_REGIONS];
    word_t      cur_pos;
} allocated_p_region_t;

BOOT_BSS static allocated_p_region_t allocated_p_regions;

BOOT_CODE static void
merge_regions(void)
{
    unsigned int i, j;
    /* Walk through all the regions and see if any can get merged */
    for (i = 1; i < allocated_p_regions.cur_pos;) {
        if (allocated_p_regions.regs[i - 1].end == allocated_p_regions.regs[i].start) {
            /* move this down */
            allocated_p_regions.regs[i - 1].end = allocated_p_regions.regs[i].end;
            /* fill the rest down */
            for (j = i; j < allocated_p_regions.cur_pos - 1; j++) {
                allocated_p_regions.regs[j] = allocated_p_regions.regs[j + 1];
            }
            allocated_p_regions.cur_pos--;
            /* don't increment 'i' since we want to recheck that the
             * region we just moved to this slot doesn't also need merging */
        } else {
            i++;
        }
    }
}

static UNUSED BOOT_CODE bool_t p_region_overlaps(p_region_t reg)
{
    unsigned int i;
    for (i = 0; i < allocated_p_regions.cur_pos; i++) {
        if (allocated_p_regions.regs[i].start < reg.end &&
                allocated_p_regions.regs[i].end > reg.start) {
            return true;
        }
    }
    return false;
}

BOOT_CODE bool_t
add_allocated_p_region(p_region_t reg)
{
    unsigned int i, j;

    assert(reg.start <= reg.end);
    assert(!p_region_overlaps(reg));

    /* Walk the existing regions and see if we can merge with an existing
     * region, or insert in order */
    for (i = 0; i < allocated_p_regions.cur_pos; i++) {
        /* see if we can merge before or after this region */
        if (allocated_p_regions.regs[i].end == reg.start) {
            allocated_p_regions.regs[i].end = reg.end;
            merge_regions();
            return true;
        }
        if (allocated_p_regions.regs[i].start == reg.end) {
            allocated_p_regions.regs[i].start = reg.start;
            merge_regions();
            return true;
        }
        /* see if this new one should be inserted before */
        if (reg.end < allocated_p_regions.regs[i].start) {
            /* ensure there's space to bump the regions up */
            if (allocated_p_regions.cur_pos + 1 == NUM_RESERVED_REGIONS) {
                printf("Ran out of reserved physical regions\n");
                return false;
            }
            /* Copy the regions up to make a gap */
            for (j = allocated_p_regions.cur_pos; j != i; j--) {
                allocated_p_regions.regs[j] = allocated_p_regions.regs[j - 1];
            }
            /* Put this region in the gap */
            allocated_p_regions.regs[i] = reg;
            allocated_p_regions.cur_pos++;
            return true;
        }
    }

    /* nothing else matched, put this one at the end */
    if (i + 1 == NUM_RESERVED_REGIONS) {
        printf("Ran out of reserved physical regions\n");
        return false;
    }
    allocated_p_regions.regs[i] = reg;
    allocated_p_regions.cur_pos = i + 1;
    return true;
}

BOOT_CODE void
init_allocated_p_regions()
{
    allocated_p_regions.cur_pos = 0;
}

BOOT_CODE static bool_t
create_untypeds(
    cap_t root_cnode_cap,
    region_t boot_mem_reuse_reg)
{
    seL4_SlotPos     slot_pos_before;
    seL4_SlotPos     slot_pos_after;
    word_t      i;

    paddr_t     start = 0;

    slot_pos_before = ndks_boot.slot_pos_cur;
    create_kernel_untypeds(root_cnode_cap, boot_mem_reuse_reg, slot_pos_before);

    for (i = 0; i < allocated_p_regions.cur_pos; i++) {
        if (start != allocated_p_regions.regs[i].start) {
            if (!create_untypeds_for_region(root_cnode_cap, true,
            paddr_to_pptr_reg((p_region_t) {
            start, allocated_p_regions.regs[i].start
            }),
            slot_pos_before)) {
                return false;
            }
        }
        start = allocated_p_regions.regs[i].end;
    }

    if (start != PADDR_USER_DEVICE_TOP) {
        if (!create_untypeds_for_region(root_cnode_cap, true,
        paddr_to_pptr_reg((p_region_t) {
        start, PADDR_USER_DEVICE_TOP
    }),
    slot_pos_before)) {
            return false;
        }
    }

    slot_pos_after = ndks_boot.slot_pos_cur;
    ndks_boot.bi_frame->untyped = (seL4_SlotRegion) {
        slot_pos_before, slot_pos_after
    };
    return true;
}

BOOT_CODE static void
init_freemem(p_region_t ui_p_reg, mem_p_regs_t mem_p_regs)
{
    word_t i;
    /* we are guaranteed that we started loading the user image after the kernel
     * so we only include addresses above ui_info.p_reg.end */
    pptr_t floor = ui_p_reg.end;
    for (i = 0; i < MAX_NUM_FREEMEM_REG; i++) {
        ndks_boot.freemem[i] = REG_EMPTY;
    }
    for (i = 0; i < mem_p_regs.count; i++) {
        pptr_t start = mem_p_regs.list[i].start;
        pptr_t end = mem_p_regs.list[i].end;
        if (start < floor) {
            start = floor;
        }
        if (end < floor) {
            end = floor;
        }
        insert_region(paddr_to_pptr_reg((p_region_t) {
            start, end
        }));
    }
}

/* This function initialises a node's kernel state. It does NOT initialise the CPU. */

BOOT_CODE bool_t
init_sys_state(
    cpu_id_t      cpu_id,
    mem_p_regs_t  mem_p_regs,
    ui_info_t     ui_info,
    p_region_t    boot_mem_reuse_p_reg,
    /* parameters below not modeled in abstract specification */
    uint32_t      num_drhu,
    paddr_t*      drhu_list,
    acpi_rmrr_list_t *rmrr_list,
    acpi_rsdp_t      *acpi_rsdp,
    seL4_X86_BootInfo_VBE *vbe,
    seL4_X86_BootInfo_mmap_t *mb_mmap,
    seL4_X86_BootInfo_fb_t *fb_info
)
{
    cap_t         root_cnode_cap;
    vptr_t        extra_bi_frame_vptr;
    vptr_t        bi_frame_vptr;
    vptr_t        ipcbuf_vptr;
    cap_t         it_vspace_cap;
    cap_t         it_ap_cap;
    cap_t         ipcbuf_cap;
    pptr_t        bi_frame_pptr;
    word_t        extra_bi_size = sizeof(seL4_BootInfoHeader);
    region_t      extra_bi_region;
    pptr_t        extra_bi_offset = 0;
    uint32_t      tsc_freq;
    create_frames_of_region_ret_t create_frames_ret;
    create_frames_of_region_ret_t extra_bi_ret;

    /* convert from physical addresses to kernel pptrs */
    region_t ui_reg             = paddr_to_pptr_reg(ui_info.p_reg);
    region_t boot_mem_reuse_reg = paddr_to_pptr_reg(boot_mem_reuse_p_reg);

    /* convert from physical addresses to userland vptrs */
    v_region_t ui_v_reg;
    v_region_t it_v_reg;
    ui_v_reg.start = ui_info.p_reg.start - ui_info.pv_offset;
    ui_v_reg.end   = ui_info.p_reg.end   - ui_info.pv_offset;

    ipcbuf_vptr = ui_v_reg.end;
    bi_frame_vptr = ipcbuf_vptr + BIT(PAGE_BITS);
    extra_bi_frame_vptr = bi_frame_vptr + BIT(PAGE_BITS);

    if (vbe->vbeMode != -1) {
        extra_bi_size += sizeof(seL4_X86_BootInfo_VBE);
    }
    if (acpi_rsdp) {
        extra_bi_size += sizeof(seL4_BootInfoHeader) + sizeof(*acpi_rsdp);
    }
    if (fb_info && fb_info->addr) {
        extra_bi_size += sizeof(seL4_BootInfoHeader) + sizeof(*fb_info);
    }

    word_t mb_mmap_size = sizeof(seL4_X86_BootInfo_mmap_t);
    extra_bi_size += mb_mmap_size;

    // room for tsc frequency
    extra_bi_size += sizeof(seL4_BootInfoHeader) + 4;

    /* The region of the initial thread is the user image + ipcbuf and boot info */
    it_v_reg.start = ui_v_reg.start;
    it_v_reg.end = ROUND_UP(extra_bi_frame_vptr + extra_bi_size, PAGE_BITS);

    init_freemem(ui_info.p_reg, mem_p_regs);

    /* create the root cnode */
    root_cnode_cap = create_root_cnode();

    /* create the IO port cap */
    write_slot(
        SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapIOPortControl),
        cap_io_port_control_cap_new()
    );

    /* create the cap for managing thread domains */
    create_domain_cap(root_cnode_cap);

    /* create the IRQ CNode */
    if (!create_irq_cnode()) {
        return false;
    }

    /* initialise the IRQ states and provide the IRQ control cap */
    init_irqs(root_cnode_cap);

    tsc_freq = tsc_init();

    /* create the bootinfo frame */
    bi_frame_pptr = allocate_bi_frame(0, ksNumCPUs, ipcbuf_vptr);
    if (!bi_frame_pptr) {
        return false;
    }

    extra_bi_region = allocate_extra_bi_region(extra_bi_size);
    if (extra_bi_region.start == 0) {
        return false;
    }

    /* populate vbe info block */
    if (vbe->vbeMode != -1) {
        vbe->header.id = SEL4_BOOTINFO_HEADER_X86_VBE;
        vbe->header.len = sizeof(seL4_X86_BootInfo_VBE);
        memcpy((void*)(extra_bi_region.start + extra_bi_offset), vbe, sizeof(seL4_X86_BootInfo_VBE));
        extra_bi_offset += sizeof(seL4_X86_BootInfo_VBE);
    }

    /* populate acpi rsdp block */
    if (acpi_rsdp) {
        seL4_BootInfoHeader header;
        header.id = SEL4_BOOTINFO_HEADER_X86_ACPI_RSDP;
        header.len = sizeof(header) + sizeof(*acpi_rsdp);
        *(seL4_BootInfoHeader*)(extra_bi_region.start + extra_bi_offset) = header;
        extra_bi_offset += sizeof(header);
        memcpy((void*)(extra_bi_region.start + extra_bi_offset), acpi_rsdp, sizeof(*acpi_rsdp));
        extra_bi_offset += sizeof(*acpi_rsdp);
    }

    /* populate framebuffer information block */
    if (fb_info && fb_info->addr) {
        seL4_BootInfoHeader header;
        header.id = SEL4_BOOTINFO_HEADER_X86_FRAMEBUFFER;
        header.len = sizeof(header) + sizeof(*fb_info);
        *(seL4_BootInfoHeader*)(extra_bi_region.start + extra_bi_offset) = header;
        extra_bi_offset += sizeof(header);
        memcpy((void*)(extra_bi_region.start + extra_bi_offset), fb_info, sizeof(*fb_info));
        extra_bi_offset += sizeof(*fb_info);
    }

    /* populate multiboot mmap block */
    mb_mmap->header.id = SEL4_BOOTINFO_HEADER_X86_MBMMAP;
    mb_mmap->header.len = mb_mmap_size;
    memcpy((void*)(extra_bi_region.start + extra_bi_offset), mb_mmap, mb_mmap_size);
    extra_bi_offset += mb_mmap_size;

    /* populate tsc frequency block */
    {
        seL4_BootInfoHeader header;
        header.id = SEL4_BOOTINFO_HEADER_X86_TSC_FREQ;
        header.len = sizeof(header) + 4;
        *(seL4_BootInfoHeader*)(extra_bi_region.start + extra_bi_offset) = header;
        extra_bi_offset += sizeof(header);
        *(uint32_t*)(extra_bi_region.start + extra_bi_offset) = tsc_freq;
        extra_bi_offset += 4;
    }

    /* provde a chunk for any leftover padding in the extended boot info */
    seL4_BootInfoHeader padding_header;
    padding_header.id = SEL4_BOOTINFO_HEADER_PADDING;
    padding_header.len = (extra_bi_region.end - extra_bi_region.start) - extra_bi_offset;
    *(seL4_BootInfoHeader*)(extra_bi_region.start + extra_bi_offset) = padding_header;

    /* Construct an initial address space with enough virtual addresses
     * to cover the user image + ipc buffer and bootinfo frames */
    it_vspace_cap = create_it_address_space(root_cnode_cap, it_v_reg);
    if (cap_get_capType(it_vspace_cap) == cap_null_cap) {
        return false;
    }

    /* Create and map bootinfo frame cap */
    create_bi_frame_cap(
        root_cnode_cap,
        it_vspace_cap,
        bi_frame_pptr,
        bi_frame_vptr
    );

    /* create and map extra bootinfo region */
    extra_bi_ret =
        create_frames_of_region(
            root_cnode_cap,
            it_vspace_cap,
            extra_bi_region,
            true,
            pptr_to_paddr((void*)(extra_bi_region.start - extra_bi_frame_vptr))
        );
    if (!extra_bi_ret.success) {
        return false;
    }
    ndks_boot.bi_frame->extraBIPages = extra_bi_ret.region;

    /* create the initial thread's IPC buffer */
    ipcbuf_cap = create_ipcbuf_frame(root_cnode_cap, it_vspace_cap, ipcbuf_vptr);
    if (cap_get_capType(ipcbuf_cap) == cap_null_cap) {
        return false;
    }

    /* create all userland image frames */
    create_frames_ret =
        create_frames_of_region(
            root_cnode_cap,
            it_vspace_cap,
            ui_reg,
            true,
            ui_info.pv_offset
        );
    if (!create_frames_ret.success) {
        return false;
    }
    ndks_boot.bi_frame->userImageFrames = create_frames_ret.region;

    /* create the initial thread's ASID pool */
    it_ap_cap = create_it_asid_pool(root_cnode_cap);
    if (cap_get_capType(it_ap_cap) == cap_null_cap) {
        return false;
    }
    write_it_asid_pool(it_ap_cap, it_vspace_cap);

    /* create the idle thread */
    if (!create_idle_thread()) {
        return false;
    }

    /* create the initial thread */
    tcb_t *initial = create_initial_thread(root_cnode_cap,
                                           it_vspace_cap,
                                           ui_info.v_entry,
                                           bi_frame_vptr,
                                           ipcbuf_vptr,
                                           ipcbuf_cap);
    if (initial == NULL) {
        return false;
    }
    init_core_state(initial);

#ifdef CONFIG_IOMMU
    /* initialise VTD-related data structures and the IOMMUs */
    if (!vtd_init(cpu_id, num_drhu, rmrr_list)) {
        return false;
    }

    /* write number of IOMMU PT levels into bootinfo */
    ndks_boot.bi_frame->numIOPTLevels = x86KSnumIOPTLevels;

    /* write IOSpace master cap */
    write_slot(SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapIOSpace), master_iospace_cap());
#else
    ndks_boot.bi_frame->numIOPTLevels = -1;
#endif

    /* create all of the untypeds. Both devices and kernel window memory */
    if (!create_untypeds(root_cnode_cap, boot_mem_reuse_reg)) {
        return false;
    }
    /* WARNING: alloc_region() must not be called anymore after here! */

    /* finalise the bootinfo frame */
    bi_finalise();

    return true;
}

/* This function initialises the CPU. It does NOT initialise any kernel state. */

BOOT_CODE bool_t
init_cpu(
    bool_t   mask_legacy_irqs
)
{
    /* initialise virtual-memory-related data structures */
    if (!init_vm_state()) {
        return false;
    }

    /* initialise CPU's descriptor table registers (GDTR, IDTR, LDTR, TR) */
    init_dtrs();

    if (config_set(CONFIG_SYSENTER)) {
        /* initialise MSRs (needs an initialised TSS) */
        init_sysenter_msrs();
    } else if (config_set(CONFIG_SYSCALL)) {
        init_syscall_msrs();
    } else {
        return false;
    }

    /* setup additional PAT MSR */
    if (!init_pat_msr()) {
        return false;
    }

    /* enable the Write Protect bit in cr0. This prevents the kernel from writing to
     * read only memory, which we shouldn't do under correct execution */
    write_cr0(read_cr0() | CR0_WRITE_PROTECT);

    /* check for SMAP and SMEP and enable */
    cpuid_007h_ebx_t ebx_007;
    ebx_007.words[0] = x86_cpuid_ebx(0x7, 0);
    if (cpuid_007h_ebx_get_smap(ebx_007)) {
        /* if we have user stack trace enabled or dangerous code injection then we cannot
         * enable this as SMAP will make them fault. */
        if (!config_set(CONFIG_PRINTING) && !config_set(CONFIG_DANGEROUS_CODE_INJECTION)) {
            write_cr4(read_cr4() | CR4_SMAP);
        }
    }
    if (cpuid_007h_ebx_get_smep(ebx_007)) {
        /* similar to smap we cannot enable smep if using dangerous code injection. it
         * does not affect stack trace printing though */
        if (!config_set(CONFIG_DANGEROUS_CODE_INJECTION)) {
            write_cr4(read_cr4() | CR4_SMEP);
        }
    }

    if (!init_ibrs()) {
        return false;
    }

#ifdef CONFIG_HARDWARE_DEBUG_API
    /* Initialize hardware breakpoints */
    Arch_initHardwareBreakpoints();
#endif

    /* initialise floating-point unit */
    if (!Arch_initFpu()) {
        return false;
    }

    /* initialise local APIC */
    if (!apic_init(mask_legacy_irqs)) {
        return false;
    }

#ifdef CONFIG_DEBUG_DISABLE_PREFETCHERS
    if (!disablePrefetchers()) {
        return false;
    }
#endif

    if (config_set(CONFIG_EXPORT_PMC_USER)) {
        enablePMCUser();
    }

#ifdef CONFIG_VTX
    /* initialise Intel VT-x extensions */
    if (!vtx_init()) {
        return false;
    }
#endif

    return true;
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/kernel/boot_sys.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <util.h>
#include <machine/io.h>
#include <arch/machine.h>
#include <arch/kernel/apic.h>
#include <arch/kernel/cmdline.h>
#include <arch/kernel/boot.h>
#include <arch/kernel/boot_sys.h>
#include <arch/kernel/smp_sys.h>
#include <arch/kernel/vspace.h>
#include <arch/kernel/elf.h>
#include <smp/lock.h>
#include <linker.h>
#include <plat/machine/acpi.h>
#include <plat/machine/devices.h>
#include <plat/machine/pic.h>
#include <plat/machine/ioapic.h>
#include <arch/api/bootinfo_types.h>

/* addresses defined in linker script */
/* need a fake array to get the pointer from the linker script */

/* start/end of CPU boot code */
extern char boot_cpu_start[1];
extern char boot_cpu_end[1];

/* start/end of boot stack */
extern char boot_stack_bottom[1];
extern char boot_stack_top[1];

/* locations in kernel image */
extern char ki_boot_end[1];
extern char ki_end[1];
extern char ki_skim_start[1];
extern char ki_skim_end[1];

#ifdef CONFIG_PRINTING
/* kernel entry point */
extern char _start[1];
#endif

/* constants */

#define HIGHMEM_PADDR 0x100000

/* type definitions (directly corresponding to abstract specification) */

typedef struct boot_state {
    p_region_t   avail_p_reg; /* region of available physical memory on platform */
    p_region_t   ki_p_reg;    /* region where the kernel image is in */
    ui_info_t    ui_info;     /* info about userland images */
    uint32_t     num_ioapic;  /* number of IOAPICs detected */
    paddr_t      ioapic_paddr[CONFIG_MAX_NUM_IOAPIC];
    uint32_t     num_drhu; /* number of IOMMUs */
    paddr_t      drhu_list[MAX_NUM_DRHU]; /* list of physical addresses of the IOMMUs */
    acpi_rmrr_list_t rmrr_list;
    acpi_rsdp_t  acpi_rsdp; /* copy of the rsdp */
    paddr_t      mods_end_paddr; /* physical address where boot modules end */
    paddr_t      boot_module_start; /* physical address of first boot module */
    uint32_t     num_cpus;    /* number of detected cpus */
    uint32_t     mem_lower;   /* lower memory size for boot code of APs to run in real mode */
    cpu_id_t     cpus[CONFIG_MAX_NUM_NODES];
    mem_p_regs_t mem_p_regs;  /* physical memory regions */
    seL4_X86_BootInfo_VBE vbe_info; /* Potential VBE information from multiboot */
    seL4_X86_BootInfo_mmap_t mb_mmap_info; /* memory map information from multiboot */
    seL4_X86_BootInfo_fb_t fb_info; /* framebuffer information as set by bootloader */
} boot_state_t;

BOOT_BSS
boot_state_t boot_state;

/* global variables (not covered by abstract specification) */

BOOT_BSS
cmdline_opt_t cmdline_opt;

/* check the module occupies in a contiguous physical memory region */
BOOT_CODE static bool_t
module_paddr_region_valid(paddr_t pa_start, paddr_t pa_end)
{
    int i = 0;
    for (i = 0; i < boot_state.mem_p_regs.count; i++) {
        paddr_t start = boot_state.mem_p_regs.list[i].start;
        paddr_t end = boot_state.mem_p_regs.list[i].end;
        if (pa_start >= start && pa_end < end) {
            return true;
        }
    }
    return false;
}

/* functions not modeled in abstract specification */

BOOT_CODE static paddr_t
find_load_paddr(paddr_t min_paddr, word_t image_size)
{
    int i;

    for (i = 0; i < boot_state.mem_p_regs.count; i++) {
        paddr_t start = MAX(min_paddr, boot_state.mem_p_regs.list[i].start);
        paddr_t end = boot_state.mem_p_regs.list[i].end;
        word_t region_size = end - start;

        if (region_size >= image_size) {
            return start;
        }
    }

    return 0;
}

BOOT_CODE static paddr_t
load_boot_module(word_t boot_module_start, paddr_t load_paddr)
{
    v_region_t v_reg;
    word_t entry;
    Elf_Header_t* elf_file = (Elf_Header_t*)boot_module_start;

    if (!elf_checkFile(elf_file)) {
        printf("Boot module does not contain a valid ELF image\n");
        return 0;
    }

    v_reg = elf_getMemoryBounds(elf_file);
    entry = elf_file->e_entry;

    if (v_reg.end == 0) {
        printf("ELF image in boot module does not contain any segments\n");
        return 0;
    }
    v_reg.end = ROUND_UP(v_reg.end, PAGE_BITS);

    printf("size=0x%lx v_entry=%p v_start=%p v_end=%p ",
           v_reg.end - v_reg.start,
           (void*)entry,
           (void*)v_reg.start,
           (void*)v_reg.end
          );

    if (!IS_ALIGNED(v_reg.start, PAGE_BITS)) {
        printf("Userland image virtual start address must be 4KB-aligned\n");
        return 0;
    }
    if (v_reg.end + 2 * BIT(PAGE_BITS) > PPTR_USER_TOP) {
        /* for IPC buffer frame and bootinfo frame, need 2*4K of additional userland virtual memory */
        printf("Userland image virtual end address too high\n");
        return 0;
    }
    if ((entry < v_reg.start) || (entry >= v_reg.end)) {
        printf("Userland image entry point does not lie within userland image\n");
        return 0;
    }

    load_paddr = find_load_paddr(load_paddr, v_reg.end - v_reg.start);
    assert(load_paddr);

    /* fill ui_info struct */
    boot_state.ui_info.pv_offset = load_paddr - v_reg.start;
    boot_state.ui_info.p_reg.start = load_paddr;
    load_paddr += v_reg.end - v_reg.start;
    boot_state.ui_info.p_reg.end = load_paddr;
    boot_state.ui_info.v_entry = entry;

    printf("p_start=0x%lx p_end=0x%lx\n",
           boot_state.ui_info.p_reg.start,
           boot_state.ui_info.p_reg.end
          );

    if (!module_paddr_region_valid(
                boot_state.ui_info.p_reg.start,
                boot_state.ui_info.p_reg.end)) {
        printf("End of loaded userland image lies outside of usable physical memory\n");
        return 0;
    }

    /* initialise all initial userland memory and load potentially sparse ELF image */
    memzero(
        (void*)boot_state.ui_info.p_reg.start,
        boot_state.ui_info.p_reg.end - boot_state.ui_info.p_reg.start
    );
    elf_load(elf_file, boot_state.ui_info.pv_offset);

    return load_paddr;
}

static BOOT_CODE bool_t
try_boot_sys_node(cpu_id_t cpu_id)
{
    p_region_t boot_mem_reuse_p_reg;

    if (!map_kernel_window(
                boot_state.num_ioapic,
                boot_state.ioapic_paddr,
                boot_state.num_drhu,
                boot_state.drhu_list
            )) {
        return false;
    }
    setCurrentVSpaceRoot(kpptr_to_paddr(X86_KERNEL_VSPACE_ROOT), 0);
    /* Sync up the compilers view of the world here to force the PD to actually
     * be set *right now* instead of delayed */
    asm volatile("" ::: "memory");

#ifdef CONFIG_KERNEL_SKIM_WINDOW
    if (!map_skim_window((vptr_t)ki_skim_start, (vptr_t)ki_skim_end)) {
        return false;
    }
#endif

    /* reuse boot code/data memory */
    boot_mem_reuse_p_reg.start = PADDR_LOAD;
    boot_mem_reuse_p_reg.end = (paddr_t)ki_boot_end - KERNEL_BASE_OFFSET;

    /* initialise the CPU */
    if (!init_cpu(config_set(CONFIG_IRQ_IOAPIC) ? 1 : 0)) {
        return false;
    }

    /* initialise NDKS and kernel heap */
    if (!init_sys_state(
                cpu_id,
                boot_state.mem_p_regs,
                boot_state.ui_info,
                boot_mem_reuse_p_reg,
                /* parameters below not modeled in abstract specification */
                boot_state.num_drhu,
                boot_state.drhu_list,
                &boot_state.rmrr_list,
                &boot_state.acpi_rsdp,
                &boot_state.vbe_info,
                &boot_state.mb_mmap_info,
                &boot_state.fb_info
            )) {
        return false;
    }

    return true;
}

static BOOT_CODE bool_t
add_mem_p_regs(p_region_t reg)
{
    if (reg.end > PADDR_TOP) {
        reg.end = PADDR_TOP;
    }
    if (reg.start > PADDR_TOP) {
        reg.start = PADDR_TOP;
    }
    if (reg.start == reg.end) {
        /* Return true here as it's not an error for there to exist memory outside the kernel window,
         * we're just going to ignore it and leave it to be given out as device memory */
        return true;
    }
    if (boot_state.mem_p_regs.count == MAX_NUM_FREEMEM_REG) {
        printf("Dropping memory region 0x%lx-0x%lx, try increasing MAX_NUM_FREEMEM_REG\n", reg.start, reg.end);
        return false;
    }
    printf("Adding physical memory region 0x%lx-0x%lx\n", reg.start, reg.end);
    boot_state.mem_p_regs.list[boot_state.mem_p_regs.count] = reg;
    boot_state.mem_p_regs.count++;
    return add_allocated_p_region(reg);
}

/*
 * the code relies that the GRUB provides correct information
 * about the actual physical memory regions.
 */
static BOOT_CODE bool_t
parse_mem_map(uint32_t mmap_length, uint32_t mmap_addr)
{
    multiboot_mmap_t *mmap = (multiboot_mmap_t *)((word_t)mmap_addr);
    printf("Parsing GRUB physical memory map\n");

    while ((word_t)mmap < (word_t)(mmap_addr + mmap_length)) {
        uint64_t mem_start = mmap->base_addr;
        uint64_t mem_length = mmap->length;
        uint32_t type = mmap->type;
        if (mem_start != (uint64_t)(word_t)mem_start) {
            printf("\tPhysical memory region not addressable\n");
        } else {
            printf("\tPhysical Memory Region from %lx size %lx type %d\n", (long)mem_start, (long)mem_length, type);
            if (type == MULTIBOOT_MMAP_USEABLE_TYPE && mem_start >= HIGHMEM_PADDR) {
                if (!add_mem_p_regs((p_region_t) {
                mem_start, mem_start + mem_length
            })) {
                    return false;
                }
            }
        }
        mmap++;
    }
    return true;
}

static BOOT_CODE bool_t
is_compiled_for_microarchitecture(void)
{
    word_t microarch_generation = 0;
    x86_cpu_identity_t *model_info = x86_cpuid_get_model_info();

    if (config_set(CONFIG_ARCH_X86_SKYLAKE) ) {
        microarch_generation = 7;
    } else if (config_set(CONFIG_ARCH_X86_BROADWELL) ) {
        microarch_generation = 6;
    } else if (config_set(CONFIG_ARCH_X86_HASWELL) ) {
        microarch_generation = 5;
    } else if (config_set(CONFIG_ARCH_X86_IVY) ) {
        microarch_generation = 4;
    } else if (config_set(CONFIG_ARCH_X86_SANDY) ) {
        microarch_generation = 3;
    } else if (config_set(CONFIG_ARCH_X86_WESTMERE) ) {
        microarch_generation = 2;
    } else if (config_set(CONFIG_ARCH_X86_NEHALEM) ) {
        microarch_generation = 1;
    }

    switch (model_info->model) {
    case SKYLAKE_1_MODEL_ID:
    case SKYLAKE_2_MODEL_ID:
        if (microarch_generation > 7) {
            return false;
        }
        break;

    case BROADWELL_1_MODEL_ID:
    case BROADWELL_2_MODEL_ID:
    case BROADWELL_3_MODEL_ID:
    case BROADWELL_4_MODEL_ID:
    case BROADWELL_5_MODEL_ID:
        if (microarch_generation > 6) {
            return false;
        }
        break;

    case HASWELL_1_MODEL_ID:
    case HASWELL_2_MODEL_ID:
    case HASWELL_3_MODEL_ID:
    case HASWELL_4_MODEL_ID:
        if (microarch_generation > 5) {
            return false;
        }
        break;

    case IVY_BRIDGE_1_MODEL_ID:
    case IVY_BRIDGE_2_MODEL_ID:
    case IVY_BRIDGE_3_MODEL_ID:
        if (microarch_generation > 4) {
            return false;
        }
        break;

    case SANDY_BRIDGE_1_MODEL_ID:
    case SANDY_BRIDGE_2_MODEL_ID:
        if (microarch_generation > 3) {
            return false;
        }
        break;

    case WESTMERE_1_MODEL_ID:
    case WESTMERE_2_MODEL_ID:
    case WESTMERE_3_MODEL_ID:
        if (microarch_generation > 2) {
            return false;
        }
        break;

    case NEHALEM_1_MODEL_ID:
    case NEHALEM_2_MODEL_ID:
    case NEHALEM_3_MODEL_ID:
        if (microarch_generation > 1) {
            return false;
        }
        break;

    default:
        if (!config_set(CONFIG_ARCH_X86_GENERIC)) {
            return false;
        }
    }

    return true;
}

static BOOT_CODE bool_t
try_boot_sys(void)
{
    paddr_t mods_end_paddr = boot_state.mods_end_paddr;
    p_region_t ui_p_regs;
    paddr_t load_paddr;

    boot_state.ki_p_reg.start = PADDR_LOAD;
    boot_state.ki_p_reg.end = kpptr_to_paddr(ki_end);

    if (!x86_cpuid_initialize()) {
        printf("Warning: Your x86 CPU has an unsupported vendor, '%s'.\n"
               "\tYour setup may not be able to competently run seL4 as "
               "intended.\n"
               "\tCurrently supported x86 vendors are AMD and Intel.\n",
               x86_cpuid_get_identity()->vendor_string);
    }

    if (!is_compiled_for_microarchitecture()) {
        printf("Warning: Your kernel was not compiled for the current microarchitecture.\n");
    }

    cpuid_007h_edx_t edx;
    edx.words[0] = x86_cpuid_edx(0x7, 0);
    /* see if we can definitively say whether or not we need the skim window by
     * checking whether the CPU is vulnerable to rogue data cache loads (rdcl) */
    if (cpuid_007h_edx_get_ia32_arch_cap_msr(edx)) {
        ia32_arch_capabilities_msr_t cap_msr;
        cap_msr.words[0] = x86_rdmsr(IA32_ARCH_CAPABILITIES_MSR);
        if (ia32_arch_capabilities_msr_get_rdcl_no(cap_msr) && config_set(CONFIG_KERNEL_SKIM_WINDOW)) {
            printf("CPU reports not vulnerable to Rogue Data Cache Load (aka Meltdown https://meltdownattack.com) "
                   "yet SKIM window is enabled. Performance is needlessly being impacted, consider disabling.\n");
        } else if (!ia32_arch_capabilities_msr_get_rdcl_no(cap_msr) && !config_set(CONFIG_KERNEL_SKIM_WINDOW)) {
            printf("CPU reports vulnerable to Rogue Data Cache Load (aka Meltdown https://meltdownattack.com) "
                   "yet SKIM window is *not* enabled. Please re-build with SKIM window enabled.");
            return false;
        }
    } else {
        /* hardware doesn't tell us directly so guess based on CPU vendor */
        if (config_set(CONFIG_KERNEL_SKIM_WINDOW) && x86_cpuid_get_identity()->vendor == X86_VENDOR_AMD) {
            printf("SKIM window for mitigating Meltdown (https://www.meltdownattack.com) "
                   "not necessary for AMD and performance is being needlessly affected, "
                   "consider disabling\n");
        }
        if (!config_set(CONFIG_KERNEL_SKIM_WINDOW) && x86_cpuid_get_identity()->vendor == X86_VENDOR_INTEL) {
            printf("***WARNING*** SKIM window not enabled, this machine is probably vulnerable "
                   "to Meltdown (https://www.meltdownattack.com), consider enabling\n");
        }
    }

#ifdef ENABLE_SMP_SUPPORT
    /* copy boot code for APs to lower memory to run in real mode */
    if (!copy_boot_code_aps(boot_state.mem_lower)) {
        return false;
    }
    /* Initialize any kernel TLS */
    mode_init_tls(0);
#endif /* ENABLE_SMP_SUPPORT */

    printf("Kernel loaded to: start=0x%lx end=0x%lx size=0x%lx entry=0x%lx\n",
           boot_state.ki_p_reg.start,
           boot_state.ki_p_reg.end,
           boot_state.ki_p_reg.end - boot_state.ki_p_reg.start,
           (paddr_t)_start
          );

    /* remapping legacy IRQs to their correct vectors */
    pic_remap_irqs(IRQ_INT_OFFSET);
    if (config_set(CONFIG_IRQ_IOAPIC)) {
        /* Disable the PIC so that it does not generate any interrupts. We need to
         * do this *before* we initialize the apic */
        pic_disable();
    }

    /* validate the ACPI table */
    if (!acpi_validate_rsdp(&boot_state.acpi_rsdp)) {
        return false;
    }

    /* check if kernel configuration matches platform requirments */
    if (!acpi_fadt_scan(&boot_state.acpi_rsdp)) {
        return false;
    }

    if (!config_set(CONFIG_IOMMU) || cmdline_opt.disable_iommu) {
        boot_state.num_drhu = 0;
    } else {
        /* query available IOMMUs from ACPI */
        acpi_dmar_scan(
            &boot_state.acpi_rsdp,
            boot_state.drhu_list,
            &boot_state.num_drhu,
            MAX_NUM_DRHU,
            &boot_state.rmrr_list
        );
    }

    /* query available CPUs from ACPI */
    boot_state.num_cpus = acpi_madt_scan(&boot_state.acpi_rsdp, boot_state.cpus, &boot_state.num_ioapic, boot_state.ioapic_paddr);
    if (boot_state.num_cpus == 0) {
        printf("No CPUs detected\n");
        return false;
    }

    if (config_set(CONFIG_IRQ_IOAPIC)) {
        if (boot_state.num_ioapic == 0) {
            printf("No IOAPICs detected\n");
            return false;
        }
    } else {
        if (boot_state.num_ioapic > 0) {
            printf("Detected %d IOAPICs, but configured to use PIC instead\n", boot_state.num_ioapic);
        }
    }

    mods_end_paddr = ROUND_UP(mods_end_paddr, PAGE_BITS);
    assert(mods_end_paddr > boot_state.ki_p_reg.end);

    printf("ELF-loading userland images from boot modules:\n");
    load_paddr = mods_end_paddr;

    load_paddr = load_boot_module(boot_state.boot_module_start, load_paddr);
    if (!load_paddr) {
        return false;
    }

    /* calculate final location of userland images */
    ui_p_regs.start = boot_state.ki_p_reg.end;
    ui_p_regs.end = ui_p_regs.start + load_paddr - mods_end_paddr;

    printf(
        "Moving loaded userland images to final location: from=0x%lx to=0x%lx size=0x%lx\n",
        mods_end_paddr,
        ui_p_regs.start,
        ui_p_regs.end - ui_p_regs.start
    );
    memcpy((void*)ui_p_regs.start, (void*)mods_end_paddr, ui_p_regs.end - ui_p_regs.start);

    /* adjust p_reg and pv_offset to final load address */
    boot_state.ui_info.p_reg.start -= mods_end_paddr - ui_p_regs.start;
    boot_state.ui_info.p_reg.end   -= mods_end_paddr - ui_p_regs.start;
    boot_state.ui_info.pv_offset   -= mods_end_paddr - ui_p_regs.start;

    /* ==== following code corresponds to abstract specification after "select" ==== */

    if (!platAddDevices()) {
        return false;
    }

    /* Total number of cores we intend to boot */
    ksNumCPUs = boot_state.num_cpus;

    printf("Starting node #0 with APIC ID %lu\n", boot_state.cpus[0]);
    if (!try_boot_sys_node(boot_state.cpus[0])) {
        return false;
    }

    if (config_set(CONFIG_IRQ_IOAPIC)) {
        ioapic_init(1, boot_state.cpus, boot_state.num_ioapic);
    }

    /* initialize BKL before booting up APs */
    SMP_COND_STATEMENT(clh_lock_init());
    SMP_COND_STATEMENT(start_boot_aps());

    /* grab BKL before leaving the kernel */
    NODE_LOCK_SYS;

    printf("Booting all finished, dropped to user space\n");

    return true;
}

static BOOT_CODE bool_t
try_boot_sys_mbi1(
    multiboot_info_t* mbi
)
{
    word_t i;
    multiboot_module_t *modules = (multiboot_module_t*)(word_t)mbi->part1.mod_list;

    cmdline_parse((const char *)(word_t)mbi->part1.cmdline, &cmdline_opt);

    if ((mbi->part1.flags & MULTIBOOT_INFO_MEM_FLAG) == 0) {
        printf("Boot loader did not provide information about physical memory size\n");
        return false;
    }

    if (!(mbi->part1.flags & MULTIBOOT_INFO_MODS_FLAG)) {
        printf("Boot loader did not provide information about boot modules\n");
        return false;
    }

    printf("Detected %d boot module(s):\n", mbi->part1.mod_count);

    if (mbi->part1.mod_count < 1) {
        printf("Expect at least one boot module (containing a userland image)\n");
        return false;
    }

    for (i = 0; i < mbi->part1.mod_count; i++) {
        printf(
            "  module #%ld: start=0x%x end=0x%x size=0x%x name='%s'\n",
            i,
            modules[i].start,
            modules[i].end,
            modules[i].end - modules[i].start,
            (char *) (long)modules[i].name
        );
        if ((sword_t)(modules[i].end - modules[i].start) <= 0) {
            printf("Invalid boot module size! Possible cause: boot module file not found by QEMU\n");
            return false;
        }
        if (boot_state.mods_end_paddr < modules[i].end) {
            boot_state.mods_end_paddr = modules[i].end;
        }
    }

    /* initialize the memory. We track two kinds of memory regions. Physical memory
     * that we will use for the kernel, and physical memory regions that we must
     * not give to the user. Memory regions that must not be given to the user
     * include all the physical memory in the kernel window, but also includes any
     * important or kernel devices. */
    boot_state.mem_p_regs.count = 0;
    init_allocated_p_regions();
    if (mbi->part1.flags & MULTIBOOT_INFO_MMAP_FLAG) {
        if (!parse_mem_map(mbi->part2.mmap_length, mbi->part2.mmap_addr)) {
            return false;
        }
        uint32_t multiboot_mmap_length = mbi->part2.mmap_length;
        if (multiboot_mmap_length > (SEL4_MULTIBOOT_MAX_MMAP_ENTRIES * sizeof(seL4_X86_mb_mmap_t))) {
            multiboot_mmap_length = SEL4_MULTIBOOT_MAX_MMAP_ENTRIES * sizeof(seL4_X86_mb_mmap_t);
            printf("Warning: Multiboot has reported more memory map entries, %zd, "
                   "than the max amount that will be passed in the bootinfo, %d. "
                   "These extra regions will still be turned into untyped caps.",
                   multiboot_mmap_length / sizeof(seL4_X86_mb_mmap_t), SEL4_MULTIBOOT_MAX_MMAP_ENTRIES);
        }
        memcpy(&boot_state.mb_mmap_info.mmap, (void*)(word_t)mbi->part2.mmap_addr, multiboot_mmap_length);
        boot_state.mb_mmap_info.mmap_length = multiboot_mmap_length;
    } else {
        /* calculate memory the old way */
        p_region_t avail;
        avail.start = HIGHMEM_PADDR;
        avail.end = ROUND_DOWN(avail.start + (mbi->part1.mem_upper << 10), PAGE_BITS);
        if (!add_mem_p_regs(avail)) {
            return false;
        }
    }

    /* copy VESA information from multiboot header */
    if ((mbi->part1.flags & MULTIBOOT_INFO_GRAPHICS_FLAG) == 0) {
        boot_state.vbe_info.vbeMode = -1;
        printf("Multiboot gave us no video information\n");
    } else {
        boot_state.vbe_info.vbeInfoBlock = *(seL4_VBEInfoBlock_t*)(seL4_Word)mbi->part2.vbe_control_info;
        boot_state.vbe_info.vbeModeInfoBlock = *(seL4_VBEModeInfoBlock_t*)(seL4_Word)mbi->part2.vbe_mode_info;
        boot_state.vbe_info.vbeMode = mbi->part2.vbe_mode;
        printf("Got VBE info in multiboot. Current video mode is %d\n", mbi->part2.vbe_mode);
        boot_state.vbe_info.vbeInterfaceSeg = mbi->part2.vbe_interface_seg;
        boot_state.vbe_info.vbeInterfaceOff = mbi->part2.vbe_interface_off;
        boot_state.vbe_info.vbeInterfaceLen = mbi->part2.vbe_interface_len;
    }

    boot_state.mem_lower = mbi->part1.mem_lower;
    boot_state.boot_module_start = modules->start;

    /* Initialize ACPI */
    if (!acpi_init(&boot_state.acpi_rsdp)) {
        return false;
    }

    return true;
}

static BOOT_CODE bool_t
try_boot_sys_mbi2(
    multiboot2_header_t* mbi2
)
{
    int mod_count                  = 0;
    multiboot2_tag_t const * tag   = (multiboot2_tag_t *)(mbi2 + 1);
    multiboot2_tag_t const * tag_e = (multiboot2_tag_t *)((word_t)mbi2 + mbi2->total_size);

    /* initialize the memory. We track two kinds of memory regions. Physical memory
     * that we will use for the kernel, and physical memory regions that we must
     * not give to the user. Memory regions that must not be given to the user
     * include all the physical memory in the kernel window, but also includes any
     * important or kernel devices. */
    boot_state.mem_p_regs.count = 0;
    init_allocated_p_regions();
    boot_state.mb_mmap_info.mmap_length = 0;
    boot_state.vbe_info.vbeMode = -1;

    while (tag < tag_e && tag->type != MULTIBOOT2_TAG_END) {
        word_t const behind_tag = (word_t)tag + sizeof(*tag);

        if (tag->type == MULTIBOOT2_TAG_CMDLINE) {
            char const * const cmdline = (char const * const)(behind_tag);
            cmdline_parse(cmdline, &cmdline_opt);
        } else if (tag->type == MULTIBOOT2_TAG_ACPI_1) {
            if (ACPI_V1_SIZE == tag->size - sizeof(*tag)) {
                memcpy(&boot_state.acpi_rsdp, (void *)behind_tag, tag->size - sizeof(*tag));
            }
        } else if (tag->type == MULTIBOOT2_TAG_ACPI_2) {
            if (sizeof(boot_state.acpi_rsdp) == tag->size - sizeof(*tag)) {
                memcpy(&boot_state.acpi_rsdp, (void *)behind_tag, sizeof(boot_state.acpi_rsdp));
            }
        } else if (tag->type == MULTIBOOT2_TAG_MODULE) {
            multiboot2_module_t const * module = (multiboot2_module_t const *)behind_tag;
            printf(
                "  module #%d: start=0x%x end=0x%x size=0x%x name='%s'\n",
                mod_count,
                module->start,
                module->end,
                module->end - module->start,
                module->string
            );

            if (mod_count == 0) {
                boot_state.boot_module_start = module->start;
            }

            mod_count ++;
            if ((sword_t)(module->end - module->start) <= 0) {
                printf("Invalid boot module size! Possible cause: boot module file not found\n");
                return false;
            }
            if (boot_state.mods_end_paddr < module->end) {
                boot_state.mods_end_paddr = module->end;
            }
        } else if (tag->type == MULTIBOOT2_TAG_MEMORY) {
            multiboot2_memory_t const * s = (multiboot2_memory_t *)(behind_tag + 8);
            multiboot2_memory_t const * e = (multiboot2_memory_t *)((word_t)tag + tag->size);

            for (multiboot2_memory_t const * m = s; m < e; m++) {
                if (!m->addr) {
                    boot_state.mem_lower = m->size;
                }

                printf("\tPhysical Memory Region from %llx size %llx type %u\n", m->addr, m->size, m->type);
                if (m->addr != (uint64_t)(word_t)m->addr) {
                    printf("\t\tPhysical memory region not addressable\n");
                }

                if (m->type == MULTIBOOT_MMAP_USEABLE_TYPE && m->addr >= HIGHMEM_PADDR) {
                    if (!add_mem_p_regs((p_region_t) {
                    m->addr, m->addr + m->size
                }))
                    return false;
                }
            }
        } else if (tag->type == MULTIBOOT2_TAG_FB) {
            multiboot2_fb_t const * fb = (multiboot2_fb_t const *)behind_tag;
            printf("Got framebuffer info in multiboot2. Current video mode is at physical address=%llx pitch=%u resolution=%ux%u@%u type=%u\n",
                   fb->addr, fb->pitch, fb->width, fb->height, fb->bpp, fb->type);
            boot_state.fb_info = *fb;
        }

        tag = (multiboot2_tag_t const *)((word_t)tag + ROUND_UP(tag->size, 3));
    }

    printf("Detected %d boot module(s):\n", mod_count);

    if (mod_count < 1) {
        printf("Expect at least one boot module (containing a userland image)\n");
        return false;
    }

    return true;
}

BOOT_CODE VISIBLE void
boot_sys(
    unsigned long multiboot_magic,
    void* mbi)
{
    bool_t result = false;

    if (multiboot_magic == MULTIBOOT_MAGIC) {
        result = try_boot_sys_mbi1(mbi);
    } else if (multiboot_magic == MULTIBOOT2_MAGIC) {
        result = try_boot_sys_mbi2(mbi);
    } else {
        printf("Boot loader is not multiboot 1 or 2 compliant %lx\n", multiboot_magic);
    }

    if (result) {
        result = try_boot_sys();
    }

    if (!result) {
        fail("boot_sys failed for some reason :(\n");
    }

    ARCH_NODE_STATE(x86KScurInterrupt) = int_invalid;
    ARCH_NODE_STATE(x86KSPendingInterrupt) = int_invalid;

    schedule();
    activateThread();
}

#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/kernel/cmdline.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <util.h>
#include <machine/io.h>
#include <arch/kernel/cmdline.h>
#include <arch/kernel/boot_sys.h>
#include <linker.h>
#include <plat/machine/io.h>

/* 'cmdline_val' is declared globally because of a C-subset restriction.
 * It is only used in cmdline_parse(), which therefore is non-reentrant.
 */
#define MAX_CMDLINE_VAL_LEN 1000
BOOT_BSS
char cmdline_val[MAX_CMDLINE_VAL_LEN];

/* workaround because string literals are not supported by C parser */
const char cmdline_str_max_num_nodes[]  = {'m', 'a', 'x', '_', 'n', 'u', 'm', '_', 'n', 'o', 'd', 'e', 's', 0};
const char cmdline_str_num_sh_frames[]  = {'n', 'u', 'm', '_', 's', 'h', '_', 'f', 'r', 'a', 'm', 'e', 's', 0};
const char cmdline_str_disable_iommu[]  = {'d', 'i', 's', 'a', 'b', 'l', 'e', '_', 'i', 'o', 'm', 'm', 'u', 0};

static int is_space(char c)
{
    return c <= ' ';
}

static int UNUSED parse_opt(const char *cmdline, const char *opt, char *value, int bufsize)
{
    int len = -1;
    const char *optptr = NULL;

    while (true) {
        for (; is_space(*cmdline) && (*cmdline != 0); cmdline++);
        if (*cmdline == 0) {
            break;
        }

        for (optptr = opt; *optptr && *cmdline && (*cmdline != '=') && !is_space(*cmdline) && (*optptr == *cmdline); optptr++, cmdline++);

        if (*optptr == '\0' && *cmdline == '=') {
            cmdline++;

            for (len = 0; !is_space(*cmdline) && (len < bufsize - 1); cmdline++, len++) {
                value[len] = *cmdline;
            }
            if (bufsize) {
                value[len] = '\0';
            }
        }
        for (; !is_space(*cmdline); cmdline++);
    }

    return len;
}

static int parse_bool(const char *cmdline, const char *opt)
{
    const char *optptr = NULL;

    while (1) {
        for (; is_space(*cmdline) && (*cmdline != 0); cmdline++);
        if (*cmdline == 0) {
            return 0;
        }

        for (optptr = opt; *optptr && *cmdline && !is_space(*cmdline) && (*optptr == *cmdline); optptr++, cmdline++);

        if (*optptr == '\0' && is_space(*cmdline)) {
            return 1;
        } else {
            for (; !is_space(*cmdline); cmdline++);
        }
    }
}

static void UNUSED parse_uint16_array(char* str, uint16_t* array, int array_size)
{
    char* last;
    int   i = 0;
    int   v;

    while (str && i < array_size) {
        for (last = str; *str && *str != ','; str++);
        if (*str == 0) {
            str = 0;
        } else {
            *str = 0;
            str++;
        }
        v = str_to_long(last);
        if (v == -1) {
            array[i] = 0;
        } else {
            array[i] = v;
        }
        i++;
    }
}

void cmdline_parse(const char *cmdline, cmdline_opt_t* cmdline_opt)
{
#if defined(CONFIG_PRINTING) || defined(CONFIG_DEBUG_BUILD)
    /* use BIOS data area to read serial configuration. The BDA is not
     * fully standardized and parts are absolete. See http://wiki.osdev.org/Memory_Map_(x86)#BIOS_Data_Area_.28BDA.29
     * for an explanation */
    const unsigned short * bda_port = (unsigned short *)0x400;
    const unsigned short * bda_equi = (unsigned short *)0x410;
    int const bda_ports_count       = (*bda_equi >> 9) & 0x7;
#endif

#ifdef CONFIG_PRINTING
    /* initialise to default or use BDA if available */
    cmdline_opt->console_port = bda_ports_count && *bda_port ? *bda_port : 0x3f8;

    if (parse_opt(cmdline, "console_port", cmdline_val, MAX_CMDLINE_VAL_LEN) != -1) {
        parse_uint16_array(cmdline_val, &cmdline_opt->console_port, 1);
    }

    /* initialise console ports to enable debug output */
    if (cmdline_opt->console_port) {
        serial_init(cmdline_opt->console_port);
        x86KSconsolePort = cmdline_opt->console_port;
    }

    /* only start printing here after having parsed/set/initialised the console_port */
    printf("\nBoot config: parsing cmdline '%s'\n", cmdline);

    if (cmdline_opt->console_port) {
        printf("Boot config: console_port = 0x%x\n", cmdline_opt->console_port);
    }
#endif

#ifdef CONFIG_DEBUG_BUILD
    /* initialise to default or use BDA if available */
    cmdline_opt->debug_port = bda_ports_count && *bda_port ? *bda_port : 0x3f8;
    if (parse_opt(cmdline, "debug_port", cmdline_val, MAX_CMDLINE_VAL_LEN) != -1) {
        parse_uint16_array(cmdline_val, &cmdline_opt->debug_port, 1);
    }

    /* initialise debug ports */
    if (cmdline_opt->debug_port) {
        serial_init(cmdline_opt->debug_port);
        x86KSdebugPort = cmdline_opt->debug_port;
        printf("Boot config: debug_port = 0x%x\n", cmdline_opt->debug_port);
    }
#endif

    cmdline_opt->disable_iommu = parse_bool(cmdline, cmdline_str_disable_iommu);
    printf("Boot config: disable_iommu = %s\n", cmdline_opt->disable_iommu ? "true" : "false");
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/kernel/ept.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>

#ifdef CONFIG_VTX

#include <model/statedata.h>
#include <arch/kernel/ept.h>
#include <arch/api/invocation.h>

struct lookupEPTPDPTSlot_ret {
    exception_t status;
    ept_pdpte_t* pdptSlot;
};
typedef struct lookupEPTPDPTSlot_ret lookupEPTPDPTSlot_ret_t;

struct lookupEPTPDSlot_ret {
    exception_t status;
    ept_pde_t*  pdSlot;
};
typedef struct lookupEPTPDSlot_ret lookupEPTPDSlot_ret_t;

struct lookupEPTPTSlot_ret {
    exception_t status;
    ept_pte_t*  ptSlot;
};
typedef struct lookupEPTPTSlot_ret lookupEPTPTSlot_ret_t;

enum ept_cache_options {
    EPTUncacheable = 0,
    EPTWriteCombining = 1,
    EPTWriteThrough = 4,
    EPTWriteProtected = 5,
    EPTWriteBack = 6
};
typedef enum ept_cache_options ept_cache_options_t;

void
deleteEPTASID(asid_t asid, ept_pml4e_t *ept)
{
    asid_pool_t* poolPtr;

    poolPtr = x86KSASIDTable[asid >> asidLowBits];
    if (poolPtr != NULL) {
        asid_map_t asid_map = poolPtr->array[asid & MASK(asidLowBits)];
        if (asid_map_get_type(asid_map) == asid_map_asid_map_ept &&
                (ept_pml4e_t*)asid_map_asid_map_ept_get_ept_root(asid_map) == ept) {
            poolPtr->array[asid & MASK(asidLowBits)] = asid_map_asid_map_none_new();
        }
    }
}

exception_t
performX86EPTPageInvocationUnmap(cap_t cap, cte_t *ctSlot)
{
    unmapEPTPage(
        cap_frame_cap_get_capFSize(cap),
        cap_frame_cap_get_capFMappedASID(cap),
        cap_frame_cap_get_capFMappedAddress(cap),
        (void *)cap_frame_cap_get_capFBasePtr(cap)
    );

    cap_frame_cap_ptr_set_capFMappedAddress(&ctSlot->cap, 0);
    cap_frame_cap_ptr_set_capFMappedASID(&ctSlot->cap, asidInvalid);
    cap_frame_cap_ptr_set_capFMapType(&ctSlot->cap, X86_MappingNone);

    return EXCEPTION_NONE;
}

findEPTForASID_ret_t
findEPTForASID(asid_t asid)
{
    findEPTForASID_ret_t ret;
    asid_map_t asid_map;

    asid_map = findMapForASID(asid);
    if (asid_map_get_type(asid_map) != asid_map_asid_map_ept) {
        current_lookup_fault = lookup_fault_invalid_root_new();

        ret.ept = NULL;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }

    ret.ept = (ept_pml4e_t*)asid_map_asid_map_ept_get_ept_root(asid_map);
    ret.status = EXCEPTION_NONE;
    return ret;
}

static ept_pml4e_t* CONST
lookupEPTPML4Slot(ept_pml4e_t *pml4, vptr_t vptr)
{
    return pml4 + GET_EPT_PML4_INDEX(vptr);
}

static lookupEPTPDPTSlot_ret_t CONST
lookupEPTPDPTSlot(ept_pml4e_t *pml4, vptr_t vptr)
{
    lookupEPTPDPTSlot_ret_t ret;
    ept_pml4e_t *pml4Slot;

    pml4Slot = lookupEPTPML4Slot(pml4, vptr);

    if (!ept_pml4e_ptr_get_read(pml4Slot)) {
        current_lookup_fault = lookup_fault_missing_capability_new(22);

        ret.pdptSlot = NULL;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }

    ept_pdpte_t *pdpt = paddr_to_pptr(ept_pml4e_ptr_get_pdpt_base_address(pml4Slot));
    uint32_t index = GET_EPT_PDPT_INDEX(vptr);
    ret.pdptSlot = pdpt + index;
    ret.status = EXCEPTION_NONE;
    return ret;
}

static lookupEPTPDSlot_ret_t
lookupEPTPDSlot(ept_pml4e_t* pml4, vptr_t vptr)
{
    lookupEPTPDSlot_ret_t ret;
    lookupEPTPDPTSlot_ret_t lu_ret;

    lu_ret = lookupEPTPDPTSlot(pml4, vptr);
    if (lu_ret.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        /* current_lookup_fault will have been set by lookupEPTPDPTSlot */
        ret.pdSlot = NULL;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }

    if (!ept_pdpte_ptr_get_read(lu_ret.pdptSlot)) {
        current_lookup_fault = lookup_fault_missing_capability_new(22);

        ret.pdSlot = NULL;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }

    ept_pde_t *pd = paddr_to_pptr(ept_pdpte_ptr_get_pd_base_address(lu_ret.pdptSlot));
    uint32_t index = GET_EPT_PD_INDEX(vptr);
    ret.pdSlot = pd + index;
    ret.status = EXCEPTION_NONE;
    return ret;
}

static lookupEPTPTSlot_ret_t
lookupEPTPTSlot(ept_pml4e_t* pml4, vptr_t vptr)
{
    lookupEPTPTSlot_ret_t ret;
    lookupEPTPDSlot_ret_t lu_ret;

    lu_ret = lookupEPTPDSlot(pml4, vptr);
    if (lu_ret.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        /* current_lookup_fault will have been set by lookupEPTPDSlot */
        ret.ptSlot = NULL;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }

    if ((ept_pde_ptr_get_page_size(lu_ret.pdSlot) != ept_pde_ept_pde_pt) ||
            !ept_pde_ept_pde_pt_ptr_get_read(lu_ret.pdSlot)) {
        current_lookup_fault = lookup_fault_missing_capability_new(22);

        ret.ptSlot = NULL;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }

    ept_pte_t *pt = paddr_to_pptr(ept_pde_ept_pde_pt_ptr_get_pt_base_address(lu_ret.pdSlot));
    uint32_t index = GET_EPT_PT_INDEX(vptr);

    ret.ptSlot = pt + index;
    ret.status = EXCEPTION_NONE;
    return ret;
}

static ept_cache_options_t
eptCacheFromVmAttr(vm_attributes_t vmAttr)
{
    /* PAT cache options are 1-1 with ept_cache_options. But need to
       verify user has specified a sensible option */
    ept_cache_options_t option = vmAttr.words[0];
    if (option != EPTUncacheable ||
            option != EPTWriteCombining ||
            option != EPTWriteThrough ||
            option != EPTWriteBack) {
        /* No failure mode is supported here, vmAttr settings should be verified earlier */
        option = EPTWriteBack;
    }
    return option;
}

EPTPDPTMapped_ret_t
EPTPDPTMapped(asid_t asid, vptr_t vptr, ept_pdpte_t *pdpt)
{
    EPTPDPTMapped_ret_t ret;
    findEPTForASID_ret_t asid_ret;
    ept_pml4e_t *pml4Slot;

    asid_ret = findEPTForASID(asid);
    if (asid_ret.status != EXCEPTION_NONE) {
        ret.pml4 = NULL;
        ret.pml4Slot = NULL;
        ret.status = asid_ret.status;
        return ret;
    }

    pml4Slot = lookupEPTPML4Slot(asid_ret.ept, vptr);

    if (ept_pml4e_ptr_get_read(pml4Slot)
            && ptrFromPAddr(ept_pml4e_ptr_get_pdpt_base_address(pml4Slot)) == pdpt) {
        ret.pml4 = asid_ret.ept;
        ret.pml4Slot = pml4Slot;
        ret.status = EXCEPTION_NONE;
        return ret;
    } else {
        ret.pml4 = NULL;
        ret.pml4Slot = NULL;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }
}

void
unmapEPTPDPT(asid_t asid, vptr_t vaddr, ept_pdpte_t *pdpt)
{
    EPTPDPTMapped_ret_t lu_ret;

    lu_ret = EPTPDPTMapped(asid, vaddr, pdpt);

    if (lu_ret.status == EXCEPTION_NONE) {
        *lu_ret.pml4Slot = ept_pml4e_new(0, 0, 0, 0);
        invept(lu_ret.pml4);
    }
}

static exception_t
performEPTPDPTInvocationUnmap(cap_t cap, cte_t *cte)
{
    if (cap_ept_pdpt_cap_get_capPDPTIsMapped(cap)) {
        ept_pdpte_t *pdpt = (ept_pdpte_t*)cap_ept_pdpt_cap_get_capPDPTBasePtr(cap);
        unmapEPTPDPT(
            cap_ept_pdpt_cap_get_capPDPTMappedASID(cap),
            cap_ept_pdpt_cap_get_capPDPTMappedAddress(cap),
            pdpt);
        clearMemory((void *)pdpt, cap_get_capSizeBits(cap));
    }
    cap_ept_pdpt_cap_ptr_set_capPDPTIsMapped(&(cte->cap), 0);

    return EXCEPTION_NONE;
}

static exception_t
performEPTPDPTInvocationMap(cap_t cap, cte_t *cte, ept_pml4e_t pml4e, ept_pml4e_t *pml4Slot, ept_pml4e_t *pml4)
{
    cte->cap = cap;
    *pml4Slot = pml4e;
    invept(pml4);

    return EXCEPTION_NONE;
}

static exception_t
decodeX86EPTPDPTInvocation(
    word_t invLabel,
    word_t length,
    cte_t *cte,
    cap_t cap,
    extra_caps_t excaps,
    word_t *buffer
)
{
    word_t          vaddr;
    cap_t           pml4Cap;
    ept_pml4e_t*    pml4;
    ept_pml4e_t     pml4e;
    paddr_t         paddr;
    asid_t          asid;
    findEPTForASID_ret_t find_ret;
    ept_pml4e_t*    pml4Slot;

    if (invLabel == X86EPTPDPTUnmap) {
        if (!isFinalCapability(cte)) {
            current_syscall_error.type = seL4_RevokeFirst;
            return EXCEPTION_SYSCALL_ERROR;
        }
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performEPTPDPTInvocationUnmap(cap, cte);
    }

    if (invLabel != X86EPTPDPTMap) {
        userError("X86EPTPDPT Illegal operation.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (length < 2 || excaps.excaprefs[0] == NULL) {
        userError("X86EPTPDPTMap: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (cap_ept_pdpt_cap_get_capPDPTIsMapped(cap)) {
        userError("X86EPTPDPTMap: EPT PDPT is already mapped to a PML4.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;

        return EXCEPTION_SYSCALL_ERROR;
    }

    vaddr = getSyscallArg(0, buffer);
    /* cannot use ~MASK(EPT_PML4_INDEX_OFFSET) because on 32-bit compilations
     * this results in an error shifting by greater than 31 bits, so we manually
     * force a 64-bit variable to do the shifting with */
    vaddr = vaddr & ~(((uint64_t)1 << EPT_PML4_INDEX_OFFSET) - 1);
    pml4Cap = excaps.excaprefs[0]->cap;

    if (cap_get_capType(pml4Cap) != cap_ept_pml4_cap) {
        userError("X86EPTPDPTMap: Not a valid EPT PML4.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;

        return EXCEPTION_SYSCALL_ERROR;
    }

    pml4 = (ept_pml4e_t*)cap_ept_pml4_cap_get_capPML4BasePtr(pml4Cap);
    asid = cap_ept_pml4_cap_get_capPML4MappedASID(pml4Cap);

    find_ret = findEPTForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;

        return EXCEPTION_SYSCALL_ERROR;
    }

    if (find_ret.ept != pml4) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;

        return EXCEPTION_SYSCALL_ERROR;
    }

    pml4Slot = lookupEPTPML4Slot(pml4, vaddr);

    if (ept_pml4e_ptr_get_read(pml4Slot)) {
        userError("X86EPTPDPTMap: PDPT already mapped here.");
        current_syscall_error.type = seL4_DeleteFirst;
        return EXCEPTION_SYSCALL_ERROR;
    }

    paddr = pptr_to_paddr((void*)cap_ept_pdpt_cap_get_capPDPTBasePtr(cap));
    pml4e = ept_pml4e_new(
                paddr,
                1,
                1,
                1
            );

    cap = cap_ept_pdpt_cap_set_capPDPTIsMapped(cap, 1);
    cap = cap_ept_pdpt_cap_set_capPDPTMappedASID(cap, asid);
    cap = cap_ept_pdpt_cap_set_capPDPTMappedAddress(cap, vaddr);

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return performEPTPDPTInvocationMap(cap, cte, pml4e, pml4Slot, pml4);
}

exception_t
decodeX86EPTInvocation(
    word_t invLabel,
    word_t length,
    cptr_t cptr,
    cte_t* cte,
    cap_t cap,
    extra_caps_t excaps,
    word_t* buffer
)
{
    switch (cap_get_capType(cap)) {
    case cap_ept_pdpt_cap:
        return decodeX86EPTPDPTInvocation(invLabel, length, cte, cap, excaps, buffer);
    case cap_ept_pd_cap:
        return decodeX86EPTPDInvocation(invLabel, length, cte, cap, excaps, buffer);
    case cap_ept_pt_cap:
        return decodeX86EPTPTInvocation(invLabel, length, cte, cap, excaps, buffer);
    default:
        fail("Invalid cap type");
    }
}

EPTPageDirectoryMapped_ret_t
EPTPageDirectoryMapped(asid_t asid, vptr_t vaddr, ept_pde_t *pd)
{
    EPTPageDirectoryMapped_ret_t ret;
    lookupEPTPDPTSlot_ret_t find_ret;
    findEPTForASID_ret_t asid_ret;

    asid_ret = findEPTForASID(asid);
    if (asid_ret.status != EXCEPTION_NONE) {
        ret.pml4 = NULL;
        ret.pdptSlot = NULL;
        ret.status = asid_ret.status;
        return ret;
    }

    find_ret = lookupEPTPDPTSlot(asid_ret.ept, vaddr);
    if (find_ret.status != EXCEPTION_NONE) {
        ret.pml4 = NULL;
        ret.pdptSlot = NULL;
        ret.status = find_ret.status;
        return ret;
    }

    if (ept_pdpte_ptr_get_read(find_ret.pdptSlot)
            && ptrFromPAddr(ept_pdpte_ptr_get_pd_base_address(find_ret.pdptSlot)) == pd) {
        ret.pml4 = asid_ret.ept;
        ret.pdptSlot = find_ret.pdptSlot;
        ret.status = EXCEPTION_NONE;
        return ret;
    } else {
        ret.pml4 = NULL;
        ret.pdptSlot = NULL;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }
}

void
unmapEPTPageDirectory(asid_t asid, vptr_t vaddr, ept_pde_t *pd)
{
    EPTPageDirectoryMapped_ret_t lu_ret;

    lu_ret = EPTPageDirectoryMapped(asid, vaddr, pd);

    if (lu_ret.status == EXCEPTION_NONE) {
        *lu_ret.pdptSlot = ept_pdpte_new(
                               0,  /* pd_base_address  */
                               0,  /* avl_cte_depth    */
                               0,  /* execute          */
                               0,  /* write            */
                               0   /* read             */
                           );
        invept(lu_ret.pml4);
    }
}

static exception_t
performEPTPDInvocationUnmap(cap_t cap, cte_t *cte)
{
    if (cap_ept_pd_cap_get_capPDIsMapped(cap)) {
        ept_pde_t *pd = (ept_pde_t*)cap_ept_pd_cap_get_capPDBasePtr(cap);
        unmapEPTPageDirectory(
            cap_ept_pd_cap_get_capPDMappedASID(cap),
            cap_ept_pd_cap_get_capPDMappedAddress(cap),
            pd);
        clearMemory((void*)pd, cap_get_capSizeBits(cap));
    }
    cap_ept_pd_cap_ptr_set_capPDIsMapped(&(cte->cap), 0);

    return EXCEPTION_NONE;
}

static exception_t
performEPTPDInvocationMap(cap_t cap, cte_t *cte, ept_pdpte_t pdpte, ept_pdpte_t *pdptSlot, ept_pml4e_t *pml4)
{
    cte->cap = cap;
    *pdptSlot = pdpte;
    invept(pml4);

    return EXCEPTION_NONE;
}

exception_t
decodeX86EPTPDInvocation(
    word_t invLabel,
    word_t length,
    cte_t* cte,
    cap_t cap,
    extra_caps_t excaps,
    word_t* buffer
)
{
    word_t          vaddr;
    cap_t           pml4Cap;
    ept_pml4e_t*    pml4;
    ept_pdpte_t     pdpte;
    paddr_t         paddr;
    asid_t          asid;
    findEPTForASID_ret_t find_ret;
    lookupEPTPDPTSlot_ret_t lu_ret;

    if (invLabel == X86EPTPDUnmap) {
        if (!isFinalCapability(cte)) {
            current_syscall_error.type = seL4_RevokeFirst;
            return EXCEPTION_SYSCALL_ERROR;
        }
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performEPTPDInvocationUnmap(cap, cte);
    }

    if (invLabel != X86EPTPDMap) {
        userError("X86EPTPD Illegal operation.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (length < 2 || excaps.excaprefs[0] == NULL) {
        userError("X86EPTPDMap: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (cap_ept_pd_cap_get_capPDIsMapped(cap)) {
        userError("X86EPTPDMap: EPT Page directory is already mapped to a PDPT.");
        current_syscall_error.type =
            seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;

        return EXCEPTION_SYSCALL_ERROR;
    }

    vaddr = getSyscallArg(0, buffer);
    vaddr = vaddr & ~MASK(EPT_PDPT_INDEX_OFFSET);
    pml4Cap = excaps.excaprefs[0]->cap;

    if (cap_get_capType(pml4Cap) != cap_ept_pml4_cap) {
        userError("X86EPTPDMap: Not a valid EPT pml4.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;

        return EXCEPTION_SYSCALL_ERROR;
    }

    pml4 = (ept_pml4e_t*)cap_ept_pml4_cap_get_capPML4BasePtr(pml4Cap);
    asid = cap_ept_pml4_cap_get_capPML4MappedASID(pml4Cap);

    find_ret = findEPTForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        userError("X86EPTPDMap: EPT PML4 is not mapped.");
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;

        return EXCEPTION_SYSCALL_ERROR;
    }

    if (find_ret.ept != pml4) {
        userError("X86EPTPDMap: EPT PML4 asid is invalid.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;

        return EXCEPTION_SYSCALL_ERROR;
    }

    lu_ret = lookupEPTPDPTSlot(pml4, vaddr);
    if (lu_ret.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (ept_pdpte_ptr_get_read(lu_ret.pdptSlot)) {
        userError("X86EPTPDMap: Page directory already mapped here.");
        current_syscall_error.type = seL4_DeleteFirst;
        return EXCEPTION_SYSCALL_ERROR;
    }

    paddr = pptr_to_paddr((void*)(cap_ept_pd_cap_get_capPDBasePtr(cap)));
    pdpte = ept_pdpte_new(
                paddr,  /* pd_base_address  */
                0,      /* avl_cte_depth    */
                1,      /* execute          */
                1,      /* write            */
                1       /* read             */
            );

    cap = cap_ept_pd_cap_set_capPDIsMapped(cap, 1);
    cap = cap_ept_pd_cap_set_capPDMappedASID(cap, asid);
    cap = cap_ept_pd_cap_set_capPDMappedAddress(cap, vaddr);

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return performEPTPDInvocationMap(cap, cte, pdpte, lu_ret.pdptSlot, pml4);
}

EPTPageTableMapped_ret_t
EPTPageTableMapped(asid_t asid, vptr_t vaddr, ept_pte_t *pt)
{
    EPTPageTableMapped_ret_t ret;
    lookupEPTPDSlot_ret_t find_ret;
    findEPTForASID_ret_t asid_ret;

    asid_ret = findEPTForASID(asid);
    if (asid_ret.status != EXCEPTION_NONE) {
        ret.pml4 = NULL;
        ret.pdSlot = NULL;
        ret.status = asid_ret.status;
        return ret;
    }

    find_ret = lookupEPTPDSlot(asid_ret.ept, vaddr);
    if (find_ret.status != EXCEPTION_NONE) {
        ret.pml4 = NULL;
        ret.pdSlot = NULL;
        ret.status = find_ret.status;
        return ret;
    }

    if (ept_pde_ptr_get_page_size(find_ret.pdSlot) == ept_pde_ept_pde_pt
            && ptrFromPAddr(ept_pde_ept_pde_pt_ptr_get_pt_base_address(find_ret.pdSlot)) == pt) {
        ret.pml4 = asid_ret.ept;
        ret.pdSlot = find_ret.pdSlot;
        ret.status = EXCEPTION_NONE;
        return ret;
    } else {
        ret.pml4 = NULL;
        ret.pdSlot = NULL;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }
}

void
unmapEPTPageTable(asid_t asid, vptr_t vaddr, ept_pte_t *pt)
{
    EPTPageTableMapped_ret_t lu_ret;

    lu_ret = EPTPageTableMapped(asid, vaddr, pt);

    if (lu_ret.status == EXCEPTION_NONE) {
        *lu_ret.pdSlot = ept_pde_ept_pde_pt_new(
                             0,  /* pt_base_address  */
                             0,  /* avl_cte_depth    */
                             0,  /* execute          */
                             0,  /* write            */
                             0   /* read             */
                         );
        invept(lu_ret.pml4);
    }
}

static exception_t
performEPTPTInvocationUnmap(cap_t cap, cte_t *cte)
{
    if (cap_ept_pt_cap_get_capPTIsMapped(cap)) {
        ept_pte_t *pt = (ept_pte_t*)cap_ept_pt_cap_get_capPTBasePtr(cap);
        unmapEPTPageTable(
            cap_ept_pt_cap_get_capPTMappedASID(cap),
            cap_ept_pt_cap_get_capPTMappedAddress(cap),
            pt);
        clearMemory((void *)pt, cap_get_capSizeBits(cap));
    }
    cap_ept_pt_cap_ptr_set_capPTIsMapped(&(cte->cap), 0);

    return EXCEPTION_NONE;
}

static exception_t
performEPTPTInvocationMap(cap_t cap, cte_t *cte, ept_pde_t pde, ept_pde_t *pdSlot, ept_pml4e_t *pml4)
{
    cte->cap = cap;
    *pdSlot = pde;
    invept(pml4);

    return EXCEPTION_NONE;
}

exception_t
decodeX86EPTPTInvocation(
    word_t invLabel,
    word_t length,
    cte_t* cte,
    cap_t cap,
    extra_caps_t excaps,
    word_t* buffer
)
{
    word_t          vaddr;
    cap_t           pml4Cap;
    ept_pml4e_t*    pml4;
    ept_pde_t       pde;
    paddr_t         paddr;
    asid_t          asid;
    findEPTForASID_ret_t find_ret;
    lookupEPTPDSlot_ret_t lu_ret;

    if (invLabel == X86EPTPTUnmap) {
        if (!isFinalCapability(cte)) {
            current_syscall_error.type = seL4_RevokeFirst;
            return EXCEPTION_SYSCALL_ERROR;
        }
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performEPTPTInvocationUnmap(cap, cte);
    }

    if (invLabel != X86EPTPTMap) {
        userError("X86EPTPT Illegal operation.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (length < 2 || excaps.excaprefs[0] == NULL) {
        userError("X86EPTPT: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (cap_ept_pt_cap_get_capPTIsMapped(cap)) {
        userError("X86EPTPT EPT Page table is already mapped to an EPT page directory.");
        current_syscall_error.type =
            seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;

        return EXCEPTION_SYSCALL_ERROR;
    }

    vaddr = getSyscallArg(0, buffer);
    vaddr = vaddr & ~MASK(EPT_PD_INDEX_OFFSET);
    pml4Cap = excaps.excaprefs[0]->cap;

    if (cap_get_capType(pml4Cap) != cap_ept_pml4_cap ||
            !cap_ept_pml4_cap_get_capPML4IsMapped(pml4Cap)) {
        userError("X86EPTPTMap: Not a valid EPT pml4.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;

        return EXCEPTION_SYSCALL_ERROR;
    }

    pml4 = (ept_pml4e_t*)(cap_ept_pml4_cap_get_capPML4BasePtr(pml4Cap));
    asid = cap_ept_pml4_cap_get_capPML4MappedASID(pml4Cap);

    find_ret = findEPTForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;

        return EXCEPTION_SYSCALL_ERROR;
    }

    if (find_ret.ept != pml4) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;

        return EXCEPTION_SYSCALL_ERROR;
    }

    lu_ret = lookupEPTPDSlot(pml4, vaddr);
    if (lu_ret.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        /* current_lookup_fault will have been set by lookupPTSlot */
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (((ept_pde_ptr_get_page_size(lu_ret.pdSlot) == ept_pde_ept_pde_pt) &&
            ept_pde_ept_pde_pt_ptr_get_read(lu_ret.pdSlot)) ||
            ((ept_pde_ptr_get_page_size(lu_ret.pdSlot) == ept_pde_ept_pde_2m) &&
             ept_pde_ept_pde_2m_ptr_get_read(lu_ret.pdSlot))) {
        userError("X86EPTPTMap: Page table already mapped here");
        current_syscall_error.type = seL4_DeleteFirst;
        return EXCEPTION_SYSCALL_ERROR;
    }

    paddr = pptr_to_paddr((void*)(cap_ept_pt_cap_get_capPTBasePtr(cap)));
    pde = ept_pde_ept_pde_pt_new(
              paddr,/* pt_base_address  */
              0,    /* avl_cte_depth    */
              1,    /* execute          */
              1,    /* write            */
              1     /* read             */
          );

    cap = cap_ept_pt_cap_set_capPTIsMapped(cap, 1);
    cap = cap_ept_pt_cap_set_capPTMappedASID(cap, asid);
    cap = cap_ept_pt_cap_set_capPTMappedAddress(cap, vaddr);

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return performEPTPTInvocationMap(cap, cte, pde, lu_ret.pdSlot, pml4);
}

static exception_t
performEPTPageMapPTE(cap_t cap, cte_t *cte, ept_pte_t *ptSlot, ept_pte_t pte, ept_pml4e_t *pml4)
{
    *ptSlot = pte;
    cte->cap = cap;
    invept(pml4);

    return EXCEPTION_NONE;
}

static exception_t
performEPTPageMapPDE(cap_t cap, cte_t *cte, ept_pde_t *pdSlot, ept_pde_t pde1, ept_pde_t pde2, ept_pml4e_t *pml4)
{
    pdSlot[0] = pde1;
    if (LARGE_PAGE_BITS == 22) {
        pdSlot[1] = pde2;
    }
    cte->cap = cap;
    invept(pml4);

    return EXCEPTION_NONE;
}

exception_t
decodeX86EPTPageMap(
    word_t invLabel,
    word_t length,
    cte_t* cte,
    cap_t cap,
    extra_caps_t excaps,
    word_t* buffer)
{
    word_t          vaddr;
    word_t          w_rightsMask;
    paddr_t         paddr;
    cap_t           pml4Cap;
    ept_pml4e_t*    pml4;
    vm_rights_t     capVMRights;
    vm_rights_t     vmRights;
    vm_attributes_t vmAttr;
    vm_page_size_t  frameSize;
    asid_t          asid;

    frameSize = cap_frame_cap_get_capFSize(cap);
    vaddr = getSyscallArg(0, buffer);
    vaddr = vaddr & ~MASK(EPT_PT_INDEX_OFFSET);
    w_rightsMask = getSyscallArg(1, buffer);
    vmAttr = vmAttributesFromWord(getSyscallArg(2, buffer));
    pml4Cap = excaps.excaprefs[0]->cap;

    capVMRights = cap_frame_cap_get_capFVMRights(cap);

    if (cap_frame_cap_get_capFMappedASID(cap) != asidInvalid) {
        userError("X86EPTPageMap: Frame already mapped.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;

        return EXCEPTION_SYSCALL_ERROR;
    }

    assert(cap_frame_cap_get_capFMapType(cap) == X86_MappingNone);

    if (cap_get_capType(pml4Cap) != cap_ept_pml4_cap ||
            !cap_ept_pml4_cap_get_capPML4IsMapped(pml4Cap)) {
        userError("X86EPTPageMap: Attempting to map frame into invalid ept pml4.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;

        return EXCEPTION_SYSCALL_ERROR;
    }

    pml4 = (ept_pml4e_t*)(cap_ept_pml4_cap_get_capPML4BasePtr(pml4Cap));
    asid = cap_ept_pml4_cap_get_capPML4MappedASID(pml4Cap);

    findEPTForASID_ret_t find_ret = findEPTForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;

        return EXCEPTION_SYSCALL_ERROR;
    }

    if (find_ret.ept != pml4) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;

        return EXCEPTION_SYSCALL_ERROR;
    }


    vmRights = maskVMRights(capVMRights, rightsFromWord(w_rightsMask));

    if (!checkVPAlignment(frameSize, vaddr)) {
        current_syscall_error.type = seL4_AlignmentError;

        return EXCEPTION_SYSCALL_ERROR;
    }

    paddr = pptr_to_paddr((void*)cap_frame_cap_get_capFBasePtr(cap));

    cap = cap_frame_cap_set_capFMappedASID(cap, asid);
    cap = cap_frame_cap_set_capFMappedAddress(cap, vaddr);
    cap = cap_frame_cap_set_capFMapType(cap, X86_MappingEPT);

    switch (frameSize) {
    /* PTE mappings */
    case X86_SmallPage: {
        lookupEPTPTSlot_ret_t lu_ret;
        ept_pte_t pte;

        lu_ret = lookupEPTPTSlot(pml4, vaddr);
        if (lu_ret.status != EXCEPTION_NONE) {
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = false;
            /* current_lookup_fault will have been set by lookupEPTPTSlot */
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (ept_pte_ptr_get_read(lu_ret.ptSlot)) {
            userError("X86EPTPageMap: Mapping already present.");
            current_syscall_error.type = seL4_DeleteFirst;
            return EXCEPTION_SYSCALL_ERROR;
        }

        pte = ept_pte_new(
                  paddr,
                  0,
                  0,
                  eptCacheFromVmAttr(vmAttr),
                  1,
                  WritableFromVMRights(vmRights),
                  1);

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performEPTPageMapPTE(cap, cte, lu_ret.ptSlot, pte, pml4);
    }

    /* PDE mappings */
    case X86_LargePage: {
        lookupEPTPDSlot_ret_t lu_ret;

        lu_ret = lookupEPTPDSlot(pml4, vaddr);
        if (lu_ret.status != EXCEPTION_NONE) {
            userError("X86EPTPageMap: Need a page directory first.");
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = false;
            /* current_lookup_fault will have been set by lookupEPTPDSlot */
            return EXCEPTION_SYSCALL_ERROR;
        }


        if ((ept_pde_ptr_get_page_size(lu_ret.pdSlot) == ept_pde_ept_pde_pt) &&
                ept_pde_ept_pde_pt_ptr_get_read(lu_ret.pdSlot)) {
            userError("X86EPTPageMap: Page table already present.");
            current_syscall_error.type = seL4_DeleteFirst;
            return EXCEPTION_SYSCALL_ERROR;
        }
        if (LARGE_PAGE_BITS != EPT_PD_INDEX_OFFSET &&
                (ept_pde_ptr_get_page_size(lu_ret.pdSlot + 1) == ept_pde_ept_pde_pt) &&
                ept_pde_ept_pde_pt_ptr_get_read(lu_ret.pdSlot + 1)) {
            userError("X86EPTPageMap: Page table already present.");
            current_syscall_error.type = seL4_DeleteFirst;
            return EXCEPTION_SYSCALL_ERROR;
        }
        if ((ept_pde_ptr_get_page_size(lu_ret.pdSlot) == ept_pde_ept_pde_2m) &&
                ept_pde_ept_pde_2m_ptr_get_read(lu_ret.pdSlot)) {
            userError("X86EPTPageMap: Mapping already present.");
            current_syscall_error.type = seL4_DeleteFirst;
            return EXCEPTION_SYSCALL_ERROR;
        }

        ept_pde_t pde1 = ept_pde_ept_pde_2m_new(
                             paddr,
                             0,
                             0,
                             eptCacheFromVmAttr(vmAttr),
                             1,
                             WritableFromVMRights(vmRights),
                             1);

        ept_pde_t pde2 = ept_pde_ept_pde_2m_new(
                             paddr + BIT(EPT_PD_INDEX_OFFSET),
                             0,
                             0,
                             eptCacheFromVmAttr(vmAttr),
                             1,
                             WritableFromVMRights(vmRights),
                             1);

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performEPTPageMapPDE(cap, cte, lu_ret.pdSlot, pde1, pde2, pml4);
    }

    default:
        /* When initializing EPT we only checked for support for 4K and 2M
         * pages, so we must disallow attempting to use any other */
        userError("X86EPTPageMap: Attempted to map unsupported page size.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }
}

void
unmapEPTPage(vm_page_size_t page_size, asid_t asid, vptr_t vptr, void *pptr)
{
    findEPTForASID_ret_t find_ret;
    paddr_t addr = addrFromPPtr(pptr);

    find_ret = findEPTForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        return;
    }

    switch (page_size) {
    case X86_SmallPage: {
        lookupEPTPTSlot_ret_t lu_ret;

        lu_ret = lookupEPTPTSlot(find_ret.ept, vptr);
        if (lu_ret.status != EXCEPTION_NONE) {
            return;
        }
        if (!ept_pte_ptr_get_read(lu_ret.ptSlot)) {
            return;
        }
        if (ept_pte_ptr_get_page_base_address(lu_ret.ptSlot) != addr) {
            return;
        }

        *lu_ret.ptSlot = ept_pte_new(0, 0, 0, 0, 0, 0, 0);
        break;
    }
    case X86_LargePage: {
        lookupEPTPDSlot_ret_t lu_ret;

        lu_ret = lookupEPTPDSlot(find_ret.ept, vptr);
        if (lu_ret.status != EXCEPTION_NONE) {
            return;
        }
        if (ept_pde_ptr_get_page_size(lu_ret.pdSlot) != ept_pde_ept_pde_2m) {
            return;
        }
        if (!ept_pde_ept_pde_2m_ptr_get_read(lu_ret.pdSlot)) {
            return;
        }
        if (ept_pde_ept_pde_2m_ptr_get_page_base_address(lu_ret.pdSlot) != addr) {
            return;
        }

        lu_ret.pdSlot[0] = ept_pde_ept_pde_2m_new(0, 0, 0, 0, 0, 0, 0);

        if (LARGE_PAGE_BITS != EPT_PD_INDEX_OFFSET) {
            assert(ept_pde_ptr_get_page_size(lu_ret.pdSlot + 1) == ept_pde_ept_pde_2m);
            assert(ept_pde_ept_pde_2m_ptr_get_read(lu_ret.pdSlot + 1));
            assert(ept_pde_ept_pde_2m_ptr_get_page_base_address(lu_ret.pdSlot + 1) == addr + BIT(21));

            lu_ret.pdSlot[1] = ept_pde_ept_pde_2m_new(0, 0, 0, 0, 0, 0, 0);
        }
        break;
    }
    default:
        /* we did not allow mapping additional page sizes into EPT objects,
         * so this should not happen. As we have no way to return an error
         * all we can do is assert */
        assert(!"Invalid page size for unmap");
    }
}

#endif /* CONFIG_VTX */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/kernel/smp_sys.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <arch/machine.h>
#include <arch/kernel/boot_sys.h>
#include <arch/kernel/smp_sys.h>
#include <smp/lock.h>

#ifdef ENABLE_SMP_SUPPORT

/* Index of next AP to boot, BSP has index zero */
BOOT_DATA VISIBLE
volatile word_t smp_aps_index = 1;

#ifdef CONFIG_USE_LOGICAL_IDS
BOOT_CODE static void
update_logical_id_mappings(void)
{
    cpu_mapping.index_to_logical_id[getCurrentCPUIndex()] = apic_get_logical_id();

    for (int i = 0; i < smp_aps_index; i++) {
        if (apic_get_cluster(cpu_mapping.index_to_logical_id[getCurrentCPUIndex()]) ==
                apic_get_cluster(cpu_mapping.index_to_logical_id[i])) {

            cpu_mapping.other_indexes_in_cluster[getCurrentCPUIndex()] |= BIT(i);
            cpu_mapping.other_indexes_in_cluster[i] |= BIT(getCurrentCPUIndex());
        }
    }
}
#endif /* CONFIG_USE_LOGICAL_IDS */

BOOT_CODE static void
start_cpu(cpu_id_t cpu_id, paddr_t boot_fun_paddr)
{
    /* memory fence needed before starting the other CPU */
    x86_mfence();

    /* starting the other CPU */
    apic_send_init_ipi(cpu_id);
    apic_send_startup_ipi(cpu_id, boot_fun_paddr);
}

BOOT_CODE void
start_boot_aps(void)
{
    /* update cpu mapping for BSP, cpus[0] is always assumed to be BSP */
    cpu_mapping.index_to_cpu_id[getCurrentCPUIndex()] = boot_state.cpus[0];
#ifdef CONFIG_USE_LOGICAL_IDS
    cpu_mapping.index_to_logical_id[getCurrentCPUIndex()] = apic_get_logical_id();
#endif /* CONFIG_USE_LOGICAL_IDS */

    /* startup APs one at a time as we use shared kernel boot stack */
    while (smp_aps_index < boot_state.num_cpus) {
        word_t current_ap_index = smp_aps_index;

        printf("Starting node #%lu with APIC ID %lu \n",
               current_ap_index, boot_state.cpus[current_ap_index]);

        /* update cpu mapping for APs, store APIC ID of the next booting AP
         * as APIC ID are not continoius e.g. 0,2,1,3 for 4 cores with hyperthreading
         * we need to store a mapping to translate the index to real APIC ID */
        cpu_mapping.index_to_cpu_id[current_ap_index] = boot_state.cpus[current_ap_index];
        start_cpu(boot_state.cpus[current_ap_index], BOOT_NODE_PADDR);

        /* wait for current AP to boot up */
        while (smp_aps_index == current_ap_index);
    }
}

BOOT_CODE bool_t
copy_boot_code_aps(uint32_t mem_lower)
{
    assert(boot_cpu_end - boot_cpu_start < 0x400);

    /* Ensure that our boot code fits in the memory hole we want to use, and check this region
     * is free according to multiboot. As boot_cpu_end and boot_cpu_start are link time
     * symbols (and not compile time) this cannot be a compile time check */
    word_t boot_size = (word_t)(boot_cpu_end - boot_cpu_start);
    word_t boot_node_top = BOOT_NODE_PADDR + boot_size;
    word_t mem_lower_bytes = mem_lower << 10;
    if (boot_node_top > BOOT_NODE_MAX_PADDR) {
        printf("AP boot code does not fit in chosen memory hole. Can be at most %lu, is %lu\n",
               (word_t)(BOOT_NODE_MAX_PADDR - BOOT_NODE_PADDR), boot_size);
        return false;
    }
    if (mem_lower_bytes < boot_node_top) {
        printf("Need lower physical memory up to %lu to be free. Multiboot reports only up to %lu\n",
               boot_node_top, mem_lower_bytes);
        return false;
    }

    /* copy CPU bootup code to lower memory */
    memcpy((void*)BOOT_NODE_PADDR, boot_cpu_start, boot_size);
    return true;
}

static BOOT_CODE bool_t
try_boot_node(void)
{
    setCurrentVSpaceRoot(kpptr_to_paddr(X86_KERNEL_VSPACE_ROOT), 0);
    /* Sync up the compilers view of the world here to force the PD to actually
     * be set *right now* instead of delayed */
    asm volatile("" ::: "memory");

    /* initialise the CPU, make sure legacy interrupts are disabled */
    if (!init_cpu(1)) {
        return false;
    }

#ifdef CONFIG_USE_LOGICAL_IDS
    update_logical_id_mappings();
#endif /* CONFIG_USE_LOGICAL_IDS */
    return true;
}

/* This is the entry function for APs. However, it is not a BOOT_CODE as
 * there is a race between exiting this function and root task running on
 * node #0 to possibly reallocate this memory */
VISIBLE void
boot_node(void)
{
    bool_t result;

    mode_init_tls(smp_aps_index);
    result = try_boot_node();

    if (!result) {
        fail("boot_node failed for some reason :(\n");
    }

    smp_aps_index++;

    /* grab BKL before leaving the kernel */
    NODE_LOCK_SYS;

    init_core_state(SchedulerAction_ChooseNewThread);
    ARCH_NODE_STATE(x86KScurInterrupt) = int_invalid;
    ARCH_NODE_STATE(x86KSPendingInterrupt) = int_invalid;

    schedule();
    activateThread();
}

#endif /* ENABLE_SMP_SUPPORT */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/kernel/thread.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <kernel/thread.h>
#include <arch/kernel/thread.h>

void
Arch_postModifyRegisters(tcb_t *tptr)
{
    Mode_postModifyRegisters(tptr);
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/kernel/vspace.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <api/syscall.h>
#include <machine/io.h>
#include <kernel/boot.h>
#include <model/statedata.h>
#include <arch/kernel/vspace.h>
#include <arch/api/invocation.h>
#include <arch/kernel/tlb_bitmap.h>
#include <mode/kernel/tlb.h>
#include <mode/kernel/vspace.h>

static exception_t
performPageGetAddress(void *vbase_ptr)
{
    paddr_t capFBasePtr;

    /* Get the physical address of this frame. */
    capFBasePtr = pptr_to_paddr(vbase_ptr);

    /* return it in the first message register */
    setRegister(NODE_STATE(ksCurThread), msgRegisters[0], capFBasePtr);
    setRegister(NODE_STATE(ksCurThread), msgInfoRegister,
                wordFromMessageInfo(seL4_MessageInfo_new(0, 0, 0, 1)));

    return EXCEPTION_NONE;
}


void deleteASIDPool(asid_t asid_base, asid_pool_t* pool)
{
    /* Haskell error: "ASID pool's base must be aligned" */
    assert(IS_ALIGNED(asid_base, asidLowBits));

    if (x86KSASIDTable[asid_base >> asidLowBits] == pool) {
        for (unsigned int offset = 0; offset < BIT(asidLowBits); offset++) {
            asid_map_t asid_map = pool->array[offset];
            if (asid_map_get_type(asid_map) == asid_map_asid_map_vspace) {
                vspace_root_t *vspace = (vspace_root_t*)asid_map_asid_map_vspace_get_vspace_root(asid_map);
                hwASIDInvalidate(asid_base + offset, vspace);
            }
        }
        x86KSASIDTable[asid_base >> asidLowBits] = NULL;
        setVMRoot(NODE_STATE(ksCurThread));
    }
}

exception_t performASIDControlInvocation(void* frame, cte_t* slot, cte_t* parent, asid_t asid_base)
{
    /** AUXUPD: "(True, typ_region_bytes (ptr_val \<acute>frame) 12)" */
    /** GHOSTUPD: "(True, gs_clear_region (ptr_val \<acute>frame) 12)" */
    cap_untyped_cap_ptr_set_capFreeIndex(&(parent->cap),
                                         MAX_FREE_INDEX(cap_untyped_cap_get_capBlockSize(parent->cap)));

    memzero(frame, BIT(pageBitsForSize(X86_SmallPage)));
    /** AUXUPD: "(True, ptr_retyps 1 (Ptr (ptr_val \<acute>frame) :: asid_pool_C ptr))" */

    cteInsert(
        cap_asid_pool_cap_new(
            asid_base,          /* capASIDBase  */
            WORD_REF(frame)     /* capASIDPool  */
        ),
        parent,
        slot
    );
    /* Haskell error: "ASID pool's base must be aligned" */
    assert((asid_base & MASK(asidLowBits)) == 0);
    x86KSASIDTable[asid_base >> asidLowBits] = (asid_pool_t*)frame;

    return EXCEPTION_NONE;
}

void deleteASID(asid_t asid, vspace_root_t *vspace)
{
    asid_pool_t* poolPtr;

    poolPtr = x86KSASIDTable[asid >> asidLowBits];
    if (poolPtr != NULL) {
        asid_map_t asid_map = poolPtr->array[asid & MASK(asidLowBits)];
        if (asid_map_get_type(asid_map) == asid_map_asid_map_vspace &&
                (vspace_root_t*)asid_map_asid_map_vspace_get_vspace_root(asid_map) == vspace) {
            hwASIDInvalidate(asid, vspace);
            poolPtr->array[asid & MASK(asidLowBits)] = asid_map_asid_map_none_new();
            setVMRoot(NODE_STATE(ksCurThread));
        }
    }
}

word_t* PURE lookupIPCBuffer(bool_t isReceiver, tcb_t *thread)
{
    word_t      w_bufferPtr;
    cap_t       bufferCap;
    vm_rights_t vm_rights;

    w_bufferPtr = thread->tcbIPCBuffer;
    bufferCap = TCB_PTR_CTE_PTR(thread, tcbBuffer)->cap;

    if (cap_get_capType(bufferCap) != cap_frame_cap) {
        return NULL;
    }
    if (unlikely(cap_frame_cap_get_capFIsDevice(bufferCap))) {
        return NULL;
    }

    vm_rights = cap_frame_cap_get_capFVMRights(bufferCap);
    if (vm_rights == VMReadWrite || (!isReceiver && vm_rights == VMReadOnly)) {
        word_t basePtr, pageBits;

        basePtr = cap_frame_cap_get_capFBasePtr(bufferCap);
        pageBits = pageBitsForSize(cap_frame_cap_get_capFSize(bufferCap));
        return (word_t *)(basePtr + (w_bufferPtr & MASK(pageBits)));
    } else {
        return NULL;
    }
}

bool_t CONST isValidVTableRoot(cap_t cap)
{
    return isValidNativeRoot(cap);
}


BOOT_CODE bool_t map_kernel_window_devices(pte_t *pt, uint32_t num_ioapic, paddr_t* ioapic_paddrs, uint32_t num_drhu, paddr_t* drhu_list)
{
    word_t idx = (PPTR_KDEV & MASK(LARGE_PAGE_BITS)) >> PAGE_BITS;
    paddr_t phys;
    pte_t pte;
    unsigned int i;
    /* map kernel devices: APIC */
    phys = apic_get_base_paddr();
    if (!phys) {
        return false;
    }
    if (!add_allocated_p_region((p_region_t) {
    phys, phys + 0x1000
})) {
        return false;
    }
    pte = x86_make_device_pte(phys);

    assert(idx == (PPTR_APIC & MASK(LARGE_PAGE_BITS)) >> PAGE_BITS);
    pt[idx] = pte;
    idx++;
    for (i = 0; i < num_ioapic; i++) {
        phys = ioapic_paddrs[i];
        if (!add_allocated_p_region((p_region_t) {
        phys, phys + 0x1000
    })) {
            return false;
        }
        pte = x86_make_device_pte(phys);
        assert(idx == ( (PPTR_IOAPIC_START + i * BIT(PAGE_BITS)) & MASK(LARGE_PAGE_BITS)) >> PAGE_BITS);
        pt[idx] = pte;
        idx++;
        if (idx == BIT(PT_INDEX_BITS)) {
            return false;
        }
    }
    /* put in null mappings for any extra IOAPICs */
    for (; i < CONFIG_MAX_NUM_IOAPIC; i++) {
        pte = x86_make_empty_pte();
        assert(idx == ( (PPTR_IOAPIC_START + i * BIT(PAGE_BITS)) & MASK(LARGE_PAGE_BITS)) >> PAGE_BITS);
        pt[idx] = pte;
        idx++;
    }

    /* map kernel devices: IOMMUs */
    for (i = 0; i < num_drhu; i++) {
        phys = (paddr_t)drhu_list[i];
        if (!add_allocated_p_region((p_region_t) {
        phys, phys + 0x1000
    })) {
            return false;
        }
        pte = x86_make_device_pte(phys);

        assert(idx == ((PPTR_DRHU_START + i * BIT(PAGE_BITS)) & MASK(LARGE_PAGE_BITS)) >> PAGE_BITS);
        pt[idx] = pte;
        idx++;
        if (idx == BIT(PT_INDEX_BITS)) {
            return false;
        }
    }

    /* mark unused kernel-device pages as 'not present' */
    while (idx < BIT(PT_INDEX_BITS)) {
        pte = x86_make_empty_pte();
        pt[idx] = pte;
        idx++;
    }

    /* Check we haven't added too many kernel-device mappings.*/
    assert(idx == BIT(PT_INDEX_BITS));
    return true;
}

BOOT_CODE static void
init_idt(idt_entry_t* idt)
{
    init_idt_entry(idt, 0x00, int_00);
    init_idt_entry(idt, 0x01, int_01);
    init_idt_entry(idt, 0x02, int_02);
    init_idt_entry(idt, 0x03, int_03);
    init_idt_entry(idt, 0x04, int_04);
    init_idt_entry(idt, 0x05, int_05);
    init_idt_entry(idt, 0x06, int_06);
    init_idt_entry(idt, 0x07, int_07);
    init_idt_entry(idt, 0x08, int_08);
    init_idt_entry(idt, 0x09, int_09);
    init_idt_entry(idt, 0x0a, int_0a);
    init_idt_entry(idt, 0x0b, int_0b);
    init_idt_entry(idt, 0x0c, int_0c);
    init_idt_entry(idt, 0x0d, int_0d);
    init_idt_entry(idt, 0x0e, int_0e);
    init_idt_entry(idt, 0x0f, int_0f);

    init_idt_entry(idt, 0x10, int_10);
    init_idt_entry(idt, 0x11, int_11);
    init_idt_entry(idt, 0x12, int_12);
    init_idt_entry(idt, 0x13, int_13);
    init_idt_entry(idt, 0x14, int_14);
    init_idt_entry(idt, 0x15, int_15);
    init_idt_entry(idt, 0x16, int_16);
    init_idt_entry(idt, 0x17, int_17);
    init_idt_entry(idt, 0x18, int_18);
    init_idt_entry(idt, 0x19, int_19);
    init_idt_entry(idt, 0x1a, int_1a);
    init_idt_entry(idt, 0x1b, int_1b);
    init_idt_entry(idt, 0x1c, int_1c);
    init_idt_entry(idt, 0x1d, int_1d);
    init_idt_entry(idt, 0x1e, int_1e);
    init_idt_entry(idt, 0x1f, int_1f);

    init_idt_entry(idt, 0x20, int_20);
    init_idt_entry(idt, 0x21, int_21);
    init_idt_entry(idt, 0x22, int_22);
    init_idt_entry(idt, 0x23, int_23);
    init_idt_entry(idt, 0x24, int_24);
    init_idt_entry(idt, 0x25, int_25);
    init_idt_entry(idt, 0x26, int_26);
    init_idt_entry(idt, 0x27, int_27);
    init_idt_entry(idt, 0x28, int_28);
    init_idt_entry(idt, 0x29, int_29);
    init_idt_entry(idt, 0x2a, int_2a);
    init_idt_entry(idt, 0x2b, int_2b);
    init_idt_entry(idt, 0x2c, int_2c);
    init_idt_entry(idt, 0x2d, int_2d);
    init_idt_entry(idt, 0x2e, int_2e);
    init_idt_entry(idt, 0x2f, int_2f);

    init_idt_entry(idt, 0x30, int_30);
    init_idt_entry(idt, 0x31, int_31);
    init_idt_entry(idt, 0x32, int_32);
    init_idt_entry(idt, 0x33, int_33);
    init_idt_entry(idt, 0x34, int_34);
    init_idt_entry(idt, 0x35, int_35);
    init_idt_entry(idt, 0x36, int_36);
    init_idt_entry(idt, 0x37, int_37);
    init_idt_entry(idt, 0x38, int_38);
    init_idt_entry(idt, 0x39, int_39);
    init_idt_entry(idt, 0x3a, int_3a);
    init_idt_entry(idt, 0x3b, int_3b);
    init_idt_entry(idt, 0x3c, int_3c);
    init_idt_entry(idt, 0x3d, int_3d);
    init_idt_entry(idt, 0x3e, int_3e);
    init_idt_entry(idt, 0x3f, int_3f);

    init_idt_entry(idt, 0x40, int_40);
    init_idt_entry(idt, 0x41, int_41);
    init_idt_entry(idt, 0x42, int_42);
    init_idt_entry(idt, 0x43, int_43);
    init_idt_entry(idt, 0x44, int_44);
    init_idt_entry(idt, 0x45, int_45);
    init_idt_entry(idt, 0x46, int_46);
    init_idt_entry(idt, 0x47, int_47);
    init_idt_entry(idt, 0x48, int_48);
    init_idt_entry(idt, 0x49, int_49);
    init_idt_entry(idt, 0x4a, int_4a);
    init_idt_entry(idt, 0x4b, int_4b);
    init_idt_entry(idt, 0x4c, int_4c);
    init_idt_entry(idt, 0x4d, int_4d);
    init_idt_entry(idt, 0x4e, int_4e);
    init_idt_entry(idt, 0x4f, int_4f);

    init_idt_entry(idt, 0x50, int_50);
    init_idt_entry(idt, 0x51, int_51);
    init_idt_entry(idt, 0x52, int_52);
    init_idt_entry(idt, 0x53, int_53);
    init_idt_entry(idt, 0x54, int_54);
    init_idt_entry(idt, 0x55, int_55);
    init_idt_entry(idt, 0x56, int_56);
    init_idt_entry(idt, 0x57, int_57);
    init_idt_entry(idt, 0x58, int_58);
    init_idt_entry(idt, 0x59, int_59);
    init_idt_entry(idt, 0x5a, int_5a);
    init_idt_entry(idt, 0x5b, int_5b);
    init_idt_entry(idt, 0x5c, int_5c);
    init_idt_entry(idt, 0x5d, int_5d);
    init_idt_entry(idt, 0x5e, int_5e);
    init_idt_entry(idt, 0x5f, int_5f);

    init_idt_entry(idt, 0x60, int_60);
    init_idt_entry(idt, 0x61, int_61);
    init_idt_entry(idt, 0x62, int_62);
    init_idt_entry(idt, 0x63, int_63);
    init_idt_entry(idt, 0x64, int_64);
    init_idt_entry(idt, 0x65, int_65);
    init_idt_entry(idt, 0x66, int_66);
    init_idt_entry(idt, 0x67, int_67);
    init_idt_entry(idt, 0x68, int_68);
    init_idt_entry(idt, 0x69, int_69);
    init_idt_entry(idt, 0x6a, int_6a);
    init_idt_entry(idt, 0x6b, int_6b);
    init_idt_entry(idt, 0x6c, int_6c);
    init_idt_entry(idt, 0x6d, int_6d);
    init_idt_entry(idt, 0x6e, int_6e);
    init_idt_entry(idt, 0x6f, int_6f);

    init_idt_entry(idt, 0x70, int_70);
    init_idt_entry(idt, 0x71, int_71);
    init_idt_entry(idt, 0x72, int_72);
    init_idt_entry(idt, 0x73, int_73);
    init_idt_entry(idt, 0x74, int_74);
    init_idt_entry(idt, 0x75, int_75);
    init_idt_entry(idt, 0x76, int_76);
    init_idt_entry(idt, 0x77, int_77);
    init_idt_entry(idt, 0x78, int_78);
    init_idt_entry(idt, 0x79, int_79);
    init_idt_entry(idt, 0x7a, int_7a);
    init_idt_entry(idt, 0x7b, int_7b);
    init_idt_entry(idt, 0x7c, int_7c);
    init_idt_entry(idt, 0x7d, int_7d);
    init_idt_entry(idt, 0x7e, int_7e);
    init_idt_entry(idt, 0x7f, int_7f);

    init_idt_entry(idt, 0x80, int_80);
    init_idt_entry(idt, 0x81, int_81);
    init_idt_entry(idt, 0x82, int_82);
    init_idt_entry(idt, 0x83, int_83);
    init_idt_entry(idt, 0x84, int_84);
    init_idt_entry(idt, 0x85, int_85);
    init_idt_entry(idt, 0x86, int_86);
    init_idt_entry(idt, 0x87, int_87);
    init_idt_entry(idt, 0x88, int_88);
    init_idt_entry(idt, 0x89, int_89);
    init_idt_entry(idt, 0x8a, int_8a);
    init_idt_entry(idt, 0x8b, int_8b);
    init_idt_entry(idt, 0x8c, int_8c);
    init_idt_entry(idt, 0x8d, int_8d);
    init_idt_entry(idt, 0x8e, int_8e);
    init_idt_entry(idt, 0x8f, int_8f);

    init_idt_entry(idt, 0x90, int_90);
    init_idt_entry(idt, 0x91, int_91);
    init_idt_entry(idt, 0x92, int_92);
    init_idt_entry(idt, 0x93, int_93);
    init_idt_entry(idt, 0x94, int_94);
    init_idt_entry(idt, 0x95, int_95);
    init_idt_entry(idt, 0x96, int_96);
    init_idt_entry(idt, 0x97, int_97);
    init_idt_entry(idt, 0x98, int_98);
    init_idt_entry(idt, 0x99, int_99);
    init_idt_entry(idt, 0x9a, int_9a);
    init_idt_entry(idt, 0x9b, int_9b);
    init_idt_entry(idt, 0x9c, int_9c);
    init_idt_entry(idt, 0x9d, int_9d);
    init_idt_entry(idt, 0x9e, int_9e);
    init_idt_entry(idt, 0x9f, int_9f);

    init_idt_entry(idt, 0xa0, int_a0);
    init_idt_entry(idt, 0xa1, int_a1);
    init_idt_entry(idt, 0xa2, int_a2);
    init_idt_entry(idt, 0xa3, int_a3);
    init_idt_entry(idt, 0xa4, int_a4);
    init_idt_entry(idt, 0xa5, int_a5);
    init_idt_entry(idt, 0xa6, int_a6);
    init_idt_entry(idt, 0xa7, int_a7);
    init_idt_entry(idt, 0xa8, int_a8);
    init_idt_entry(idt, 0xa9, int_a9);
    init_idt_entry(idt, 0xaa, int_aa);
    init_idt_entry(idt, 0xab, int_ab);
    init_idt_entry(idt, 0xac, int_ac);
    init_idt_entry(idt, 0xad, int_ad);
    init_idt_entry(idt, 0xae, int_ae);
    init_idt_entry(idt, 0xaf, int_af);

    init_idt_entry(idt, 0xb0, int_b0);
    init_idt_entry(idt, 0xb1, int_b1);
    init_idt_entry(idt, 0xb2, int_b2);
    init_idt_entry(idt, 0xb3, int_b3);
    init_idt_entry(idt, 0xb4, int_b4);
    init_idt_entry(idt, 0xb5, int_b5);
    init_idt_entry(idt, 0xb6, int_b6);
    init_idt_entry(idt, 0xb7, int_b7);
    init_idt_entry(idt, 0xb8, int_b8);
    init_idt_entry(idt, 0xb9, int_b9);
    init_idt_entry(idt, 0xba, int_ba);
    init_idt_entry(idt, 0xbb, int_bb);
    init_idt_entry(idt, 0xbc, int_bc);
    init_idt_entry(idt, 0xbd, int_bd);
    init_idt_entry(idt, 0xbe, int_be);
    init_idt_entry(idt, 0xbf, int_bf);

    init_idt_entry(idt, 0xc0, int_c0);
    init_idt_entry(idt, 0xc1, int_c1);
    init_idt_entry(idt, 0xc2, int_c2);
    init_idt_entry(idt, 0xc3, int_c3);
    init_idt_entry(idt, 0xc4, int_c4);
    init_idt_entry(idt, 0xc5, int_c5);
    init_idt_entry(idt, 0xc6, int_c6);
    init_idt_entry(idt, 0xc7, int_c7);
    init_idt_entry(idt, 0xc8, int_c8);
    init_idt_entry(idt, 0xc9, int_c9);
    init_idt_entry(idt, 0xca, int_ca);
    init_idt_entry(idt, 0xcb, int_cb);
    init_idt_entry(idt, 0xcc, int_cc);
    init_idt_entry(idt, 0xcd, int_cd);
    init_idt_entry(idt, 0xce, int_ce);
    init_idt_entry(idt, 0xcf, int_cf);

    init_idt_entry(idt, 0xd0, int_d0);
    init_idt_entry(idt, 0xd1, int_d1);
    init_idt_entry(idt, 0xd2, int_d2);
    init_idt_entry(idt, 0xd3, int_d3);
    init_idt_entry(idt, 0xd4, int_d4);
    init_idt_entry(idt, 0xd5, int_d5);
    init_idt_entry(idt, 0xd6, int_d6);
    init_idt_entry(idt, 0xd7, int_d7);
    init_idt_entry(idt, 0xd8, int_d8);
    init_idt_entry(idt, 0xd9, int_d9);
    init_idt_entry(idt, 0xda, int_da);
    init_idt_entry(idt, 0xdb, int_db);
    init_idt_entry(idt, 0xdc, int_dc);
    init_idt_entry(idt, 0xdd, int_dd);
    init_idt_entry(idt, 0xde, int_de);
    init_idt_entry(idt, 0xdf, int_df);

    init_idt_entry(idt, 0xe0, int_e0);
    init_idt_entry(idt, 0xe1, int_e1);
    init_idt_entry(idt, 0xe2, int_e2);
    init_idt_entry(idt, 0xe3, int_e3);
    init_idt_entry(idt, 0xe4, int_e4);
    init_idt_entry(idt, 0xe5, int_e5);
    init_idt_entry(idt, 0xe6, int_e6);
    init_idt_entry(idt, 0xe7, int_e7);
    init_idt_entry(idt, 0xe8, int_e8);
    init_idt_entry(idt, 0xe9, int_e9);
    init_idt_entry(idt, 0xea, int_ea);
    init_idt_entry(idt, 0xeb, int_eb);
    init_idt_entry(idt, 0xec, int_ec);
    init_idt_entry(idt, 0xed, int_ed);
    init_idt_entry(idt, 0xee, int_ee);
    init_idt_entry(idt, 0xef, int_ef);

    init_idt_entry(idt, 0xf0, int_f0);
    init_idt_entry(idt, 0xf1, int_f1);
    init_idt_entry(idt, 0xf2, int_f2);
    init_idt_entry(idt, 0xf3, int_f3);
    init_idt_entry(idt, 0xf4, int_f4);
    init_idt_entry(idt, 0xf5, int_f5);
    init_idt_entry(idt, 0xf6, int_f6);
    init_idt_entry(idt, 0xf7, int_f7);
    init_idt_entry(idt, 0xf8, int_f8);
    init_idt_entry(idt, 0xf9, int_f9);
    init_idt_entry(idt, 0xfa, int_fa);
    init_idt_entry(idt, 0xfb, int_fb);
    init_idt_entry(idt, 0xfc, int_fc);
    init_idt_entry(idt, 0xfd, int_fd);
    init_idt_entry(idt, 0xfe, int_fe);
    init_idt_entry(idt, 0xff, int_ff);
}

BOOT_CODE bool_t
init_vm_state(void)
{
    word_t cacheLineSize;
    x86KScacheLineSizeBits = getCacheLineSizeBits();
    if (!x86KScacheLineSizeBits) {
        return false;
    }

    cacheLineSize = BIT(x86KScacheLineSizeBits);
    if (cacheLineSize != L1_CACHE_LINE_SIZE) {
        printf("Configured cache line size is %d but detected size is %lu\n",
               L1_CACHE_LINE_SIZE, cacheLineSize);
        SMP_COND_STATEMENT(return false);
    }

    init_tss(&x86KSGlobalState[CURRENT_CPU_INDEX()].x86KStss.tss);
    init_gdt(x86KSGlobalState[CURRENT_CPU_INDEX()].x86KSgdt, &x86KSGlobalState[CURRENT_CPU_INDEX()].x86KStss.tss);
    init_idt(x86KSGlobalState[CURRENT_CPU_INDEX()].x86KSidt);
    return true;
}

BOOT_CODE bool_t
init_pat_msr(void)
{
    x86_pat_msr_t pat_msr;
    /* First verify PAT is supported by the machine.
     *      See section 11.12.1 of Volume 3 of the Intel manual */
    if ( (x86_cpuid_edx(0x1, 0x0) & BIT(16)) == 0) {
        printf("PAT support not found\n");
        return false;
    }
    pat_msr.words[0] = x86_rdmsr_low(IA32_PAT_MSR);
    pat_msr.words[1] = x86_rdmsr_high(IA32_PAT_MSR);
    /* Set up the PAT MSR to the Intel defaults, just in case
     * they have been changed but a bootloader somewhere along the way */
    pat_msr = x86_pat_msr_set_pa0(pat_msr, IA32_PAT_MT_WRITE_BACK);
    pat_msr = x86_pat_msr_set_pa1(pat_msr, IA32_PAT_MT_WRITE_THROUGH);
    pat_msr = x86_pat_msr_set_pa2(pat_msr, IA32_PAT_MT_UNCACHED);
    pat_msr = x86_pat_msr_set_pa3(pat_msr, IA32_PAT_MT_UNCACHEABLE);
    /* Add the WriteCombining cache type to the PAT */
    pat_msr = x86_pat_msr_set_pa4(pat_msr, IA32_PAT_MT_WRITE_COMBINING);
    x86_wrmsr(IA32_PAT_MSR, ((uint64_t)pat_msr.words[1]) << 32 | pat_msr.words[0]);
    return true;
}

BOOT_CODE void
write_it_asid_pool(cap_t it_ap_cap, cap_t it_vspace_cap)
{
    asid_pool_t* ap = ASID_POOL_PTR(pptr_of_cap(it_ap_cap));
    ap->array[IT_ASID] = asid_map_asid_map_vspace_new(pptr_of_cap(it_vspace_cap));
    x86KSASIDTable[IT_ASID >> asidLowBits] = ap;
}

asid_map_t
findMapForASID(asid_t asid)
{
    asid_pool_t*        poolPtr;

    poolPtr = x86KSASIDTable[asid >> asidLowBits];
    if (!poolPtr) {
        return asid_map_asid_map_none_new();
    }

    return poolPtr->array[asid & MASK(asidLowBits)];
}

findVSpaceForASID_ret_t findVSpaceForASID(asid_t asid)
{
    findVSpaceForASID_ret_t ret;
    asid_map_t asid_map;

    asid_map = findMapForASID(asid);
    if (asid_map_get_type(asid_map) != asid_map_asid_map_vspace) {
        current_lookup_fault = lookup_fault_invalid_root_new();

        ret.vspace_root = NULL;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }

    ret.vspace_root = (vspace_root_t*)asid_map_asid_map_vspace_get_vspace_root(asid_map);
    ret.status = EXCEPTION_NONE;
    return ret;
}

exception_t handleVMFault(tcb_t* thread, vm_fault_type_t vm_faultType)
{
    word_t addr;
    uint32_t fault;

    addr = getFaultAddr();
    fault = getRegister(thread, Error);

    switch (vm_faultType) {
    case X86DataFault:
        current_fault = seL4_Fault_VMFault_new(addr, fault, false);
        return EXCEPTION_FAULT;

    case X86InstructionFault:
        current_fault = seL4_Fault_VMFault_new(addr, fault, true);
        return EXCEPTION_FAULT;

    default:
        fail("Invalid VM fault type");
    }
}

uint32_t CONST WritableFromVMRights(vm_rights_t vm_rights)
{
    switch (vm_rights) {
    case VMReadOnly:
        return 0;

    case VMKernelOnly:
    case VMReadWrite:
        return 1;

    default:
        fail("Invalid VM rights");
    }
}

uint32_t CONST SuperUserFromVMRights(vm_rights_t vm_rights)
{
    switch (vm_rights) {
    case VMKernelOnly:
        return 0;

    case VMReadOnly:
    case VMReadWrite:
        return 1;

    default:
        fail("Invalid VM rights");
    }
}

lookupPTSlot_ret_t lookupPTSlot(vspace_root_t *vspace, vptr_t vptr)
{
    lookupPTSlot_ret_t ret;
    lookupPDSlot_ret_t pdSlot;

    pdSlot = lookupPDSlot(vspace, vptr);
    if (pdSlot.status != EXCEPTION_NONE) {
        ret.ptSlot = NULL;
        ret.status = pdSlot.status;
        return ret;
    }
    if ((pde_ptr_get_page_size(pdSlot.pdSlot) != pde_pde_pt) ||
            !pde_pde_pt_ptr_get_present(pdSlot.pdSlot)) {
        current_lookup_fault = lookup_fault_missing_capability_new(PAGE_BITS + PT_INDEX_BITS);
        ret.ptSlot = NULL;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    } else {
        pte_t* pt;
        pte_t* ptSlot;
        word_t ptIndex;

        pt = paddr_to_pptr(pde_pde_pt_ptr_get_pt_base_address(pdSlot.pdSlot));
        ptIndex = (vptr >> PAGE_BITS) & MASK(PT_INDEX_BITS);
        ptSlot = pt + ptIndex;

        ret.ptSlot = ptSlot;
        ret.status = EXCEPTION_NONE;
        return ret;
    }
}

exception_t checkValidIPCBuffer(vptr_t vptr, cap_t cap)
{
    if (cap_get_capType(cap) != cap_frame_cap) {
        userError("IPC Buffer is an invalid cap.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
    if (unlikely(cap_frame_cap_get_capFIsDevice(cap))) {
        userError("Specifying a device frame as an IPC buffer is not permitted.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (!IS_ALIGNED(vptr, seL4_IPCBufferSizeBits)) {
        userError("IPC Buffer vaddr 0x%x is not aligned.", (int)vptr);
        current_syscall_error.type = seL4_AlignmentError;
        return EXCEPTION_SYSCALL_ERROR;
    }

    return EXCEPTION_NONE;
}

vm_rights_t CONST maskVMRights(vm_rights_t vm_rights, seL4_CapRights_t cap_rights_mask)
{
    if (vm_rights == VMReadOnly && seL4_CapRights_get_capAllowRead(cap_rights_mask)) {
        return VMReadOnly;
    }
    if (vm_rights == VMReadWrite && seL4_CapRights_get_capAllowRead(cap_rights_mask)) {
        if (!seL4_CapRights_get_capAllowWrite(cap_rights_mask)) {
            return VMReadOnly;
        } else {
            return VMReadWrite;
        }
    }
    return VMKernelOnly;
}

void flushTable(vspace_root_t *vspace, word_t vptr, pte_t* pt, asid_t asid)
{
    word_t i;
    cap_t        threadRoot;

    assert(IS_ALIGNED(vptr, PT_INDEX_BITS + PAGE_BITS));

    /* check if page table belongs to current address space */
    threadRoot = TCB_PTR_CTE_PTR(NODE_STATE(ksCurThread), tcbVTable)->cap;
    /* find valid mappings */
    for (i = 0; i < BIT(PT_INDEX_BITS); i++) {
        if (pte_get_present(pt[i])) {
            if (config_set(CONFIG_SUPPORT_PCID) || (isValidNativeRoot(threadRoot) && (vspace_root_t*)pptr_of_cap(threadRoot) == vspace)) {
                invalidateTranslationSingleASID(vptr + (i << PAGE_BITS), asid,
                                                SMP_TERNARY(tlb_bitmap_get(vspace), 0));
            }
        }
    }
}


void unmapPage(vm_page_size_t page_size, asid_t asid, vptr_t vptr, void *pptr)
{
    findVSpaceForASID_ret_t find_ret;
    lookupPTSlot_ret_t  lu_ret;
    cap_t               threadRoot;
    lookupPDSlot_ret_t  pd_ret;
    pde_t               *pde;

    find_ret = findVSpaceForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        return;
    }

    switch (page_size) {
    case X86_SmallPage:
        lu_ret = lookupPTSlot(find_ret.vspace_root, vptr);
        if (lu_ret.status != EXCEPTION_NONE) {
            return;
        }
        if (! (pte_ptr_get_present(lu_ret.ptSlot)
                && (pte_ptr_get_page_base_address(lu_ret.ptSlot)
                    == pptr_to_paddr(pptr)))) {
            return;
        }
        *lu_ret.ptSlot = makeUserPTEInvalid();
        break;

    case X86_LargePage:
        pd_ret = lookupPDSlot(find_ret.vspace_root, vptr);
        if (pd_ret.status != EXCEPTION_NONE) {
            return;
        }
        pde = pd_ret.pdSlot;
        if (! (pde_ptr_get_page_size(pde) == pde_pde_large
                && pde_pde_large_ptr_get_present(pde)
                && (pde_pde_large_ptr_get_page_base_address(pde)
                    == pptr_to_paddr(pptr)))) {
            return;
        }
        *pde = makeUserPDEInvalid();
        break;

    default:
        if (!modeUnmapPage(page_size, find_ret.vspace_root, vptr, pptr)) {
            return;
        }
        break;
    }

    /* check if page belongs to current address space */
    threadRoot = TCB_PTR_CTE_PTR(NODE_STATE(ksCurThread), tcbVTable)->cap;
    if (config_set(CONFIG_SUPPORT_PCID) || (isValidNativeRoot(threadRoot) && (vspace_root_t*)pptr_of_cap(threadRoot) == find_ret.vspace_root)) {
        invalidateTranslationSingleASID(vptr, asid,
                                        SMP_TERNARY(tlb_bitmap_get(find_ret.vspace_root), 0));
    }
}

void unmapPageTable(asid_t asid, vptr_t vaddr, pte_t* pt)
{
    findVSpaceForASID_ret_t find_ret;
    lookupPDSlot_ret_t    lu_ret;

    find_ret = findVSpaceForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        return;
    }

    lu_ret = lookupPDSlot(find_ret.vspace_root, vaddr);
    if (lu_ret.status != EXCEPTION_NONE) {
        return;
    }

    /* check if the PD actually refers to the PT */
    if (! (pde_ptr_get_page_size(lu_ret.pdSlot) == pde_pde_pt &&
            pde_pde_pt_ptr_get_present(lu_ret.pdSlot) &&
            (pde_pde_pt_ptr_get_pt_base_address(lu_ret.pdSlot) == pptr_to_paddr(pt)))) {
        return;
    }

    flushTable(find_ret.vspace_root, vaddr, pt, asid);

    *lu_ret.pdSlot = makeUserPDEInvalid();

    invalidatePageStructureCacheASID(pptr_to_paddr(find_ret.vspace_root), asid,
                                     SMP_TERNARY(tlb_bitmap_get(find_ret.vspace_root), 0));
}

static exception_t
performX86PageInvocationMapPTE(cap_t cap, cte_t *ctSlot, pte_t *ptSlot, pte_t pte, vspace_root_t *vspace)
{
    ctSlot->cap = cap;
    *ptSlot = pte;
    invalidatePageStructureCacheASID(pptr_to_paddr(vspace), cap_frame_cap_get_capFMappedASID(cap),
                                     SMP_TERNARY(tlb_bitmap_get(vspace), 0));
    return EXCEPTION_NONE;
}

static exception_t
performX86PageInvocationMapPDE(cap_t cap, cte_t *ctSlot, pde_t *pdSlot, pde_t pde, vspace_root_t *vspace)
{
    ctSlot->cap = cap;
    *pdSlot = pde;
    invalidatePageStructureCacheASID(pptr_to_paddr(vspace), cap_frame_cap_get_capFMappedASID(cap),
                                     SMP_TERNARY(tlb_bitmap_get(vspace), 0));
    return EXCEPTION_NONE;
}

static exception_t
performX86PageInvocationRemapPTE(pte_t *ptSlot, pte_t pte, asid_t asid, vspace_root_t *vspace)
{
    *ptSlot = pte;
    invalidatePageStructureCacheASID(pptr_to_paddr(vspace), asid,
                                     SMP_TERNARY(tlb_bitmap_get(vspace), 0));
    return EXCEPTION_NONE;
}

static exception_t
performX86PageInvocationRemapPDE(pde_t *pdSlot, pde_t pde, asid_t asid, vspace_root_t *vspace)
{
    *pdSlot = pde;
    invalidatePageStructureCacheASID(pptr_to_paddr(vspace), asid,
                                     SMP_TERNARY(tlb_bitmap_get(vspace), 0));
    return EXCEPTION_NONE;
}

static exception_t
performX86PageInvocationUnmap(cap_t cap, cte_t *ctSlot)
{
    assert(cap_frame_cap_get_capFMappedASID(cap));
    assert(cap_frame_cap_get_capFMapType(cap) == X86_MappingVSpace);
    // We have this `if` for something we just asserted to be true for simplicity of verification
    // This has no performance implications as when this function is inlined this `if` will be
    // inside an identical `if` and will therefore be elided
    if (cap_frame_cap_get_capFMappedASID(cap)) {
        unmapPage(
            cap_frame_cap_get_capFSize(cap),
            cap_frame_cap_get_capFMappedASID(cap),
            cap_frame_cap_get_capFMappedAddress(cap),
            (void *)cap_frame_cap_get_capFBasePtr(cap)
        );
    }

    cap_frame_cap_ptr_set_capFMappedAddress(&ctSlot->cap, 0);
    cap_frame_cap_ptr_set_capFMappedASID(&ctSlot->cap, asidInvalid);
    cap_frame_cap_ptr_set_capFMapType(&ctSlot->cap, X86_MappingNone);

    return EXCEPTION_NONE;
}

static exception_t
performX86FrameInvocationUnmap(cap_t cap, cte_t *cte)
{
    if (cap_frame_cap_get_capFMappedASID(cap) != asidInvalid) {
        switch (cap_frame_cap_get_capFMapType(cap)) {
        case X86_MappingVSpace:
            return performX86PageInvocationUnmap(cap, cte);
#ifdef CONFIG_IOMMU
        case X86_MappingIOSpace:
            return performX86IOUnMapInvocation(cap, cte);
#endif
#ifdef CONFIG_VTX
        case X86_MappingEPT:
            return performX86EPTPageInvocationUnmap(cap, cte);
#endif
        case X86_MappingNone:
            fail("Mapped frame cap was not mapped");
            break;
        }
    }

    return EXCEPTION_NONE;
}

struct create_mapping_pte_return {
    exception_t status;
    pte_t pte;
    pte_t *ptSlot;
};
typedef struct create_mapping_pte_return create_mapping_pte_return_t;

static create_mapping_pte_return_t
createSafeMappingEntries_PTE(paddr_t base, word_t vaddr, vm_rights_t vmRights, vm_attributes_t attr,
                             vspace_root_t *vspace)
{
    create_mapping_pte_return_t ret;
    lookupPTSlot_ret_t          lu_ret;

    lu_ret = lookupPTSlot(vspace, vaddr);
    if (lu_ret.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        ret.status = EXCEPTION_SYSCALL_ERROR;
        /* current_lookup_fault will have been set by lookupPTSlot */
        return ret;
    }

    ret.pte = makeUserPTE(base, attr, vmRights);
    ret.ptSlot = lu_ret.ptSlot;
    ret.status = EXCEPTION_NONE;
    return ret;
}

struct create_mapping_pde_return {
    exception_t status;
    pde_t pde;
    pde_t *pdSlot;
};
typedef struct create_mapping_pde_return create_mapping_pde_return_t;

static create_mapping_pde_return_t
createSafeMappingEntries_PDE(paddr_t base, word_t vaddr, vm_rights_t vmRights, vm_attributes_t attr,
                             vspace_root_t *vspace)
{
    create_mapping_pde_return_t ret;
    lookupPDSlot_ret_t          lu_ret;

    lu_ret = lookupPDSlot(vspace, vaddr);
    if (lu_ret.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        ret.status = EXCEPTION_SYSCALL_ERROR;
        /* current_lookup_fault will have been set by lookupPDSlot */
        return ret;
    }
    ret.pdSlot = lu_ret.pdSlot;

    /* check for existing page table */
    if ((pde_ptr_get_page_size(ret.pdSlot) == pde_pde_pt) &&
            (pde_pde_pt_ptr_get_present(ret.pdSlot))) {
        current_syscall_error.type = seL4_DeleteFirst;
        ret.status = EXCEPTION_SYSCALL_ERROR;
        return ret;
    }


    ret.pde = makeUserPDELargePage(base, attr, vmRights);
    ret.status = EXCEPTION_NONE;
    return ret;
}


exception_t decodeX86FrameInvocation(
    word_t invLabel,
    word_t length,
    cte_t* cte,
    cap_t cap,
    extra_caps_t excaps,
    word_t* buffer
)
{
    switch (invLabel) {
    case X86PageMap: { /* Map */
        word_t          vaddr;
        word_t          vtop;
        word_t          w_rightsMask;
        paddr_t         paddr;
        cap_t           vspaceCap;
        vspace_root_t*  vspace;
        vm_rights_t     capVMRights;
        vm_rights_t     vmRights;
        vm_attributes_t vmAttr;
        vm_page_size_t  frameSize;
        asid_t          asid;

        if (length < 3 || excaps.excaprefs[0] == NULL) {
            current_syscall_error.type = seL4_TruncatedMessage;

            return EXCEPTION_SYSCALL_ERROR;
        }

        frameSize = cap_frame_cap_get_capFSize(cap);
        vaddr = getSyscallArg(0, buffer);
        w_rightsMask = getSyscallArg(1, buffer);
        vmAttr = vmAttributesFromWord(getSyscallArg(2, buffer));
        vspaceCap = excaps.excaprefs[0]->cap;

        capVMRights = cap_frame_cap_get_capFVMRights(cap);

        if (cap_frame_cap_get_capFMappedASID(cap) != asidInvalid) {
            userError("X86FrameMap: Frame already mapped.");
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;

            return EXCEPTION_SYSCALL_ERROR;
        }

        assert(cap_frame_cap_get_capFMapType(cap) == X86_MappingNone);

        if (!isValidNativeRoot(vspaceCap)) {
            userError("X86FrameMap: Attempting to map frame into invalid page directory cap.");
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 1;

            return EXCEPTION_SYSCALL_ERROR;
        }
        vspace = (vspace_root_t*)pptr_of_cap(vspaceCap);
        asid = cap_get_capMappedASID(vspaceCap);

        {
            findVSpaceForASID_ret_t find_ret;

            find_ret = findVSpaceForASID(asid);
            if (find_ret.status != EXCEPTION_NONE) {
                current_syscall_error.type = seL4_FailedLookup;
                current_syscall_error.failedLookupWasSource = false;

                return EXCEPTION_SYSCALL_ERROR;
            }

            if (find_ret.vspace_root != vspace) {
                current_syscall_error.type = seL4_InvalidCapability;
                current_syscall_error.invalidCapNumber = 1;

                return EXCEPTION_SYSCALL_ERROR;
            }
        }

        vtop = vaddr + BIT(pageBitsForSize(frameSize));

        // check vaddr and vtop against PPTR_USER_TOP to catch case where vaddr + frame_size wrapped around
        if (vaddr > PPTR_USER_TOP || vtop > PPTR_USER_TOP) {
            userError("X86Frame: Mapping address too high.");
            current_syscall_error.type = seL4_InvalidArgument;
            current_syscall_error.invalidArgumentNumber = 0;

            return EXCEPTION_SYSCALL_ERROR;
        }

        vmRights = maskVMRights(capVMRights, rightsFromWord(w_rightsMask));

        if (!checkVPAlignment(frameSize, vaddr)) {
            current_syscall_error.type = seL4_AlignmentError;

            return EXCEPTION_SYSCALL_ERROR;
        }

        paddr = pptr_to_paddr((void*)cap_frame_cap_get_capFBasePtr(cap));

        cap = cap_frame_cap_set_capFMappedASID(cap, asid);
        cap = cap_frame_cap_set_capFMappedAddress(cap, vaddr);
        cap = cap_frame_cap_set_capFMapType(cap, X86_MappingVSpace);

        switch (frameSize) {
        /* PTE mappings */
        case X86_SmallPage: {
            create_mapping_pte_return_t map_ret;

            map_ret = createSafeMappingEntries_PTE(paddr, vaddr, vmRights, vmAttr, vspace);
            if (map_ret.status != EXCEPTION_NONE) {
                return map_ret.status;
            }

            setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
            return performX86PageInvocationMapPTE(cap, cte, map_ret.ptSlot, map_ret.pte, vspace);
        }

        /* PDE mappings */
        case X86_LargePage: {
            create_mapping_pde_return_t map_ret;

            map_ret = createSafeMappingEntries_PDE(paddr, vaddr, vmRights, vmAttr, vspace);
            if (map_ret.status != EXCEPTION_NONE) {
                return map_ret.status;
            }

            setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
            return performX86PageInvocationMapPDE(cap, cte, map_ret.pdSlot, map_ret.pde, vspace);
        }

        default: {
            return decodeX86ModeMapRemapPage(invLabel, frameSize, cte, cap, vspace, vaddr, paddr, vmRights, vmAttr);
        }
        }

        return EXCEPTION_SYSCALL_ERROR;
    }

    case X86PageRemap: { /* Remap */
        word_t          vaddr;
        word_t          w_rightsMask;
        paddr_t         paddr;
        cap_t           vspaceCap;
        vspace_root_t*  vspace;
        vm_rights_t     capVMRights;
        vm_rights_t     vmRights;
        vm_attributes_t vmAttr;
        vm_page_size_t  frameSize;
        asid_t          asid, mappedASID;

        if (length < 2 || excaps.excaprefs[0] == NULL) {
            userError("X86FrameRemap: Truncated message");
            current_syscall_error.type = seL4_TruncatedMessage;

            return EXCEPTION_SYSCALL_ERROR;
        }

        if (cap_frame_cap_get_capFMapType(cap) != X86_MappingVSpace) {
            userError("X86FrameRemap: Attempting to remap frame with different mapping type");
            current_syscall_error.type = seL4_IllegalOperation;

            return EXCEPTION_SYSCALL_ERROR;
        }

        w_rightsMask = getSyscallArg(0, buffer);
        vmAttr = vmAttributesFromWord(getSyscallArg(1, buffer));
        vspaceCap = excaps.excaprefs[0]->cap;

        if (!isValidNativeRoot(vspaceCap)) {
            userError("X86FrameRemap: Attempting to map frame into invalid vspace.");
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 1;

            return EXCEPTION_SYSCALL_ERROR;
        }

        mappedASID = cap_frame_cap_get_capFMappedASID(cap);

        if (mappedASID == asidInvalid) {
            userError("X86PageRemap: Frame cap is not mapped.");
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;

            return EXCEPTION_SYSCALL_ERROR;
        }

        vspace = (vspace_root_t*)pptr_of_cap(vspaceCap);
        asid = cap_get_capMappedASID(vspaceCap);

        {
            findVSpaceForASID_ret_t find_ret;

            find_ret = findVSpaceForASID(mappedASID);
            if (find_ret.status != EXCEPTION_NONE) {
                userError("X86PageRemap: No VSpace for ASID");
                current_syscall_error.type = seL4_FailedLookup;
                current_syscall_error.failedLookupWasSource = false;

                return EXCEPTION_SYSCALL_ERROR;
            }

            if (find_ret.vspace_root != vspace || asid != mappedASID) {
                userError("X86PageRemap: Failed ASID lookup");
                current_syscall_error.type = seL4_InvalidCapability;
                current_syscall_error.invalidCapNumber = 1;

                return EXCEPTION_SYSCALL_ERROR;
            }
        }

        vaddr       = cap_frame_cap_get_capFMappedAddress(cap);
        frameSize   = cap_frame_cap_get_capFSize(cap);
        capVMRights = cap_frame_cap_get_capFVMRights(cap);
        paddr       = pptr_to_paddr((void*)cap_frame_cap_get_capFBasePtr(cap));

        vmRights = maskVMRights(capVMRights, rightsFromWord(w_rightsMask));

        if (!checkVPAlignment(frameSize, vaddr)) {
            current_syscall_error.type = seL4_AlignmentError;

            return EXCEPTION_SYSCALL_ERROR;
        }

        switch (frameSize) {
        /* PTE mappings */
        case X86_SmallPage: {
            create_mapping_pte_return_t map_ret;

            map_ret = createSafeMappingEntries_PTE(paddr, vaddr, vmRights, vmAttr, vspace);
            if (map_ret.status != EXCEPTION_NONE) {
                return map_ret.status;
            }

            setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
            return performX86PageInvocationRemapPTE(map_ret.ptSlot, map_ret.pte, asid, vspace);

        }

        /* PDE mappings */
        case X86_LargePage: {
            create_mapping_pde_return_t map_ret;

            map_ret = createSafeMappingEntries_PDE(paddr, vaddr, vmRights, vmAttr, vspace);
            if (map_ret.status != EXCEPTION_NONE) {
                return map_ret.status;
            }

            setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
            return performX86PageInvocationRemapPDE(map_ret.pdSlot, map_ret.pde, asid, vspace);
        }

        default: {
            return decodeX86ModeMapRemapPage(invLabel, frameSize, cte, cap, vspace, vaddr, paddr, vmRights, vmAttr);
        }
        }

        return EXCEPTION_SYSCALL_ERROR;
    }

    case X86PageUnmap: { /* Unmap */
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performX86FrameInvocationUnmap(cap, cte);
    }

#ifdef CONFIG_IOMMU
    case X86PageMapIO: { /* MapIO */
        return decodeX86IOMapInvocation(length, cte, cap, excaps, buffer);
    }
#endif

#ifdef CONFIG_VTX
    case X86PageMapEPT:
        return decodeX86EPTPageMap(invLabel, length, cte, cap, excaps, buffer);
#endif

    case X86PageGetAddress: {
        /* Return it in the first message register. */
        assert(n_msgRegisters >= 1);

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performPageGetAddress((void*)cap_frame_cap_get_capFBasePtr(cap));
    }

    default:
        current_syscall_error.type = seL4_IllegalOperation;

        return EXCEPTION_SYSCALL_ERROR;
    }
}

static exception_t
performX86PageTableInvocationUnmap(cap_t cap, cte_t *ctSlot)
{

    if (cap_page_table_cap_get_capPTIsMapped(cap)) {
        pte_t *pt = PTE_PTR(cap_page_table_cap_get_capPTBasePtr(cap));
        unmapPageTable(
            cap_page_table_cap_get_capPTMappedASID(cap),
            cap_page_table_cap_get_capPTMappedAddress(cap),
            pt
        );
        clearMemory((void *)pt, cap_get_capSizeBits(cap));
    }
    cap_page_table_cap_ptr_set_capPTIsMapped(&(ctSlot->cap), 0);

    return EXCEPTION_NONE;
}

static exception_t
performX86PageTableInvocationMap(cap_t cap, cte_t *ctSlot, pde_t pde, pde_t *pdSlot, vspace_root_t *root)
{
    ctSlot->cap = cap;
    *pdSlot = pde;
    invalidatePageStructureCacheASID(pptr_to_paddr(root), cap_page_table_cap_get_capPTMappedASID(cap),
                                     SMP_TERNARY(tlb_bitmap_get(root), 0));
    return EXCEPTION_NONE;
}

static exception_t
decodeX86PageTableInvocation(
    word_t invLabel,
    word_t length,
    cte_t* cte, cap_t cap,
    extra_caps_t excaps,
    word_t* buffer
)
{
    word_t          vaddr;
    vm_attributes_t attr;
    lookupPDSlot_ret_t pdSlot;
    cap_t           vspaceCap;
    vspace_root_t*  vspace;
    pde_t           pde;
    paddr_t         paddr;
    asid_t          asid;

    if (invLabel == X86PageTableUnmap) {
        if (! isFinalCapability(cte)) {
            current_syscall_error.type = seL4_RevokeFirst;
            userError("X86PageTable: Cannot unmap if more than one cap exists.");
            return EXCEPTION_SYSCALL_ERROR;
        }
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performX86PageTableInvocationUnmap(cap, cte);
    }

    if (invLabel != X86PageTableMap ) {
        userError("X86PageTable: Illegal operation.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (length < 2 || excaps.excaprefs[0] == NULL) {
        userError("X86PageTable: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (cap_page_table_cap_get_capPTIsMapped(cap)) {
        userError("X86PageTable: Page table is already mapped to a page directory.");
        current_syscall_error.type =
            seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;

        return EXCEPTION_SYSCALL_ERROR;
    }

    vaddr = getSyscallArg(0, buffer) & (~MASK(PT_INDEX_BITS + PAGE_BITS));
    attr = vmAttributesFromWord(getSyscallArg(1, buffer));
    vspaceCap = excaps.excaprefs[0]->cap;

    if (!isValidNativeRoot(vspaceCap)) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;

        return EXCEPTION_SYSCALL_ERROR;
    }

    vspace = (vspace_root_t*)pptr_of_cap(vspaceCap);
    asid = cap_get_capMappedASID(vspaceCap);

    if (vaddr > PPTR_USER_TOP) {
        userError("X86PageTable: Mapping address too high.");
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 0;

        return EXCEPTION_SYSCALL_ERROR;
    }

    {
        findVSpaceForASID_ret_t find_ret;

        find_ret = findVSpaceForASID(asid);
        if (find_ret.status != EXCEPTION_NONE) {
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = false;

            return EXCEPTION_SYSCALL_ERROR;
        }

        if (find_ret.vspace_root != vspace) {
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 1;

            return EXCEPTION_SYSCALL_ERROR;
        }
    }

    pdSlot = lookupPDSlot(vspace, vaddr);
    if (pdSlot.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;

        return EXCEPTION_SYSCALL_ERROR;
    }

    if (((pde_ptr_get_page_size(pdSlot.pdSlot) == pde_pde_pt) && pde_pde_pt_ptr_get_present(pdSlot.pdSlot)) ||
            ((pde_ptr_get_page_size(pdSlot.pdSlot) == pde_pde_large) && pde_pde_large_ptr_get_present(pdSlot.pdSlot))) {
        current_syscall_error.type = seL4_DeleteFirst;

        return EXCEPTION_SYSCALL_ERROR;
    }

    paddr = pptr_to_paddr(PTE_PTR(cap_page_table_cap_get_capPTBasePtr(cap)));
    pde = makeUserPDEPageTable(paddr, attr);

    cap = cap_page_table_cap_set_capPTIsMapped(cap, 1);
    cap = cap_page_table_cap_set_capPTMappedASID(cap, asid);
    cap = cap_page_table_cap_set_capPTMappedAddress(cap, vaddr);

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return performX86PageTableInvocationMap(cap, cte, pde, pdSlot.pdSlot, vspace);
}

exception_t decodeX86MMUInvocation(
    word_t invLabel,
    word_t length,
    cptr_t cptr,
    cte_t* cte,
    cap_t cap,
    extra_caps_t excaps,
    word_t* buffer
)
{
    switch (cap_get_capType(cap)) {

    case cap_frame_cap:
        return decodeX86FrameInvocation(invLabel, length, cte, cap, excaps, buffer);

    case cap_page_table_cap:
        return decodeX86PageTableInvocation(invLabel, length, cte, cap, excaps, buffer);

    case cap_asid_control_cap: {
        word_t     i;
        asid_t           asid_base;
        word_t           index;
        word_t           depth;
        cap_t            untyped;
        cap_t            root;
        cte_t*           parentSlot;
        cte_t*           destSlot;
        lookupSlot_ret_t lu_ret;
        void*            frame;
        exception_t      status;

        if (invLabel != X86ASIDControlMakePool) {
            current_syscall_error.type = seL4_IllegalOperation;

            return EXCEPTION_SYSCALL_ERROR;
        }

        if (length < 2 || excaps.excaprefs[0] == NULL
                || excaps.excaprefs[1] == NULL) {
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }

        index = getSyscallArg(0, buffer);
        depth = getSyscallArg(1, buffer);
        parentSlot = excaps.excaprefs[0];
        untyped = parentSlot->cap;
        root = excaps.excaprefs[1]->cap;

        /* Find first free pool */
        for (i = 0; i < nASIDPools && x86KSASIDTable[i]; i++);

        if (i == nASIDPools) {
            /* no unallocated pool is found */
            current_syscall_error.type = seL4_DeleteFirst;

            return EXCEPTION_SYSCALL_ERROR;
        }

        asid_base = i << asidLowBits;


        if (cap_get_capType(untyped) != cap_untyped_cap ||
                cap_untyped_cap_get_capBlockSize(untyped) != seL4_ASIDPoolBits ||
                cap_untyped_cap_get_capIsDevice(untyped)) {
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 1;

            return EXCEPTION_SYSCALL_ERROR;
        }

        status = ensureNoChildren(parentSlot);
        if (status != EXCEPTION_NONE) {
            return status;
        }

        frame = WORD_PTR(cap_untyped_cap_get_capPtr(untyped));

        lu_ret = lookupTargetSlot(root, index, depth);
        if (lu_ret.status != EXCEPTION_NONE) {
            return lu_ret.status;
        }
        destSlot = lu_ret.slot;

        status = ensureEmptySlot(destSlot);
        if (status != EXCEPTION_NONE) {
            return status;
        }

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performASIDControlInvocation(frame, destSlot, parentSlot, asid_base);
    }

    case cap_asid_pool_cap: {
        cap_t        vspaceCap;
        cte_t*       vspaceCapSlot;
        asid_pool_t* pool;
        word_t i;
        asid_t       asid;

        if (invLabel != X86ASIDPoolAssign) {
            current_syscall_error.type = seL4_IllegalOperation;

            return EXCEPTION_SYSCALL_ERROR;
        }
        if (excaps.excaprefs[0] == NULL) {
            current_syscall_error.type = seL4_TruncatedMessage;

            return EXCEPTION_SYSCALL_ERROR;
        }

        vspaceCapSlot = excaps.excaprefs[0];
        vspaceCap = vspaceCapSlot->cap;

        if (!(isVTableRoot(vspaceCap) || VTX_TERNARY(cap_get_capType(vspaceCap) == cap_ept_pml4_cap, 0))
                || cap_get_capMappedASID(vspaceCap) != asidInvalid) {
            userError("X86ASIDPool: Invalid vspace root.");
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 1;

            return EXCEPTION_SYSCALL_ERROR;
        }

        pool = x86KSASIDTable[cap_asid_pool_cap_get_capASIDBase(cap) >> asidLowBits];
        if (!pool) {
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = false;
            current_lookup_fault = lookup_fault_invalid_root_new();
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (pool != ASID_POOL_PTR(cap_asid_pool_cap_get_capASIDPool(cap))) {
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        /* Find first free ASID */
        asid = cap_asid_pool_cap_get_capASIDBase(cap);
        for (i = 0; i < BIT(asidLowBits) && (asid + i == 0 || asid_map_get_type(pool->array[i]) != asid_map_asid_map_none); i++);

        if (i == BIT(asidLowBits)) {
            current_syscall_error.type = seL4_DeleteFirst;

            return EXCEPTION_SYSCALL_ERROR;
        }

        asid += i;

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performASIDPoolInvocation(asid, pool, vspaceCapSlot);
    }

    default:
        return decodeX86ModeMMUInvocation(invLabel, length, cptr, cte, cap, excaps, buffer);
    }
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/kernel/x2apic.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <arch/kernel/x2apic.h>

BOOT_CODE bool_t
x2apic_is_enabled(void)
{
    apic_base_msr_t apic_base_msr;
    apic_base_msr.words[0] = x86_rdmsr_low(IA32_APIC_BASE_MSR);

    if ((x86_cpuid_ecx(1, 0) & BIT(21)) &&
            apic_base_msr_get_enabled(apic_base_msr) &&
            apic_base_msr_get_x2apic(apic_base_msr)) {
        return true;
    }
    return false;
}

#ifdef CONFIG_X2APIC
BOOT_CODE bool_t
apic_enable(void)
{
    apic_base_msr_t apic_base_msr;
    apic_base_msr.words[0] = x86_rdmsr_low(IA32_APIC_BASE_MSR);

    if (!apic_base_msr_get_enabled(apic_base_msr)) {
        printf("APIC: Enabled bit not set\n");
        return false;
    }

    if (x86_cpuid_ecx(1, 0) & BIT(21)) {
        apic_base_msr = apic_base_msr_set_x2apic(apic_base_msr, 1);
        x86_wrmsr(IA32_APIC_BASE_MSR, apic_base_msr.words[0]);
    } else {
        printf("APIC: x2APIC is not supported on this machine\n");
        return false;
    }

    return true;
}

bool_t apic_is_interrupt_pending(void)
{
    word_t i;

    assert(int_irq_min % 32 == 0);
    for (i = int_irq_min; i <= int_irq_max; i += 32) {
        if (apic_read_reg(APIC_IRR_BASE + ((i / 32) - 1)) != 0) {
            return true;
        }
    }
    return false;
}

BOOT_CODE void
apic_send_init_ipi(cpu_id_t cpu_id)
{
    apic_write_icr(
        x2apic_icr2_new(
            cpu_id      /* dest */
        ).words[0],
        x2apic_icr1_new(
            0,          /* dest_shorthand  */
            1,          /* trigger_mode    */
            1,          /* level           */
            0,          /* dest_mode       */
            5,          /* delivery_mode   */
            0           /* vector          */
        ).words[0]
    );
    apic_write_icr(
        apic_icr2_new(
            cpu_id      /* dest */
        ).words[0],
        x2apic_icr1_new(
            0,          /* dest_shorthand  */
            1,          /* trigger_mode    */
            0,          /* level           */
            0,          /* dest_mode       */
            5,          /* delivery_mode   */
            0           /* vector          */
        ).words[0]
    );
}

BOOT_CODE void
apic_send_startup_ipi(cpu_id_t cpu_id, paddr_t startup_addr)
{
    /* check if 4K aligned */
    assert(IS_ALIGNED(startup_addr, PAGE_BITS));
    /* check if startup_addr < 640K */
    assert(startup_addr < 0xa0000);
    startup_addr >>= PAGE_BITS;

    apic_write_icr(
        x2apic_icr2_new(
            cpu_id      /* dest */
        ).words[0],
        x2apic_icr1_new(
            0,           /* dest_shorthand  */
            0,           /* trigger_mode    */
            0,           /* level           */
            0,           /* dest_mode       */
            6,           /* delivery_mode   */
            startup_addr /* vector          */
        ).words[0]
    );
}

void apic_send_ipi_core(irq_t vector, cpu_id_t cpu_id)
{
    apic_write_icr(
        x2apic_icr2_new(
            cpu_id      /* dest */
        ).words[0],
        x2apic_icr1_new(
            0,          /* dest_shorthand  */
            0,          /* trigger_mode    */
            0,          /* level           */
            0,          /* dest_mode       */
            0,          /* delivery_mode   */
            vector      /* vector          */
        ).words[0]
    );
}

void apic_send_ipi_cluster(irq_t vector, word_t mda)
{
    apic_write_icr(
        x2apic_icr2_new(
            mda         /* message destination address */
        ).words[0],
        x2apic_icr1_new(
            0,          /* dest_shorthand  */
            0,          /* trigger_mode    */
            0,          /* level           */
            1,          /* dest_mode       */
            0,          /* delivery_mode   */
            vector      /* vector          */
        ).words[0]
    );
}
#endif /* CONFIG_X2APIC */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/kernel/xapic.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <arch/kernel/xapic.h>
#include <arch/kernel/x2apic.h>

#ifdef CONFIG_XAPIC
#ifdef CONFIG_USE_LOGICAL_IDS
/* using flat cluster mode we only support 8 cores */
compile_assert(number_of_cores_invalid_for_logical_ids, CONFIG_MAX_NUM_NODES <= 8)

BOOT_CODE static void
init_xapic_ldr(void)
{
    uint32_t ldr;

    apic_write_reg(APIC_DEST_FORMAT, XAPIC_DFR_FLAT);
    ldr = apic_read_reg(APIC_LOGICAL_DEST) & MASK(XAPIC_LDR_SHIFT);
    ldr |= (BIT(getCurrentCPUIndex()) << XAPIC_LDR_SHIFT);
    apic_write_reg(APIC_LOGICAL_DEST, ldr);
}
#endif /* CONFIG_USE_LOGICAL_IDS */

BOOT_CODE bool_t
apic_enable(void)
{
    apic_base_msr_t apic_base_msr;
    apic_base_msr.words[0] = x86_rdmsr_low(IA32_APIC_BASE_MSR);

    if (!apic_base_msr_get_enabled(apic_base_msr)) {
        printf("APIC: Enabled bit not set\n");
        return false;
    }

    if (x2apic_is_enabled()) {
        printf("x2APIC enabled in BIOS but kernel does not support that\n");
        return false;
    }

#ifdef CONFIG_USE_LOGICAL_IDS
    init_xapic_ldr();
#endif /* CONFIG_USE_LOGICAL_IDS */

    return true;
}

bool_t apic_is_interrupt_pending(void)
{
    word_t i;

    /* read 256-bit register: each 32-bit word is 16 byte aligned */
    assert(int_irq_min % 32 == 0);
    for (i = int_irq_min; i <= int_irq_max; i += 32) {
        if (apic_read_reg(APIC_IRR_BASE + i / 2) != 0) {
            return true;
        }
    }
    return false;
}

BOOT_CODE void
apic_send_init_ipi(cpu_id_t cpu_id)
{
    apic_write_icr(
        apic_icr2_new(
            cpu_id      /* dest */
        ).words[0],
        apic_icr1_new(
            0,          /* dest_shorthand  */
            1,          /* trigger_mode    */
            1,          /* level           */
            0,          /* delivery_status */
            0,          /* dest_mode       */
            5,          /* delivery_mode   */
            0           /* vector          */
        ).words[0]
    );
    apic_write_icr(
        apic_icr2_new(
            cpu_id      /* dest */
        ).words[0],
        apic_icr1_new(
            0,          /* dest_shorthand  */
            1,          /* trigger_mode    */
            0,          /* level           */
            0,          /* delivery_status */
            0,          /* dest_mode       */
            5,          /* delivery_mode   */
            0           /* vector          */
        ).words[0]
    );
}

BOOT_CODE void
apic_send_startup_ipi(cpu_id_t cpu_id, paddr_t startup_addr)
{
    /* check if 4K aligned */
    assert(IS_ALIGNED(startup_addr, PAGE_BITS));
    /* check if startup_addr < 640K */
    assert(startup_addr < 0xa0000);
    startup_addr >>= PAGE_BITS;

    apic_write_icr(
        apic_icr2_new(
            cpu_id       /* dest */
        ).words[0],
        apic_icr1_new(
            0,           /* dest_shorthand  */
            0,           /* trigger_mode    */
            0,           /* level           */
            0,           /* delivery_status */
            0,           /* dest_mode       */
            6,           /* delivery_mode   */
            startup_addr /* vector          */
        ).words[0]
    );
}

void apic_send_ipi_core(irq_t vector, cpu_id_t cpu_id)
{
    apic_icr1_t icr1;
    /* wait till we can send an IPI */
    do {
        icr1.words[0] = apic_read_reg(APIC_ICR1);
    } while (apic_icr1_get_delivery_status(icr1));

    apic_write_icr(
        apic_icr2_new(
            cpu_id      /* dest */
        ).words[0],
        apic_icr1_new(
            0,          /* dest_shorthand  */
            0,          /* trigger_mode    */
            0,          /* level           */
            0,          /* delivery_status */
            0,          /* dest_mode       */
            0,          /* delivery_mode   */
            vector      /* vector          */
        ).words[0]
    );
}

void apic_send_ipi_cluster(irq_t vector, word_t mda)
{
    apic_icr1_t icr1;
    /* wait till we can send an IPI */
    do {
        icr1.words[0] = apic_read_reg(APIC_ICR1);
    } while (apic_icr1_get_delivery_status(icr1));

    apic_write_icr(
        apic_icr2_new(
            mda         /* message destination address */
        ).words[0],
        apic_icr1_new(
            0,          /* dest_shorthand  */
            0,          /* trigger_mode    */
            0,          /* level           */
            0,          /* delivery_status */
            1,          /* dest_mode       */
            0,          /* delivery_mode   */
            vector      /* vector          */
        ).words[0]
    );
}
#endif /* CONFIG_XAPIC */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/machine/breakpoint.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>

#ifdef CONFIG_HARDWARE_DEBUG_API

#include <arch/machine/debug.h>
#include <mode/machine/debug.h>
#include <arch/machine.h>
#include <machine/registerset.h>
#include <plat/api/constants.h> /* seL4_NumHWBReakpoints */

/* Intel manual Vol3, 17.2.4 */
#define X86_DEBUG_BP_SIZE_1B                (0x0u)
#define X86_DEBUG_BP_SIZE_2B                (0x1u)
#define X86_DEBUG_BP_SIZE_4B                (0x3u)
#define X86_DEBUG_BP_SIZE_8B                (0x2u)

#define X86_DEBUG_BP0_SIZE_SHIFT            (18)
#define X86_DEBUG_BP1_SIZE_SHIFT            (22)
#define X86_DEBUG_BP2_SIZE_SHIFT            (26)
#define X86_DEBUG_BP3_SIZE_SHIFT            (30)

/* NOTE: Intel manual 17.2.4:
 * I/O breakpoints are supported by every processor later than i486, but only
 * when CR4.DE=1.
 * When CR4.DE=0, or if processor is earlier than i586, this bit is "Undefined",
 * which is not the same as "Reserved", so it won't trigger an exception - it
 * will just cause an undefined reaction from the CPU.
 */
#define X86_DEBUG_BP_TYPE_IO                (0x2u)
#define X86_DEBUG_BP_TYPE_INSTR             (0x0u)
#define X86_DEBUG_BP_TYPE_DATA_WRITE        (0x1u)
#define X86_DEBUG_BP_TYPE_DATA_READWRITE    (0x3u)

#define X86_DEBUG_BP0_TYPE_SHIFT            (16)
#define X86_DEBUG_BP1_TYPE_SHIFT            (20)
#define X86_DEBUG_BP2_TYPE_SHIFT            (24)
#define X86_DEBUG_BP3_TYPE_SHIFT            (28)

#define X86_DEBUG_EFLAGS_TRAP_FLAG    ((word_t)BIT(8))
#define X86_DEBUG_EFLAGS_RESUME_FLAG    ((word_t)BIT(16))
#define X86_DEBUG_DR6_SINGLE_STEP_FLAG  ((word_t)BIT(14))

#define X86_DEBUG_DR6_BP_MASK     (0xFu)

static bool_t byte8_bps_supported = false;

bool_t
byte8BreakpointsSupported(void)
{
    return byte8_bps_supported;
}

static inline void
bitwiseAndDr6Reg(word_t mask)
{
    word_t tmp;

    tmp = readDr6Reg() & mask;
    writeDr6Reg(tmp);
}

static inline word_t
readDr7Context(tcb_t *t)
{
    return t->tcbArch.tcbContext.breakpointState.dr[5];
}

static inline void
bitwiseOrDr7Context(tcb_t *t, word_t val)
{
    t->tcbArch.tcbContext.breakpointState.dr[5] |= val;
}

static inline void
bitwiseAndDr7Context(tcb_t *t, word_t mask)
{
    t->tcbArch.tcbContext.breakpointState.dr[5] &= mask;
}

static void
unsetDr7BitsFor(tcb_t *t, uint16_t bp_num)
{
    word_t mask;

    switch (bp_num) {
    case 0:
        mask = (0x3u << X86_DEBUG_BP0_SIZE_SHIFT) | (0x3u << X86_DEBUG_BP0_TYPE_SHIFT);
        break;
    case 1:
        mask = (0x3u << X86_DEBUG_BP1_SIZE_SHIFT) | (0x3u << X86_DEBUG_BP1_TYPE_SHIFT);
        break;
    case 2:
        mask = (0x3u << X86_DEBUG_BP2_SIZE_SHIFT) | (0x3u << X86_DEBUG_BP2_TYPE_SHIFT);
        break;
    default: /* 3 */
        assert(bp_num == 3);
        mask = (0x3u << X86_DEBUG_BP3_SIZE_SHIFT) | (0x3u << X86_DEBUG_BP3_TYPE_SHIFT);
        break;
    }

    mask = ~mask;
    bitwiseAndDr7Context(t, mask);
}

/** Converts an seL4_BreakpointType value into the underlying hardware
 * equivalent.
 * @param bp_num Breakpoint number.
 * @param type One of the values of seL4_BreakpointType.
 * @param rw Access trigger condition (read/write).
 * @return Hardware specific register value representing the inputs.
 */
PURE static inline word_t
convertTypeAndAccessToArch(uint16_t bp_num, word_t type, word_t rw)
{
    switch (type) {
    case seL4_InstructionBreakpoint:
        type = X86_DEBUG_BP_TYPE_INSTR;
        break;
    default: /* seL4_DataBreakpoint */
        assert(type == seL4_DataBreakpoint);
        type = (rw == seL4_BreakOnWrite)
               ? X86_DEBUG_BP_TYPE_DATA_WRITE
               : X86_DEBUG_BP_TYPE_DATA_READWRITE;
    }

    switch (bp_num) {
    case 0:
        return type << X86_DEBUG_BP0_TYPE_SHIFT;
    case 1:
        return type << X86_DEBUG_BP1_TYPE_SHIFT;
    case 2:
        return type << X86_DEBUG_BP2_TYPE_SHIFT;
    default: /* 3 */
        assert(bp_num == 3);
        return type << X86_DEBUG_BP3_TYPE_SHIFT;
    }
}

/** Reverse of convertTypeAndAccessToArch(): converts hardware values into
 * seL4 API values.
 * @param dr7 Hardware register value as input for conversion.
 * @param bp_num Breakpoint number.
 * @param type[out] Converted type value.
 * @param rw[out] Converted output access trigger value.
 */
typedef struct {
    word_t type, rw;
} convertedTypeAndAccess_t;

PURE static inline convertedTypeAndAccess_t
convertArchToTypeAndAccess(word_t dr7, uint16_t bp_num)
{
    convertedTypeAndAccess_t ret;

    switch (bp_num) {
    case 0:
        dr7 &= 0x3u << X86_DEBUG_BP0_TYPE_SHIFT;
        dr7 >>= X86_DEBUG_BP0_TYPE_SHIFT;
        break;
    case 1:
        dr7 &= 0x3u << X86_DEBUG_BP1_TYPE_SHIFT;
        dr7 >>= X86_DEBUG_BP1_TYPE_SHIFT;
        break;
    case 2:
        dr7 &= 0x3u << X86_DEBUG_BP2_TYPE_SHIFT;
        dr7 >>= X86_DEBUG_BP2_TYPE_SHIFT;
        break;
    default: /* 3 */
        assert(bp_num == 3);
        dr7 &= 0x3u << X86_DEBUG_BP3_TYPE_SHIFT;
        dr7 >>= X86_DEBUG_BP3_TYPE_SHIFT;
    }

    switch (dr7) {
    case X86_DEBUG_BP_TYPE_INSTR:
        ret.type = seL4_InstructionBreakpoint;
        ret.rw = seL4_BreakOnRead;
        break;
    case X86_DEBUG_BP_TYPE_DATA_WRITE:
        ret.type = seL4_DataBreakpoint;
        ret.rw = seL4_BreakOnWrite;
        break;
    default: /* Read-write */
        assert(dr7 == X86_DEBUG_BP_TYPE_DATA_READWRITE);
        ret.type = seL4_DataBreakpoint;
        ret.rw = seL4_BreakOnReadWrite;
        break;
    }
    return ret;
}

/** Converts an integer size number into an equivalent hardware register value.
 * @param n Breakpoint number.
 * @param type One value from seL4_BreakpointType.
 * @param size An integer for the operand size of the breakpoint.
 * @return Converted, hardware-specific value.
 */
PURE static inline word_t
convertSizeToArch(uint16_t bp_num, word_t type, word_t size)
{
    if (type == seL4_InstructionBreakpoint) {
        /* Intel manual vol3 17.2.4:
         * "If the corresponding RWn field in register DR7 is 00 (instruction
         * execution), then the LENn field should also be 00"
         */
        size = 0;
    } else {
        switch (size) {
        case 1:
            size = X86_DEBUG_BP_SIZE_1B;
            break;
        case 2:
            size = X86_DEBUG_BP_SIZE_2B;
            break;
        case 8:
            size = X86_DEBUG_BP_SIZE_8B;
            break;
        default: /* 4B */
            assert(size == 4);
            size = X86_DEBUG_BP_SIZE_4B;
        }
    }

    switch (bp_num) {
    case 0:
        return size << X86_DEBUG_BP0_SIZE_SHIFT;
    case 1:
        return size << X86_DEBUG_BP1_SIZE_SHIFT;
    case 2:
        return size << X86_DEBUG_BP2_SIZE_SHIFT;
    default: /* 3 */
        assert(bp_num == 3);
        return size << X86_DEBUG_BP3_SIZE_SHIFT;
    }
}

/** Reverse of convertSizeToArch(): converts a hardware-specific size value
 * into an integer representation.
 * @param dr7 Hardware register value as input.
 * @param n Breakpoint number.
 * @return Converted size value.
 */
PURE static inline word_t
convertArchToSize(word_t dr7, uint16_t bp_num)
{
    word_t type;

    switch (bp_num) {
    case 0:
        type = dr7 & (0x3u << X86_DEBUG_BP0_TYPE_SHIFT);
        type >>= X86_DEBUG_BP0_TYPE_SHIFT;
        dr7 &= 0x3u << X86_DEBUG_BP0_SIZE_SHIFT;
        dr7 >>= X86_DEBUG_BP0_SIZE_SHIFT;
        break;
    case 1:
        type = dr7 & (0x3u << X86_DEBUG_BP1_TYPE_SHIFT);
        type >>= X86_DEBUG_BP1_TYPE_SHIFT;
        dr7 &= 0x3u << X86_DEBUG_BP1_SIZE_SHIFT;
        dr7 >>= X86_DEBUG_BP1_SIZE_SHIFT;
        break;
    case 2:
        type = dr7 & (0x3u << X86_DEBUG_BP2_TYPE_SHIFT);
        type >>= X86_DEBUG_BP2_TYPE_SHIFT;
        dr7 &= 0x3u << X86_DEBUG_BP2_SIZE_SHIFT;
        dr7 >>= X86_DEBUG_BP2_SIZE_SHIFT;
        break;
    default: /* 3 */
        assert(bp_num == 3);
        type = dr7 & (0x3u << X86_DEBUG_BP3_TYPE_SHIFT);
        type >>= X86_DEBUG_BP3_TYPE_SHIFT;
        dr7 &= 0x3u << X86_DEBUG_BP3_SIZE_SHIFT;
        dr7 >>= X86_DEBUG_BP3_SIZE_SHIFT;
    }

    /* Force size to 0 if type is instruction breakpoint. */
    if (type == X86_DEBUG_BP_TYPE_INSTR) {
        return 0;
    }

    switch (dr7) {
    case X86_DEBUG_BP_SIZE_1B:
        return 1;
    case X86_DEBUG_BP_SIZE_2B:
        return 2;
    case X86_DEBUG_BP_SIZE_8B:
        return 8;
    default: /* 4B */
        assert(dr7 == X86_DEBUG_BP_SIZE_4B);
        return 4;
    }
}

/** Enables a breakpoint.
 * @param bp_num Hardware breakpoint ID. Usually an integer from 0..N.
 */
static void
enableBreakpoint(tcb_t *t, uint16_t bp_num)
{
    word_t enable_bit;

    assert(t != NULL);
    assert(bp_num < X86_DEBUG_BP_N_REGS);

    switch (bp_num) {
    case 0:
        enable_bit = X86_DEBUG_BP0_ENABLE_BIT;
        break;
    case 1:
        enable_bit = X86_DEBUG_BP1_ENABLE_BIT;
        break;
    case 2:
        enable_bit = X86_DEBUG_BP2_ENABLE_BIT;
        break;
    default:
        enable_bit = X86_DEBUG_BP3_ENABLE_BIT;
        break;
    }

    bitwiseOrDr7Context(t, enable_bit);
}

/** Disables a breakpoint without clearing its configuration.
 * @param bp_num Hardware breakpoint ID. Usually an integer from 0..N.
 */
static void
disableBreakpoint(tcb_t *t, uint16_t bp_num)
{
    word_t disable_mask;

    assert(t != NULL);
    assert(bp_num < X86_DEBUG_BP_N_REGS);

    switch (bp_num) {
    case 0:
        disable_mask = ~X86_DEBUG_BP0_ENABLE_BIT;
        break;
    case 1:
        disable_mask = ~X86_DEBUG_BP1_ENABLE_BIT;
        break;
    case 2:
        disable_mask = ~X86_DEBUG_BP2_ENABLE_BIT;
        break;
    default:
        disable_mask = ~X86_DEBUG_BP3_ENABLE_BIT;
        break;
    }

    bitwiseAndDr7Context(t, disable_mask);
}

/** Returns a boolean for whether or not a breakpoint is enabled.
 * @param bp_num Hardware breakpoint ID. Usually an integer from 0..N.
 */
static bool_t
breakpointIsEnabled(tcb_t *t, uint16_t bp_num)
{
    word_t dr7;

    assert(t != NULL);
    assert(bp_num < X86_DEBUG_BP_N_REGS);

    dr7 = readDr7Context(t);
    switch (bp_num) {
    case 0:
        return !!(dr7 & X86_DEBUG_BP0_ENABLE_BIT);
    case 1:
        return !!(dr7 & X86_DEBUG_BP1_ENABLE_BIT);
    case 2:
        return !!(dr7 & X86_DEBUG_BP2_ENABLE_BIT);
    default:
        return !!(dr7 & X86_DEBUG_BP3_ENABLE_BIT);
    }
}

static void
setBpVaddrContext(tcb_t *t, uint16_t bp_num, word_t vaddr)
{
    assert(t != NULL);
    user_breakpoint_state_t *ubs = &t->tcbArch.tcbContext.breakpointState;

    switch (bp_num) {
    case 0:
        ubs->dr[0] = vaddr;
        break;
    case 1:
        ubs->dr[1] = vaddr;
        break;
    case 2:
        ubs->dr[2] = vaddr;
        break;
    default:
        assert(bp_num == 3);
        ubs->dr[3] = vaddr;
        break;
    }
    return;
}

/** Backend for the seL4_TCB_SetBreakpoint invocation.
 *
 * @param uds Arch TCB register context structure.
 * @param bp_num Hardware breakpoint ID.
 * @param vaddr USerspace virtual address on which you'd like this breakpoing
 *        to trigger.
 * @param types One of the seL4_BreakpointType values.
 * @param size positive integer indicating the byte-range size that should
 *        trigger the breakpoint. 0 is valid for Instruction breakpoints.
 * @param rw Access type that should trigger the BP (read/write).
 */
void
setBreakpoint(tcb_t *t,
              uint16_t bp_num, word_t vaddr, word_t types, word_t size, word_t rw)
{
    word_t dr7val;

    assert(t != NULL);

    dr7val = convertTypeAndAccessToArch(bp_num, types, rw);
    dr7val |= convertSizeToArch(bp_num, types, size);

    setBpVaddrContext(t, bp_num, vaddr);
    unsetDr7BitsFor(t, bp_num);
    bitwiseOrDr7Context(t, dr7val);
    enableBreakpoint(t, bp_num);
}

static word_t
getBpVaddrContext(tcb_t *t, uint16_t bp_num)
{
    assert(t != NULL);
    user_breakpoint_state_t *ubs = &t->tcbArch.tcbContext.breakpointState;

    switch (bp_num) {
    case 0:
        return ubs->dr[0];
    case 1:
        return ubs->dr[1];
    case 2:
        return ubs->dr[2];
    default:
        assert(bp_num == 3);
        return ubs->dr[3];
    }
}

/** Backend for the x86 seL4_TCB_GetBreakpoint invocation.
 *
 * Returns information about a particular breakpoint ID, including whether or
 * not it's enabled.
 *
 * @param uds Arch TCB register context pointer.
 * @param bp_num Hardware breakpoint ID of the BP you'd like to query.
 * @return Structure containing information about the status of the breakpoint.
 */
getBreakpoint_t
getBreakpoint(tcb_t *t, uint16_t bp_num)
{
    word_t dr7val;
    getBreakpoint_t ret;
    convertedTypeAndAccess_t res;

    dr7val = readDr7Context(t);
    ret.vaddr = getBpVaddrContext(t, bp_num);
    ret.size = convertArchToSize(dr7val, bp_num);
    res = convertArchToTypeAndAccess(dr7val, bp_num);
    ret.type = res.type;
    ret.rw = res.rw;
    ret.is_enabled = breakpointIsEnabled(t, bp_num);
    return ret;
}

/** Backend for the x86 seL4_TCB_UnsetBreakpoint invocation.
 *
 * Unsets and *clears* a hardware breakpoint.
 * @param uds Arch TCB register context pointer.
 * @param bp_num The hardware breakpoint ID you'd like to clear.
 */
void
unsetBreakpoint(tcb_t *t, uint16_t bp_num)
{
    disableBreakpoint(t, bp_num);
    unsetDr7BitsFor(t, bp_num);
    setBpVaddrContext(t, bp_num, 0);
}

/** Used in the exception path to determine if an exception was caused by
 * single-stepping being active.
 *
 * @param uc Arch TCB register context structure.
 * @return a structure stating whether or not the exception was caused by
 *          hardware single-stepping, and what the instruction vaddr was.
 */
typedef struct {
    bool_t ret;
    word_t instr_vaddr;
} testAndResetSingleStepException_t;

static testAndResetSingleStepException_t
testAndResetSingleStepException(tcb_t *t)
{
    testAndResetSingleStepException_t ret;
    word_t dr6;

    dr6 = readDr6Reg();
    if (!(dr6 & X86_DEBUG_DR6_SINGLE_STEP_FLAG)) {
        ret.ret = false;
        return ret;
    }

    ret.ret = true;
    ret.instr_vaddr = t->tcbArch.tcbContext.registers[FaultIP];
    bitwiseAndDr6Reg(~X86_DEBUG_DR6_SINGLE_STEP_FLAG);

    /* And that's not all: if the breakpoint is an instruction breakpoint, we
     * also need to set EFLAGS.RF. The processor raises the #DB exception BEFORE
     * the instruction executes. This means that when we IRET to userspace, the
     * SAME breakpoint will trigger again, and so on ad infinitum. EFLAGS.RF
     * solves this problem:
     *
     * When EFLAGS.RF is set, the processor will ignore instruction breakpoints
     * that should be raised, for one instruction. After that instruction
     * executes, the processor will also automatically unset EFLAGS.RF. See
     * Intel manuals, vol3, section 17.3.1.1.
     */
    /* This will automatically be popped by restore_user_context() */
    t->tcbArch.tcbContext.registers[FLAGS] |= X86_DEBUG_EFLAGS_RESUME_FLAG;
    return ret;
}

bool_t
configureSingleStepping(tcb_t *t, uint16_t bp_num, word_t n_instr,
                        UNUSED bool_t is_reply)
{
    /* On x86 no hardware breakpoints are needed for single stepping. */
    if (n_instr == 0) {
        /* If n_instr (number of instructions to single-step) is 0, that is the
          * same as requesting that single-stepping be disabled.
          */
        t->tcbArch.tcbContext.breakpointState.single_step_enabled = false;
        t->tcbArch.tcbContext.registers[FLAGS] &= ~X86_DEBUG_EFLAGS_TRAP_FLAG;
    } else {
        t->tcbArch.tcbContext.breakpointState.single_step_enabled = true;
    }

    t->tcbArch.tcbContext.breakpointState.n_instructions = n_instr;
    return false;
}

/** Used in the exception path to determine which breakpoint triggered the
 * exception.
 *
 * First, checks to see which hardware breakpoint was triggered, and saves
 * the ID of that breakpoint. Secondly, resets that breakpoint such that its
 * "triggered" bit is no longer in the asserted state -- whatever that means
 * for the arch. So on x86, that means clearing the indicator bit in DR6.
 *
 * Aside from the ID of the breakpoint that was raised, also returns
 * information about the breakpoint (vaddr, access, type, etc).
 *
 * @param uc Arch TCB register context pointer.
 * @return Structure with a "bp_num" member that states which hardware
 *          breakpoint was triggered, and gives information describing the
 *          breakpoint.
 */
typedef struct {
    int bp_num;
    word_t vaddr, reason;
} getAndResetActiveBreakpoint_t;

static getAndResetActiveBreakpoint_t
getAndResetActiveBreakpoint(tcb_t *t)
{
    convertedTypeAndAccess_t tmp;
    getAndResetActiveBreakpoint_t ret;

    /* Read from the hardware regs, not user context */
    word_t dr6 = readDr6Reg();
    if (dr6 & BIT(0)) {
        ret.bp_num = 0;
    } else if (dr6 & BIT(1)) {
        ret.bp_num = 1;
    } else if (dr6 & BIT(2)) {
        ret.bp_num = 2;
    } else if (dr6 & BIT(3)) {
        ret.bp_num = 3;
    } else {
        ret.bp_num = -1;
        return ret;
    }

    tmp = convertArchToTypeAndAccess(readDr7Context(t), ret.bp_num);
    ret.vaddr = getBpVaddrContext(t, ret.bp_num);
    ret.reason = tmp.type;

    bitwiseAndDr6Reg(~BIT(ret.bp_num));
    return ret;
}

exception_t
handleUserLevelDebugException(int int_vector)
{
    tcb_t *ct;
    getAndResetActiveBreakpoint_t active_bp;
    testAndResetSingleStepException_t single_step_info;

#if defined(CONFIG_DEBUG_BUILD) || defined(CONFIG_BENCHMARK_TRACK_KERNEL_ENTRIES)
    ksKernelEntry.path = Entry_UserLevelFault;
    ksKernelEntry.word = int_vector;
#else
    (void)int_vector;
#endif /* DEBUG */

#ifdef CONFIG_BENCHMARK_TRACK_KERNEL_ENTRIES
    benchmark_track_start();
#endif

    ct = NODE_STATE(ksCurThread);

    /* Software break request (INT3) is detected by the vector number */
    if (int_vector == int_software_break_request) {
        current_fault = seL4_Fault_DebugException_new(getRestartPC(NODE_STATE(ksCurThread)),
                                                      0, seL4_SoftwareBreakRequest);
    } else {
        /* Hardware breakpoint trigger is detected using DR6 */
        active_bp = getAndResetActiveBreakpoint(ct);
        if (active_bp.bp_num >= 0) {
            current_fault = seL4_Fault_DebugException_new(active_bp.vaddr,
                                                          active_bp.bp_num,
                                                          active_bp.reason);
        } else {
            single_step_info = testAndResetSingleStepException(ct);
            if (single_step_info.ret == true) {
                /* If the caller asked us to skip over N instructions before
                 * generating the next single-step breakpoint, we shouldn't
                 * bother to construct a fault message until we've skipped N
                 * instructions.
                 */
                if (singleStepFaultCounterReady(ct) == false) {
                    return EXCEPTION_NONE;
                }
                current_fault = seL4_Fault_DebugException_new(single_step_info.instr_vaddr,
                                                              0, seL4_SingleStep);
            } else {
                return EXCEPTION_SYSCALL_ERROR;
            }
        }
    }

    handleFault(NODE_STATE(ksCurThread));

    schedule();
    activateThread();

    return EXCEPTION_NONE;
}

BOOT_CODE bool_t
Arch_initHardwareBreakpoints(void)
{
    x86_cpu_identity_t *modelinfo;

    modelinfo = x86_cpuid_get_model_info();
    /* Intel manuals, vol3, section 17.2.4, "NOTES". */
    if (modelinfo->family == 15) {
        if (modelinfo->model == 3 || modelinfo->model == 4
                || modelinfo->model == 6) {
            byte8_bps_supported = true;
        }
    }
    if (modelinfo->family == 6) {
        if (modelinfo->model == 15 || modelinfo->model == 23
                || modelinfo->model == 0x1C) {
            byte8_bps_supported = true;
        }
    }
    return true;
}

void
Arch_initBreakpointContext(user_breakpoint_state_t *uds)
{
    memset(uds, 0, sizeof(*uds));

    /* Preload reserved values into register context */
    uds->dr[4] = readDr6Reg() &
                 ~(BIT(0)
                   | BIT(1)
                   | BIT(2)
                   | BIT(3)
                   | X86_DEBUG_DR6_SINGLE_STEP_FLAG);

    uds->dr[5] = readDr7Reg() &
                 ~(X86_DEBUG_BP0_ENABLE_BIT | X86_DEBUG_BP1_ENABLE_BIT
                   | X86_DEBUG_BP2_ENABLE_BIT
                   | X86_DEBUG_BP3_ENABLE_BIT);
}

#endif
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/machine/capdl.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <object/structures.h>
#include <object/tcb.h>
#include <model/statedata.h>
#include <machine/capdl.h>
#include <arch/machine/capdl.h>
#include <machine/io.h>

#ifdef CONFIG_DEBUG_BUILD

#define ARCH 0xe1

#define PD_READ_SIZE         BIT(PD_INDEX_BITS)
#define PT_READ_SIZE         BIT(PT_INDEX_BITS)
#define ASID_POOL_READ_SIZE  BIT(ASID_POOL_INDEX_BITS)
#define IO_PT_READ_SIZE      BIT(VTD_PT_INDEX_BITS)

static int getDecodedChar(unsigned char *result)
{
    unsigned char c;
    c = getDebugChar();
    if (c == START) {
        return 1;
    }
    if (c == ESCAPE) {
        c = getDebugChar();
        if (c == START) {
            return 1;
        }
        switch (c) {
        case ESCAPE_ESCAPE:
            *result = ESCAPE;
            break;
        case START_ESCAPE:
            *result = START;
            break;
        case END_ESCAPE:
            *result = END;
            break;
        default:
            if (c >= 20 && c < 40) {
                *result = c - 20;
            } else {
                return 1;
            }
        }
        return 0;
    } else {
        *result = c;
        return 0;
    }
}

static void putEncodedChar(unsigned char c)
{
    switch (c) {
    case ESCAPE:
        putDebugChar(ESCAPE);
        putDebugChar(ESCAPE_ESCAPE);
        break;
    case START:
        putDebugChar(ESCAPE);
        putDebugChar(START_ESCAPE);
        break;
    case END:
        putDebugChar(ESCAPE);
        putDebugChar(END_ESCAPE);
        break;
    default:
        if (c < 20) {
            putDebugChar(ESCAPE);
            putDebugChar(c + 20);
        } else {
            putDebugChar(c);
        }
    }
}

static int getArg(unsigned long *res)
{
    unsigned long i;
    unsigned char byte;
    *res = 0;
    for (i = 0; i < sizeof(unsigned long); i++) {
        if (getDecodedChar(&byte)) {
            return 1;
        }
        (*res) = ((*res) << 8) | byte;
    }
    return 0;
}

static void sendWord(unsigned long word)
{
    unsigned long i;
    for (i = 0; i < sizeof(unsigned long); i++) {
        putEncodedChar( (word >> (i * 8)) & 0xff);
    }
}

static cte_t *getMDBParent(cte_t *slot)
{
    cte_t *oldSlot = CTE_PTR(mdb_node_get_mdbPrev(slot->cteMDBNode));

    while (oldSlot != 0 && !isMDBParentOf(oldSlot, slot)) {
        oldSlot = CTE_PTR(mdb_node_get_mdbPrev(oldSlot->cteMDBNode));
    }

    return oldSlot;
}

static void sendPD(unsigned long address)
{
    unsigned long i;
    unsigned int exists;
    pde_t *start = (pde_t *)address;
    for (i = 0; i < PD_READ_SIZE; i++) {
        pde_t pde = start[i];
        exists = 1;
        if (pde_get_page_size(pde) == pde_pde_pt && (pde_pde_pt_get_pt_base_address(pde) == 0 ||
                                                     !pde_pde_pt_get_present(pde) || !pde_pde_pt_get_super_user(pde))) {
            exists = 0;
        } else if (pde_get_page_size(pde) == pde_pde_large && (pde_pde_large_get_page_base_address(pde) == 0 ||
                                                               !pde_pde_large_get_present(pde) || !pde_pde_large_get_super_user(pde))) {
            exists = 0;
        }
        if (exists != 0 && i < PPTR_BASE >> pageBitsForSize(X86_LargePage)) {
            sendWord(i);
            sendWord(pde.words[0]);
        }
    }
}

static void sendPT(unsigned long address)
{
    unsigned long i;
    pte_t *start = (pte_t *)address;
    for (i = 0; i < PT_READ_SIZE; i++) {
        pte_t pte = start[i];
        if (pte_get_page_base_address(pte) != 0 && pte_get_present(pte) && pte_get_super_user(pte)) {
            sendWord(i);
            sendWord(pte.words[0]);
        }
    }
}

static void sendASIDPool(unsigned long address)
{
    unsigned long i;
    pde_t **start = (pde_t **)address;
    for (i = 0; i < ASID_POOL_READ_SIZE; i++) {
        pde_t *pde = start[i];
        if (pde != 0) {
            sendWord(i);
            sendWord((unsigned long)pde);
        }
    }
}

#ifdef CONFIG_IOMMU
static void sendIOPT(unsigned long address, unsigned int level)
{
    unsigned long i;
    vtd_pte_t *start = (vtd_pte_t *)address;
    for (i = 0; i < IO_PT_READ_SIZE; i++) {
        vtd_pte_t vtd_pte = start[i];
        if (vtd_pte_get_addr(vtd_pte) != 0) {
            sendWord(i);
            sendWord(vtd_pte.words[0]);
#ifdef CONFIG_ARCH_IA32
            sendWord(vtd_pte.words[1]);
#endif
            if (level == x86KSnumIOPTLevels) {
                sendWord(1);
            } else {
                sendWord(0);
            }
        }
    }
}

static void sendIOSpace(uint32_t pci_request_id)
{
    uint32_t   vtd_root_index;
    uint32_t   vtd_context_index;
    vtd_rte_t* vtd_root_slot;
    vtd_cte_t* vtd_context;
    vtd_cte_t* vtd_context_slot;

    vtd_root_index = get_pci_bus(pci_request_id);
    vtd_root_slot = x86KSvtdRootTable + vtd_root_index;

    vtd_context = (vtd_cte_t*)paddr_to_pptr(vtd_rte_ptr_get_ctp(vtd_root_slot));
    vtd_context_index = (get_pci_dev(pci_request_id) << 3) | get_pci_fun(pci_request_id);
    vtd_context_slot = &vtd_context[vtd_context_index];

    if (vtd_cte_ptr_get_present(vtd_context_slot)) {
        sendWord(vtd_cte_ptr_get_asr(vtd_context_slot));
    } else {
        sendWord(0);
    }
}
#endif

static void sendRunqueues(void)
{
    word_t i;
    sendWord((unsigned long)NODE_STATE(ksCurThread));
    for (i = 0; i < NUM_READY_QUEUES; i++) {
        tcb_t *current = NODE_STATE(ksReadyQueues[i]).head;
        if (current != 0) {
            while (current != NODE_STATE(ksReadyQueues[i]).end) {
                sendWord((unsigned long)current);
                current = current -> tcbSchedNext;
            }
            sendWord((unsigned long)current);
        }
    }
}

static void sendEPQueue(unsigned long epptr)
{
    tcb_t *current = (tcb_t *)endpoint_ptr_get_epQueue_head((endpoint_t *)epptr);
    tcb_t *tail = (tcb_t *)endpoint_ptr_get_epQueue_tail((endpoint_t *)epptr);
    if (current == 0) {
        return;
    }
    while (current != tail) {
        sendWord((unsigned long)current);
        current = current->tcbEPNext;
    }
    sendWord((unsigned long)current);
}

static void sendCNode(unsigned long address, unsigned int sizebits)
{
    unsigned long i;
    cte_t *start = (cte_t *)address;
    for (i = 0; i < (1 << sizebits); i++) {
        cap_t cap = start[i].cap;
        if (cap_get_capType(cap) != cap_null_cap) {
            cte_t *parent = getMDBParent(&start[i]);
            sendWord(i);
            sendWord(cap.words[0]);
            sendWord(cap.words[1]);
            sendWord((unsigned long)parent);
        }
    }
}

static void sendIRQNode(void)
{
    sendCNode((unsigned long)intStateIRQNode, 8);
}

static void sendVersion(void)
{
    sendWord(ARCH);
    sendWord(CAPDL_VERSION);
}

void capDL(void)
{
    int result;
    int done = 0;
    while (done == 0) {
        unsigned char c;
        do {
            c = getDebugChar();
        } while (c != START);
        do {
            result = getDecodedChar(&c);
            if (result) {
                continue;
            }
            switch (c) {
            case PD_COMMAND: {
                /*pgdir */
                unsigned long arg;
                result = getArg(&arg);
                if (result) {
                    continue;
                }
                sendPD(arg);
                putDebugChar(END);
            }
            break;
            case PT_COMMAND: {
                /*pg table */
                unsigned long arg;
                result = getArg(&arg);
                if (result) {
                    continue;
                }
                sendPT(arg);
                putDebugChar(END);
            }
            break;
            case ASID_POOL_COMMAND: {
                /*asid pool */
                unsigned long arg;
                result = getArg(&arg);
                if (result) {
                    continue;
                }
                sendASIDPool(arg);
                putDebugChar(END);
            }
            break;
#ifdef CONFIG_IOMMU
            case IO_PT_COMMAND: {
                /*io pt table */
                unsigned long address, level;
                result = getArg(&address);
                if (result) {
                    continue;
                }
                result = getArg(&level);
                if (result) {
                    continue;
                }
                sendIOPT(address, level);
                putDebugChar(END);
            }
            break;
            case IO_SPACE_COMMAND: {
                /*io space */
                unsigned long arg;
                result = getArg(&arg);
                if (result) {
                    continue;
                }
                sendIOSpace(arg);
                putDebugChar(END);
            }
#endif
            break;
            case RQ_COMMAND: {
                /*runqueues */
                sendRunqueues();
                putDebugChar(END);
                result = 0;
            }
            break;
            case EP_COMMAND: {
                /*endpoint waiters */
                unsigned long arg;
                result = getArg(&arg);
                if (result) {
                    continue;
                }
                sendEPQueue(arg);
                putDebugChar(END);
            }
            break;
            case CN_COMMAND: {
                /*cnode */
                unsigned long address, sizebits;
                result = getArg(&address);
                if (result) {
                    continue;
                }
                result = getArg(&sizebits);
                if (result) {
                    continue;
                }

                sendCNode(address, sizebits);
                putDebugChar(END);
            }
            break;
            case IRQ_COMMAND: {
                sendIRQNode();
                putDebugChar(END);
                result = 0;
            }
            break;
            case VERSION_COMMAND: {
                sendVersion();
                putDebugChar(END);
            }
            break;
            case DONE: {
                done = 1;
                putDebugChar(END);
            }
            default:
                result = 0;
                break;
            }
        } while (result);
    }
}

#endif
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/machine/cpu_identification.c"
/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */
#include <string.h>
#include <util.h>
#include <arch/machine.h>

/** @file Support routines for identifying the processor family, model, etc
 * on INTEL x86 processors, as well as attempting to determine the model string.
 *
 * AMD processors would be different.
 */

const char X86_CPUID_VENDOR_STRING_INTEL[] = {'G', 'e', 'n', 'u', 'i', 'n', 'e', 'I', 'n', 't', 'e', 'l', 0};
const char X86_CPUID_VENDOR_STRING_AMD_LEGACY[] = { 'A', 'M', 'D', 'i', 's', 'b', 'e', 't', 't', 'e', 'r', '!', 0};
const char X86_CPUID_VENDOR_STRING_AMD[] = {'A', 'u', 't', 'h', 'e', 'n', 't', 'i', 'c', 'A', 'M', 'D', 0};

BOOT_BSS static cpu_identity_t cpu_identity;

BOOT_CODE cpu_identity_t *x86_cpuid_get_identity(void)
{
    return &cpu_identity;
}

BOOT_CODE x86_cpu_identity_t *x86_cpuid_get_model_info(void)
{
    return &cpu_identity.display;
}

/** Extracts the vendor string from CPUID_000H.E[BCD]X.
 * Will be one of "GenuineIntel", "AMDisbetter!", "AuthenticAMD", "CentaurHauls"
 * etc. We don't support x86 CPUs from vendors other than AMD and Intel.
 */
BOOT_CODE static void
x86_cpuid_fill_vendor_string(cpu_identity_t *ci)
{
    MAY_ALIAS uint32_t *vendor_string32 = (uint32_t *)ci->vendor_string;

    if (ci == NULL) {
        return;
    }

    vendor_string32[0] = x86_cpuid_ebx(0, 0);
    vendor_string32[1] = x86_cpuid_edx(0, 0);
    vendor_string32[2] = x86_cpuid_ecx(0, 0);

    ci->vendor_string[X86_CPUID_VENDOR_STRING_MAXLENGTH] = '\0';
}

struct family_model {
    uint8_t family, model;
};

BOOT_CODE static void
x86_cpuid_intel_identity_initialize(cpu_identity_t *ci,
                                    struct family_model original)
{
    /* Next, there are some values which require additional adjustment, and
     * require you to take into account an additional extended family and model
     * ID.
     *
     * See Intel manuals vol2, section 3.2 for the literal constants.
     */
    if (original.family != 0x0F) {
        ci->display.family = original.family;
    } else {
        ci->display.family = ci->display.extended_family + original.family;
    }

    /* The Intel manuals' wording would make you think you should use the
     * original family_ID value read from CPUID.EAX, like:
     *      if (original->family == 0x06 || original->family == 0x0F) {
     *
     * But Linux doesn't do that, Linux uses the family_ID value AFTER
     * adjustment, like:
     *      if (ci->display.family == 0x06 || ci->display.family == 0x0F) {
     *
     * Additionally, even though the Intel manuals say to adjust the model
     * number if the family number is 0x6 OR 0xF, Linux just adusts it as long
     * as the family number is GREATER THAN OR EQUAL to 0x6.
     *
     * I have followed Linux in the first case, where it could be a case of
     * them having the correct interpretation of the text, but in the second case
     * where they flagrantly disobey the manual, I have not followed them.
     *
     * See Linux source at: /arch/x86/lib/cpu.c:
     *      http://lxr.free-electrons.com/source/arch/x86/lib/cpu.c
     */
    if (ci->display.family == 0x06 || ci->display.family == 0x0F) {
        ci->display.model = (ci->display.extended_model << 4u) + original.model;
    } else {
        ci->display.model = original.model;
    }
}

BOOT_CODE static void
x86_cpuid_amd_identity_initialize(cpu_identity_t *ci,
                                  struct family_model original)
{
    /* Intel and AMD's specifications give slightly different ways to compose
     * the family and model IDs (AMD CPUID manual, section 2.)
     *
     * AMD says that if family is LESS THAN 0xF, then adjustments are needed.
     * Intel says that if family == 0xF || family == 0x6, then adjustments are
     * needed.
     */
    if (original.family < 0xF) {
        ci->display.family = original.family;
        ci->display.model = original.model;
    } else {
        ci->display.family = original.family + ci->display.extended_family;
        ci->display.family = (ci->display.extended_model << 4u) + original.model;
    }
}

bool_t
x86_cpuid_initialize(void)
{
    cpu_identity_t *ci = x86_cpuid_get_identity();
    struct family_model original;
    cpuid_001h_eax_t eax;
    cpuid_001h_ebx_t ebx;

    memset(ci, 0, sizeof(*ci));

    /* First determine which vendor manufactured the CPU. */
    x86_cpuid_fill_vendor_string(ci);

    /* Need both eax and ebx ouput values. */
    eax.words[0] = x86_cpuid_eax(1, 0);
    ebx.words[0] = x86_cpuid_ebx(1, 0);

    /* We now use EAX for the family, model, stepping values, and EBX for the
     * brand index. Store the original values from CPUID_001H.EAX.
     */
    original.family = cpuid_001h_eax_get_family(eax);
    original.model = cpuid_001h_eax_get_model(eax);
    ci->display.stepping = cpuid_001h_eax_get_stepping(eax);

    /* Also store extended family and model values used for adjustment */
    ci->display.extended_family = cpuid_001h_eax_get_extended_family(eax);
    ci->display.extended_model = cpuid_001h_eax_get_extended_model(eax);

    /* Also store the brand index value given in EBX */
    ci->display.brand = cpuid_001h_ebx_get_brand(ebx);

    if (strncmp(ci->vendor_string, X86_CPUID_VENDOR_STRING_INTEL,
                X86_CPUID_VENDOR_STRING_MAXLENGTH) == 0) {
        ci->vendor = X86_VENDOR_INTEL;
        x86_cpuid_intel_identity_initialize(ci, original);
        return true;
    } else if (strncmp(ci->vendor_string, X86_CPUID_VENDOR_STRING_AMD_LEGACY,
                       X86_CPUID_VENDOR_STRING_MAXLENGTH) == 0
               || strncmp(ci->vendor_string, X86_CPUID_VENDOR_STRING_AMD,
                          X86_CPUID_VENDOR_STRING_MAXLENGTH) == 0) {
        ci->vendor = X86_VENDOR_AMD;
        x86_cpuid_amd_identity_initialize(ci, original);
        return true;
    } else {
        /* CPU from unsupported vendor. Examples could be Cyrix, Centaur, etc.
         * The old time x86 clones. Return false to the boot and let the upper
         * level caller decide what to do.
         */
        ci->vendor = X86_VENDOR_OTHER;
        return false;
    }
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/machine/fpu.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <model/statedata.h>
#include <arch/machine/fpu.h>
#include <arch/machine/cpu_registers.h>
#include <arch/object/structures.h>
#include <arch/machine/fpu.h>

/*
 * Setup the FPU register state for a new thread.
 */
void
Arch_initFpuContext(user_context_t *context)
{
    context->fpuState = x86KSnullFpuState;
}

/*
 * Initialise the FPU for this machine.
 */
BOOT_CODE bool_t
Arch_initFpu(void)
{
    /* Enable FPU / SSE / SSE2 / SSE3 / SSSE3 / SSE4 Extensions. */
    write_cr4(read_cr4() | CR4_OSFXSR);

    /* Enable the FPU in general. */
    write_cr0((read_cr0() & ~CR0_EMULATION) | CR0_MONITOR_COPROC | CR0_NUMERIC_ERROR);
    enableFpu();

    /* Initialize the fpu state */
    finit();

    if (config_set(CONFIG_XSAVE)) {
        uint64_t xsave_features;
        uint32_t xsave_instruction;
        uint64_t desired_features = config_ternary(CONFIG_XSAVE, CONFIG_XSAVE_FEATURE_SET, 1);
        xsave_state_t *nullFpuState = (xsave_state_t *) &x86KSnullFpuState;

        /* create NULL state for FPU to be used by XSAVE variants */
        memzero(&x86KSnullFpuState, sizeof(x86KSnullFpuState));

        /* check for XSAVE support */
        if (!(x86_cpuid_ecx(1, 0) & BIT(26))) {
            printf("XSAVE not supported\n");
            return false;
        }
        /* enable XSAVE support */
        write_cr4(read_cr4() | CR4_OSXSAVE);
        /* check feature mask */
        xsave_features = ((uint64_t)x86_cpuid_edx(0x0d, 0x0) << 32) | x86_cpuid_eax(0x0d, 0x0);
        if ((xsave_features & desired_features) != desired_features) {
            printf("Requested feature mask is 0x%llx, but only 0x%llx supported\n", desired_features, (long long)xsave_features);
            return false;
        }
        /* enable feature mask */
        write_xcr0(desired_features);
        /* validate the xsave buffer size and instruction */
        if (x86_cpuid_ebx(0x0d, 0x0) > CONFIG_XSAVE_SIZE) {
            printf("XSAVE buffer set set to %d, but needs to be at least %d\n", CONFIG_XSAVE_SIZE, x86_cpuid_ebx(0x0d, 0x0));
            return false;
        }
        if (x86_cpuid_ebx(0x0d, 0x0) < CONFIG_XSAVE_SIZE) {
            printf("XSAVE buffer set set to %d, but only needs to be %d.\n"
                   "Warning: Memory may be wasted with larger than needed TCBs.\n",
                   CONFIG_XSAVE_SIZE, x86_cpuid_ebx(0x0d, 0x0));
        }
        /* check if a specialized XSAVE instruction was requested */
        xsave_instruction = x86_cpuid_eax(0x0d, 0x1);
        if (config_set(CONFIG_XSAVE_XSAVEOPT)) {
            if (!(xsave_instruction & BIT(0))) {
                printf("XSAVEOPT requested, but not supported\n");
                return false;
            }
        } else if (config_set(CONFIG_XSAVE_XSAVEC)) {
            if (!(xsave_instruction & BIT(1))) {
                printf("XSAVEC requested, but not supported\n");
                return false;
            }
        } else if (config_set(CONFIG_XSAVE_XSAVES)) {
            if (!(xsave_instruction & BIT(3))) {
                printf("XSAVES requested, but not supported\n");
                return false;
            }

            /* AVX state from extended region should be in compacted format */
            nullFpuState->header.xcomp_bv = XCOMP_BV_COMPACTED_FORMAT;

            /* initialize the XSS MSR */
            x86_wrmsr(IA32_XSS_MSR, desired_features);
        }

        /* copy i387 FPU initial state from FPU */
        saveFpuState(&x86KSnullFpuState);
        nullFpuState->i387.mxcsr = MXCSR_INIT_VALUE;
    } else {
        /* Store the null fpu state */
        saveFpuState(&x86KSnullFpuState);
    }
    /* Set the FPU to lazy switch mode */
    disableFpu();
    return true;
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/machine/hardware.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <types.h>
#include <machine/registerset.h>
#include <model/statedata.h>
#include <object/structures.h>
#include <arch/machine.h>
#include <arch/machine/hardware.h>
#include <arch/machine/registerset.h>
#include <linker.h>

/* initialises MSRs required to setup sysenter and sysexit */
BOOT_CODE void
init_sysenter_msrs(void)
{
    x86_wrmsr(IA32_SYSENTER_CS_MSR,  (uint64_t)(word_t)SEL_CS_0);
    x86_wrmsr(IA32_SYSENTER_EIP_MSR, (uint64_t)(word_t)&handle_syscall);
    if (config_set(CONFIG_ARCH_IA32) && !config_set(CONFIG_HARDWARE_DEBUG_API)) {
        /* manually add 4 bytes to x86KStss so that it is valid for both
         * 32-bit and 64-bit, although only ia32 actually requires a valid
         * sysenter esp */
        x86_wrmsr(IA32_SYSENTER_ESP_MSR, (uint64_t)(word_t)((char *)&x86KSGlobalState[CURRENT_CPU_INDEX()].x86KStss.tss.words[0] + 4));
    }
}

word_t PURE getRestartPC(tcb_t *thread)
{
    return getRegister(thread, FaultIP);
}

void setNextPC(tcb_t *thread, word_t v)
{
    setRegister(thread, NextIP, v);
}

/* Returns the size of CPU's cacheline */
BOOT_CODE uint32_t CONST
getCacheLineSizeBits(void)
{
    uint32_t line_size;
    uint32_t n;

    line_size = getCacheLineSize();
    if (line_size == 0) {
        printf("Cacheline size must be >0\n");
        return 0;
    }

    /* determine size_bits */
    n = 0;
    while (!(line_size & 1)) {
        line_size >>= 1;
        n++;
    }

    if (line_size != 1) {
        printf("Cacheline size must be a power of two\n");
        return 0;
    }

    return n;
}

/* Flushes a specific memory range from the CPU cache */

void flushCacheRange(void* vaddr, uint32_t size_bits)
{
    word_t v;

    assert(size_bits < seL4_WordBits);
    assert(IS_ALIGNED((word_t)vaddr, size_bits));

    x86_mfence();

    for (v = ROUND_DOWN((word_t)vaddr, x86KScacheLineSizeBits);
            v < (word_t)vaddr + BIT(size_bits);
            v += BIT(x86KScacheLineSizeBits)) {
        flushCacheLine((void*)v);
    }
    x86_mfence();
}

/* Disables as many prefetchers as possible */
BOOT_CODE bool_t
disablePrefetchers()
{
    x86_cpu_identity_t *model_info;
    uint32_t low, high;
    word_t i;

    uint32_t valid_models[] = { BROADWELL_1_MODEL_ID, BROADWELL_2_MODEL_ID,
                                BROADWELL_3_MODEL_ID, BROADWELL_4_MODEL_ID,
                                BROADWELL_5_MODEL_ID,
                                HASWELL_1_MODEL_ID,  HASWELL_2_MODEL_ID,
                                HASWELL_3_MODEL_ID, HASWELL_4_MODEL_ID,
                                IVY_BRIDGE_1_MODEL_ID,  IVY_BRIDGE_2_MODEL_ID,
                                IVY_BRIDGE_3_MODEL_ID,
                                SANDY_BRIDGE_1_MODEL_ID, SANDY_BRIDGE_2_MODEL_ID, WESTMERE_1_MODEL_ID, WESTMERE_2_MODEL_ID,
                                WESTMERE_3_MODEL_ID, NEHALEM_1_MODEL_ID, NEHALEM_2_MODEL_ID, NEHALEM_3_MODEL_ID,
                                SKYLAKE_1_MODEL_ID, SKYLAKE_2_MODEL_ID
                              };

    model_info = x86_cpuid_get_model_info();

    for (i = 0; i < ARRAY_SIZE(valid_models); i++) {
        /* The model ID is only useful when hashed together with the family ID.
         * They are both meant to be combined to form a unique identifier.
         *
         * As far as I can tell though, we might be able to actually just
         * disable prefetching on anything that matches family_ID==0x6, and
         * there is no need to also look at the model_ID.
         */
        if (model_info->family == IA32_PREFETCHER_COMPATIBLE_FAMILIES_ID
                && model_info->model == valid_models[i]) {
            low = x86_rdmsr_low(IA32_PREFETCHER_MSR);
            high = x86_rdmsr_high(IA32_PREFETCHER_MSR);

            low |= IA32_PREFETCHER_MSR_L2;
            low |= IA32_PREFETCHER_MSR_L2_ADJACENT;
            low |= IA32_PREFETCHER_MSR_DCU;
            low |= IA32_PREFETCHER_MSR_DCU_IP;

            x86_wrmsr(IA32_PREFETCHER_MSR, ((uint64_t)high) << 32 | low);

            return true;
        }
    }

    printf("Disabling prefetchers not implemented for CPU fam %x model %x\n",
           model_info->family, model_info->model);
    return false;
}

BOOT_CODE void
enablePMCUser(void)
{
    write_cr4(read_cr4() | CR4_PCE);
}

BOOT_CODE bool_t
init_ibrs(void)
{
    cpuid_007h_edx_t edx;
    edx.words[0] = x86_cpuid_edx(0x7, 0);
    bool_t support_ibrs = cpuid_007h_edx_get_ibrs_ibpb(edx);
    if ((config_set(CONFIG_KERNEL_X86_IBRS_BASIC) || config_set(CONFIG_KERNEL_X86_IBRS_STIBP)) && !support_ibrs) {
        printf("IBRS not supported by CPU\n");
        return false;
    } else if (support_ibrs) {
        /* 'disable' IBRS. For IBRS_BASIC this does nothing, and for STIBP this will cause
         * us to enable STIBP, and we can then forget about it */
        x86_disable_ibrs();
    }
    /* IBRS is also the feature flag for IBPB */
    if (config_set(CONFIG_KERNEL_X86_IBPB_ON_CONTEXT_SWITCH) && !support_ibrs) {
        printf("IBPB not supported by CPU\n");
        return false;
    }
    /* check for enhanced IBRS */
    bool_t enhanced_ibrs = false;
    if (cpuid_007h_edx_get_ia32_arch_cap_msr(edx)) {
        ia32_arch_capabilities_msr_t cap_msr;
        cap_msr.words[0] = x86_rdmsr(IA32_ARCH_CAPABILITIES_MSR);
        if (ia32_arch_capabilities_msr_get_ibrs_all(cap_msr)) {
            enhanced_ibrs = true;
        }
    }
    if (config_set(CONFIG_KERNEL_X86_IBRS_BASIC) && enhanced_ibrs) {
        printf("Kernel configured for basic IBRS, but CPU supports enhanced IBRS. "
               "Enable enhanced IBRS for improved performance\n");
    }
    if (config_set(CONFIG_KERNEL_X86_IBRS_ALL)) {
        if (!enhanced_ibrs) {
            printf("Enhanced IBRS not supported by CPU\n");
            return false;
        }
        /* enable IBRS and then we can forget about it */
        x86_enable_ibrs();
    }
    return true;
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/machine/registerset.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <arch/machine/registerset.h>

void Arch_initContext(user_context_t* context)
{
    Mode_initContext(context);
    context->registers[TLS_BASE] = 0;
    context->registers[Error] = 0;
    context->registers[FaultIP] = 0;
    context->registers[NextIP] = 0;            /* overwritten by setNextPC() later on */
    context->registers[CS] = SEL_CS_3;
    context->registers[FLAGS] = FLAGS_USER_DEFAULT;
    context->registers[SS] = SEL_DS_3;

    Arch_initFpuContext(context);
#ifdef CONFIG_HARDWARE_DEBUG_API
    Arch_initBreakpointContext(&context->breakpointState);
#endif
}

word_t sanitiseRegister(register_t reg, word_t v, bool_t archInfo)
{
    /* First perform any mode specific sanitization */
    v = Mode_sanitiseRegister(reg, v);
    if (reg == FLAGS) {
        /* Set architecturally defined high and low bits */
        v |=  FLAGS_HIGH;
        v &= ~FLAGS_LOW;
        /* require user to have interrupts and no traps */
        v |=  FLAGS_IF;
        v &= ~FLAGS_TF;
        /* remove any other bits that shouldn't be set */
        v &=  FLAGS_MASK;
    }
    return v;
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/model/statedata.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <util.h>
#include <api/types.h>
#include <arch/types.h>
#include <arch/model/statedata.h>
#include <arch/object/structures.h>

/* ==== read/write kernel state not preserved across kernel entries ==== */

/* Interrupt currently being handled */
UP_STATE_DEFINE(interrupt_t, x86KScurInterrupt VISIBLE);

UP_STATE_DEFINE(interrupt_t, x86KSPendingInterrupt);

/* ==== proper read/write kernel state ==== */

x86_arch_global_state_t x86KSGlobalState[CONFIG_MAX_NUM_NODES] ALIGN(L1_CACHE_LINE_SIZE) SKIM_BSS;

/* The top level ASID table */
asid_pool_t* x86KSASIDTable[BIT(asidHighBits)];

/* Current user value of the fs/gs base */
UP_STATE_DEFINE(word_t, x86KSCurrentFSBase);
UP_STATE_DEFINE(word_t, x86KSCurrentGSBase);

UP_STATE_DEFINE(word_t, x86KSGPExceptReturnTo);

/* ==== read-only kernel state (only written during bootstrapping) ==== */

/* Defines a translation of cpu ids from an index of our actual CPUs */
SMP_STATE_DEFINE(cpu_id_mapping_t, cpu_mapping);

/* CPU Cache Line Size */
uint32_t x86KScacheLineSizeBits;

/* A valid initial FPU state, copied to every new thread. */
user_fpu_state_t x86KSnullFpuState ALIGN(MIN_FPU_ALIGNMENT);

/* Number of IOMMUs (DMA Remapping Hardware Units) */
uint32_t x86KSnumDrhu;

#ifdef CONFIG_IOMMU
/* Intel VT-d Root Entry Table */
vtd_rte_t* x86KSvtdRootTable;
uint32_t x86KSnumIOPTLevels;
uint32_t x86KSnumIODomainIDBits;
uint32_t x86KSFirstValidIODomain;
#endif

#ifdef CONFIG_VTX
UP_STATE_DEFINE(vcpu_t *, x86KSCurrentVCPU);
#endif

#ifdef CONFIG_PRINTING
uint16_t x86KSconsolePort;
#endif
#ifdef CONFIG_DEBUG_BUILD
uint16_t x86KSdebugPort;
#endif

/* State data tracking what IRQ source is related to each
 * CPU vector */
x86_irq_state_t x86KSIRQState[maxIRQ + 1];

word_t x86KSAllocatedIOPorts[NUM_IO_PORTS / CONFIG_WORD_SIZE];
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/object/interrupt.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <kernel/boot.h>
#include <model/statedata.h>
#include <arch/object/interrupt.h>
#include <arch/api/invocation.h>
#include <linker.h>
#include <plat/machine/hardware.h>
#include <plat/machine/pci.h>

void
Arch_irqStateInit(void)
{
    int i = 0;
    for (i = 0; i <= maxIRQ; i++) {
        if (i == irq_timer
#ifdef CONFIG_IOMMU
                || i == irq_iommu
#endif
           ) {
            x86KSIRQState[i] = x86_irq_state_irq_reserved_new();
        } else {
            x86KSIRQState[i] = x86_irq_state_irq_free_new();
        }
    }
}

/* for x86, the IRQIssueIRQHandler is only allowed to
 * issue a hander for IRQ 0-15, the isa IRQs.
 * Use getIRQHandlerIOAPIC and getIRQHandlerMSI for
 * the IRQs >= 16. Additionally these IRQs only exist
 * if using the legacy PIC interrupt
 */
exception_t
Arch_checkIRQ(word_t irq_w)
{
    if (config_set(CONFIG_IRQ_PIC) && irq_w >= irq_isa_min && irq_w <= irq_isa_max) {
        return EXCEPTION_NONE;
    }
    if (config_set(CONFIG_IRQ_IOAPIC)) {
        userError("IRQControl: Illegal operation");
        current_syscall_error.type = seL4_IllegalOperation;
    } else {
        userError("IRQControl: IRQ %ld should be in range %ld - %ld", irq_w, (long)irq_isa_min, (long)irq_isa_max);
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = irq_isa_min;
        current_syscall_error.rangeErrorMax = irq_isa_max;
    }
    return EXCEPTION_SYSCALL_ERROR;
}

static exception_t
Arch_invokeIRQControl(irq_t irq, cte_t *handlerSlot, cte_t *controlSlot, x86_irq_state_t irqState)
{
    updateIRQState(irq, irqState);
    return invokeIRQControl(irq, handlerSlot, controlSlot);
}

static exception_t
invokeIssueIRQHandlerIOAPIC(irq_t irq, word_t ioapic, word_t pin, word_t level, word_t polarity, word_t vector,
                            cte_t *handlerSlot, cte_t *controlSlot)
{
    x86_irq_state_t irqState = x86_irq_state_irq_ioapic_new(ioapic, pin, level, polarity, 1);
    ioapic_map_pin_to_vector(ioapic, pin, level, polarity, vector);
    return Arch_invokeIRQControl(irq, handlerSlot, controlSlot, irqState);
}

exception_t
Arch_decodeIRQControlInvocation(word_t invLabel, word_t length, cte_t *srcSlot, extra_caps_t excaps, word_t *buffer)
{
    word_t index, depth;
    cte_t *destSlot;
    cap_t cnodeCap;
    lookupSlot_ret_t lu_ret;
    exception_t status;
    irq_t irq;
    word_t vector;

    if (!config_set(CONFIG_IRQ_IOAPIC)) {
        userError("IRQControl: Illegal operation.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* ensure we have a valid invocation before continuing any decoding */
    if (invLabel != X86IRQIssueIRQHandlerIOAPIC && invLabel != X86IRQIssueIRQHandlerMSI) {
        userError("IRQControl: Illegal operation");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* check the common parameters */

    if (length < 7 || excaps.excaprefs[0] == NULL) {
        userError("IRQControl: Truncated message");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }
    index = getSyscallArg(0, buffer);
    depth = getSyscallArg(1, buffer);
    cnodeCap = excaps.excaprefs[0]->cap;
    irq = getSyscallArg(6, buffer);
    if (irq > irq_user_max - irq_user_min) {
        userError("IRQControl: Invalid irq %ld should be between 0-%ld", (long)irq, (long)(irq_user_max - irq_user_min));
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 0;
        current_syscall_error.rangeErrorMax = irq_user_max - irq_user_min;
        return EXCEPTION_SYSCALL_ERROR;
    }
    irq += irq_user_min;

    if (isIRQActive(irq)) {
        userError("IRQControl: IRQ %d is already active.", (int)irq);
        current_syscall_error.type = seL4_RevokeFirst;
        return EXCEPTION_SYSCALL_ERROR;
    }

    vector = (word_t)irq + IRQ_INT_OFFSET;

    lu_ret = lookupTargetSlot(cnodeCap, index, depth);
    if (lu_ret.status != EXCEPTION_NONE) {
        return lu_ret.status;
    }

    destSlot = lu_ret.slot;

    status = ensureEmptySlot(destSlot);
    if (status != EXCEPTION_NONE) {
        return status;
    }

    switch (invLabel) {
    case X86IRQIssueIRQHandlerIOAPIC: {
        word_t ioapic = getSyscallArg(2, buffer);
        word_t pin = getSyscallArg(3, buffer);
        word_t level = getSyscallArg(4, buffer);
        word_t polarity = getSyscallArg(5, buffer);

        status = ioapic_decode_map_pin_to_vector(ioapic, pin, level, polarity, vector);
        if (status != EXCEPTION_NONE) {
            return status;
        }

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return invokeIssueIRQHandlerIOAPIC(irq, ioapic, pin, level, polarity, vector, destSlot, srcSlot);
    }
    break;
    case X86IRQIssueIRQHandlerMSI: {
        word_t pci_bus = getSyscallArg(2, buffer);
        word_t pci_dev = getSyscallArg(3, buffer);
        word_t pci_func = getSyscallArg(4, buffer);
        word_t handle = getSyscallArg(5, buffer);
        x86_irq_state_t irqState;
        /* until we support msi interrupt remaping through vt-d we ignore the
         * vector and trust the user */
        (void)vector;

        if (pci_bus > PCI_BUS_MAX) {
            current_syscall_error.type = seL4_RangeError;
            current_syscall_error.rangeErrorMin = 0;
            current_syscall_error.rangeErrorMax = PCI_BUS_MAX;
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (pci_dev > PCI_DEV_MAX) {
            current_syscall_error.type = seL4_RangeError;
            current_syscall_error.rangeErrorMin = 0;
            current_syscall_error.rangeErrorMax = PCI_DEV_MAX;
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (pci_func > PCI_FUNC_MAX) {
            current_syscall_error.type = seL4_RangeError;
            current_syscall_error.rangeErrorMin = 0;
            current_syscall_error.rangeErrorMax = PCI_FUNC_MAX;
            return EXCEPTION_SYSCALL_ERROR;
        }

        irqState = x86_irq_state_irq_msi_new(pci_bus, pci_dev, pci_func, handle);

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return Arch_invokeIRQControl(irq, destSlot, srcSlot, irqState);
    }
    break;
    default:
        /* the check at the start of this function should guarantee we do not get here */
        fail("IRQControl: Illegal operation");
    }
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/object/ioport.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <kernel/thread.h>
#include <api/failures.h>
#include <api/syscall.h>
#include <machine/io.h>
#include <arch/object/ioport.h>
#include <arch/api/invocation.h>
#include <plat/machine/io.h>

static inline void
apply_pattern(word_t_may_alias *w, word_t pattern, bool_t set)
{
    if (set) {
        *w |= pattern;
    } else {
        *w &= ~pattern;
    }
}

static inline word_t
make_pattern(int start, int end)
{
    // number of bits we want to have set
    int num_bits = end - start;
    // shift down to cut off the bits we don't want, then shift up to put the
    // bits into position
    return (~(word_t)0) >> (CONFIG_WORD_SIZE - num_bits) << start;
}

static exception_t
ensurePortOperationAllowed(cap_t cap, uint32_t start_port, uint32_t size)
{
    uint32_t first_allowed = cap_io_port_cap_get_capIOPortFirstPort(cap);
    uint32_t last_allowed = cap_io_port_cap_get_capIOPortLastPort(cap);
    uint32_t end_port = start_port + size - 1;
    assert(first_allowed <= last_allowed);
    assert(start_port <= end_port);

    if ((start_port < first_allowed) || (end_port > last_allowed)) {
        userError("IOPort: Ports %d--%d fall outside permitted range %d--%d.",
                  (int)start_port, (int)end_port,
                  (int)first_allowed, (int)last_allowed);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    return EXCEPTION_NONE;
}

void
freeIOPortRange(uint16_t first_port, uint16_t last_port)
{
    setIOPortMask(x86KSAllocatedIOPorts, first_port, last_port, false);
}

static bool_t
isIOPortRangeFree(uint16_t first_port, uint16_t last_port)
{
    int low_word = first_port >> wordRadix;
    int high_word = last_port >> wordRadix;
    int low_index = first_port & MASK(wordRadix);
    int high_index = last_port & MASK(wordRadix);

    // check if we are operating on a partial word
    if (low_word == high_word) {
        if ((x86KSAllocatedIOPorts[low_word] & make_pattern(low_index, high_index + 1)) != 0) {
            return false;
        }
        return true;
    }
    // check the starting word
    if ((x86KSAllocatedIOPorts[low_word] & make_pattern(low_index, CONFIG_WORD_SIZE)) != 0) {
        return false;
    }
    low_word++;
    // check the rest of the whole words
    while (low_word < high_word) {
        if (x86KSAllocatedIOPorts[low_word] != 0) {
            return false;
        }
        low_word++;
    }
    // check any trailing bits
    if ((x86KSAllocatedIOPorts[low_word] & make_pattern(0, high_index + 1)) != 0) {
        return false;
    }
    return true;
}

static exception_t
invokeX86PortControl(uint16_t first_port, uint16_t last_port, cte_t *ioportSlot, cte_t *controlSlot)
{
    setIOPortMask(x86KSAllocatedIOPorts, first_port, last_port, true);
    cteInsert(cap_io_port_cap_new(first_port, last_port
#ifdef CONFIG_VTX
                                  , VPID_INVALID
#endif
                                 ),
              controlSlot, ioportSlot);

    return EXCEPTION_NONE;
}

exception_t
decodeX86PortControlInvocation(
    word_t invLabel,
    word_t length,
    cptr_t cptr,
    cte_t* slot,
    cap_t cap,
    extra_caps_t excaps,
    word_t* buffer
)
{
    uint16_t first_port;
    uint16_t last_port;
    word_t index, depth;
    cap_t cnodeCap;
    cte_t *destSlot;
    lookupSlot_ret_t lu_ret;
    exception_t status;

    if (invLabel != X86IOPortControlIssue) {
        userError("IOPortControl: Unknown operation.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (length < 4 || excaps.excaprefs[0] == NULL) {
        userError("IOPortControl: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    first_port = getSyscallArg(0, buffer) & 0xffff;
    last_port = getSyscallArg(1, buffer) & 0xffff;
    index = getSyscallArg(2, buffer);
    depth = getSyscallArg(3, buffer);

    cnodeCap = excaps.excaprefs[0]->cap;

    if (last_port < first_port) {
        userError("IOPortControl: Last port must be > first port.");
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (!isIOPortRangeFree(first_port, last_port)) {
        userError("IOPortControl: Some ports in range already in use.");
        current_syscall_error.type = seL4_RevokeFirst;
        return EXCEPTION_SYSCALL_ERROR;
    }

    lu_ret = lookupTargetSlot(cnodeCap, index, depth);
    if (lu_ret.status != EXCEPTION_NONE ) {
        userError("Target slot for new IO Port cap invalid: cap %lu.", getExtraCPtr(buffer, 0));
        return lu_ret.status;
    }
    destSlot = lu_ret.slot;

    status = ensureEmptySlot(destSlot);
    if (status != EXCEPTION_NONE) {
        userError("Target slot for new IO Port cap not empty: cap %lu.", getExtraCPtr(buffer, 0));
        return status;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeX86PortControl(first_port, last_port, destSlot, slot);
}

static exception_t
invokeX86PortIn(word_t invLabel, uint16_t port, bool_t call)
{
    uint32_t res;
    word_t len;

    switch (invLabel) {
    case X86IOPortIn8:
        res = in8(port);
        break;
    case X86IOPortIn16:
        res = in16(port);
        break;
    case X86IOPortIn32:
        res = in32(port);
        break;
    }

    if (call) {
        setRegister(NODE_STATE(ksCurThread), badgeRegister, 0);

        if (n_msgRegisters < 1) {
            word_t* ipcBuffer;
            ipcBuffer = lookupIPCBuffer(true, NODE_STATE(ksCurThread));
            if (ipcBuffer != NULL) {
                ipcBuffer[1] = res;
                len = 1;
            } else {
                len = 0;
            }
        } else {
            setRegister(NODE_STATE(ksCurThread), msgRegisters[0], res);
            len = 1;
        }

        setRegister(NODE_STATE(ksCurThread), msgInfoRegister,
                    wordFromMessageInfo(seL4_MessageInfo_new(0, 0, 0, len)));
    }
    // Prevent handleInvocation from attempting to complete the 'call' with an empty
    // message (via replyFromKernel_success_empty) by forcing the thread state to
    // be running. This prevents our stored message we just created from being
    // overwritten.
    setThreadState(NODE_STATE(ksCurThread), ThreadState_Running);

    return EXCEPTION_NONE;
}

static exception_t
invokeX86PortOut(word_t invLabel, uint16_t port, uint32_t data)
{
    switch (invLabel) {
    case X86IOPortOut8:
        out8(port, data);
        break;
    case X86IOPortOut16:
        out16(port, data);
        break;
    case X86IOPortOut32:
        out32(port, data);
        break;
    }

    return EXCEPTION_NONE;
}

exception_t
decodeX86PortInvocation(
    word_t invLabel,
    word_t length,
    cptr_t cptr,
    cte_t* slot,
    cap_t cap,
    extra_caps_t excaps,
    bool_t call,
    word_t* buffer
)
{
    exception_t ret;

    if (invLabel == X86IOPortIn8 || invLabel == X86IOPortIn16 || invLabel == X86IOPortIn32) {
        if (length < 1) {
            userError("IOPort: Truncated message.");
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }
        /* Get the port the user is trying to read from. */
        uint16_t port = getSyscallArg(0, buffer) & 0xffff;
        switch (invLabel) {
        case X86IOPortIn8:
            ret = ensurePortOperationAllowed(cap, port, 1);
            break;
        case X86IOPortIn16:
            ret = ensurePortOperationAllowed(cap, port, 2);
            break;
        case X86IOPortIn32:
            ret = ensurePortOperationAllowed(cap, port, 4);
            break;
        }
        if (ret != EXCEPTION_NONE) {
            return ret;
        }
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return invokeX86PortIn(invLabel, port, call);
    } else if (invLabel == X86IOPortOut8 || invLabel == X86IOPortOut16 || invLabel == X86IOPortOut32) {
        /* Ensure the incoming message is long enough for the write. */
        if (length < 2) {
            userError("IOPort Out: Truncated message.");
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }
        /* Get the port the user is trying to write to. */
        uint16_t port = getSyscallArg(0, buffer) & 0xffff;
        seL4_Word raw_data = getSyscallArg(1, buffer);
        /* We construct the value for data from raw_data based on the actual size of the port
           operation. This ensures that there is no 'random' user data left over in the value
           passed to invokeX86PortOut. Whilst invokeX86PortOut will ignore any extra data and
           cast down to the correct word size removing the extra here is currently relied upon
           for verification */
        uint32_t data;

        switch (invLabel) {
        case X86IOPortOut8:
            ret = ensurePortOperationAllowed(cap, port, 1);
            data = raw_data & 0xff;
            break;
        case X86IOPortOut16:
            ret = ensurePortOperationAllowed(cap, port, 2);
            data = raw_data & 0xffff;
            break;
        case X86IOPortOut32:
            ret = ensurePortOperationAllowed(cap, port, 4);
            data = raw_data & 0xffffffff;
            break;
        }
        if (ret != EXCEPTION_NONE) {
            return ret;
        }
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return invokeX86PortOut(invLabel, port, data);
    } else {
        userError("IOPort: Unknown operation.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
}

void
setIOPortMask(void *ioport_bitmap, uint16_t low, uint16_t high, bool_t set)
{
    //get an aliasing pointer
    word_t_may_alias *bitmap = ioport_bitmap;

    int low_word = low >> wordRadix;
    int high_word = high >> wordRadix;
    int low_index = low & MASK(wordRadix);
    int high_index = high & MASK(wordRadix);

    // see if we are just manipulating bits inside a single word. handling this
    // specially makes reasoning easier
    if (low_word == high_word) {
        apply_pattern(bitmap + low_word, make_pattern(low_index, high_index + 1), set);
    } else {
        // operate on the potentially partial first word
        apply_pattern(bitmap + low_word, make_pattern(low_index, CONFIG_WORD_SIZE), set);
        low_word++;
        // iterate over the whole words
        while (low_word < high_word) {
            apply_pattern(bitmap + low_word, ~(word_t)0, set);
            low_word++;
        }
        // apply to any remaining bits
        apply_pattern(bitmap + low_word, make_pattern(0, high_index + 1), set);
    }
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/object/iospace.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>

#ifdef CONFIG_IOMMU

#include <api/syscall.h>
#include <machine/io.h>
#include <kernel/thread.h>
#include <arch/api/invocation.h>
#include <arch/object/iospace.h>
#include <arch/model/statedata.h>
#include <linker.h>
#include <plat/machine/intel-vtd.h>


typedef struct lookupVTDContextSlot_ret {
    vtd_cte_t   *cte;
    word_t      index;
} lookupVTDContextSlot_ret_t;


BOOT_CODE cap_t
master_iospace_cap(void)
{
    if (x86KSnumDrhu == 0) {
        return cap_null_cap_new();
    }

    return
        cap_io_space_cap_new(
            0,              /* capDomainID  */
            0              /* capPCIDevice */
        );
}

static vtd_cte_t*
lookup_vtd_context_slot(cap_t cap)
{
    uint32_t   vtd_root_index;
    uint32_t   vtd_context_index;
    uint32_t   pci_request_id;
    vtd_rte_t* vtd_root_slot;
    vtd_cte_t* vtd_context;
    vtd_cte_t* vtd_context_slot;

    switch (cap_get_capType(cap)) {
    case cap_io_space_cap:
        pci_request_id = cap_io_space_cap_get_capPCIDevice(cap);
        break;

    case cap_io_page_table_cap:
        pci_request_id = cap_io_page_table_cap_get_capIOPTIOASID(cap);
        break;

    case cap_frame_cap:
        pci_request_id = cap_frame_cap_get_capFMappedASID(cap);
        break;

    default:
        fail("Invalid cap type");
    }

    vtd_root_index = get_pci_bus(pci_request_id);
    vtd_root_slot = x86KSvtdRootTable + vtd_root_index;

    vtd_context = (vtd_cte_t*)paddr_to_pptr(vtd_rte_ptr_get_ctp(vtd_root_slot));
    vtd_context_index = (get_pci_dev(pci_request_id) << 3) | get_pci_fun(pci_request_id);
    vtd_context_slot = &vtd_context[vtd_context_index];

    return vtd_context_slot;
}

static lookupIOPTSlot_ret_t
lookupIOPTSlot_resolve_levels(vtd_pte_t *iopt, word_t translation,
                              word_t levels_to_resolve, word_t levels_remaining)
{
    lookupIOPTSlot_ret_t ret;

    word_t      iopt_index = 0;
    vtd_pte_t   *iopt_slot = 0;
    vtd_pte_t   *next_iopt_slot = 0;

    if (iopt == 0) {
        ret.ioptSlot = 0;
        ret.level = levels_remaining;
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }

    iopt_index = (translation  >> (VTD_PT_INDEX_BITS * (x86KSnumIOPTLevels - 1 - (levels_to_resolve - levels_remaining)))) & MASK(VTD_PT_INDEX_BITS);
    iopt_slot = iopt + iopt_index;

    if (!vtd_pte_ptr_get_write(iopt_slot) || levels_remaining == 0) {
        ret.ioptSlot = iopt_slot;
        ret.level = levels_remaining;
        ret.status = EXCEPTION_NONE;
        return ret;
    }
    next_iopt_slot = (vtd_pte_t *)paddr_to_pptr(vtd_pte_ptr_get_addr(iopt_slot));
    return lookupIOPTSlot_resolve_levels(next_iopt_slot, translation, levels_to_resolve, levels_remaining - 1);
}


static inline lookupIOPTSlot_ret_t
lookupIOPTSlot(vtd_pte_t* iopt, word_t io_address)
{
    lookupIOPTSlot_ret_t ret;

    if (iopt == 0) {
        ret.ioptSlot    = 0;
        ret.level       = 0;
        ret.status      = EXCEPTION_LOOKUP_FAULT;
        return ret;
    } else {
        return lookupIOPTSlot_resolve_levels(iopt, io_address >> PAGE_BITS,
                                             x86KSnumIOPTLevels - 1, x86KSnumIOPTLevels - 1);
    }
}

void
unmapVTDContextEntry(cap_t cap)
{
    vtd_cte_t *cte = lookup_vtd_context_slot(cap);
    assert(cte != 0);
    *cte = vtd_cte_new(
               0,
               false,
               0,
               0,
               0,
               false
           );

    flushCacheRange(cte, VTD_CTE_SIZE_BITS);
    invalidate_iotlb();
    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return;
}

static exception_t
performX86IOPTInvocationUnmap(cap_t cap, cte_t *ctSlot)
{
    deleteIOPageTable(cap);
    cap = cap_io_page_table_cap_set_capIOPTIsMapped(cap, 0);
    ctSlot->cap = cap;

    return EXCEPTION_NONE;
}

static exception_t
performX86IOPTInvocationMapContextRoot(cap_t cap, cte_t *ctSlot, vtd_cte_t vtd_cte, vtd_cte_t *vtd_context_slot)
{
    *vtd_context_slot = vtd_cte;
    flushCacheRange(vtd_context_slot, VTD_CTE_SIZE_BITS);
    ctSlot->cap = cap;

    return EXCEPTION_NONE;
}

static exception_t
performX86IOPTInvocationMapPT(cap_t cap, cte_t *ctSlot, vtd_pte_t iopte, vtd_pte_t *ioptSlot)
{
    *ioptSlot = iopte;
    flushCacheRange(ioptSlot, VTD_PTE_SIZE_BITS);
    ctSlot->cap = cap;

    return EXCEPTION_NONE;
}

exception_t
decodeX86IOPTInvocation(
    word_t       invLabel,
    word_t       length,
    cte_t*       slot,
    cap_t        cap,
    extra_caps_t excaps,
    word_t*      buffer
)
{
    cap_t      io_space;
    paddr_t    paddr;
    uint32_t   pci_request_id;
    word_t   io_address;
    uint16_t   domain_id;
    vtd_cte_t* vtd_context_slot;
    vtd_pte_t* vtd_pte;

    if (invLabel == X86IOPageTableUnmap) {

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performX86IOPTInvocationUnmap(cap, slot);
    }

    if (invLabel != X86IOPageTableMap ) {
        userError("X86IOPageTable: Illegal operation.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (excaps.excaprefs[0] == NULL || length < 1) {
        userError("X86IOPageTableMap: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    io_space     = excaps.excaprefs[0]->cap;
    io_address   = getSyscallArg(0, buffer) & ~MASK(VTD_PT_INDEX_BITS + seL4_PageBits);

    if (cap_io_page_table_cap_get_capIOPTIsMapped(cap)) {
        userError("X86IOPageTableMap: IO page table is already mapped.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (cap_get_capType(io_space) != cap_io_space_cap) {
        userError("X86IOPageTableMap: Invalid IO space capability.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    pci_request_id = cap_io_space_cap_get_capPCIDevice(io_space);
    domain_id = cap_io_space_cap_get_capDomainID(io_space);
    if (pci_request_id == asidInvalid) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;

        return EXCEPTION_SYSCALL_ERROR;
    }

    paddr = pptr_to_paddr(VTD_PTE_PTR(cap_io_page_table_cap_get_capIOPTBasePtr(cap)));
    vtd_context_slot = lookup_vtd_context_slot(io_space);

    if (!vtd_cte_ptr_get_present(vtd_context_slot)) {

        /* 1st Level Page Table */
        vtd_cte_t vtd_cte = vtd_cte_new(
                                domain_id,                  /* domain ID                   */
                                false,                      /* RMRR                        */
                                x86KSnumIOPTLevels - 2,     /* addr width (x = levels - 2) */
                                paddr,                      /* address space root          */
                                0,                          /* translation type            */
                                true                        /* present                     */
                            );

        cap = cap_io_page_table_cap_set_capIOPTIsMapped(cap, 1);
        cap = cap_io_page_table_cap_set_capIOPTLevel(cap, 0);
        cap = cap_io_page_table_cap_set_capIOPTIOASID(cap, pci_request_id);

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performX86IOPTInvocationMapContextRoot(cap, slot, vtd_cte, vtd_context_slot);
    } else {
        lookupIOPTSlot_ret_t lu_ret;
        vtd_pte_t   iopte;

        vtd_pte = (vtd_pte_t *)paddr_to_pptr(vtd_cte_ptr_get_asr(vtd_context_slot));
        lu_ret  = lookupIOPTSlot(vtd_pte, io_address);

        if (lu_ret.status != EXCEPTION_NONE) {
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = false;
            return EXCEPTION_SYSCALL_ERROR;
        }

        lu_ret.level = x86KSnumIOPTLevels - lu_ret.level;
        if (vtd_pte_ptr_get_addr(lu_ret.ioptSlot) != 0) {
            current_syscall_error.type = seL4_DeleteFirst;

            return EXCEPTION_SYSCALL_ERROR;
        }

        iopte = vtd_pte_new(
                    paddr,      /* physical addr            */
                    1,          /* write permission flag    */
                    1           /* read  permission flag    */
                );

        cap = cap_io_page_table_cap_set_capIOPTIsMapped(cap, 1);
        cap = cap_io_page_table_cap_set_capIOPTLevel(cap, lu_ret.level);
        cap = cap_io_page_table_cap_set_capIOPTIOASID(cap, pci_request_id);
        cap = cap_io_page_table_cap_set_capIOPTMappedAddress(cap, io_address);

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performX86IOPTInvocationMapPT(cap, slot, iopte, lu_ret.ioptSlot);
    }
}

static exception_t
performX86IOInvocationMap(cap_t cap, cte_t *ctSlot, vtd_pte_t iopte, vtd_pte_t *ioptSlot)
{
    ctSlot->cap = cap;
    *ioptSlot = iopte;
    flushCacheRange(ioptSlot, VTD_PTE_SIZE_BITS);

    return EXCEPTION_NONE;
}


exception_t
decodeX86IOMapInvocation(
    word_t       length,
    cte_t*       slot,
    cap_t        cap,
    extra_caps_t excaps,
    word_t*      buffer
)
{
    cap_t      io_space;
    word_t     io_address;
    uint32_t   pci_request_id;
    vtd_cte_t* vtd_context_slot;
    vtd_pte_t* vtd_pte;
    vtd_pte_t  iopte;
    paddr_t    paddr;
    lookupIOPTSlot_ret_t lu_ret;
    vm_rights_t frame_cap_rights;
    seL4_CapRights_t dma_cap_rights_mask;

    if (excaps.excaprefs[0] == NULL || length < 2) {
        userError("X86PageMapIO: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (cap_frame_cap_get_capFSize(cap) != X86_SmallPage) {
        userError("X86PageMapIO: Invalid page size.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (cap_frame_cap_get_capFMappedASID(cap) != asidInvalid) {
        userError("X86PageMapIO: Page already mapped.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    io_space    = excaps.excaprefs[0]->cap;
    io_address  = getSyscallArg(1, buffer) & ~MASK(PAGE_BITS);
    paddr       = pptr_to_paddr((void*)cap_frame_cap_get_capFBasePtr(cap));

    if (cap_get_capType(io_space) != cap_io_space_cap) {
        userError("X86PageMapIO: Invalid IO space capability.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    pci_request_id = cap_io_space_cap_get_capPCIDevice(io_space);

    if (pci_request_id == asidInvalid) {
        userError("X86PageMapIO: Invalid PCI device.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    vtd_context_slot = lookup_vtd_context_slot(io_space);

    if (!vtd_cte_ptr_get_present(vtd_context_slot)) {
        /* 1st Level Page Table is not installed */
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        return EXCEPTION_SYSCALL_ERROR;
    }

    vtd_pte = (vtd_pte_t*)paddr_to_pptr(vtd_cte_ptr_get_asr(vtd_context_slot));
    lu_ret  = lookupIOPTSlot(vtd_pte, io_address);
    if (lu_ret.status != EXCEPTION_NONE || lu_ret.level != 0) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (vtd_pte_ptr_get_addr(lu_ret.ioptSlot) != 0) {
        current_syscall_error.type = seL4_DeleteFirst;
        return EXCEPTION_SYSCALL_ERROR;
    }

    dma_cap_rights_mask = rightsFromWord(getSyscallArg(0, buffer));
    frame_cap_rights    = cap_frame_cap_get_capFVMRights(cap);

    bool_t write = seL4_CapRights_get_capAllowWrite(dma_cap_rights_mask) && (frame_cap_rights == VMReadWrite);
    bool_t read = seL4_CapRights_get_capAllowRead(dma_cap_rights_mask) && (frame_cap_rights != VMKernelOnly);
    if (write || read) {
        iopte = vtd_pte_new(paddr, !!write, !!read);
    } else {
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    cap = cap_frame_cap_set_capFMapType(cap, X86_MappingIOSpace);
    cap = cap_frame_cap_set_capFMappedASID(cap, pci_request_id);
    cap = cap_frame_cap_set_capFMappedAddress(cap, io_address);

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return performX86IOInvocationMap(cap, slot, iopte, lu_ret.ioptSlot);
}

void deleteIOPageTable(cap_t io_pt_cap)
{
    lookupIOPTSlot_ret_t lu_ret;
    uint32_t             level;
    word_t               io_address;
    vtd_cte_t*           vtd_context_slot;
    vtd_pte_t*           vtd_pte;

    if (cap_io_page_table_cap_get_capIOPTIsMapped(io_pt_cap)) {
        io_pt_cap = cap_io_page_table_cap_set_capIOPTIsMapped(io_pt_cap, 0);
        level = cap_io_page_table_cap_get_capIOPTLevel(io_pt_cap);
        vtd_context_slot = lookup_vtd_context_slot(io_pt_cap);

        if (!vtd_cte_ptr_get_present(vtd_context_slot)) {
            return;
        }

        vtd_pte = (vtd_pte_t*)paddr_to_pptr(vtd_cte_ptr_get_asr(vtd_context_slot));

        if (level == 0) {
            /* if we have been overmapped or something */
            if (pptr_to_paddr(vtd_pte) != pptr_to_paddr((void *)cap_io_page_table_cap_get_capIOPTBasePtr(io_pt_cap))) {
                return;
            }
            *vtd_context_slot = vtd_cte_new(
                                    0,      /* Domain ID          */
                                    false,  /* RMRR               */
                                    0,      /* Address Width      */
                                    0,      /* Address Space Root */
                                    0,      /* Translation Type   */
                                    0       /* Present            */
                                );
            flushCacheRange(vtd_context_slot, VTD_CTE_SIZE_BITS);
        } else {
            io_address = cap_io_page_table_cap_get_capIOPTMappedAddress(io_pt_cap);
            lu_ret = lookupIOPTSlot_resolve_levels(vtd_pte, io_address >> PAGE_BITS, level - 1, level - 1 );

            /* if we have been overmapped or something */
            if (lu_ret.status != EXCEPTION_NONE || lu_ret.level != 0) {
                return;
            }
            if (vtd_pte_ptr_get_addr(lu_ret.ioptSlot) != pptr_to_paddr((void *)cap_io_page_table_cap_get_capIOPTBasePtr(io_pt_cap))) {
                return;
            }
            *lu_ret.ioptSlot = vtd_pte_new(
                                   0,  /* Physical Address */
                                   0,  /* Read Permission  */
                                   0   /* Write Permission */
                               );
            flushCacheRange(lu_ret.ioptSlot, VTD_PTE_SIZE_BITS);
        }
        invalidate_iotlb();
    }
}

void unmapIOPage(cap_t cap)
{
    lookupIOPTSlot_ret_t lu_ret;
    word_t               io_address;
    vtd_cte_t*           vtd_context_slot;
    vtd_pte_t*           vtd_pte;

    io_address  = cap_frame_cap_get_capFMappedAddress(cap);
    vtd_context_slot = lookup_vtd_context_slot(cap);


    if (!vtd_cte_ptr_get_present(vtd_context_slot)) {
        return;
    }

    vtd_pte = (vtd_pte_t*)paddr_to_pptr(vtd_cte_ptr_get_asr(vtd_context_slot));

    lu_ret  = lookupIOPTSlot(vtd_pte, io_address);
    if (lu_ret.status != EXCEPTION_NONE || lu_ret.level != 0) {
        return;
    }

    if (vtd_pte_ptr_get_addr(lu_ret.ioptSlot) != pptr_to_paddr((void *)cap_frame_cap_get_capFBasePtr(cap))) {
        return;
    }

    *lu_ret.ioptSlot = vtd_pte_new(
                           0,  /* Physical Address */
                           0,  /* Read Permission  */
                           0   /* Write Permission */
                       );

    flushCacheRange(lu_ret.ioptSlot, VTD_PTE_SIZE_BITS);
    invalidate_iotlb();
}

exception_t
performX86IOUnMapInvocation(cap_t cap, cte_t *ctSlot)
{
    unmapIOPage(ctSlot->cap);

    ctSlot->cap = cap_frame_cap_set_capFMappedAddress(ctSlot->cap, 0);
    ctSlot->cap = cap_frame_cap_set_capFMapType(ctSlot->cap, X86_MappingNone);
    ctSlot->cap = cap_frame_cap_set_capFMappedASID(ctSlot->cap, asidInvalid);

    return EXCEPTION_NONE;
}

exception_t decodeX86IOSpaceInvocation(word_t invLabel, cap_t cap)
{
    userError("IOSpace capability has no invocations");
    current_syscall_error.type = seL4_IllegalOperation;
    return EXCEPTION_SYSCALL_ERROR;
}

#endif /* CONFIG_IOMMU */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/object/objecttype.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <types.h>
#include <api/failures.h>
#include <kernel/vspace.h>
#include <object/structures.h>
#include <arch/machine.h>
#include <arch/model/statedata.h>
#include <machine/fpu.h>
#include <arch/object/objecttype.h>
#include <arch/object/ioport.h>
#include <plat/machine/devices.h>

#include <arch/object/iospace.h>
#include <arch/object/vcpu.h>
#include <plat/machine/intel-vtd.h>

deriveCap_ret_t Arch_deriveCap(cte_t* slot, cap_t cap)
{
    deriveCap_ret_t ret;

    switch (cap_get_capType(cap)) {
    case cap_page_table_cap:
        if (cap_page_table_cap_get_capPTIsMapped(cap)) {
            ret.cap = cap;
            ret.status = EXCEPTION_NONE;
        } else {
            userError("Deriving an unmapped PT cap");
            current_syscall_error.type = seL4_IllegalOperation;
            ret.cap = cap_null_cap_new();
            ret.status = EXCEPTION_SYSCALL_ERROR;
        }
        return ret;

    case cap_page_directory_cap:
        if (cap_page_directory_cap_get_capPDIsMapped(cap)) {
            ret.cap = cap;
            ret.status = EXCEPTION_NONE;
        } else {
            userError("Deriving a PD cap without an assigned ASID");
            current_syscall_error.type = seL4_IllegalOperation;
            ret.cap = cap_null_cap_new();
            ret.status = EXCEPTION_SYSCALL_ERROR;
        }
        return ret;

    case cap_asid_control_cap:
    case cap_asid_pool_cap:
        ret.cap = cap;
        ret.status = EXCEPTION_NONE;
        return ret;
    case cap_io_port_control_cap:
        ret.status = EXCEPTION_NONE;
        ret.cap = cap_null_cap_new();
        return ret;
    case cap_io_port_cap:
        ret.cap = cap;
        ret.status = EXCEPTION_NONE;
        return ret;

#ifdef CONFIG_IOMMU
    case cap_io_space_cap:
        ret.cap = cap;
        ret.status = EXCEPTION_NONE;
        return ret;
    case cap_io_page_table_cap:
        if (cap_io_page_table_cap_get_capIOPTIsMapped(cap)) {
            ret.cap = cap;
            ret.status = EXCEPTION_NONE;
        } else {
            current_syscall_error.type = seL4_IllegalOperation;
            ret.cap = cap_null_cap_new();
            ret.status = EXCEPTION_SYSCALL_ERROR;
        }
        return ret;
#endif

#ifdef CONFIG_VTX
    case cap_vcpu_cap:
        ret.cap = cap;
        ret.status = EXCEPTION_NONE;
        return ret;
    case cap_ept_pml4_cap:
        if (cap_ept_pml4_cap_get_capPML4IsMapped(cap)) {
            ret.cap = cap;
            ret.status = EXCEPTION_NONE;
        } else {
            userError("Deriving a EPT PML4 cap without an assigned ASID.");
            current_syscall_error.type = seL4_IllegalOperation;
            ret.cap = cap_null_cap_new();
            ret.status = EXCEPTION_SYSCALL_ERROR;
        }
        return ret;
    case cap_ept_pdpt_cap:
        if (cap_ept_pdpt_cap_get_capPDPTIsMapped(cap)) {
            ret.cap = cap;
            ret.status = EXCEPTION_NONE;
        } else {
            userError("Deriving an unmapped EPT PDPT cap.");
            current_syscall_error.type = seL4_IllegalOperation;
            ret.cap = cap_null_cap_new();
            ret.status = EXCEPTION_SYSCALL_ERROR;
        }
        return ret;

    case cap_ept_pd_cap:
        if (cap_ept_pd_cap_get_capPDIsMapped(cap)) {
            ret.cap = cap;
            ret.status = EXCEPTION_NONE;
        } else {
            userError("Deriving an unmapped EPT PD cap.");
            current_syscall_error.type = seL4_IllegalOperation;
            ret.cap = cap_null_cap_new();
            ret.status = EXCEPTION_SYSCALL_ERROR;
        }
        return ret;

    case cap_ept_pt_cap:
        if (cap_ept_pt_cap_get_capPTIsMapped(cap)) {
            ret.cap = cap;
            ret.status = EXCEPTION_NONE;
        } else {
            userError("Deriving an unmapped EPT PT cap.");
            current_syscall_error.type = seL4_IllegalOperation;
            ret.cap = cap_null_cap_new();
            ret.status = EXCEPTION_SYSCALL_ERROR;
        }
        return ret;
#endif

    default:
        return Mode_deriveCap(slot, cap);
    }
}

cap_t CONST Arch_updateCapData(bool_t preserve, word_t data, cap_t cap)
{
    /* Avoid a switch statement with just a 'default' case as the C parser does not like this */
#ifdef CONFIG_IOMMU
    switch (cap_get_capType(cap)) {
    case cap_io_space_cap: {
        io_space_capdata_t w = { { data } };
        uint16_t PCIDevice = io_space_capdata_get_PCIDevice(w);
        uint16_t domainID = io_space_capdata_get_domainID(w);
        if (!preserve && cap_io_space_cap_get_capPCIDevice(cap) == 0 &&
                domainID >= x86KSFirstValidIODomain &&
                domainID != 0                        &&
                domainID <= MASK(x86KSnumIODomainIDBits)) {
            return cap_io_space_cap_new(domainID, PCIDevice);
        } else {
            return cap_null_cap_new();
        }
    }

    default:
        return cap;
    }
#endif
    return cap;
}

cap_t CONST Arch_maskCapRights(seL4_CapRights_t cap_rights_mask, cap_t cap)
{
    if (cap_get_capType(cap) == cap_frame_cap) {
        vm_rights_t vm_rights;

        vm_rights = vmRightsFromWord(cap_frame_cap_get_capFVMRights(cap));
        vm_rights = maskVMRights(vm_rights, cap_rights_mask);
        return cap_frame_cap_set_capFVMRights(cap, wordFromVMRights(vm_rights));
    } else {
        return cap;
    }
}

finaliseCap_ret_t Arch_finaliseCap(cap_t cap, bool_t final)
{
    finaliseCap_ret_t fc_ret;

    switch (cap_get_capType(cap)) {
    case cap_page_directory_cap:
        if (final && cap_page_directory_cap_get_capPDIsMapped(cap)) {
            unmapPageDirectory(
                cap_page_directory_cap_get_capPDMappedASID(cap),
                cap_page_directory_cap_get_capPDMappedAddress(cap),
                PDE_PTR(cap_page_directory_cap_get_capPDBasePtr(cap))
            );
        }
        break;

    case cap_page_table_cap:
        if (final && cap_page_table_cap_get_capPTIsMapped(cap)) {
            unmapPageTable(
                cap_page_table_cap_get_capPTMappedASID(cap),
                cap_page_table_cap_get_capPTMappedAddress(cap),
                PT_PTR(cap_page_table_cap_get_capPTBasePtr(cap))
            );
        }
        break;

    case cap_asid_pool_cap:
        if (final) {
            deleteASIDPool(
                cap_asid_pool_cap_get_capASIDBase(cap),
                ASID_POOL_PTR(cap_asid_pool_cap_get_capASIDPool(cap))
            );
        }
        break;
    case cap_asid_control_cap:
    case cap_io_port_control_cap:
        break;
    case cap_io_port_cap:
#ifdef CONFIG_VTX
        clearVPIDIOPortMappings(cap_io_port_cap_get_capIOPortVPID(cap),
                                cap_io_port_cap_get_capIOPortFirstPort(cap),
                                cap_io_port_cap_get_capIOPortLastPort(cap));
#endif
        if (final) {
            fc_ret.remainder = cap_null_cap_new();
            fc_ret.cleanupInfo = cap;
            return fc_ret;
        }
        break;
#ifdef CONFIG_IOMMU
    case cap_io_space_cap:
        if (final) {
            unmapVTDContextEntry(cap);
        }
        break;

    case cap_io_page_table_cap:
        if (final && cap_io_page_table_cap_get_capIOPTIsMapped(cap)) {
            deleteIOPageTable(cap);
        }
        break;
#endif

#ifdef CONFIG_VTX
    case cap_vcpu_cap:
        if (final) {
            vcpu_finalise(VCPU_PTR(cap_vcpu_cap_get_capVCPUPtr(cap)));
        }
        break;
    case cap_ept_pml4_cap:
        if (final && cap_ept_pml4_cap_get_capPML4IsMapped(cap)) {
            deleteEPTASID(cap_ept_pml4_cap_get_capPML4MappedASID(cap),
                          (ept_pml4e_t*)cap_ept_pml4_cap_get_capPML4BasePtr(cap));
        }
        break;

    case cap_ept_pdpt_cap:
        if (final && cap_ept_pdpt_cap_get_capPDPTIsMapped(cap)) {
            unmapEPTPDPT(
                cap_ept_pdpt_cap_get_capPDPTMappedASID(cap),
                cap_ept_pdpt_cap_get_capPDPTMappedAddress(cap),
                (ept_pdpte_t*)cap_ept_pdpt_cap_get_capPDPTBasePtr(cap));
        }
        break;

    case cap_ept_pd_cap:
        if (final && cap_ept_pd_cap_get_capPDIsMapped(cap)) {
            unmapEPTPageDirectory(
                cap_ept_pd_cap_get_capPDMappedASID(cap),
                cap_ept_pd_cap_get_capPDMappedAddress(cap),
                (ept_pde_t*)cap_ept_pd_cap_get_capPDBasePtr(cap));
        }
        break;

    case cap_ept_pt_cap:
        if (final && cap_ept_pt_cap_get_capPTIsMapped(cap)) {
            unmapEPTPageTable(
                cap_ept_pt_cap_get_capPTMappedASID(cap),
                cap_ept_pt_cap_get_capPTMappedAddress(cap),
                (ept_pte_t*)cap_ept_pt_cap_get_capPTBasePtr(cap));
        }
        break;
#endif

    default:
        return Mode_finaliseCap(cap, final);
    }

    fc_ret.remainder = cap_null_cap_new();
    fc_ret.cleanupInfo = cap_null_cap_new();
    return fc_ret;
}

bool_t CONST Arch_sameRegionAs(cap_t cap_a, cap_t cap_b)
{
    switch (cap_get_capType(cap_a)) {
    case cap_frame_cap:
        if (cap_get_capType(cap_b) == cap_frame_cap) {
            word_t botA, botB, topA, topB;
            botA = cap_frame_cap_get_capFBasePtr(cap_a);
            botB = cap_frame_cap_get_capFBasePtr(cap_b);
            topA = botA + MASK (pageBitsForSize(cap_frame_cap_get_capFSize(cap_a)));
            topB = botB + MASK (pageBitsForSize(cap_frame_cap_get_capFSize(cap_b)));
            return ((botA <= botB) && (topA >= topB) && (botB <= topB));
        }
        break;

    case cap_page_table_cap:
        if (cap_get_capType(cap_b) == cap_page_table_cap) {
            return cap_page_table_cap_get_capPTBasePtr(cap_a) ==
                   cap_page_table_cap_get_capPTBasePtr(cap_b);
        }
        break;

    case cap_page_directory_cap:
        if (cap_get_capType(cap_b) == cap_page_directory_cap) {
            return cap_page_directory_cap_get_capPDBasePtr(cap_a) ==
                   cap_page_directory_cap_get_capPDBasePtr(cap_b);
        }
        break;

    case cap_asid_control_cap:
        if (cap_get_capType(cap_b) == cap_asid_control_cap) {
            return true;
        }
        break;

    case cap_asid_pool_cap:
        if (cap_get_capType(cap_b) == cap_asid_pool_cap) {
            return cap_asid_pool_cap_get_capASIDPool(cap_a) ==
                   cap_asid_pool_cap_get_capASIDPool(cap_b);
        }
        break;

    case cap_io_port_control_cap:
        if (cap_get_capType(cap_b) == cap_io_port_control_cap ||
                cap_get_capType(cap_b) == cap_io_port_cap) {
            return true;
        }
        break;

    case cap_io_port_cap:
        if (cap_get_capType(cap_b) == cap_io_port_cap) {
            return  cap_io_port_cap_get_capIOPortFirstPort(cap_a) ==
                    cap_io_port_cap_get_capIOPortFirstPort(cap_b) &&
                    cap_io_port_cap_get_capIOPortLastPort(cap_a) ==
                    cap_io_port_cap_get_capIOPortLastPort(cap_b);
        }
        break;

#ifdef CONFIG_IOMMU
    case cap_io_space_cap:
        if (cap_get_capType(cap_b) == cap_io_space_cap) {
            return cap_io_space_cap_get_capPCIDevice(cap_a) ==
                   cap_io_space_cap_get_capPCIDevice(cap_b);
        }
        break;

    case cap_io_page_table_cap:
        if (cap_get_capType(cap_b) == cap_io_page_table_cap) {
            return cap_io_page_table_cap_get_capIOPTBasePtr(cap_a) ==
                   cap_io_page_table_cap_get_capIOPTBasePtr(cap_b);
        }
        break;
#endif

#ifdef CONFIG_VTX
    case cap_vcpu_cap:
        if (cap_get_capType(cap_b) == cap_vcpu_cap) {
            return cap_vcpu_cap_get_capVCPUPtr(cap_a) ==
                   cap_vcpu_cap_get_capVCPUPtr(cap_b);
        }
        break;

    case cap_ept_pml4_cap:
        if (cap_get_capType(cap_b) == cap_ept_pml4_cap) {
            return cap_ept_pml4_cap_get_capPML4BasePtr(cap_a) ==
                   cap_ept_pml4_cap_get_capPML4BasePtr(cap_b);
        }
        break;

    case cap_ept_pdpt_cap:
        if (cap_get_capType(cap_b) == cap_ept_pdpt_cap) {
            return cap_ept_pdpt_cap_get_capPDPTBasePtr(cap_a) ==
                   cap_ept_pdpt_cap_get_capPDPTBasePtr(cap_b);
        }
        break;

    case cap_ept_pd_cap:
        if (cap_get_capType(cap_b) == cap_ept_pd_cap) {
            return cap_ept_pd_cap_get_capPDBasePtr(cap_a) ==
                   cap_ept_pd_cap_get_capPDBasePtr(cap_b);
        }
        break;

    case cap_ept_pt_cap:
        if (cap_get_capType(cap_b) == cap_ept_pt_cap) {
            return cap_ept_pt_cap_get_capPTBasePtr(cap_a) ==
                   cap_ept_pt_cap_get_capPTBasePtr(cap_b);
        }
        break;

#endif

    }

    return Mode_sameRegionAs(cap_a, cap_b);
}

bool_t CONST Arch_sameObjectAs(cap_t cap_a, cap_t cap_b)
{
    if (cap_get_capType(cap_a) == cap_io_port_control_cap &&
            cap_get_capType(cap_b) == cap_io_port_cap) {
        return false;
    }
    if (cap_get_capType(cap_a) == cap_frame_cap) {
        if (cap_get_capType(cap_b) == cap_frame_cap) {
            return ((cap_frame_cap_get_capFBasePtr(cap_a) ==
                     cap_frame_cap_get_capFBasePtr(cap_b)) &&
                    (cap_frame_cap_get_capFSize(cap_a) ==
                     cap_frame_cap_get_capFSize(cap_b)) &&
                    ((cap_frame_cap_get_capFIsDevice(cap_a) == 0) ==
                     (cap_frame_cap_get_capFIsDevice(cap_b) == 0)));
        }
    }
    return Arch_sameRegionAs(cap_a, cap_b);
}

word_t
Arch_getObjectSize(word_t t)
{
    switch (t) {
    case seL4_X86_4K:
        return pageBitsForSize(X86_SmallPage);
    case seL4_X86_LargePageObject:
        return pageBitsForSize(X86_LargePage);
    case seL4_X86_PageTableObject:
        return seL4_PageTableBits;
    case seL4_X86_PageDirectoryObject:
        return seL4_PageDirBits;
    case seL4_IA32_PDPTObject:
        return seL4_PDPTBits;
    case seL4_X86_IOPageTableObject:
        return seL4_IOPageTableBits;
#ifdef CONFIG_VTX
    case seL4_X86_VCPUObject:
        return seL4_X86_VCPUBits;
    case seL4_X86_EPTPML4Object:
        return seL4_X86_EPTPML4Bits;
    case seL4_X86_EPTPDPTObject:
        return seL4_X86_EPTPDPTBits;
    case seL4_X86_EPTPDObject:
        return seL4_X86_EPTPDBits;
    case seL4_X86_EPTPTObject:
        return seL4_X86_EPTPTBits;
#endif
    default:
        return Mode_getObjectSize(t);
    }
}

cap_t
Arch_createObject(object_t t, void *regionBase, word_t userSize, bool_t deviceMemory)
{
#ifdef CONFIG_VTX
    switch (t) {
    case seL4_X86_VCPUObject: {
        vcpu_t *vcpu;
        vcpu = VCPU_PTR((word_t)regionBase);
        vcpu_init(vcpu);
        return cap_vcpu_cap_new(VCPU_REF(vcpu));
    }
    case seL4_X86_EPTPML4Object:
        return cap_ept_pml4_cap_new(
                   0,                  /* capPML4IsMapped      */
                   VPID_INVALID,       /* capPML4MappedASID    */
                   (word_t)regionBase  /* capPML4BasePtr       */
               );
    case seL4_X86_EPTPDPTObject:
        return cap_ept_pdpt_cap_new(
                   0,                  /* capPDPTMappedAddress */
                   0,                  /* capPDPTIsMapped      */
                   VPID_INVALID,       /* capPDPTMappedASID    */
                   (word_t)regionBase   /* capPDPTBasePtr      */
               );
    case seL4_X86_EPTPDObject:
        return cap_ept_pd_cap_new(
                   0,                  /* capPDMappedAddress   */
                   0,                  /* capPDIsMapped        */
                   VPID_INVALID,       /* capPDMappedASID      */
                   (word_t)regionBase  /* capPDBasePtr         */
               );
    case seL4_X86_EPTPTObject:
        return cap_ept_pt_cap_new(
                   0,                  /* capPTMappedAddress   */
                   0,                  /* capPTIsMapped        */
                   VPID_INVALID,       /* capPTMappedASID      */
                   (word_t)regionBase  /* capPTBasePtr         */
               );
    default:
#endif
        return Mode_createObject(t, regionBase, userSize, deviceMemory);
#ifdef CONFIG_VTX
    }
#endif
}

exception_t
Arch_decodeInvocation(
    word_t invLabel,
    word_t length,
    cptr_t cptr,
    cte_t* slot,
    cap_t cap,
    extra_caps_t excaps,
    bool_t call,
    word_t* buffer
)
{
    switch (cap_get_capType(cap)) {
    case cap_asid_control_cap:
    case cap_asid_pool_cap:
        return decodeX86MMUInvocation(invLabel, length, cptr, slot, cap, excaps, buffer);
    case cap_io_port_control_cap:
        return decodeX86PortControlInvocation(invLabel, length, cptr, slot, cap, excaps, buffer);
    case cap_io_port_cap:
        return decodeX86PortInvocation(invLabel, length, cptr, slot, cap, excaps, call, buffer);
#ifdef CONFIG_IOMMU
    case cap_io_space_cap:
        return decodeX86IOSpaceInvocation(invLabel, cap);
    case cap_io_page_table_cap:
        return decodeX86IOPTInvocation(invLabel, length, slot, cap, excaps, buffer);
#endif
#ifdef CONFIG_VTX
    case cap_vcpu_cap:
        return decodeX86VCPUInvocation(invLabel, length, cptr, slot, cap, excaps, buffer);
    case cap_ept_pml4_cap:
    case cap_ept_pdpt_cap:
    case cap_ept_pd_cap:
    case cap_ept_pt_cap:
        return decodeX86EPTInvocation(invLabel, length, cptr, slot, cap, excaps, buffer);
#endif
    default:
        return Mode_decodeInvocation(invLabel, length, cptr, slot, cap, excaps, buffer);
    }
}

void
Arch_prepareThreadDelete(tcb_t *thread)
{
    /* Notify the lazy FPU module about this thread's deletion. */
    fpuThreadDelete(thread);
}

void Arch_postCapDeletion(cap_t cap)
{
    if (cap_get_capType(cap) == cap_io_port_cap) {
        uint16_t first_port = cap_io_port_cap_get_capIOPortFirstPort(cap);
        uint16_t last_port = cap_io_port_cap_get_capIOPortLastPort(cap);

        freeIOPortRange(first_port, last_port);
    }
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/object/tcb.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <types.h>
#include <api/failures.h>
#include <machine/registerset.h>
#include <object/structures.h>
#include <arch/object/tcb.h>
#include <arch/machine.h>

word_t CONST Arch_decodeTransfer(word_t flags)
{
    return 0;
}

exception_t CONST Arch_performTransfer(word_t arch, tcb_t *tcb_src, tcb_t *tcb_dest)
{
    return EXCEPTION_NONE;
}

#ifdef CONFIG_VTX
void Arch_leaveVMAsyncTransfer(tcb_t *tcb)
{
    vcpu_sysvmenter_reply_to_user(tcb);
}

static exception_t performSetEPTRoot(tcb_t *tcb, cap_t cap, cte_t *slot)
{
    cte_t *rootSlot;
    exception_t e;

    rootSlot = TCB_PTR_CTE_PTR(tcb, tcbArchEPTRoot);
    e = cteDelete(rootSlot, true);
    if (e != EXCEPTION_NONE) {
        return e;
    }

    cteInsert(cap, slot, rootSlot);

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return EXCEPTION_NONE;
}

exception_t decodeSetEPTRoot(cap_t cap, extra_caps_t excaps)
{
    cap_t rootCap;
    cte_t *rootSlot;
    deriveCap_ret_t dc_ret;

    rootSlot = excaps.excaprefs[0];

    if (rootSlot == NULL) {
        userError("TCB SetEPTRoot: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    rootCap = rootSlot->cap;

    if (cap_get_capType(rootCap) != cap_ept_pml4_cap) {
        userError("TCB SetEPTRoot: EPT PDPT is invalid.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    dc_ret = deriveCap(rootSlot, rootCap);
    if (dc_ret.status != EXCEPTION_NONE) {
        return dc_ret.status;
    }

    if (!cap_ept_pml4_cap_get_capPML4IsMapped(dc_ret.cap)) {
        userError("decodeSetEPTRoot: Invalid EPT cap.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    return performSetEPTRoot(TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)), dc_ret.cap, rootSlot);
}
#endif

#ifdef ENABLE_SMP_SUPPORT
void
Arch_migrateTCB(tcb_t *thread)
{
    /* check if thread own its current core FPU */
    if (nativeThreadUsingFPU(thread)) {
        switchFpuOwner(NULL, thread->tcbAffinity);
    }
}
#endif /* ENABLE_SMP_SUPPORT */

void
Arch_setTCBIPCBuffer(tcb_t *thread, word_t bufferAddr)
{
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/object/vcpu.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>

#ifdef CONFIG_VTX

#include <types.h>
#include <machine/io.h>
#include <api/failures.h>
#include <api/syscall.h>
#include <kernel/thread.h>
#include <object/objecttype.h>
#include <arch/machine/cpu_registers.h>
#include <arch/model/statedata.h>
#include <arch/object/vcpu.h>
#include <arch/object/ioport.h>
#include <util.h>
#include <arch/api/vmenter.h>

#define VMX_EXIT_QUAL_TYPE_MOV_CR 0
#define VMX_EXIT_QUAL_TYPE_CLTS 2
#define VMX_EXIT_QUAL_TYPE_LMSW 3

#define VMXON_REGION_SIZE 4096

const vcpu_gp_register_t crExitRegs[] = {
    VCPU_EAX, VCPU_ECX, VCPU_EDX, VCPU_EBX, VCPU_ESP, VCPU_EBP, VCPU_ESI, VCPU_EDI
};

typedef struct msr_bitmap {
    word_t bitmap[0x2000 / sizeof(word_t) / 8];
} msr_bitmap_t;

typedef struct msr_bitmaps {
    msr_bitmap_t low_msr_read;
    msr_bitmap_t high_msr_read;
    msr_bitmap_t low_msr_write;
    msr_bitmap_t high_msr_write;
} msr_bitmaps_t;

static struct PACKED {
    uint32_t revision;
    char data[VMXON_REGION_SIZE - sizeof(uint32_t)];
} vmxon_region ALIGN(VMXON_REGION_SIZE);

static msr_bitmaps_t msr_bitmap_region ALIGN(BIT(seL4_PageBits));

static char null_ept_space[seL4_PageBits] ALIGN(BIT(seL4_PageBits));

/* Cached value of the hardware defined vmcs revision */
static uint32_t vmcs_revision;

/* Cached value of the VPID capability MSR */
static vmx_ept_vpid_cap_msr_t vpid_capability;

/* Cache the values that we calculated for bits that need to be set high
 * and low in various vmcs fields */
static uint32_t pin_control_high;
static uint32_t pin_control_low;
static uint32_t primary_control_high;
static uint32_t primary_control_low;
static uint32_t secondary_control_high;
static uint32_t secondary_control_low;
static uint32_t entry_control_high;
static uint32_t entry_control_low;
static uint32_t exit_control_high;
static uint32_t exit_control_low;
static uint32_t cr0_high;
static uint32_t cr0_low;
static uint32_t cr4_high;
static uint32_t cr4_low;

/* these flags indicate the presence of specific VT-x features. These features
 * are checked for at boot time and are constant from then on */
static bool_t vmx_feature_vpid;
static bool_t vmx_feature_load_perf_global_ctrl;
static bool_t vmx_feature_ack_on_exit;

static vcpu_t *x86KSVPIDTable[VPID_LAST + 1];
static vpid_t x86KSNextVPID = VPID_FIRST;

static inline bool_t
vmxon(paddr_t vmxon_region)
{
    uint8_t error;
    /* vmxon requires a 64bit memory address, so perform a
     * cast here to guarantee this on 32-bit platforms */
    uint64_t vmxonreg = vmxon_region;
    asm volatile(
        "vmxon %1; setnae %0"
        : "=q"(error)
        : "m"(vmxonreg)
        : "memory", "cc"
    );
    return !!error;
}

static void
vmclear(void *vmcs_ptr)
{
    uint64_t physical_address;
    physical_address = pptr_to_paddr((void*)vmcs_ptr);
    asm volatile (
        "vmclear %0"
        :
        : "m"(physical_address)
        : "cc"
    );
}

void
clearCurrentVCPU(void)
{
    vcpu_t *vcpu = ARCH_NODE_STATE(x86KSCurrentVCPU);
    if (vcpu) {
        vmclear(vcpu);
        vcpu->launched = false;
        ARCH_NODE_STATE(x86KSCurrentVCPU) = NULL;
    }
}

static void
vmptrld(void *vmcs_ptr)
{
    uint64_t physical_address;
    uint8_t error;
    physical_address = pptr_to_paddr(vmcs_ptr);
    asm volatile (
        "vmptrld %1; setna %0"
        : "=q"(error)
        : "m"(physical_address)
        : "cc"
    );
    /* The usage of vmptrld should be correct by construction. As there is no
     * capacity to propogate errors where vmptrld is used we will do our best
     * to detect bugs in debug builds by asserting */
    assert(!error);
}

static void
switchVCPU(vcpu_t *vcpu)
{
#ifdef ENABLE_SMP_SUPPORT
    if (vcpu->last_cpu != getCurrentCPUIndex() && ARCH_NODE_STATE_ON_CORE(x86KSCurrentVCPU, vcpu->last_cpu) == vcpu) {
        /* vcpu is currently loaded on another core, need to do vmclear on that core */
        doRemoteClearCurrentVCPU(vcpu->last_cpu);
    }
#endif
    clearCurrentVCPU();
    vmptrld(vcpu);
#ifdef ENABLE_SMP_SUPPORT
    if (vcpu->last_cpu != getCurrentCPUIndex()) {
        /* migrate host state */
        vmwrite(VMX_HOST_TR_BASE, (word_t)&x86KSGlobalState[CURRENT_CPU_INDEX()].x86KStss);
        vmwrite(VMX_HOST_GDTR_BASE, (word_t)x86KSGlobalState[CURRENT_CPU_INDEX()].x86KSgdt);
        vmwrite(VMX_HOST_IDTR_BASE, (word_t)x86KSGlobalState[CURRENT_CPU_INDEX()].x86KSidt);
        vmwrite(VMX_HOST_SYSENTER_ESP, (uint64_t)(word_t)((char *)&x86KSGlobalState[CURRENT_CPU_INDEX()].x86KStss.tss.words[0] + 4));
    }
    vcpu->last_cpu = getCurrentCPUIndex();
#endif
    ARCH_NODE_STATE(x86KSCurrentVCPU) = vcpu;
}

static void
print_bits(word_t bits)
{
    bool_t first = true;
    while (bits) {
        int index = seL4_WordBits - 1 - clzl(bits);
        if (first) {
            printf("%d", index);
            first = false;
        } else {
            printf(",%d", index);
        }
        bits &= ~BIT(index);
    }
}

static bool_t
check_fixed_value(word_t val, word_t low, word_t high)
{
    word_t not_high;
    word_t not_low;
    /* check if any bits that should be high, are not
     * high & val represents the set of bits that are
     * correctly set to high. if this is equal to high
     * then everything is good, to detect exactly which
     * bits were not high we can invert and mask with
     * high again. Now if this is 0 everythins is fine,
     * and if not each bit set indicates a bit we had
     * failed to set */
    not_high = high & ~(high & val);
    if (not_high != 0) {
        printf("Failed to set bits: ");
        print_bits(not_high);
        return false;
    }
    /* we can do the same thing for finding things
     * that should be low by first inverting */
    not_low = ~low & ~(~low & ~val);
    if (not_low != 0) {
        printf("Incorrectly cleared bits: ");
        print_bits(not_low);
        return false;
    }
    return true;
}

static bool_t
vtx_check_fixed_values(word_t cr0, word_t cr4)
{
    if (!check_fixed_value(cr0, cr0_low, cr0_high)) {
        printf(" of CR0\n");
        return false;
    }
    if (!check_fixed_value(cr4, cr4_low, cr4_high)) {
        printf(" of CR4\n");
        return false;
    }
    return true;
}

static bool_t BOOT_CODE
init_vtx_fixed_values(bool_t useTrueMsrs)
{
    uint32_t pin_control_mask =
        BIT(0) |    //Extern interrupt exiting
        BIT(3) |    //NMI exiting
        BIT(5);     //virtual NMIs
    uint32_t primary_control_mask =
        BIT(25) |   //Use I/O bitmaps
        BIT(28) |   //Use MSR bitmaps
        BIT(31);    //Activate secondary controls
    uint32_t secondary_control_mask =
        BIT(1);     //Enable EPT
    uint32_t exit_control_mask =
        BIT(2)  |   //Save debug controls
        BIT(18) |   //Save guest IA32_PAT on exit
        BIT(19) |   //Load host IA32_PAT
        BIT(20) |   //Save guest IA32_EFER on exit
        BIT(21);    //Load host IA32_EFER
#ifdef CONFIG_ARCH_X86_64
    exit_control_mask |= BIT(9); //Host address-space size
#endif
    /* Read out the fixed high and low bits from the MSRs */
    uint32_t pinbased_ctls;
    uint32_t procbased_ctls;
    uint32_t exit_ctls;
    uint32_t entry_ctls;
    if (useTrueMsrs) {
        pinbased_ctls = IA32_VMX_TRUE_PINBASED_CTLS_MSR;
        procbased_ctls = IA32_VMX_TRUE_PROCBASED_CTLS_MSR;
        exit_ctls = IA32_VMX_TRUE_EXIT_CTLS_MSR;
        entry_ctls = IA32_VMX_TRUE_ENTRY_CTLS_MSR;
    } else {
        pinbased_ctls = IA32_VMX_PINBASED_CTLS_MSR;
        procbased_ctls = IA32_VMX_PROCBASED_CTLS_MSR;
        exit_ctls = IA32_VMX_EXIT_CTLS_MSR;
        entry_ctls = IA32_VMX_ENTRY_CTLS_MSR;
    }
    pin_control_high = x86_rdmsr_low(pinbased_ctls);
    pin_control_low = x86_rdmsr_high(pinbased_ctls);
    primary_control_high = x86_rdmsr_low(procbased_ctls);
    primary_control_low = x86_rdmsr_high(procbased_ctls);
    secondary_control_high = x86_rdmsr_low(IA32_VMX_PROCBASED_CTLS2_MSR);
    secondary_control_low = x86_rdmsr_high(IA32_VMX_PROCBASED_CTLS2_MSR);
    exit_control_high = x86_rdmsr_low(exit_ctls);
    exit_control_low = x86_rdmsr_high(exit_ctls);
    entry_control_high = x86_rdmsr_low(entry_ctls);
    entry_control_low = x86_rdmsr_high(entry_ctls);

    cr0_high = x86_rdmsr_low(IA32_VMX_CR0_FIXED0_MSR);
    cr0_low = x86_rdmsr_low(IA32_VMX_CR0_FIXED1_MSR);
    cr4_high = x86_rdmsr_low(IA32_VMX_CR4_FIXED0_MSR);
    cr4_low = x86_rdmsr_low(IA32_VMX_CR4_FIXED1_MSR);

    /* Check for VPID support */
    if (!(secondary_control_low & BIT(5))) {
        vmx_feature_vpid = 0;
        printf("vt-x: VPIDs are not supported. Expect performance degredation\n");
    } else {
        vmx_feature_vpid = 1;
        secondary_control_mask |= BIT(5);
    }

    /* Check for load perf global control */
    if (!(exit_control_low & BIT(12))) {
        vmx_feature_load_perf_global_ctrl = 0;
        printf("vt-x: Load IA32_PERF_GLOBAL_CONTROL not supported. Hardware debugging may not work\n");
    } else {
        vmx_feature_load_perf_global_ctrl = 1;
        exit_control_mask |= BIT(12);
    }

    /* Check for external interrupt exiting */
    if (!(exit_control_low & BIT(15))) {
        vmx_feature_ack_on_exit = 0;
        printf("vt-x: Interrupt ack on exit not supported. Expect performance degredation\n");
    } else {
        vmx_feature_ack_on_exit = 1;
        exit_control_mask |= BIT(15);
    }

    /* See if the hardware requires bits that require to be high to be low */
    uint32_t missing;
    missing = (~pin_control_low) & pin_control_mask;
    if (missing) {
        printf("vt-x: Unsupported pin control features %lx\n", (long)missing);
        return false;
    }
    missing = (~primary_control_low) & primary_control_mask;
    if (missing) {
        printf("vt-x: Unsupported primary control features %lx\n", (long)missing);
        return false;
    }
    missing = (~secondary_control_low) & secondary_control_mask;
    if (missing) {
        printf("vt-x: Unsupported secondary control features %lx\n", (long)missing);
        return false;
    }
    missing = (~exit_control_low) & exit_control_mask;
    if (missing) {
        printf("vt-x: Unsupported exit control features %lx\n", (long)missing);
        return false;
    }

    /* Force the bits we require to be high */
    pin_control_high |= pin_control_mask;
    primary_control_high |= primary_control_mask;
    secondary_control_high |= secondary_control_mask;
    exit_control_high |= exit_control_mask;

    return true;
}

static bool_t BOOT_CODE
check_vtx_fixed_values(bool_t useTrueMsrs)
{
    uint32_t pinbased_ctls;
    uint32_t procbased_ctls;
    uint32_t exit_ctls;
    uint32_t entry_ctls;
    if (useTrueMsrs) {
        pinbased_ctls = IA32_VMX_TRUE_PINBASED_CTLS_MSR;
        procbased_ctls = IA32_VMX_TRUE_PROCBASED_CTLS_MSR;
        exit_ctls = IA32_VMX_TRUE_EXIT_CTLS_MSR;
        entry_ctls = IA32_VMX_TRUE_ENTRY_CTLS_MSR;
    } else {
        pinbased_ctls = IA32_VMX_PINBASED_CTLS_MSR;
        procbased_ctls = IA32_VMX_PROCBASED_CTLS_MSR;
        exit_ctls = IA32_VMX_EXIT_CTLS_MSR;
        entry_ctls = IA32_VMX_ENTRY_CTLS_MSR;
    }
    uint32_t local_pin_control_high = x86_rdmsr_low(pinbased_ctls);
    uint32_t local_pin_control_low = x86_rdmsr_high(pinbased_ctls);
    uint32_t local_primary_control_high = x86_rdmsr_low(procbased_ctls);
    uint32_t local_primary_control_low = x86_rdmsr_high(procbased_ctls);
    uint32_t local_secondary_control_high = x86_rdmsr_low(IA32_VMX_PROCBASED_CTLS2_MSR);
    uint32_t local_secondary_control_low = x86_rdmsr_high(IA32_VMX_PROCBASED_CTLS2_MSR);
    uint32_t local_exit_control_high = x86_rdmsr_low(exit_ctls);
    uint32_t local_exit_control_low = x86_rdmsr_high(exit_ctls);
    uint32_t local_entry_control_high = x86_rdmsr_low(entry_ctls);
    uint32_t local_entry_control_low = x86_rdmsr_high(entry_ctls);

    uint32_t local_cr0_high = x86_rdmsr_low(IA32_VMX_CR0_FIXED0_MSR);
    uint32_t local_cr0_low = x86_rdmsr_low(IA32_VMX_CR0_FIXED1_MSR);
    uint32_t local_cr4_high = x86_rdmsr_low(IA32_VMX_CR4_FIXED0_MSR);
    uint32_t local_cr4_low = x86_rdmsr_low(IA32_VMX_CR4_FIXED1_MSR);

    /* We want to check that any bits that there are no bits that this core
     * requires to be high, that the BSP did not require to be high. This can
     * be checked with 'local_high & high == local_high'.
     * Also need to make sure that the BSP has not determined that any bits should
     * be high that this core requires to be low. This can be checked with
     * '~local_low & high == 0'
     */
    return
        (local_pin_control_high & pin_control_high) == local_pin_control_high &&
        (~local_pin_control_low & pin_control_high) == 0 &&
        (local_primary_control_high & primary_control_high) == local_primary_control_high &&
        (~local_primary_control_low & primary_control_high) == 0 &&
        (local_secondary_control_high & secondary_control_high) == local_secondary_control_high &&
        (~local_secondary_control_low & secondary_control_high) == 0 &&
        (local_exit_control_high & exit_control_high) == local_exit_control_high &&
        (~local_exit_control_low & exit_control_high) == 0 &&
        (local_entry_control_high & entry_control_high) == local_entry_control_high &&
        (~local_entry_control_low & entry_control_high) == 0 &&
        local_cr0_high == cr0_high &&
        local_cr0_low == cr0_low &&
        local_cr4_high == cr4_high &&
        local_cr4_low == cr4_low;
}

static inline uint32_t
applyFixedBits(uint32_t original, uint32_t high, uint32_t low)
{
    original |= high;
    original &= low;
    return original;
}

void
vcpu_init(vcpu_t *vcpu)
{
    vcpu->vcpuTCB = NULL;
    vcpu->launched = false;

    memcpy(vcpu->vmcs, &vmcs_revision, 4);

    switchVCPU(vcpu);

    vcpu->cr0 = cr0_high & cr0_low;
    vcpu->cr0_shadow = 0;
    vcpu->cr0_mask = 0;
    vcpu->exception_bitmap = 0;
    vcpu->vpid = VPID_INVALID;
#ifdef ENABLE_SMP_SUPPORT
    vcpu->last_cpu = getCurrentCPUIndex();
#endif /* ENABLE_SMP_SUPPORT */

    vmwrite(VMX_HOST_PAT, x86_rdmsr(IA32_PAT_MSR));
    vmwrite(VMX_HOST_EFER, x86_rdmsr(IA32_EFER_MSR));
    // By default we will disable performance counters when we come out
    // of a VM. When performance counters are supported this host state
    // needs to be updated on VM entry
    if (vmx_feature_load_perf_global_ctrl) {
        vmwrite(VMX_HOST_PERF_GLOBAL_CTRL, 0);
    }
    vmwrite(VMX_HOST_CR0, read_cr0());
    vmwrite(VMX_HOST_CR4, read_cr4());
    vmwrite(VMX_HOST_FS_BASE, 0);
    vmwrite(VMX_HOST_GS_BASE, 0);
    vmwrite(VMX_HOST_TR_BASE, (word_t)&x86KSGlobalState[CURRENT_CPU_INDEX()].x86KStss);
    vmwrite(VMX_HOST_GDTR_BASE, (word_t)x86KSGlobalState[CURRENT_CPU_INDEX()].x86KSgdt);
    vmwrite(VMX_HOST_IDTR_BASE, (word_t)x86KSGlobalState[CURRENT_CPU_INDEX()].x86KSidt);
    vmwrite(VMX_HOST_SYSENTER_CS, (word_t)SEL_CS_0);
    vmwrite(VMX_HOST_SYSENTER_EIP, (word_t)&handle_syscall);
    if (!config_set(CONFIG_HARDWARE_DEBUG_API)) {
        vmwrite(VMX_HOST_SYSENTER_ESP, (uint64_t)(word_t)((char *)&x86KSGlobalState[CURRENT_CPU_INDEX()].x86KStss.tss.words[0] + 4));
    }
    /* Set host SP to point just beyond the first field to be stored on exit. */
    vmwrite(VMX_HOST_RSP, (word_t)&vcpu->gp_registers[n_vcpu_gp_register]);
    vmwrite(VMX_HOST_RIP, (word_t)&handle_vmexit);
#ifdef CONFIG_KERNEL_SKIM_WINDOW
    /* if we have a skim window then our host cr3 is a constant and is always the
     * the kernel address space, so we set it here instead of lazily in restoreVMCS */
    vmwrite(VMX_HOST_CR3, makeCR3(kpptr_to_paddr(x64KSKernelPML4), 0).words[0]);
#endif /* CONFIG_KERNEL_SKIM_WINDOW */

    vmwrite(VMX_HOST_ES_SELECTOR, SEL_DS_0);
    vmwrite(VMX_HOST_CS_SELECTOR, SEL_CS_0);
    vmwrite(VMX_HOST_SS_SELECTOR, SEL_DS_0);
    vmwrite(VMX_HOST_DS_SELECTOR, SEL_DS_0);
    vmwrite(VMX_HOST_FS_SELECTOR, 0);
    vmwrite(VMX_HOST_GS_SELECTOR, 0);
    vmwrite(VMX_HOST_TR_SELECTOR, SEL_TSS);

    /* Set fixed VMCS control fields. */
    vmwrite(VMX_CONTROL_PIN_EXECUTION_CONTROLS, pin_control_high & pin_control_low);
    vmwrite(VMX_CONTROL_PRIMARY_PROCESSOR_CONTROLS, primary_control_high & primary_control_low);
    vmwrite(VMX_CONTROL_SECONDARY_PROCESSOR_CONTROLS, secondary_control_high & secondary_control_low);
    vmwrite(VMX_CONTROL_EXIT_CONTROLS, exit_control_high & exit_control_low);
    vmwrite(VMX_CONTROL_ENTRY_CONTROLS, entry_control_high & entry_control_low);
    vmwrite(VMX_CONTROL_MSR_ADDRESS, (word_t)kpptr_to_paddr(&msr_bitmap_region));
    vmwrite(VMX_GUEST_CR0, vcpu->cr0);
    vmwrite(VMX_GUEST_CR4, cr4_high & cr4_low);

    vmwrite(VMX_GUEST_VMCS_LINK_POINTER, ~(word_t)0);
    vmwrite(VMX_GUEST_VMCS_LINK_POINTER_HIGH, ~(word_t)0);

    memset(vcpu->io, ~(word_t)0, VCPU_IOBITMAP_SIZE);
    vmwrite(VMX_CONTROL_IOA_ADDRESS, pptr_to_paddr(vcpu->io));
    vmwrite(VMX_CONTROL_IOB_ADDRESS, pptr_to_paddr((char *)vcpu->io + (VCPU_IOBITMAP_SIZE / 2)));
}

static void
dissociateVcpuTcb(tcb_t *tcb, vcpu_t *vcpu)
{
    assert(tcb->tcbArch.tcbVCPU == vcpu);
    assert(vcpu->vcpuTCB == tcb);
    tcb->tcbArch.tcbVCPU = NULL;
    vcpu->vcpuTCB = NULL;
}

void
vcpu_finalise(vcpu_t *vcpu)
{
    if (vcpu->vcpuTCB) {
        dissociateVcpuTcb(vcpu->vcpuTCB, vcpu);
    }
    if (ARCH_NODE_STATE_ON_CORE(x86KSCurrentVCPU, vcpu->last_cpu) == vcpu) {
#ifdef ENABLE_SMP_SUPPORT
        if (vcpu->last_cpu == getCurrentCPUIndex()) {
            doRemoteClearCurrentVCPU(vcpu->last_cpu);
        } else
#endif /* ENABLE_SMP_SUPPORT */
        {
            clearCurrentVCPU();
        }
    }
}

static void
associateVcpuTcb(tcb_t *tcb, vcpu_t *vcpu)
{
    if (tcb->tcbArch.tcbVCPU) {
        dissociateVcpuTcb(tcb, tcb->tcbArch.tcbVCPU);
    }
    if (vcpu->vcpuTCB) {
        dissociateVcpuTcb(vcpu->vcpuTCB, vcpu);
    }
    vcpu->vcpuTCB = tcb;
    tcb->tcbArch.tcbVCPU = vcpu;
}

static exception_t
invokeVCPUWriteRegisters(vcpu_t *vcpu, word_t *buffer)
{
    int i;
    for (i = 0; i < n_vcpu_gp_register; i++) {
        vcpu->gp_registers[i] = getSyscallArg(i, buffer);
    }
    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return EXCEPTION_NONE;
}

static exception_t
decodeVCPUWriteRegisters(cap_t cap, word_t length, word_t *buffer)
{
    if (length < 7) {
        userError("VCPU WriteRegisters: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }
    return invokeVCPUWriteRegisters(VCPU_PTR(cap_vcpu_cap_get_capVCPUPtr(cap)), buffer);
}

static exception_t
invokeEnableIOPort(vcpu_t *vcpu, cte_t *slot, cap_t cap, uint16_t low, uint16_t high)
{
    /* remove any existing io ports from this cap */
    clearVPIDIOPortMappings(cap_io_port_cap_get_capIOPortVPID(cap),
                            cap_io_port_cap_get_capIOPortFirstPort(cap),
                            cap_io_port_cap_get_capIOPortLastPort(cap));
    /* update the assigned vpid. If the vcpu does not have a valid vpid then
     * this is fine as whilst the cap will not point to the vcpu, the vcpu
     * will have its port mask cleared when it gets assigned a vpid */
    cap = cap_io_port_cap_set_capIOPortVPID(cap, vcpu->vpid);
    slot->cap = cap;
    setIOPortMask(vcpu->io, low, high, false);
    return EXCEPTION_NONE;
}

static exception_t
decodeEnableIOPort(cap_t cap, word_t length, word_t* buffer, extra_caps_t excaps)
{
    vcpu_t *vcpu;
    cap_t ioCap;
    cte_t *ioSlot;
    uint16_t low, high;

    if (length < 2) {
        userError("VCPU EnableIOPort: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }
    if (excaps.excaprefs[0] == NULL) {
        userError("VCPU EnableIOPort: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }
    ioSlot = excaps.excaprefs[0];
    ioCap  = excaps.excaprefs[0]->cap;

    if (cap_get_capType(ioCap) != cap_io_port_cap) {
        userError("VCPU EnableIOPort: IOPort cap is not a IOPort cap.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    low = getSyscallArg(0, buffer);
    high = getSyscallArg(1, buffer);

    if (low < cap_io_port_cap_get_capIOPortFirstPort(ioCap) || high > cap_io_port_cap_get_capIOPortLastPort(ioCap)) {
        userError("VCPU EnableIOPort: Requested range not valid for given IOPort cap");
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    vcpu = VCPU_PTR(cap_vcpu_cap_get_capVCPUPtr(cap));

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeEnableIOPort(vcpu, ioSlot, ioCap, low, high);
}

static exception_t
invokeDisableIOPort(vcpu_t *vcpu, uint16_t low, uint16_t high)
{
    setIOPortMask(vcpu->io, low, high, true);
    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return EXCEPTION_NONE;
}

static exception_t
decodeDisableIOPort(cap_t cap, word_t length, word_t* buffer)
{
    vcpu_t *vcpu;
    uint16_t low, high;

    if (length < 2) {
        userError("VCPU EnableIOPort: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    low = getSyscallArg(0, buffer);
    high = getSyscallArg(1, buffer);

    vcpu = VCPU_PTR(cap_vcpu_cap_get_capVCPUPtr(cap));

    return invokeDisableIOPort(vcpu, low, high);
}

static exception_t
invokeWriteVMCS(vcpu_t *vcpu, word_t *buffer, word_t field, word_t value)
{
    tcb_t *thread;
    thread = NODE_STATE(ksCurThread);
    if (ARCH_NODE_STATE(x86KSCurrentVCPU) != vcpu) {
        switchVCPU(vcpu);
    }
    switch (field) {
    case VMX_CONTROL_EXCEPTION_BITMAP:
        vcpu->exception_bitmap = vcpu->cached_exception_bitmap = value;
        break;
    case VMX_GUEST_CR0:
        vcpu->cr0 = vcpu->cached_cr0 = value;
        break;
    case VMX_CONTROL_CR0_MASK:
        vcpu->cr0_mask = vcpu->cached_cr0_mask = value;
        break;
    case VMX_CONTROL_CR0_READ_SHADOW:
        vcpu->cr0_shadow = vcpu->cached_cr0_shadow = value;
        break;
    }
    setMR(thread, buffer, 0, value);
    vmwrite(field, value);
    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return EXCEPTION_NONE;
}

static exception_t
decodeWriteVMCS(cap_t cap, word_t length, word_t* buffer)
{
    word_t field;
    word_t value;

    if (length < 2) {
        userError("VCPU WriteVMCS: Not enough arguments.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    field = getSyscallArg(0, buffer);
    value = getSyscallArg(1, buffer);
    switch (field) {
    case VMX_GUEST_RIP:
    case VMX_GUEST_RSP:
    case VMX_GUEST_ES_SELECTOR:
    case VMX_GUEST_CS_SELECTOR:
    case VMX_GUEST_SS_SELECTOR:
    case VMX_GUEST_DS_SELECTOR:
    case VMX_GUEST_FS_SELECTOR:
    case VMX_GUEST_GS_SELECTOR:
    case VMX_GUEST_LDTR_SELECTOR:
    case VMX_GUEST_TR_SELECTOR:
    case VMX_GUEST_DEBUGCTRL:
    case VMX_GUEST_PAT:
    case VMX_GUEST_EFER:
    case VMX_GUEST_PERF_GLOBAL_CTRL:
    case VMX_GUEST_PDPTE0:
    case VMX_GUEST_PDPTE1:
    case VMX_GUEST_PDPTE2:
    case VMX_GUEST_PDPTE3:
    case VMX_GUEST_ES_LIMIT:
    case VMX_GUEST_CS_LIMIT:
    case VMX_GUEST_SS_LIMIT:
    case VMX_GUEST_DS_LIMIT:
    case VMX_GUEST_FS_LIMIT:
    case VMX_GUEST_GS_LIMIT:
    case VMX_GUEST_LDTR_LIMIT:
    case VMX_GUEST_TR_LIMIT:
    case VMX_GUEST_GDTR_LIMIT:
    case VMX_GUEST_IDTR_LIMIT:
    case VMX_GUEST_ES_ACCESS_RIGHTS:
    case VMX_GUEST_CS_ACCESS_RIGHTS:
    case VMX_GUEST_SS_ACCESS_RIGHTS:
    case VMX_GUEST_DS_ACCESS_RIGHTS:
    case VMX_GUEST_FS_ACCESS_RIGHTS:
    case VMX_GUEST_GS_ACCESS_RIGHTS:
    case VMX_GUEST_LDTR_ACCESS_RIGHTS:
    case VMX_GUEST_TR_ACCESS_RIGHTS:
    case VMX_GUEST_INTERRUPTABILITY:
    case VMX_GUEST_ACTIVITY:
    case VMX_GUEST_SMBASE:
    case VMX_GUEST_SYSENTER_CS:
    case VMX_GUEST_PREEMPTION_TIMER_VALUE:
    case VMX_GUEST_ES_BASE:
    case VMX_GUEST_CS_BASE:
    case VMX_GUEST_SS_BASE:
    case VMX_GUEST_DS_BASE:
    case VMX_GUEST_FS_BASE:
    case VMX_GUEST_GS_BASE:
    case VMX_GUEST_LDTR_BASE:
    case VMX_GUEST_TR_BASE:
    case VMX_GUEST_GDTR_BASE:
    case VMX_GUEST_IDTR_BASE:
    case VMX_GUEST_DR7:
    case VMX_GUEST_RFLAGS:
    case VMX_GUEST_PENDING_DEBUG_EXCEPTIONS:
    case VMX_GUEST_SYSENTER_ESP:
    case VMX_GUEST_SYSENTER_EIP:
    case VMX_CONTROL_CR0_MASK:
    case VMX_CONTROL_CR4_MASK:
    case VMX_CONTROL_CR0_READ_SHADOW:
    case VMX_CONTROL_CR4_READ_SHADOW:
    case VMX_GUEST_CR3:
    case VMX_CONTROL_EXCEPTION_BITMAP:
    case VMX_CONTROL_ENTRY_INTERRUPTION_INFO:
    case VMX_CONTROL_ENTRY_EXCEPTION_ERROR_CODE:
        break;
    case VMX_CONTROL_PIN_EXECUTION_CONTROLS:
        value = applyFixedBits(value, pin_control_high, pin_control_low);
        break;
    case VMX_CONTROL_PRIMARY_PROCESSOR_CONTROLS:
        value = applyFixedBits(value, primary_control_high, primary_control_low);
        break;
    case VMX_CONTROL_SECONDARY_PROCESSOR_CONTROLS:
        value = applyFixedBits(value, secondary_control_high, secondary_control_low);
        break;
    case VMX_CONTROL_EXIT_CONTROLS:
        value = applyFixedBits(value, exit_control_high, exit_control_low);
        break;
    case VMX_GUEST_CR0:
        value = applyFixedBits(value, cr0_high, cr0_low);
        break;
    case VMX_GUEST_CR4:
        value = applyFixedBits(value, cr4_high, cr4_low);
        break;
    default:
        userError("VCPU WriteVMCS: Invalid field %lx.", (long)field);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
    return invokeWriteVMCS(VCPU_PTR(cap_vcpu_cap_get_capVCPUPtr(cap)), buffer, field, value);
}

static word_t readVMCSField(vcpu_t *vcpu, word_t field)
{
    switch (field) {
    case VMX_CONTROL_EXCEPTION_BITMAP:
        return vcpu->exception_bitmap;
    case VMX_GUEST_CR0:
        return vcpu->cr0;
    case VMX_CONTROL_CR0_MASK:
        return vcpu->cr0_mask;
    case VMX_CONTROL_CR0_READ_SHADOW:
        return vcpu->cr0_shadow;
    }
    if (ARCH_NODE_STATE(x86KSCurrentVCPU) != vcpu) {
        switchVCPU(vcpu);
    }
    return vmread(field);
}

static exception_t
invokeReadVMCS(vcpu_t *vcpu, word_t field, word_t *buffer)
{
    tcb_t *thread;
    thread = NODE_STATE(ksCurThread);

    setMR(thread, buffer, 0, readVMCSField(vcpu, field));
    setRegister(thread, msgInfoRegister, wordFromMessageInfo(
                    seL4_MessageInfo_new(0, 0, 0, 1)));
    setThreadState(thread, ThreadState_Restart);
    return EXCEPTION_NONE;
}

static exception_t
decodeReadVMCS(cap_t cap, word_t length, word_t* buffer)
{
    if (length < 1) {
        userError("VCPU ReadVMCS: Not enough arguments.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
    word_t field = getSyscallArg(0, buffer);
    switch (field) {
    case VMX_GUEST_RIP:
    case VMX_GUEST_RSP:
    case VMX_GUEST_ES_SELECTOR:
    case VMX_GUEST_CS_SELECTOR:
    case VMX_GUEST_SS_SELECTOR:
    case VMX_GUEST_DS_SELECTOR:
    case VMX_GUEST_FS_SELECTOR:
    case VMX_GUEST_GS_SELECTOR:
    case VMX_GUEST_LDTR_SELECTOR:
    case VMX_GUEST_TR_SELECTOR:
    case VMX_GUEST_DEBUGCTRL:
    case VMX_GUEST_PAT:
    case VMX_GUEST_EFER:
    case VMX_GUEST_PERF_GLOBAL_CTRL:
    case VMX_GUEST_PDPTE0:
    case VMX_GUEST_PDPTE1:
    case VMX_GUEST_PDPTE2:
    case VMX_GUEST_PDPTE3:
    case VMX_GUEST_ES_LIMIT:
    case VMX_GUEST_CS_LIMIT:
    case VMX_GUEST_SS_LIMIT:
    case VMX_GUEST_DS_LIMIT:
    case VMX_GUEST_FS_LIMIT:
    case VMX_GUEST_GS_LIMIT:
    case VMX_GUEST_LDTR_LIMIT:
    case VMX_GUEST_TR_LIMIT:
    case VMX_GUEST_GDTR_LIMIT:
    case VMX_GUEST_IDTR_LIMIT:
    case VMX_GUEST_ES_ACCESS_RIGHTS:
    case VMX_GUEST_CS_ACCESS_RIGHTS:
    case VMX_GUEST_SS_ACCESS_RIGHTS:
    case VMX_GUEST_DS_ACCESS_RIGHTS:
    case VMX_GUEST_FS_ACCESS_RIGHTS:
    case VMX_GUEST_GS_ACCESS_RIGHTS:
    case VMX_GUEST_LDTR_ACCESS_RIGHTS:
    case VMX_GUEST_TR_ACCESS_RIGHTS:
    case VMX_GUEST_INTERRUPTABILITY:
    case VMX_GUEST_ACTIVITY:
    case VMX_GUEST_SMBASE:
    case VMX_GUEST_SYSENTER_CS:
    case VMX_GUEST_PREEMPTION_TIMER_VALUE:
    case VMX_GUEST_ES_BASE:
    case VMX_GUEST_CS_BASE:
    case VMX_GUEST_SS_BASE:
    case VMX_GUEST_DS_BASE:
    case VMX_GUEST_FS_BASE:
    case VMX_GUEST_GS_BASE:
    case VMX_GUEST_LDTR_BASE:
    case VMX_GUEST_TR_BASE:
    case VMX_GUEST_GDTR_BASE:
    case VMX_GUEST_IDTR_BASE:
    case VMX_GUEST_DR7:
    case VMX_GUEST_RFLAGS:
    case VMX_GUEST_PENDING_DEBUG_EXCEPTIONS:
    case VMX_GUEST_SYSENTER_ESP:
    case VMX_GUEST_SYSENTER_EIP:
    case VMX_CONTROL_CR0_MASK:
    case VMX_CONTROL_CR4_MASK:
    case VMX_CONTROL_CR0_READ_SHADOW:
    case VMX_CONTROL_CR4_READ_SHADOW:
    case VMX_DATA_INSTRUCTION_ERROR:
    case VMX_DATA_EXIT_INTERRUPT_INFO:
    case VMX_DATA_EXIT_INTERRUPT_ERROR:
    case VMX_DATA_IDT_VECTOR_INFO:
    case VMX_DATA_IDT_VECTOR_ERROR:
    case VMX_DATA_EXIT_INSTRUCTION_LENGTH:
    case VMX_DATA_EXIT_INSTRUCTION_INFO:
    case VMX_DATA_GUEST_PHYSICAL:
    case VMX_DATA_IO_RCX:
    case VMX_DATA_IO_RSI:
    case VMX_DATA_IO_RDI:
    case VMX_DATA_IO_RIP:
    case VMX_DATA_GUEST_LINEAR_ADDRESS:
    case VMX_CONTROL_ENTRY_INTERRUPTION_INFO:
    case VMX_CONTROL_PIN_EXECUTION_CONTROLS:
    case VMX_CONTROL_PRIMARY_PROCESSOR_CONTROLS:
    case VMX_CONTROL_EXCEPTION_BITMAP:
    case VMX_CONTROL_EXIT_CONTROLS:
    case VMX_GUEST_CR0:
    case VMX_GUEST_CR3:
    case VMX_GUEST_CR4:
        break;
    default:
        userError("VCPU ReadVMCS: Invalid field %lx.", (long)field);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
    return invokeReadVMCS(VCPU_PTR(cap_vcpu_cap_get_capVCPUPtr(cap)), field, buffer);
}

static exception_t
invokeSetTCB(vcpu_t *vcpu, tcb_t *tcb)
{
    associateVcpuTcb(tcb, vcpu);

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return EXCEPTION_NONE;
}

static exception_t
decodeSetTCB(cap_t cap, word_t length, word_t* buffer, extra_caps_t excaps)
{
    cap_t tcbCap;
    if ( excaps.excaprefs[0] == NULL) {
        userError("VCPU SetTCB: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }
    tcbCap  = excaps.excaprefs[0]->cap;

    if (cap_get_capType(tcbCap) != cap_thread_cap) {
        userError("TCB cap is not a TCB cap.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    return invokeSetTCB(VCPU_PTR(cap_vcpu_cap_get_capVCPUPtr(cap)), TCB_PTR(cap_thread_cap_get_capTCBPtr(tcbCap)));
}

void
vcpu_update_state_sysvmenter(vcpu_t *vcpu)
{
    word_t *buffer;
    if (ARCH_NODE_STATE(x86KSCurrentVCPU) != vcpu) {
        switchVCPU(vcpu);
    }
    buffer = lookupIPCBuffer(false, NODE_STATE(ksCurThread));
    if (!buffer) {
        userError("No IPC buffer.");
        return;
    }
    vmwrite(VMX_GUEST_RIP, getSyscallArg(0, buffer));
    vmwrite(VMX_CONTROL_PRIMARY_PROCESSOR_CONTROLS, applyFixedBits(getSyscallArg(1, buffer), primary_control_high, primary_control_low));
    vmwrite(VMX_CONTROL_ENTRY_INTERRUPTION_INFO, getSyscallArg(2, buffer));
}

void
vcpu_sysvmenter_reply_to_user(tcb_t *tcb)
{
    word_t *buffer;
    vcpu_t *vcpu;

    buffer = lookupIPCBuffer(true, tcb);
    vcpu = tcb->tcbArch.tcbVCPU;

    assert(vcpu);

    if (ARCH_NODE_STATE(x86KSCurrentVCPU) != vcpu) {
        switchVCPU(vcpu);
    }

    setMR(tcb, buffer, SEL4_VMENTER_CALL_EIP_MR, vmread(VMX_GUEST_RIP));
    setMR(tcb, buffer, SEL4_VMENTER_CALL_CONTROL_PPC_MR, vmread(VMX_CONTROL_PRIMARY_PROCESSOR_CONTROLS));

    setMR(tcb, buffer, SEL4_VMENTER_CALL_CONTROL_ENTRY_MR, vmread(VMX_CONTROL_ENTRY_INTERRUPTION_INFO));
    setRegister(tcb, msgInfoRegister, 0);
}

exception_t
decodeX86VCPUInvocation(
    word_t invLabel,
    word_t length,
    cptr_t cptr,
    cte_t* slot,
    cap_t cap,
    extra_caps_t excaps,
    word_t* buffer
)
{
    switch (invLabel) {
    case X86VCPUSetTCB:
        return decodeSetTCB(cap, length, buffer, excaps);
    case X86VCPUReadVMCS:
        return decodeReadVMCS(cap, length, buffer);
    case X86VCPUWriteVMCS:
        return decodeWriteVMCS(cap, length, buffer);
    case X86VCPUEnableIOPort:
        return decodeEnableIOPort(cap, length, buffer, excaps);
    case X86VCPUDisableIOPort:
        return decodeDisableIOPort(cap, length, buffer);
    case X86VCPUWriteRegisters:
        return decodeVCPUWriteRegisters(cap, length, buffer);
    default:
        userError("VCPU: Illegal operation.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
}

static bool_t
is_vtx_supported(void)
{
    /* check for VMX support in CPUID
     * see section 23.7 of Volume 3 of the Intel manual */
    return !!(x86_cpuid_ecx(0x1, 0) & BIT(5));
}

static inline void
clear_bit(word_t *bitmap, word_t bit)
{
    int index = bit / (sizeof(word_t) * 8);
    int offset = bit % (sizeof(word_t) * 8);
    bitmap[index] &= ~BIT(offset);
}

BOOT_CODE bool_t
vtx_init(void)
{
    if (!is_vtx_supported()) {
        printf("vt-x: not supported\n");
        return false;
    }
    vmx_basic_msr_t vmx_basic;
    feature_control_msr_t feature_control;
    vmx_basic.words[0] = x86_rdmsr_low(IA32_VMX_BASIC_MSR);
    vmx_basic.words[1] = x86_rdmsr_high(IA32_VMX_BASIC_MSR);
    vmcs_revision = vmx_basic_msr_get_vmcs_revision(vmx_basic);
    feature_control.words[0] = x86_rdmsr_low(IA32_FEATURE_CONTROL_MSR);
    if (!feature_control_msr_get_vmx_outside_smx(feature_control)) {
        /* enable if the MSR is not locked */
        if (feature_control_msr_get_lock(feature_control)) {
            printf("vt-x: feature locked\n");
            return false;
        }
        feature_control = feature_control_msr_set_vmx_outside_smx(feature_control, 1);
        x86_wrmsr_parts(IA32_FEATURE_CONTROL_MSR, x86_rdmsr_high(IA32_FEATURE_CONTROL_MSR), feature_control.words[0]);
    }
    /* make sure the msr is locked */
    if (!feature_control_msr_get_lock(feature_control)) {
        feature_control = feature_control_msr_set_lock(feature_control, 1);
        x86_wrmsr_parts(IA32_FEATURE_CONTROL_MSR, x86_rdmsr_high(IA32_FEATURE_CONTROL_MSR), feature_control.words[0]);
    }
    /* Initialize the fixed values only on the boot core. All other cores
     * will just check that the fixed values are valid */
    if (SMP_TERNARY(getCurrentCPUIndex(), 0) == 0) {
        if (!init_vtx_fixed_values(vmx_basic_msr_get_true_msrs(vmx_basic))) {
            printf("vt-x: lack of required features\n");
            return false;
        }
    }
    if (!check_vtx_fixed_values(vmx_basic_msr_get_true_msrs(vmx_basic))) {
        printf("vt-x: cores have inconsistent features\n");
        return false;
    }
    write_cr4(read_cr4() | CR4_VMXE);
    /* we are required to set the VMCS region in the VMXON region */
    vmxon_region.revision = vmcs_revision;
    /* Before calling vmxon, we must check that CR0 and CR4 are not set to values
     * that are unsupported by vt-x */
    if (!vtx_check_fixed_values(read_cr0(), read_cr4())) {
        return false;
    }
    if (vmxon(kpptr_to_paddr(&vmxon_region))) {
        printf("vt-x: vmxon failure\n");
        return false;
    }
    memset(&msr_bitmap_region, ~0, sizeof(msr_bitmap_region));
    /* Set sysenter MSRs to writeable and readable. These are all low msrs */
    clear_bit(msr_bitmap_region.low_msr_read.bitmap, IA32_SYSENTER_CS_MSR);
    clear_bit(msr_bitmap_region.low_msr_read.bitmap, IA32_SYSENTER_ESP_MSR);
    clear_bit(msr_bitmap_region.low_msr_read.bitmap, IA32_SYSENTER_EIP_MSR);
    clear_bit(msr_bitmap_region.low_msr_write.bitmap, IA32_SYSENTER_CS_MSR);
    clear_bit(msr_bitmap_region.low_msr_write.bitmap, IA32_SYSENTER_ESP_MSR);
    clear_bit(msr_bitmap_region.low_msr_write.bitmap, IA32_SYSENTER_EIP_MSR);

    /* The VMX_EPT_VPID_CAP MSR exists if VMX supports EPT or VPIDs. Whilst
     * VPID support is optional, EPT support is not and is already checked for,
     * so we know that this MSR is safe to read */
    vpid_capability.words[0] = x86_rdmsr_low(IA32_VMX_EPT_VPID_CAP_MSR);
    vpid_capability.words[1] = x86_rdmsr_high(IA32_VMX_EPT_VPID_CAP_MSR);

    /* check for supported EPT features */
    if (!vmx_ept_vpid_cap_msr_get_ept_wb(vpid_capability)) {
        printf("vt-x: Expected wb attribute for EPT paging structure\n");
        return false;
    }
    if (!vmx_ept_vpid_cap_msr_get_ept_2m(vpid_capability)) {
        printf("vt-x: Expected supported for 2m pages\n");
        return false;
    }

    return true;
}

static void
setMRs_vmexit(uint32_t reason, word_t qualification)
{
    word_t *buffer;
    int i;

    buffer = lookupIPCBuffer(true, NODE_STATE(ksCurThread));

    setMR(NODE_STATE(ksCurThread), buffer, SEL4_VMENTER_CALL_EIP_MR, vmread(VMX_GUEST_RIP));
    setMR(NODE_STATE(ksCurThread), buffer, SEL4_VMENTER_CALL_CONTROL_PPC_MR, vmread(VMX_CONTROL_PRIMARY_PROCESSOR_CONTROLS));
    setMR(NODE_STATE(ksCurThread), buffer, SEL4_VMENTER_CALL_CONTROL_ENTRY_MR, vmread(VMX_CONTROL_ENTRY_INTERRUPTION_INFO));
    setMR(NODE_STATE(ksCurThread), buffer, SEL4_VMENTER_FAULT_REASON_MR, reason);
    setMR(NODE_STATE(ksCurThread), buffer, SEL4_VMENTER_FAULT_QUALIFICATION_MR, qualification);

    setMR(NODE_STATE(ksCurThread), buffer, SEL4_VMENTER_FAULT_INSTRUCTION_LEN_MR, vmread(VMX_DATA_EXIT_INSTRUCTION_LENGTH));
    setMR(NODE_STATE(ksCurThread), buffer, SEL4_VMENTER_FAULT_GUEST_PHYSICAL_MR, vmread(VMX_DATA_GUEST_PHYSICAL));
    setMR(NODE_STATE(ksCurThread), buffer, SEL4_VMENTER_FAULT_RFLAGS_MR, vmread(VMX_GUEST_RFLAGS));
    setMR(NODE_STATE(ksCurThread), buffer, SEL4_VMENTER_FAULT_GUEST_INT_MR, vmread(VMX_GUEST_INTERRUPTABILITY));
    setMR(NODE_STATE(ksCurThread), buffer, SEL4_VMENTER_FAULT_CR3_MR, vmread(VMX_GUEST_CR3));

    for (i = 0; i < n_vcpu_gp_register; i++) {
        setMR(NODE_STATE(ksCurThread), buffer, SEL4_VMENTER_FAULT_EAX + i, NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->gp_registers[i]);
    }
}

static void
handleVmxFault(uint32_t reason, word_t qualification)
{
    /* Indicate that we are returning the from VMEnter with a fault */
    setRegister(NODE_STATE(ksCurThread), msgInfoRegister, SEL4_VMENTER_RESULT_FAULT);

    setMRs_vmexit(reason, qualification);

    /* Set the thread back to running */
    setThreadState(NODE_STATE(ksCurThread), ThreadState_Running);

    /* No need to schedule because this wasn't an interrupt and
     * we run at the same priority */
    activateThread();
}

static inline void
finishVmexitSaving(void)
{
    vcpu_t *vcpu = ARCH_NODE_STATE(x86KSCurrentVCPU);
    assert(vcpu == NODE_STATE(ksCurThread)->tcbArch.tcbVCPU);
    vcpu->launched = true;
    /* Update our cache of what is in the vmcs. This is the only value
     * that we cache that can be modified by the guest during execution */
    vcpu->cached_cr0 = vmread(VMX_GUEST_CR0);
    if (vcpuThreadUsingFPU(NODE_STATE(ksCurThread))) {
        /* If the vcpu owns the fpu then we did not modify the active cr0 to anything different
         * to what the VCPU owner requested, so we can update it with any modifications
         * the guest may have made */
        vcpu->cr0 = vcpu->cached_cr0;
    } else {
        /* If the vcpu does not own the fpu then we will have forced the task switched flag
         * to be set in the cr0 that was put into the vmcs. Since the VCPU owner (or the guest)
         * may believe the task switched flag is not set, and the guest may have modified other
         * parts of cr0 during execution then to update the desired cr0 value to be the cr0
         * value from the vmcs (thus pulling in any modifications the guest made) but removing
         * the task switched flag that we set and then adding back in the task switched flag
         * that may be in the desired current cr0 */
        vcpu->cr0 = (vcpu->cached_cr0 & ~CR0_TASK_SWITCH) | (NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->cr0 & CR0_TASK_SWITCH);
    }
}

exception_t
handleVmexit(void)
{
    uint32_t interrupt;
    /* qualification is host width, reason is defined as being 32 bit */
    word_t qualification;
    uint32_t reason;
    finishVmexitSaving();
    /* the basic exit reason is the bottom 16 bits of the exit reason field */
    reason = vmread(VMX_DATA_EXIT_REASON) & MASK(16);
    if (reason == EXTERNAL_INTERRUPT) {
        if (vmx_feature_ack_on_exit) {
            interrupt = vmread(VMX_DATA_EXIT_INTERRUPT_INFO);
            ARCH_NODE_STATE(x86KScurInterrupt) = interrupt & 0xff;
            NODE_LOCK_IRQ_IF(interrupt != int_remote_call_ipi);
            handleInterruptEntry();
        } else {
            /* poll for the pending irq. We will then handle it once we return back
             * up to restore_user_context */
            receivePendingIRQ();
        }
        return EXCEPTION_NONE;
    }

    NODE_LOCK_SYS;

    if (!vcpuThreadUsingFPU(NODE_STATE(ksCurThread))) {
        /* since this vcpu does not currently own the fpu state, check if the kernel should
         * switch the fpu owner or not. We switch if the guest performed and unimplemented device
         * exception AND the owner of this vcpu has not requested that these exceptions be forwarded
         * to them (i.e. if they have not explicitly set the unimplemented device exception in the
         * exception_bitmap) */
        if (reason == EXCEPTION_OR_NMI && !(NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->exception_bitmap & BIT(int_unimpl_dev))) {
            interrupt = vmread(VMX_DATA_EXIT_INTERRUPT_INFO);
            /* The exception number is the bottom 8 bits of the interrupt info */
            if ((interrupt & 0xff) == int_unimpl_dev) {
                switchLocalFpuOwner(&NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->fpuState);
                return EXCEPTION_NONE;
            }
        } else if (reason == CONTROL_REGISTER && !(NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->cr0_mask & CR0_TASK_SWITCH)) {
            /* we get here if the guest is attempting to write to a control register that is set (by
             * a 1 bit in the cr0 mask) as being owned by the host. If we got here then the previous check
             * on cr0_mask meant that the VCPU owner did not claim ownership of the the task switch bit
             * however we may have temporarily claimed ownership for the purposes of FPU switching.
             * At this point we could still have a false positive, as the guest could be attempted to
             * manipulate bits that are not task switch, so we still have to be careful and propogate
             * all or some of an attempted write */
            qualification = vmread(VMX_DATA_EXIT_QUALIFICATION);
            vmx_data_exit_qualification_control_regster_t qual;
            qual.words[0] = qualification;
            /* We only care about some of the exit qualification cases, we handle them here
             * and will deliver any others through to fault handler */
            switch (vmx_data_exit_qualification_control_regster_get_access_type(qual)) {
            case VMX_EXIT_QUAL_TYPE_MOV_CR: {
                /* check for cr0 */
                if (vmx_data_exit_qualification_control_regster_get_cr(qual) == 0) {
                    vcpu_gp_register_t source = crExitRegs[vmx_data_exit_qualification_control_regster_get_reg(qual)];
                    word_t value;
                    if (source == VCPU_ESP) {
                        /* ESP is the only register that is is not part of the general purpose
                         * registers that we have to save and restore ourselves, so we need to
                         * get this one from the vmcs */
                        value = vmread(VMX_GUEST_RSP);
                    } else {
                        value = NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->gp_registers[source];
                    }
                    /* First unset the task switch bit in cr0 */
                    NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->cr0 &= ~CR0_TASK_SWITCH;
                    /* now set it to the value we were given */
                    NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->cr0 |= value & CR0_TASK_SWITCH;
                    /* check if there are any parts of the write remaining to forward. we only need
                     * to consider bits that the hardware will not have handled without faulting, which
                     * is writing any bit such that it is different to the shadow, but only considering
                     * bits that the VCPU owner has declared that they want to own (via the cr0_shadow)
                     */
                    if (!((value ^ NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->cr0_shadow) &
                            NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->cr0_mask)) {
                        return EXCEPTION_NONE;
                    }
                }
                break;
            }
            case VMX_EXIT_QUAL_TYPE_CLTS: {
                /* Easy case. Just remove the task switch bit out of cr0 */
                NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->cr0 &= ~CR0_TASK_SWITCH;
                return EXCEPTION_NONE;
            }
            case VMX_EXIT_QUAL_TYPE_LMSW: {
                uint16_t value = vmx_data_exit_qualification_control_regster_get_data(qual);
                /* First unset the task switch bit in cr0 */
                NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->cr0 &= ~CR0_TASK_SWITCH;
                /* now set it to the value we were given */
                NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->cr0 |= value & CR0_TASK_SWITCH;
                /* check if there are any parts of the write remaining to forward. we only need
                 * to consider bits that the hardware will not have handled without faulting, which
                 * is writing any bit such that it is different to the shadow, but only considering
                 * bits that the VCPU owner has declared that they want to own (via the cr0_shadow).
                 * Additionally since LMSW only loads the bottom 4 bits of CR0 we only consider
                 * the low 4 bits
                 */
                if (!((value ^ NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->cr0_shadow) &
                        NODE_STATE(ksCurThread)->tcbArch.tcbVCPU->cr0_mask & MASK(4))) {
                    return EXCEPTION_NONE;
                }
                break;
            }
            }
        }
    }
    switch (reason) {
    case EXCEPTION_OR_NMI:
    case MOV_DR:
    case TASK_SWITCH:
    case CONTROL_REGISTER:
    case IO:
    case MWAIT:
    case SIPI:
    case INVLPG:
    case INVEPT:
    case INVVPID:
    case VMCLEAR:
    case VMPTRLD:
    case VMPTRST:
    case VMREAD:
    case VMWRITE:
    case VMXON:
    case EPT_VIOLATION:
    case GDTR_OR_IDTR:
    case LDTR_OR_TR:
    case TPR_BELOW_THRESHOLD:
    case APIC_ACCESS:
        qualification = vmread(VMX_DATA_EXIT_QUALIFICATION);
        break;
    default:
        qualification = 0;
    }

    handleVmxFault(reason, qualification);

    return EXCEPTION_NONE;
}

exception_t
handleVmEntryFail(void)
{
    handleVmxFault(-1, -1);

    return EXCEPTION_NONE;
}

#ifdef ENABLE_SMP_SUPPORT
void
VMCheckBoundNotification(tcb_t *tcb)
{
    /* We want to check if the VM we are currently running has received
     * a message on its bound notification object. This check is done
     * in c_traps when we first peform a SysVMEnter, but we could presently
     * be running a VM and another core may have placed a message on the
     * endpoint
     */
    assert(tcb->tcbAffinity == getCurrentCPUIndex());
    notification_t *ntfnPtr = tcb->tcbBoundNotification;
    if (thread_state_ptr_get_tsType(&tcb->tcbState) == ThreadState_RunningVM
            && ntfnPtr && notification_ptr_get_state(ntfnPtr) == NtfnState_Active) {

        word_t badge = notification_ptr_get_ntfnMsgIdentifier(ntfnPtr);
        notification_ptr_set_state(ntfnPtr, NtfnState_Idle);
        setThreadState(tcb, ThreadState_Running);
        setRegister(tcb, badgeRegister, badge);
        Arch_leaveVMAsyncTransfer(tcb);
        /* In the process of performing Arch_leavVMAsyncTransfer we will have
         * had to switch the active VMCS. As a result we might as well try and
         * run this tcb if it is permitted instead of switching VMCS contexts
         * back and forth */
        if (tcb != NODE_STATE(ksCurThread)) {
            possibleSwitchTo(tcb);
        }
    }
}
#endif /* ENABLE_SMP_SUPPORT */

static void
invvpid_context(uint16_t vpid)
{
    struct {
        uint64_t vpid : 16;
        uint64_t rsvd : 48;
        uint64_t address;
    } PACKED operand = {vpid, 0, 0};
    asm volatile("invvpid %0, %1" :: "m"(operand), "r"((word_t)1) : "cc");
}

static void
setEPTRoot(cap_t vmxSpace, vcpu_t* vcpu)
{
    paddr_t ept_root;
    if (cap_get_capType(vmxSpace) != cap_ept_pml4_cap ||
            !cap_ept_pml4_cap_get_capPML4IsMapped(vmxSpace)) {
        ept_root = kpptr_to_paddr(null_ept_space);
    } else {
        findEPTForASID_ret_t find_ret;
        ept_pml4e_t *pml4;

        pml4 = (ept_pml4e_t*)cap_ept_pml4_cap_get_capPML4BasePtr(vmxSpace);
        find_ret = findEPTForASID(cap_ept_pml4_cap_get_capPML4MappedASID(vmxSpace));
        if (find_ret.status != EXCEPTION_NONE || find_ret.ept != pml4) {
            ept_root = kpptr_to_paddr(null_ept_space);
        } else {
            ept_root = pptr_to_paddr(pml4);
        }
    }
    if (ept_root != vcpu->last_ept_root) {
        vcpu->last_ept_root = ept_root;
        vmx_eptp_t eptp = vmx_eptp_new(
                              ept_root,       /* paddr of ept */
                              0,              /* do not use accessed and dirty flags */
                              3,              /* depth (4) minus 1 of desired table walking */
                              6               /* write back memory type */
                          );
        vmwrite(VMX_CONTROL_EPT_POINTER, eptp.words[0]);
        assert(vcpu->vpid != VPID_INVALID);
        if (vmx_feature_vpid) {
            invvpid_context(vcpu->vpid);
        }
    }
}

static void
handleLazyFpu(void)
{
    vcpu_t *vcpu = NODE_STATE(ksCurThread)->tcbArch.tcbVCPU;
    word_t cr0 = vcpu->cr0;
    word_t exception_bitmap = vcpu->exception_bitmap;
    word_t cr0_mask = vcpu->cr0_mask;
    word_t cr0_shadow = vcpu->cr0_shadow;
    /* if the vcpu actually owns the fpu then we do not need to change any bits
     * and so we will put into the vmcs precisely what the VCPU owner has requested */
    if (!vcpuThreadUsingFPU(NODE_STATE(ksCurThread))) {
        /* when the vcpu doesn't own the fpu we need to force the task switched flag
         * so that we can take an exception and perform lazy fpu switching */
        cr0 |= CR0_TASK_SWITCH;
        /* once we have forced the task switched flag we also need to handle
         * unimplemented device exceptions so we force these to trap. In the case
         * where the VCPU owner had already set these to trap then this well be
         * checked in handleVmexit and the exception will get forwarded */
        exception_bitmap |= BIT(int_unimpl_dev);
        /* we need to claim ownership of the task switch bit so that any modifications
         * of it cause an exception and we must do this regardless of whether the
         * VCPU owner also wants to claim ownership. In the scenario where the VCPU
         * owner had also claimed ownership then in handleVmexit we won't actually
         * do any fpu switching and will forward the fault */
        cr0_mask |= CR0_TASK_SWITCH;
        /* since we have forced a value in the cr0 mask we need to set an appropriate value
         * in the cr0 read shadow. If the VCPU owner is also masking this bit then
         * we should use the value they have put in the cr0 read shadow. If they aren't
         * then the read shadow will contain garbage and we should instead set the
         * read shadow to the actual desired cr0 value */
        if (!(vcpu->cr0_mask & CR0_TASK_SWITCH)) {
            cr0_shadow &= ~CR0_TASK_SWITCH;
            cr0_shadow |= vcpu->cr0 & CR0_TASK_SWITCH;
        }
    }
    if (cr0 != vcpu->cached_cr0) {
        vmwrite(VMX_GUEST_CR0, cr0);
        vcpu->cached_cr0 = cr0;
    }
    if (exception_bitmap != vcpu->cached_exception_bitmap) {
        vmwrite(VMX_CONTROL_EXCEPTION_BITMAP, exception_bitmap);
        vcpu->cached_exception_bitmap = exception_bitmap;
    }
    if (cr0_mask != vcpu->cached_cr0_mask) {
        vmwrite(VMX_CONTROL_CR0_MASK, cr0_mask);
        vcpu->cached_cr0_mask = cr0_mask;
    }
    if (cr0_shadow != vcpu->cached_cr0_shadow) {
        vmwrite(VMX_CONTROL_CR0_READ_SHADOW, cr0_shadow);
        vcpu->cached_cr0_shadow = cr0_shadow;
    }
}

void
clearVPIDIOPortMappings(vpid_t vpid, uint16_t first, uint16_t last)
{
    if (vpid == VPID_INVALID) {
        return;
    }
    vcpu_t *vcpu = x86KSVPIDTable[vpid];
    if (vcpu == NULL) {
        return;
    }
    assert(vcpu->vpid == vpid);
    setIOPortMask(vcpu->io, first, last, true);
}

static inline vpid_t
nextVPID(vpid_t vpid)
{
    if (vpid == VPID_LAST) {
        return VPID_FIRST;
    } else {
        return vpid + 1;
    }
}

static void
invalidateVPID(vpid_t vpid)
{
    vcpu_t *vcpu = x86KSVPIDTable[vpid];
    /* clear the IO bitmap as when we sever the VPID asignment we lose
     * the ability for the references in IO port capabilities to invalidate */
    memset(vcpu->io, ~0, sizeof(vcpu->io));
    /* invalidate the VPID context */
    if (vmx_feature_vpid) {
        invvpid_context(vpid);
    }
}

static vpid_t
findFreeVPID(void)
{
    vpid_t vpid;

    vpid = x86KSNextVPID;
    do {
        if (x86KSVPIDTable[vpid] == NULL) {
            return vpid;
        }
        vpid = nextVPID(vpid);
    } while (vpid != x86KSNextVPID);

    /* Forcively take the next VPID */
    vpid = x86KSNextVPID;
    invalidateVPID(vpid);

    x86KSVPIDTable[vpid]->vpid = VPID_INVALID;
    x86KSVPIDTable[vpid] = NULL;

    x86KSNextVPID = nextVPID(x86KSNextVPID);
    return vpid;
}

static void
storeVPID(vcpu_t *vcpu, vpid_t vpid)
{
    assert(x86KSVPIDTable[vpid] == NULL);
    assert(vcpu->vpid == VPID_INVALID);
    x86KSVPIDTable[vpid] = vcpu;
    vcpu->vpid = vpid;
}

void
restoreVMCS(void)
{
    vcpu_t *expected_vmcs = NODE_STATE(ksCurThread)->tcbArch.tcbVCPU;

    /* Check that the right VMCS is active and current. */
    if (ARCH_NODE_STATE(x86KSCurrentVCPU) != expected_vmcs) {
        switchVCPU(expected_vmcs);
    }

#ifndef CONFIG_KERNEL_SKIM_WINDOW
    if (getCurrentCR3().words[0] != expected_vmcs->last_host_cr3) {
        expected_vmcs->last_host_cr3 = getCurrentCR3().words[0];
        vmwrite(VMX_HOST_CR3, getCurrentCR3().words[0]);
    }
#endif
    if (expected_vmcs->vpid == VPID_INVALID) {
        vpid_t vpid = findFreeVPID();
        storeVPID(expected_vmcs, vpid);
        if (vmx_feature_vpid) {
            vmwrite(VMX_CONTROL_VPID, vpid);
        }
    }
    setEPTRoot(TCB_PTR_CTE_PTR(NODE_STATE(ksCurThread), tcbArchEPTRoot)->cap, expected_vmcs);
    handleLazyFpu();
}

void
invept(ept_pml4e_t *ept_pml4)
{
    if (vmx_ept_vpid_cap_msr_get_invept(vpid_capability)) {
        struct {
            uint64_t parts[2];
        } address;
        word_t type;
        if (vmx_ept_vpid_cap_msr_get_invept_single_context(vpid_capability)) {
            type = 1;
        } else if (vmx_ept_vpid_cap_msr_get_invept_all_context(vpid_capability)) {
            type = 2;
        } else {
            /* hardware claims to support invept yet provides us with no actual
             * invept mechanism. This is probably impossible, but just silently
             * ignore if it happens */
            userError("Hardware claimed to support invept, yet provided no mechanism");
            return;
        }

        address.parts[0] = pptr_to_paddr((void*)ept_pml4);
        address.parts[1] = 0;
        asm volatile (
            "invept %0, %1"
            :
            : "m"(address),  "r"(type)
            : "memory"
        );
    }
}

#endif
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/arch/x86/smp/ipi.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <mode/smp/ipi.h>
#include <smp/ipi.h>
#include <smp/lock.h>

#ifdef ENABLE_SMP_SUPPORT

static IpiModeRemoteCall_t remoteCall;   /* the remote call being requested */

static inline void init_ipi_args(IpiModeRemoteCall_t func,
                                 word_t data1, word_t data2, word_t data3,
                                 word_t mask)
{
    remoteCall = func;
    ipi_args[0] = data1;
    ipi_args[1] = data2;
    ipi_args[2] = data3;

    /* get number of cores involved in this IPI */
    totalCoreBarrier = popcountl(mask);
}

static void handleRemoteCall(IpiModeRemoteCall_t call, word_t arg0,
                             word_t arg1, word_t arg2, bool_t irqPath)
{
    /* we gets spurious irq_remote_call_ipi calls, e.g. when handling IPI
     * in lock while hardware IPI is pending. Guard against spurious IPIs! */
    if (clh_is_ipi_pending(getCurrentCPUIndex())) {
        switch ((IpiRemoteCall_t)call) {
        case IpiRemoteCall_Stall:
            ipiStallCoreCallback(irqPath);
            break;

        case IpiRemoteCall_InvalidatePageStructureCacheASID:
            invalidateLocalPageStructureCacheASID(arg0, arg1);
            break;

        case IpiRemoteCall_InvalidateTranslationSingle:
            invalidateLocalTranslationSingle(arg0);
            break;

        case IpiRemoteCall_InvalidateTranslationSingleASID:
            invalidateLocalTranslationSingleASID(arg0, arg1);
            break;

        case IpiRemoteCall_InvalidateTranslationAll:
            invalidateLocalTranslationAll();
            break;

        case IpiRemoteCall_switchFpuOwner:
            switchLocalFpuOwner((user_fpu_state_t *)arg0);
            break;

#ifdef CONFIG_VTX
        case IpiRemoteCall_ClearCurrentVCPU:
            clearCurrentVCPU();
            break;
        case IpiRemoteCall_VMCheckBoundNotification:
            VMCheckBoundNotification((tcb_t*)arg0);
            break;
#endif
        default:
            Mode_handleRemoteCall(call, arg0, arg1, arg2);
            break;
        }

        big_kernel_lock.node_owners[getCurrentCPUIndex()].ipi = 0;
        ipi_wait(totalCoreBarrier);
    }
}

/* make sure all cpu IDs for number of core fit in bitwise word */
compile_assert(invalid_number_of_supported_nodes, CONFIG_MAX_NUM_NODES <= wordBits);

#ifdef CONFIG_USE_LOGICAL_IDS
static void x86_ipi_send_mask(interrupt_t ipi, word_t mask, bool_t isBlocking)
{
    word_t nr_target_clusters = 0;
    word_t target_clusters[CONFIG_MAX_NUM_NODES];

    do {
        int core = wordBits - 1 - clzl(mask);
        target_clusters[nr_target_clusters] = 0;

        /* get mask of all cores in bitmask which are in same cluster as 'core' */
        word_t sub_mask = mask & cpu_mapping.other_indexes_in_cluster[core];
        target_clusters[nr_target_clusters] |= cpu_mapping.index_to_logical_id[core];
        if (isBlocking) {
            big_kernel_lock.node_owners[core].ipi = 1;
        }

        /* check if there is any other core in this cluster */
        while (sub_mask) {
            int index = wordBits - 1 - clzl(sub_mask);
            target_clusters[nr_target_clusters] |= cpu_mapping.index_to_logical_id[index];
            if (isBlocking) {
                big_kernel_lock.node_owners[index].ipi = 1;
            }
            sub_mask &= ~BIT(index);
        }

        mask &= ~(cpu_mapping.other_indexes_in_cluster[core] | BIT(core));
        nr_target_clusters++;
    } while (mask != 0);

    /* broadcast IPIs to clusters... */
    IPI_ICR_BARRIER;
    for (int i = 0; i < nr_target_clusters; i++) {
        apic_send_ipi_cluster(ipi, target_clusters[i]);
    }
}
#endif /* CONFIG_USE_LOGICAL_IDS */

void ipi_send_mask(irq_t ipi, word_t mask, bool_t isBlocking)
{
    interrupt_t interrupt_ipi = ipi + IRQ_INT_OFFSET;

#ifdef CONFIG_USE_LOGICAL_IDS
    x86_ipi_send_mask(interrupt_ipi, mask, isBlocking);
#else
    generic_ipi_send_mask(interrupt_ipi, mask, isBlocking);
#endif /* CONFIG_USE_LOGICAL_IDS */
}
#endif /* ENABLE_SMP_SUPPORT */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/assert.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <assert.h>
#include <machine/io.h>

#ifdef CONFIG_DEBUG_BUILD

void _fail(
    const char*  s,
    const char*  file,
    unsigned int line,
    const char*  function)
{
    printf(
        "seL4 called fail at %s:%u in function %s, saying \"%s\"\n",
        file,
        line,
        function,
        s
    );
    halt();
}

void _assert_fail(
    const char*  assertion,
    const char*  file,
    unsigned int line,
    const char*  function)
{
    printf("seL4 failed assertion '%s' at %s:%u in function %s\n",
           assertion,
           file,
           line,
           function
          );
    halt();
}

#endif
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/benchmark/benchmark_track.c"
/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <benchmark/benchmark_track.h>
#include <model/statedata.h>

#ifdef CONFIG_BENCHMARK_TRACK_KERNEL_ENTRIES

timestamp_t ksEnter;
seL4_Word ksLogIndex;
seL4_Word ksLogIndexFinalized;

void benchmark_track_exit(void)
{
    timestamp_t duration = 0;
    timestamp_t ksExit = timestamp();
    benchmark_track_kernel_entry_t *ksLog = (benchmark_track_kernel_entry_t *) KS_LOG_PPTR;

    if (likely(ksUserLogBuffer != 0)) {
        /* If Log buffer is filled, do nothing */
        if (likely(ksLogIndex < MAX_LOG_SIZE)) {
            duration = ksExit - ksEnter;
            ksLog[ksLogIndex].entry = ksKernelEntry;
            ksLog[ksLogIndex].start_time = ksEnter;
            ksLog[ksLogIndex].duration = duration;
            ksLogIndex++;
        }
    }
}
#endif /* CONFIG_BENCHMARK_TRACK_KERNEL_ENTRIES */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/benchmark/benchmark_utilisation.c"
/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <benchmark/benchmark_utilisation.h>

#ifdef CONFIG_BENCHMARK_TRACK_UTILISATION

bool_t benchmark_log_utilisation_enabled;
timestamp_t ksEnter;
timestamp_t benchmark_start_time;
timestamp_t benchmark_end_time;

void benchmark_track_utilisation_dump(void)
{
    uint64_t *buffer = ((uint64_t *) & (((seL4_IPCBuffer *)lookupIPCBuffer(true, NODE_STATE(ksCurThread)))->msg[0]));
    tcb_t *tcb = NULL;
    word_t tcb_cptr = getRegister(NODE_STATE(ksCurThread), capRegister);
    lookupCap_ret_t lu_ret;
    word_t cap_type;

    lu_ret = lookupCap(NODE_STATE(ksCurThread), tcb_cptr);
    /* ensure we got a TCB cap */
    cap_type = cap_get_capType(lu_ret.cap);
    if (cap_type != cap_thread_cap) {
        userError("SysBenchmarkFinalizeLog: cap is not a TCB, halting");
        return;
    }

    tcb = TCB_PTR(cap_thread_cap_get_capTCBPtr(lu_ret.cap));
    buffer[BENCHMARK_TCB_UTILISATION] = tcb->benchmark.utilisation; /* Requested thread utilisation */
    buffer[BENCHMARK_IDLE_LOCALCPU_UTILISATION] = NODE_STATE(ksIdleThread)->benchmark.utilisation; /* Idle thread utilisation of current CPU */
#ifdef ENABLE_SMP_SUPPORT
    buffer[BENCHMARK_IDLE_TCBCPU_UTILISATION] = NODE_STATE_ON_CORE(ksIdleThread, tcb->tcbAffinity)->benchmark.utilisation; /* Idle thread utilisation of CPU the TCB is running on */
#else
    buffer[BENCHMARK_IDLE_TCBCPU_UTILISATION] = buffer[BENCHMARK_IDLE_LOCALCPU_UTILISATION];
#endif

#ifdef CONFIG_ARM_ENABLE_PMU_OVERFLOW_INTERRUPT
    buffer[BENCHMARK_TOTAL_UTILISATION] =
        (ccnt_num_overflows * 0xFFFFFFFFU) + benchmark_end_time - benchmark_start_time;
#else
    buffer[BENCHMARK_TOTAL_UTILISATION] = benchmark_end_time - benchmark_start_time; /* Overall time */
#endif /* CONFIG_ARM_ENABLE_PMU_OVERFLOW_INTERRUPT */

}

void benchmark_track_reset_utilisation(void)
{
    tcb_t *tcb = NULL;
    word_t tcb_cptr = getRegister(NODE_STATE(ksCurThread), capRegister);
    lookupCap_ret_t lu_ret;
    word_t cap_type;

    lu_ret = lookupCap(NODE_STATE(ksCurThread), tcb_cptr);
    /* ensure we got a TCB cap */
    cap_type = cap_get_capType(lu_ret.cap);
    if (cap_type != cap_thread_cap) {
        userError("SysBenchmarkResetThreadUtilisation: cap is not a TCB, halting");
        return;
    }

    tcb = TCB_PTR(cap_thread_cap_get_capTCBPtr(lu_ret.cap));

    tcb->benchmark.utilisation = 0;
    tcb->benchmark.schedule_start_time = 0;
}
#endif /* CONFIG_BENCHMARK_TRACK_UTILISATION */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/fastpath/fastpath.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <fastpath/fastpath.h>

#ifdef CONFIG_BENCHMARK_TRACK_KERNEL_ENTRIES
#include <benchmark/benchmark_track.h>
#endif
#include <benchmark/benchmark_utilisation.h>

void
#ifdef ARCH_X86
NORETURN
#endif
fastpath_call(word_t cptr, word_t msgInfo)
{
    seL4_MessageInfo_t info;
    cap_t ep_cap;
    endpoint_t *ep_ptr;
    word_t length;
    tcb_t *dest;
    word_t badge;
    cte_t *replySlot, *callerSlot;
    cap_t newVTable;
    vspace_root_t *cap_pd;
    pde_t stored_hw_asid;
    word_t fault_type;
    dom_t dom;

    /* Get message info, length, and fault type. */
    info = messageInfoFromWord_raw(msgInfo);
    length = seL4_MessageInfo_get_length(info);
    fault_type = seL4_Fault_get_seL4_FaultType(NODE_STATE(ksCurThread)->tcbFault);

    /* Check there's no extra caps, the length is ok and there's no
     * saved fault. */
    if (unlikely(fastpath_mi_check(msgInfo) ||
                 fault_type != seL4_Fault_NullFault)) {
        slowpath(SysCall);
    }

    /* Lookup the cap */
    ep_cap = lookup_fp(TCB_PTR_CTE_PTR(NODE_STATE(ksCurThread), tcbCTable)->cap, cptr);

    /* Check it's an endpoint */
    if (unlikely(!cap_capType_equals(ep_cap, cap_endpoint_cap) ||
                 !cap_endpoint_cap_get_capCanSend(ep_cap))) {
        slowpath(SysCall);
    }

    /* Get the endpoint address */
    ep_ptr = EP_PTR(cap_endpoint_cap_get_capEPPtr(ep_cap));

    /* Get the destination thread, which is only going to be valid
     * if the endpoint is valid. */
    dest = TCB_PTR(endpoint_ptr_get_epQueue_head(ep_ptr));

    /* Check that there's a thread waiting to receive */
    if (unlikely(endpoint_ptr_get_state(ep_ptr) != EPState_Recv)) {
        slowpath(SysCall);
    }

    /* ensure we are not single stepping the destination in ia32 */
#if defined(CONFIG_HARDWARE_DEBUG_API) && defined(CONFIG_ARCH_IA32)
    if (dest->tcbArch.tcbContext.breakpointState.single_step_enabled) {
        slowpath(SysCall);
    }
#endif

    /* Get destination thread.*/
    newVTable = TCB_PTR_CTE_PTR(dest, tcbVTable)->cap;

    /* Get vspace root. */
    cap_pd = cap_vtable_cap_get_vspace_root_fp(newVTable);

    /* Ensure that the destination has a valid VTable. */
    if (unlikely(! isValidVTableRoot_fp(newVTable))) {
        slowpath(SysCall);
    }

#ifdef CONFIG_ARCH_AARCH32
    /* Get HW ASID */
    stored_hw_asid = cap_pd[PD_ASID_SLOT];
#endif

#ifdef CONFIG_ARCH_X86_64
    /* borrow the stored_hw_asid for PCID */
    stored_hw_asid.words[0] = cap_pml4_cap_get_capPML4MappedASID_fp(newVTable);
#endif

#ifdef CONFIG_ARCH_AARCH64
    stored_hw_asid.words[0] = cap_page_global_directory_cap_get_capPGDMappedASID(newVTable);
#endif

#ifdef CONFIG_ARCH_RISCV
    /* Get HW ASID */
    stored_hw_asid.words[0] = cap_page_table_cap_get_capPTMappedASID(newVTable);
#endif

    /* let gcc optimise this out for 1 domain */
    dom = maxDom ? ksCurDomain : 0;
    /* ensure only the idle thread or lower prio threads are present in the scheduler */
    if (likely(dest->tcbPriority < NODE_STATE(ksCurThread->tcbPriority)) &&
            !isHighestPrio(dom, dest->tcbPriority)) {
        slowpath(SysCall);
    }

    /* Ensure that the endpoint has has grant rights so that we can
     * create the reply cap */
    if (unlikely(!cap_endpoint_cap_get_capCanGrant(ep_cap))) {
        slowpath(SysCall);
    }

#ifdef CONFIG_ARCH_AARCH32
    if (unlikely(!pde_pde_invalid_get_stored_asid_valid(stored_hw_asid))) {
        slowpath(SysCall);
    }
#endif

    /* Ensure the original caller is in the current domain and can be scheduled directly. */
    if (unlikely(dest->tcbDomain != ksCurDomain && maxDom)) {
        slowpath(SysCall);
    }

#ifdef ENABLE_SMP_SUPPORT
    /* Ensure both threads have the same affinity */
    if (unlikely(NODE_STATE(ksCurThread)->tcbAffinity != dest->tcbAffinity)) {
        slowpath(SysCall);
    }
#endif /* ENABLE_SMP_SUPPORT */

    /*
     * --- POINT OF NO RETURN ---
     *
     * At this stage, we have committed to performing the IPC.
     */

#ifdef CONFIG_BENCHMARK_TRACK_KERNEL_ENTRIES
    ksKernelEntry.is_fastpath = true;
#endif

    /* Dequeue the destination. */
    endpoint_ptr_set_epQueue_head_np(ep_ptr, TCB_REF(dest->tcbEPNext));
    if (unlikely(dest->tcbEPNext)) {
        dest->tcbEPNext->tcbEPPrev = NULL;
    } else {
        endpoint_ptr_mset_epQueue_tail_state(ep_ptr, 0, EPState_Idle);
    }

    badge = cap_endpoint_cap_get_capEPBadge(ep_cap);

    /* Block sender */
    thread_state_ptr_set_tsType_np(&NODE_STATE(ksCurThread)->tcbState,
                                   ThreadState_BlockedOnReply);

    /* Get sender reply slot */
    replySlot = TCB_PTR_CTE_PTR(NODE_STATE(ksCurThread), tcbReply);

    /* Get dest caller slot */
    callerSlot = TCB_PTR_CTE_PTR(dest, tcbCaller);

    /* Insert reply cap */
    cap_reply_cap_ptr_new_np(&callerSlot->cap, 0, TCB_REF(NODE_STATE(ksCurThread)));
    mdb_node_ptr_set_mdbPrev_np(&callerSlot->cteMDBNode, CTE_REF(replySlot));
    mdb_node_ptr_mset_mdbNext_mdbRevocable_mdbFirstBadged(
        &replySlot->cteMDBNode, CTE_REF(callerSlot), 1, 1);

    fastpath_copy_mrs (length, NODE_STATE(ksCurThread), dest);

    /* Dest thread is set Running, but not queued. */
    thread_state_ptr_set_tsType_np(&dest->tcbState,
                                   ThreadState_Running);
    switchToThread_fp(dest, cap_pd, stored_hw_asid);

    msgInfo = wordFromMessageInfo(seL4_MessageInfo_set_capsUnwrapped(info, 0));

    fastpath_restore(badge, msgInfo, NODE_STATE(ksCurThread));
}

void
fastpath_reply_recv(word_t cptr, word_t msgInfo)
{
    seL4_MessageInfo_t info;
    cap_t ep_cap;
    endpoint_t *ep_ptr;
    word_t length;
    cte_t *callerSlot;
    cap_t callerCap;
    tcb_t *caller;
    word_t badge;
    tcb_t *endpointTail;
    word_t fault_type;

    cap_t newVTable;
    vspace_root_t *cap_pd;
    pde_t stored_hw_asid;
    dom_t dom;

    /* Get message info and length */
    info = messageInfoFromWord_raw(msgInfo);
    length = seL4_MessageInfo_get_length(info);
    fault_type = seL4_Fault_get_seL4_FaultType(NODE_STATE(ksCurThread)->tcbFault);

    /* Check there's no extra caps, the length is ok and there's no
     * saved fault. */
    if (unlikely(fastpath_mi_check(msgInfo) ||
                 fault_type != seL4_Fault_NullFault)) {
        slowpath(SysReplyRecv);
    }

    /* Lookup the cap */
    ep_cap = lookup_fp(TCB_PTR_CTE_PTR(NODE_STATE(ksCurThread), tcbCTable)->cap,
                       cptr);

    /* Check it's an endpoint */
    if (unlikely(!cap_capType_equals(ep_cap, cap_endpoint_cap) ||
                 !cap_endpoint_cap_get_capCanReceive(ep_cap))) {
        slowpath(SysReplyRecv);
    }

    /* Check there is nothing waiting on the notification */
    if (NODE_STATE(ksCurThread)->tcbBoundNotification &&
            notification_ptr_get_state(NODE_STATE(ksCurThread)->tcbBoundNotification) == NtfnState_Active) {
        slowpath(SysReplyRecv);
    }

    /* Get the endpoint address */
    ep_ptr = EP_PTR(cap_endpoint_cap_get_capEPPtr(ep_cap));

    /* Check that there's not a thread waiting to send */
    if (unlikely(endpoint_ptr_get_state(ep_ptr) == EPState_Send)) {
        slowpath(SysReplyRecv);
    }

    /* Only reply if the reply cap is valid. */
    callerSlot = TCB_PTR_CTE_PTR(NODE_STATE(ksCurThread), tcbCaller);
    callerCap = callerSlot->cap;
    if (unlikely(!fastpath_reply_cap_check(callerCap))) {
        slowpath(SysReplyRecv);
    }

    /* Determine who the caller is. */
    caller = TCB_PTR(cap_reply_cap_get_capTCBPtr(callerCap));

    /* ensure we are not single stepping the caller in ia32 */
#if defined(CONFIG_HARDWARE_DEBUG_API) && defined(CONFIG_ARCH_IA32)
    if (caller->tcbArch.tcbContext.breakpointState.single_step_enabled) {
        slowpath(SysReplyRecv);
    }
#endif

    /* Check that the caller has not faulted, in which case a fault
       reply is generated instead. */
    fault_type = seL4_Fault_get_seL4_FaultType(caller->tcbFault);
    if (unlikely(fault_type != seL4_Fault_NullFault)) {
        slowpath(SysReplyRecv);
    }

    /* Get destination thread.*/
    newVTable = TCB_PTR_CTE_PTR(caller, tcbVTable)->cap;

    /* Get vspace root. */
    cap_pd = cap_vtable_cap_get_vspace_root_fp(newVTable);

    /* Ensure that the destination has a valid MMU. */
    if (unlikely(! isValidVTableRoot_fp (newVTable))) {
        slowpath(SysReplyRecv);
    }

#ifdef CONFIG_ARCH_AARCH32
    /* Get HWASID. */
    stored_hw_asid = cap_pd[PD_ASID_SLOT];
#endif

#ifdef CONFIG_ARCH_X86_64
    stored_hw_asid.words[0] = cap_pml4_cap_get_capPML4MappedASID(newVTable);
#endif

#ifdef CONFIG_ARCH_AARCH64
    stored_hw_asid.words[0] = cap_page_global_directory_cap_get_capPGDMappedASID(newVTable);
#endif

#ifdef CONFIG_ARCH_RISCV
    stored_hw_asid.words[0] = cap_page_table_cap_get_capPTMappedASID(newVTable);
#endif

    /* Ensure the original caller can be scheduled directly. */
    dom = maxDom ? ksCurDomain : 0;
    if (unlikely(!isHighestPrio(dom, caller->tcbPriority))) {
        slowpath(SysReplyRecv);
    }

#ifdef CONFIG_ARCH_AARCH32
    /* Ensure the HWASID is valid. */
    if (unlikely(!pde_pde_invalid_get_stored_asid_valid(stored_hw_asid))) {
        slowpath(SysReplyRecv);
    }
#endif

    /* Ensure the original caller is in the current domain and can be scheduled directly. */
    if (unlikely(caller->tcbDomain != ksCurDomain && maxDom)) {
        slowpath(SysReplyRecv);
    }

#ifdef ENABLE_SMP_SUPPORT
    /* Ensure both threads have the same affinity */
    if (unlikely(NODE_STATE(ksCurThread)->tcbAffinity != caller->tcbAffinity)) {
        slowpath(SysReplyRecv);
    }
#endif /* ENABLE_SMP_SUPPORT */

    /*
     * --- POINT OF NO RETURN ---
     *
     * At this stage, we have committed to performing the IPC.
     */

#ifdef CONFIG_BENCHMARK_TRACK_KERNEL_ENTRIES
    ksKernelEntry.is_fastpath = true;
#endif

    /* Set thread state to BlockedOnReceive */
    thread_state_ptr_mset_blockingObject_tsType(
        &NODE_STATE(ksCurThread)->tcbState, (word_t)ep_ptr, ThreadState_BlockedOnReceive);

    /* Place the thread in the endpoint queue */
    endpointTail = endpoint_ptr_get_epQueue_tail_fp(ep_ptr);
    if (likely(!endpointTail)) {
        NODE_STATE(ksCurThread)->tcbEPPrev = NULL;
        NODE_STATE(ksCurThread)->tcbEPNext = NULL;

        /* Set head/tail of queue and endpoint state. */
        endpoint_ptr_set_epQueue_head_np(ep_ptr, TCB_REF(NODE_STATE(ksCurThread)));
        endpoint_ptr_mset_epQueue_tail_state(ep_ptr, TCB_REF(NODE_STATE(ksCurThread)),
                                             EPState_Recv);
    } else {
        /* Append current thread onto the queue. */
        endpointTail->tcbEPNext = NODE_STATE(ksCurThread);
        NODE_STATE(ksCurThread)->tcbEPPrev = endpointTail;
        NODE_STATE(ksCurThread)->tcbEPNext = NULL;

        /* Update tail of queue. */
        endpoint_ptr_mset_epQueue_tail_state(ep_ptr, TCB_REF(NODE_STATE(ksCurThread)),
                                             EPState_Recv);
    }

    /* Delete the reply cap. */
    mdb_node_ptr_mset_mdbNext_mdbRevocable_mdbFirstBadged(
        &CTE_PTR(mdb_node_get_mdbPrev(callerSlot->cteMDBNode))->cteMDBNode,
        0, 1, 1);
    callerSlot->cap = cap_null_cap_new();
    callerSlot->cteMDBNode = nullMDBNode;

    /* I know there's no fault, so straight to the transfer. */

    /* Replies don't have a badge. */
    badge = 0;

    fastpath_copy_mrs (length, NODE_STATE(ksCurThread), caller);

    /* Dest thread is set Running, but not queued. */
    thread_state_ptr_set_tsType_np(&caller->tcbState,
                                   ThreadState_Running);
    switchToThread_fp(caller, cap_pd, stored_hw_asid);

    msgInfo = wordFromMessageInfo(seL4_MessageInfo_set_capsUnwrapped(info, 0));

    fastpath_restore(badge, msgInfo, NODE_STATE(ksCurThread));
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/inlines.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <types.h>
#include <api/failures.h>

lookup_fault_t current_lookup_fault;
seL4_Fault_t current_fault;
syscall_error_t current_syscall_error;
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/kernel/boot.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <assert.h>
#include <kernel/boot.h>
#include <kernel/thread.h>
#include <machine/io.h>
#include <machine/registerset.h>
#include <model/statedata.h>
#include <arch/machine.h>
#include <arch/kernel/boot.h>
#include <arch/kernel/vspace.h>
#include <linker.h>
#include <plat/machine/hardware.h>
#include <util.h>

/* (node-local) state accessed only during bootstrapping */

ndks_boot_t ndks_boot BOOT_DATA;

BOOT_CODE bool_t
insert_region(region_t reg)
{
    word_t i;

    assert(reg.start <= reg.end);
    if (is_reg_empty(reg)) {
        return true;
    }
    for (i = 0; i < MAX_NUM_FREEMEM_REG; i++) {
        if (is_reg_empty(ndks_boot.freemem[i])) {
            ndks_boot.freemem[i] = reg;
            return true;
        }
    }
    return false;
}

BOOT_CODE static inline word_t
reg_size(region_t reg)
{
    return reg.end - reg.start;
}

BOOT_CODE pptr_t
alloc_region(word_t size_bits)
{
    word_t i;
    word_t reg_index = 0; /* gcc cannot work out that this will not be used uninitialized */
    region_t reg = REG_EMPTY;
    region_t rem_small = REG_EMPTY;
    region_t rem_large = REG_EMPTY;
    region_t new_reg;
    region_t new_rem_small;
    region_t new_rem_large;

    /* Search for a freemem region that will be the best fit for an allocation. We favour allocations
     * that are aligned to either end of the region. If an allocation must split a region we favour
     * an unbalanced split. In both cases we attempt to use the smallest region possible. In general
     * this means we aim to make the size of the smallest remaining region smaller (ideally zero)
     * followed by making the size of the largest remaining region smaller */

    for (i = 0; i < MAX_NUM_FREEMEM_REG; i++) {
        /* Determine whether placing the region at the start or the end will create a bigger left over region */
        if (ROUND_UP(ndks_boot.freemem[i].start, size_bits) - ndks_boot.freemem[i].start <
                ndks_boot.freemem[i].end - ROUND_DOWN(ndks_boot.freemem[i].end, size_bits)) {
            new_reg.start = ROUND_UP(ndks_boot.freemem[i].start, size_bits);
            new_reg.end = new_reg.start + BIT(size_bits);
        } else {
            new_reg.end = ROUND_DOWN(ndks_boot.freemem[i].end, size_bits);
            new_reg.start = new_reg.end - BIT(size_bits);
        }
        if (new_reg.end > new_reg.start &&
                new_reg.start >= ndks_boot.freemem[i].start &&
                new_reg.end <= ndks_boot.freemem[i].end) {
            if (new_reg.start - ndks_boot.freemem[i].start < ndks_boot.freemem[i].end - new_reg.end) {
                new_rem_small.start = ndks_boot.freemem[i].start;
                new_rem_small.end = new_reg.start;
                new_rem_large.start = new_reg.end;
                new_rem_large.end = ndks_boot.freemem[i].end;
            } else {
                new_rem_large.start = ndks_boot.freemem[i].start;
                new_rem_large.end = new_reg.start;
                new_rem_small.start = new_reg.end;
                new_rem_small.end = ndks_boot.freemem[i].end;
            }
            if ( is_reg_empty(reg) ||
                    (reg_size(new_rem_small) < reg_size(rem_small)) ||
                    (reg_size(new_rem_small) == reg_size(rem_small) && reg_size(new_rem_large) < reg_size(rem_large)) ) {
                reg = new_reg;
                rem_small = new_rem_small;
                rem_large = new_rem_large;
                reg_index = i;
            }
        }
    }
    if (is_reg_empty(reg)) {
        printf("Kernel init failing: not enough memory\n");
        return 0;
    }
    /* Remove the region in question */
    ndks_boot.freemem[reg_index] = REG_EMPTY;
    /* Add the remaining regions in largest to smallest order */
    insert_region(rem_large);
    if (!insert_region(rem_small)) {
        printf("alloc_region(): wasted 0x%lx bytes due to alignment, try to increase MAX_NUM_FREEMEM_REG\n",
               (word_t)(rem_small.end - rem_small.start));
    }
    return reg.start;
}

BOOT_CODE void
write_slot(slot_ptr_t slot_ptr, cap_t cap)
{
    slot_ptr->cap = cap;

    slot_ptr->cteMDBNode = nullMDBNode;
    mdb_node_ptr_set_mdbRevocable  (&slot_ptr->cteMDBNode, true);
    mdb_node_ptr_set_mdbFirstBadged(&slot_ptr->cteMDBNode, true);
}

/* Our root CNode needs to be able to fit all the initial caps and not
 * cover all of memory.
 */
compile_assert(root_cnode_size_valid,
               CONFIG_ROOT_CNODE_SIZE_BITS < 32 - seL4_SlotBits &&
               (1U << CONFIG_ROOT_CNODE_SIZE_BITS) >= seL4_NumInitialCaps)

BOOT_CODE cap_t
create_root_cnode(void)
{
    pptr_t  pptr;
    cap_t   cap;

    /* write the number of root CNode slots to global state */
    ndks_boot.slot_pos_max = BIT(CONFIG_ROOT_CNODE_SIZE_BITS);

    /* create an empty root CNode */
    pptr = alloc_region(CONFIG_ROOT_CNODE_SIZE_BITS + seL4_SlotBits);
    if (!pptr) {
        printf("Kernel init failing: could not create root cnode\n");
        return cap_null_cap_new();
    }
    memzero(CTE_PTR(pptr), 1U << (CONFIG_ROOT_CNODE_SIZE_BITS + seL4_SlotBits));
    cap =
        cap_cnode_cap_new(
            CONFIG_ROOT_CNODE_SIZE_BITS,      /* radix      */
            wordBits - CONFIG_ROOT_CNODE_SIZE_BITS, /* guard size */
            0,                                /* guard      */
            pptr                              /* pptr       */
        );

    /* write the root CNode cap into the root CNode */
    write_slot(SLOT_PTR(pptr, seL4_CapInitThreadCNode), cap);

    return cap;
}

compile_assert(irq_cnode_size, BIT(IRQ_CNODE_BITS - seL4_SlotBits) > maxIRQ)

BOOT_CODE bool_t
create_irq_cnode(void)
{
    pptr_t pptr;
    /* create an empty IRQ CNode */
    pptr = alloc_region(IRQ_CNODE_BITS);
    if (!pptr) {
        printf("Kernel init failing: could not create irq cnode\n");
        return false;
    }
    memzero((void*)pptr, 1 << IRQ_CNODE_BITS);
    intStateIRQNode = (cte_t*)pptr;
    return true;
}

/* Check domain scheduler assumptions. */
compile_assert(num_domains_valid,
               CONFIG_NUM_DOMAINS >= 1 && CONFIG_NUM_DOMAINS <= 256)
compile_assert(num_priorities_valid,
               CONFIG_NUM_PRIORITIES >= 1 && CONFIG_NUM_PRIORITIES <= 256)

BOOT_CODE void
create_domain_cap(cap_t root_cnode_cap)
{
    cap_t cap;
    word_t i;

    /* Check domain scheduler assumptions. */
    assert(ksDomScheduleLength > 0);
    for (i = 0; i < ksDomScheduleLength; i++) {
        assert(ksDomSchedule[i].domain < CONFIG_NUM_DOMAINS);
        assert(ksDomSchedule[i].length > 0);
    }

    cap = cap_domain_cap_new();
    write_slot(SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapDomain), cap);
}


BOOT_CODE cap_t
create_ipcbuf_frame(cap_t root_cnode_cap, cap_t pd_cap, vptr_t vptr)
{
    cap_t cap;
    pptr_t pptr;

    /* allocate the IPC buffer frame */
    pptr = alloc_region(PAGE_BITS);
    if (!pptr) {
        printf("Kernel init failing: could not create ipc buffer frame\n");
        return cap_null_cap_new();
    }
    clearMemory((void*)pptr, PAGE_BITS);

    /* create a cap of it and write it into the root CNode */
    cap = create_mapped_it_frame_cap(pd_cap, pptr, vptr, IT_ASID, false, false);
    write_slot(SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapInitThreadIPCBuffer), cap);

    return cap;
}

BOOT_CODE void
create_bi_frame_cap(
    cap_t      root_cnode_cap,
    cap_t      pd_cap,
    pptr_t     pptr,
    vptr_t     vptr
)
{
    cap_t cap;

    /* create a cap of it and write it into the root CNode */
    cap = create_mapped_it_frame_cap(pd_cap, pptr, vptr, IT_ASID, false, false);
    write_slot(SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapBootInfoFrame), cap);
}

BOOT_CODE region_t
allocate_extra_bi_region(word_t extra_size)
{
    /* determine power of 2 size of this region. avoid calling clzl on 0 though */
    if (extra_size == 0) {
        /* return any valid address to correspond to the zero allocation */
        return (region_t) {
            0x1000, 0x1000
        };
    }
    word_t size_bits = seL4_WordBits - 1 - clzl(ROUND_UP(extra_size, seL4_PageBits));
    pptr_t pptr = alloc_region(size_bits);
    if (!pptr) {
        printf("Kernel init failed: could not allocate extra bootinfo region size bits %lu\n", size_bits);
        return REG_EMPTY;
    }

    clearMemory((void*)pptr, size_bits);
    ndks_boot.bi_frame->extraLen = BIT(size_bits);

    return (region_t) {
        pptr, pptr + BIT(size_bits)
    };
}

BOOT_CODE pptr_t
allocate_bi_frame(
    node_id_t  node_id,
    word_t   num_nodes,
    vptr_t ipcbuf_vptr
)
{
    pptr_t pptr;

    /* create the bootinfo frame object */
    pptr = alloc_region(BI_FRAME_SIZE_BITS);
    if (!pptr) {
        printf("Kernel init failed: could not allocate bootinfo frame\n");
        return 0;
    }
    clearMemory((void*)pptr, BI_FRAME_SIZE_BITS);

    /* initialise bootinfo-related global state */
    ndks_boot.bi_frame = BI_PTR(pptr);
    ndks_boot.slot_pos_cur = seL4_NumInitialCaps;

    BI_PTR(pptr)->nodeID = node_id;
    BI_PTR(pptr)->numNodes = num_nodes;
    BI_PTR(pptr)->numIOPTLevels = 0;
    BI_PTR(pptr)->ipcBuffer = (seL4_IPCBuffer *) ipcbuf_vptr;
    BI_PTR(pptr)->initThreadCNodeSizeBits = CONFIG_ROOT_CNODE_SIZE_BITS;
    BI_PTR(pptr)->initThreadDomain = ksDomSchedule[ksDomScheduleIdx].domain;
    BI_PTR(pptr)->extraLen = 0;
    BI_PTR(pptr)->extraBIPages.start = 0;
    BI_PTR(pptr)->extraBIPages.end = 0;

    return pptr;
}

BOOT_CODE bool_t
provide_cap(cap_t root_cnode_cap, cap_t cap)
{
    if (ndks_boot.slot_pos_cur >= ndks_boot.slot_pos_max) {
        printf("Kernel init failed: ran out of cap slots\n");
        return false;
    }
    write_slot(SLOT_PTR(pptr_of_cap(root_cnode_cap), ndks_boot.slot_pos_cur), cap);
    ndks_boot.slot_pos_cur++;
    return true;
}

BOOT_CODE create_frames_of_region_ret_t
create_frames_of_region(
    cap_t    root_cnode_cap,
    cap_t    pd_cap,
    region_t reg,
    bool_t   do_map,
    sword_t  pv_offset
)
{
    pptr_t     f;
    cap_t      frame_cap;
    seL4_SlotPos slot_pos_before;
    seL4_SlotPos slot_pos_after;

    slot_pos_before = ndks_boot.slot_pos_cur;

    for (f = reg.start; f < reg.end; f += BIT(PAGE_BITS)) {
        if (do_map) {
            frame_cap = create_mapped_it_frame_cap(pd_cap, f, pptr_to_paddr((void*)(f - pv_offset)), IT_ASID, false, true);
        } else {
            frame_cap = create_unmapped_it_frame_cap(f, false);
        }
        if (!provide_cap(root_cnode_cap, frame_cap))
            return (create_frames_of_region_ret_t) {
            S_REG_EMPTY, false
        };
    }

    slot_pos_after = ndks_boot.slot_pos_cur;

    return (create_frames_of_region_ret_t) {
        (seL4_SlotRegion) { slot_pos_before, slot_pos_after }, true
    };
}

BOOT_CODE cap_t
create_it_asid_pool(cap_t root_cnode_cap)
{
    pptr_t ap_pptr;
    cap_t  ap_cap;

    /* create ASID pool */
    ap_pptr = alloc_region(seL4_ASIDPoolBits);
    if (!ap_pptr) {
        printf("Kernel init failed: failed to create initial thread asid pool\n");
        return cap_null_cap_new();
    }
    memzero(ASID_POOL_PTR(ap_pptr), 1 << seL4_ASIDPoolBits);
    ap_cap = cap_asid_pool_cap_new(IT_ASID >> asidLowBits, ap_pptr);
    write_slot(SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapInitThreadASIDPool), ap_cap);

    /* create ASID control cap */
    write_slot(
        SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapASIDControl),
        cap_asid_control_cap_new()
    );

    return ap_cap;
}

BOOT_CODE bool_t
create_idle_thread(void)
{
    pptr_t pptr;

#ifdef ENABLE_SMP_SUPPORT
    for (int i = 0; i < CONFIG_MAX_NUM_NODES; i++) {
#endif /* ENABLE_SMP_SUPPORT */
        pptr = alloc_region(seL4_TCBBits);
        if (!pptr) {
            printf("Kernel init failed: Unable to allocate tcb for idle thread\n");
            return false;
        }
        memzero((void *)pptr, 1 << seL4_TCBBits);
        NODE_STATE_ON_CORE(ksIdleThread, i) = TCB_PTR(pptr + TCB_OFFSET);
        configureIdleThread(NODE_STATE_ON_CORE(ksIdleThread, i));
#ifdef CONFIG_DEBUG_BUILD
        setThreadName(NODE_STATE_ON_CORE(ksIdleThread, i), "idle_thread");
#endif
        SMP_COND_STATEMENT(NODE_STATE_ON_CORE(ksIdleThread, i)->tcbAffinity = i);
#ifdef ENABLE_SMP_SUPPORT
    }
#endif /* ENABLE_SMP_SUPPORT */
    return true;
}

BOOT_CODE tcb_t *
create_initial_thread(
    cap_t  root_cnode_cap,
    cap_t  it_pd_cap,
    vptr_t ui_v_entry,
    vptr_t bi_frame_vptr,
    vptr_t ipcbuf_vptr,
    cap_t  ipcbuf_cap
)
{
    pptr_t pptr;
    cap_t  cap;
    tcb_t* tcb;
    deriveCap_ret_t dc_ret;

    /* allocate TCB */
    pptr = alloc_region(seL4_TCBBits);
    if (!pptr) {
        printf("Kernel init failed: Unable to allocate tcb for initial thread\n");
        return NULL;
    }
    memzero((void*)pptr, 1 << seL4_TCBBits);
    tcb = TCB_PTR(pptr + TCB_OFFSET);
    tcb->tcbTimeSlice = CONFIG_TIME_SLICE;
    Arch_initContext(&tcb->tcbArch.tcbContext);

    /* derive a copy of the IPC buffer cap for inserting */
    dc_ret = deriveCap(SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapInitThreadIPCBuffer), ipcbuf_cap);
    if (dc_ret.status != EXCEPTION_NONE) {
        printf("Failed to derive copy of IPC Buffer\n");
        return NULL;
    }

    /* initialise TCB (corresponds directly to abstract specification) */
    cteInsert(
        root_cnode_cap,
        SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapInitThreadCNode),
        SLOT_PTR(pptr, tcbCTable)
    );
    cteInsert(
        it_pd_cap,
        SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapInitThreadVSpace),
        SLOT_PTR(pptr, tcbVTable)
    );
    cteInsert(
        dc_ret.cap,
        SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapInitThreadIPCBuffer),
        SLOT_PTR(pptr, tcbBuffer)
    );
    tcb->tcbIPCBuffer = ipcbuf_vptr;

    /* Set the root thread's IPC buffer */
    Arch_setTCBIPCBuffer(tcb, ipcbuf_vptr);

    setRegister(tcb, capRegister, bi_frame_vptr);
    setNextPC(tcb, ui_v_entry);

    /* initialise TCB */
    tcb->tcbPriority = seL4_MaxPrio;
    tcb->tcbMCP = seL4_MaxPrio;
    setupReplyMaster(tcb);
    setThreadState(tcb, ThreadState_Running);

    ksCurDomain = ksDomSchedule[ksDomScheduleIdx].domain;
    ksDomainTime = ksDomSchedule[ksDomScheduleIdx].length;
    assert(ksCurDomain < CONFIG_NUM_DOMAINS && ksDomainTime > 0);

    SMP_COND_STATEMENT(tcb->tcbAffinity = 0);

    /* create initial thread's TCB cap */
    cap = cap_thread_cap_new(TCB_REF(tcb));
    write_slot(SLOT_PTR(pptr_of_cap(root_cnode_cap), seL4_CapInitThreadTCB), cap);

#ifdef CONFIG_DEBUG_BUILD
    setThreadName(tcb, "rootserver");
#endif

    return tcb;
}

BOOT_CODE void
init_core_state(tcb_t *scheduler_action)
{
#ifdef CONFIG_HAVE_FPU
    NODE_STATE(ksActiveFPUState) = NULL;
#endif
#ifdef CONFIG_DEBUG_BUILD
    /* add initial threads to the debug queue */
    NODE_STATE(ksDebugTCBs) = NULL;
    if (scheduler_action != SchedulerAction_ResumeCurrentThread &&
            scheduler_action != SchedulerAction_ChooseNewThread) {
        tcbDebugAppend(scheduler_action);
    }
    tcbDebugAppend(NODE_STATE(ksIdleThread));
#endif
    NODE_STATE(ksSchedulerAction) = scheduler_action;
    NODE_STATE(ksCurThread) = NODE_STATE(ksIdleThread);
}

BOOT_CODE static bool_t
provide_untyped_cap(
    cap_t      root_cnode_cap,
    bool_t     device_memory,
    pptr_t     pptr,
    word_t     size_bits,
    seL4_SlotPos first_untyped_slot
)
{
    bool_t ret;
    cap_t ut_cap;
    word_t i = ndks_boot.slot_pos_cur - first_untyped_slot;
    if (i < CONFIG_MAX_NUM_BOOTINFO_UNTYPED_CAPS) {
        ndks_boot.bi_frame->untypedList[i] = (seL4_UntypedDesc) {
            pptr_to_paddr((void*)pptr), 0, 0, size_bits, device_memory
        };
        ut_cap = cap_untyped_cap_new(MAX_FREE_INDEX(size_bits),
                                     device_memory, size_bits, pptr);
        ret = provide_cap(root_cnode_cap, ut_cap);
    } else {
        printf("Kernel init: Too many untyped regions for boot info\n");
        ret = true;
    }
    return ret;
}

BOOT_CODE bool_t
create_untypeds_for_region(
    cap_t      root_cnode_cap,
    bool_t     device_memory,
    region_t   reg,
    seL4_SlotPos first_untyped_slot
)
{
    word_t align_bits;
    word_t size_bits;

    while (!is_reg_empty(reg)) {
        /* Determine the maximum size of the region */
        size_bits = seL4_WordBits - 1 - clzl(reg.end - reg.start);

        /* Determine the alignment of the region */
        if (reg.start != 0) {
            align_bits = ctzl(reg.start);
        } else {
            align_bits = size_bits;
        }
        /* Reduce size bits to align if needed */
        if (align_bits < size_bits) {
            size_bits = align_bits;
        }
        if (size_bits > seL4_MaxUntypedBits) {
            size_bits = seL4_MaxUntypedBits;
        }

        if (size_bits >= seL4_MinUntypedBits) {
            if (!provide_untyped_cap(root_cnode_cap, device_memory, reg.start, size_bits, first_untyped_slot)) {
                return false;
            }
        }
        reg.start += BIT(size_bits);
    }
    return true;
}

BOOT_CODE bool_t
create_kernel_untypeds(cap_t root_cnode_cap, region_t boot_mem_reuse_reg, seL4_SlotPos first_untyped_slot)
{
    word_t     i;
    region_t   reg;

    /* if boot_mem_reuse_reg is not empty, we can create UT objs from boot code/data frames */
    if (!create_untypeds_for_region(root_cnode_cap, false, boot_mem_reuse_reg, first_untyped_slot)) {
        return false;
    }

    /* convert remaining freemem into UT objects and provide the caps */
    for (i = 0; i < MAX_NUM_FREEMEM_REG; i++) {
        reg = ndks_boot.freemem[i];
        ndks_boot.freemem[i] = REG_EMPTY;
        if (!create_untypeds_for_region(root_cnode_cap, false, reg, first_untyped_slot)) {
            return false;
        }
    }

    return true;
}

BOOT_CODE void
bi_finalise(void)
{
    seL4_SlotPos slot_pos_start = ndks_boot.slot_pos_cur;
    seL4_SlotPos slot_pos_end = ndks_boot.slot_pos_max;
    ndks_boot.bi_frame->empty = (seL4_SlotRegion) {
        slot_pos_start, slot_pos_end
    };
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/kernel/cspace.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <types.h>
#include <object.h>
#include <api/failures.h>
#include <kernel/thread.h>
#include <kernel/cspace.h>
#include <model/statedata.h>
#include <arch/machine.h>

lookupCap_ret_t
lookupCap(tcb_t *thread, cptr_t cPtr)
{
    lookupSlot_raw_ret_t lu_ret;
    lookupCap_ret_t ret;

    lu_ret = lookupSlot(thread, cPtr);
    if (unlikely(lu_ret.status != EXCEPTION_NONE)) {
        ret.status = lu_ret.status;
        ret.cap = cap_null_cap_new();
        return ret;
    }

    ret.status = EXCEPTION_NONE;
    ret.cap = lu_ret.slot->cap;
    return ret;
}

lookupCapAndSlot_ret_t
lookupCapAndSlot(tcb_t *thread, cptr_t cPtr)
{
    lookupSlot_raw_ret_t lu_ret;
    lookupCapAndSlot_ret_t ret;

    lu_ret = lookupSlot(thread, cPtr);
    if (unlikely(lu_ret.status != EXCEPTION_NONE)) {
        ret.status = lu_ret.status;
        ret.slot = NULL;
        ret.cap = cap_null_cap_new();
        return ret;
    }

    ret.status = EXCEPTION_NONE;
    ret.slot = lu_ret.slot;
    ret.cap = lu_ret.slot->cap;
    return ret;
}

lookupSlot_raw_ret_t
lookupSlot(tcb_t *thread, cptr_t capptr)
{
    cap_t threadRoot;
    resolveAddressBits_ret_t res_ret;
    lookupSlot_raw_ret_t ret;

    threadRoot = TCB_PTR_CTE_PTR(thread, tcbCTable)->cap;
    res_ret = resolveAddressBits(threadRoot, capptr, wordBits);

    ret.status = res_ret.status;
    ret.slot = res_ret.slot;
    return ret;
}

lookupSlot_ret_t
lookupSlotForCNodeOp(bool_t isSource, cap_t root, cptr_t capptr,
                     word_t depth)
{
    resolveAddressBits_ret_t res_ret;
    lookupSlot_ret_t ret;

    ret.slot = NULL;

    if (unlikely(cap_get_capType(root) != cap_cnode_cap)) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = isSource;
        current_lookup_fault = lookup_fault_invalid_root_new();
        ret.status = EXCEPTION_SYSCALL_ERROR;
        return ret;
    }

    if (unlikely(depth < 1 || depth > wordBits)) {
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 1;
        current_syscall_error.rangeErrorMax = wordBits;
        ret.status = EXCEPTION_SYSCALL_ERROR;
        return ret;
    }
    res_ret = resolveAddressBits(root, capptr, depth);
    if (unlikely(res_ret.status != EXCEPTION_NONE)) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = isSource;
        /* current_lookup_fault will have been set by resolveAddressBits */
        ret.status = EXCEPTION_SYSCALL_ERROR;
        return ret;
    }

    if (unlikely(res_ret.bitsRemaining != 0)) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = isSource;
        current_lookup_fault =
            lookup_fault_depth_mismatch_new(0, res_ret.bitsRemaining);
        ret.status = EXCEPTION_SYSCALL_ERROR;
        return ret;
    }

    ret.slot = res_ret.slot;
    ret.status = EXCEPTION_NONE;
    return ret;
}

lookupSlot_ret_t
lookupSourceSlot(cap_t root, cptr_t capptr, word_t depth)
{
    return lookupSlotForCNodeOp(true, root, capptr, depth);
}

lookupSlot_ret_t
lookupTargetSlot(cap_t root, cptr_t capptr, word_t depth)
{
    return lookupSlotForCNodeOp(false, root, capptr, depth);
}

lookupSlot_ret_t
lookupPivotSlot(cap_t root, cptr_t capptr, word_t depth)
{
    return lookupSlotForCNodeOp(true, root, capptr, depth);
}

resolveAddressBits_ret_t
resolveAddressBits(cap_t nodeCap, cptr_t capptr, word_t n_bits)
{
    resolveAddressBits_ret_t ret;
    word_t radixBits, guardBits, levelBits, guard;
    word_t capGuard, offset;
    cte_t *slot;

    ret.bitsRemaining = n_bits;
    ret.slot = NULL;

    if (unlikely(cap_get_capType(nodeCap) != cap_cnode_cap)) {
        current_lookup_fault = lookup_fault_invalid_root_new();
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }

    while (1) {
        radixBits = cap_cnode_cap_get_capCNodeRadix(nodeCap);
        guardBits = cap_cnode_cap_get_capCNodeGuardSize(nodeCap);
        levelBits = radixBits + guardBits;

        /* Haskell error: "All CNodes must resolve bits" */
        assert(levelBits != 0);

        capGuard = cap_cnode_cap_get_capCNodeGuard(nodeCap);

        /* sjw --- the MASK(5) here is to avoid the case where n_bits = 32
           and guardBits = 0, as it violates the C spec to >> by more
           than 31 */

        guard = (capptr >> ((n_bits - guardBits) & MASK(wordRadix))) & MASK(guardBits);
        if (unlikely(guardBits > n_bits || guard != capGuard)) {
            current_lookup_fault =
                lookup_fault_guard_mismatch_new(capGuard, n_bits, guardBits);
            ret.status = EXCEPTION_LOOKUP_FAULT;
            return ret;
        }

        if (unlikely(levelBits > n_bits)) {
            current_lookup_fault =
                lookup_fault_depth_mismatch_new(levelBits, n_bits);
            ret.status = EXCEPTION_LOOKUP_FAULT;
            return ret;
        }

        offset = (capptr >> (n_bits - levelBits)) & MASK(radixBits);
        slot = CTE_PTR(cap_cnode_cap_get_capCNodePtr(nodeCap)) + offset;

        if (likely(n_bits <= levelBits)) {
            ret.status = EXCEPTION_NONE;
            ret.slot = slot;
            ret.bitsRemaining = 0;
            return ret;
        }

        /** GHOSTUPD: "(\<acute>levelBits > 0, id)" */

        n_bits -= levelBits;
        nodeCap = slot->cap;

        if (unlikely(cap_get_capType(nodeCap) != cap_cnode_cap)) {
            ret.status = EXCEPTION_NONE;
            ret.slot = slot;
            ret.bitsRemaining = n_bits;
            return ret;
        }
    }

    ret.status = EXCEPTION_NONE;
    return ret;
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/kernel/faulthandler.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <api/failures.h>
#include <kernel/cspace.h>
#include <kernel/faulthandler.h>
#include <kernel/thread.h>
#include <machine/io.h>
#include <arch/machine.h>

void
handleFault(tcb_t *tptr)
{
    exception_t status;
    seL4_Fault_t fault = current_fault;

    status = sendFaultIPC(tptr);
    if (status != EXCEPTION_NONE) {
        handleDoubleFault(tptr, fault);
    }
}

exception_t
sendFaultIPC(tcb_t *tptr)
{
    cptr_t handlerCPtr;
    cap_t  handlerCap;
    lookupCap_ret_t lu_ret;
    lookup_fault_t original_lookup_fault;

    original_lookup_fault = current_lookup_fault;

    handlerCPtr = tptr->tcbFaultHandler;
    lu_ret = lookupCap(tptr, handlerCPtr);
    if (lu_ret.status != EXCEPTION_NONE) {
        current_fault = seL4_Fault_CapFault_new(handlerCPtr, false);
        return EXCEPTION_FAULT;
    }
    handlerCap = lu_ret.cap;

    if (cap_get_capType(handlerCap) == cap_endpoint_cap &&
            cap_endpoint_cap_get_capCanSend(handlerCap) &&
            cap_endpoint_cap_get_capCanGrant(handlerCap)) {
        tptr->tcbFault = current_fault;
        if (seL4_Fault_get_seL4_FaultType(current_fault) == seL4_Fault_CapFault) {
            tptr->tcbLookupFailure = original_lookup_fault;
        }
        sendIPC(true, false,
                cap_endpoint_cap_get_capEPBadge(handlerCap),
                true, tptr,
                EP_PTR(cap_endpoint_cap_get_capEPPtr(handlerCap)));

        return EXCEPTION_NONE;
    } else {
        current_fault = seL4_Fault_CapFault_new(handlerCPtr, false);
        current_lookup_fault = lookup_fault_missing_capability_new(0);

        return EXCEPTION_FAULT;
    }
}

#ifdef CONFIG_PRINTING
static void
print_fault(seL4_Fault_t f)
{
    switch (seL4_Fault_get_seL4_FaultType(f)) {
    case seL4_Fault_NullFault:
        printf("null fault");
        break;
    case seL4_Fault_CapFault:
        printf("cap fault in %s phase at address %p",
               seL4_Fault_CapFault_get_inReceivePhase(f) ? "receive" : "send",
               (void *)seL4_Fault_CapFault_get_address(f));
        break;
    case seL4_Fault_VMFault:
        printf("vm fault on %s at address %p with status %p",
               seL4_Fault_VMFault_get_instructionFault(f) ? "code" : "data",
               (void *)seL4_Fault_VMFault_get_address(f),
               (void *)seL4_Fault_VMFault_get_FSR(f));
        break;
    case seL4_Fault_UnknownSyscall:
        printf("unknown syscall %p",
               (void *)seL4_Fault_UnknownSyscall_get_syscallNumber(f));
        break;
    case seL4_Fault_UserException:
        printf("user exception %p code %p",
               (void *)seL4_Fault_UserException_get_number(f),
               (void *)seL4_Fault_UserException_get_code(f));
        break;
    default:
        printf("unknown fault");
        break;
    }
}
#endif

/* The second fault, ex2, is stored in the global current_fault */
void
handleDoubleFault(tcb_t *tptr, seL4_Fault_t ex1)
{
#ifdef CONFIG_PRINTING
    seL4_Fault_t ex2 = current_fault;
    printf("Caught ");
    print_fault(ex2);
    printf("\nwhile trying to handle:\n");
    print_fault(ex1);

#ifdef CONFIG_DEBUG_BUILD
    printf("\nin thread %p \"%s\" ", tptr, tptr->tcbName);
#endif /* CONFIG_DEBUG_BUILD */

    printf("at address %p\n", (void*)getRestartPC(tptr));
    printf("With stack:\n");
    Arch_userStackTrace(tptr);
#endif

    setThreadState(tptr, ThreadState_Inactive);
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/kernel/stack.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */
#include <kernel/stack.h>

VISIBLE ALIGN(KERNEL_STACK_ALIGNMENT)
char kernel_stack_alloc[CONFIG_MAX_NUM_NODES][BIT(CONFIG_KERNEL_STACK_BITS)];
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/kernel/thread.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <object.h>
#include <util.h>
#include <api/faults.h>
#include <api/types.h>
#include <kernel/cspace.h>
#include <kernel/thread.h>
#include <kernel/vspace.h>
#include <model/statedata.h>
#include <arch/machine.h>
#include <arch/kernel/thread.h>
#include <machine/registerset.h>
#include <linker.h>

static seL4_MessageInfo_t
transferCaps(seL4_MessageInfo_t info, extra_caps_t caps,
             endpoint_t *endpoint, tcb_t *receiver,
             word_t *receiveBuffer);

static inline bool_t PURE
isBlocked(const tcb_t *thread)
{
    switch (thread_state_get_tsType(thread->tcbState)) {
    case ThreadState_Inactive:
    case ThreadState_BlockedOnReceive:
    case ThreadState_BlockedOnSend:
    case ThreadState_BlockedOnNotification:
    case ThreadState_BlockedOnReply:
        return true;

    default:
        return false;
    }
}

BOOT_CODE void
configureIdleThread(tcb_t *tcb)
{
    Arch_configureIdleThread(tcb);
    setThreadState(tcb, ThreadState_IdleThreadState);
}

void
activateThread(void)
{
    switch (thread_state_get_tsType(NODE_STATE(ksCurThread)->tcbState)) {
    case ThreadState_Running:
#ifdef CONFIG_VTX
    case ThreadState_RunningVM:
#endif
        break;

    case ThreadState_Restart: {
        word_t pc;

        pc = getRestartPC(NODE_STATE(ksCurThread));
        setNextPC(NODE_STATE(ksCurThread), pc);
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Running);
        break;
    }

    case ThreadState_IdleThreadState:
        Arch_activateIdleThread(NODE_STATE(ksCurThread));
        break;

    default:
        fail("Current thread is blocked");
    }
}

void
suspend(tcb_t *target)
{
    cancelIPC(target);
    setThreadState(target, ThreadState_Inactive);
    tcbSchedDequeue(target);
}

void
restart(tcb_t *target)
{
    if (isBlocked(target)) {
        cancelIPC(target);
        setupReplyMaster(target);
        setThreadState(target, ThreadState_Restart);
        SCHED_ENQUEUE(target);
        possibleSwitchTo(target);
    }
}

void
doIPCTransfer(tcb_t *sender, endpoint_t *endpoint, word_t badge,
              bool_t grant, tcb_t *receiver)
{
    void *receiveBuffer, *sendBuffer;

    receiveBuffer = lookupIPCBuffer(true, receiver);

    if (likely(seL4_Fault_get_seL4_FaultType(sender->tcbFault) == seL4_Fault_NullFault)) {
        sendBuffer = lookupIPCBuffer(false, sender);
        doNormalTransfer(sender, sendBuffer, endpoint, badge, grant,
                         receiver, receiveBuffer);
    } else {
        doFaultTransfer(badge, sender, receiver, receiveBuffer);
    }
}

void
doReplyTransfer(tcb_t *sender, tcb_t *receiver, cte_t *slot)
{
    assert(thread_state_get_tsType(receiver->tcbState) ==
           ThreadState_BlockedOnReply);

    if (likely(seL4_Fault_get_seL4_FaultType(receiver->tcbFault) == seL4_Fault_NullFault)) {
        doIPCTransfer(sender, NULL, 0, true, receiver);
        /** GHOSTUPD: "(True, gs_set_assn cteDeleteOne_'proc (ucast cap_reply_cap))" */
        cteDeleteOne(slot);
        setThreadState(receiver, ThreadState_Running);
        possibleSwitchTo(receiver);
    } else {
        bool_t restart;

        /** GHOSTUPD: "(True, gs_set_assn cteDeleteOne_'proc (ucast cap_reply_cap))" */
        cteDeleteOne(slot);
        restart = handleFaultReply(receiver, sender);
        receiver->tcbFault = seL4_Fault_NullFault_new();
        if (restart) {
            setThreadState(receiver, ThreadState_Restart);
            possibleSwitchTo(receiver);
        } else {
            setThreadState(receiver, ThreadState_Inactive);
        }
    }
}

void
doNormalTransfer(tcb_t *sender, word_t *sendBuffer, endpoint_t *endpoint,
                 word_t badge, bool_t canGrant, tcb_t *receiver,
                 word_t *receiveBuffer)
{
    word_t msgTransferred;
    seL4_MessageInfo_t tag;
    exception_t status;
    extra_caps_t caps;

    tag = messageInfoFromWord(getRegister(sender, msgInfoRegister));

    if (canGrant) {
        status = lookupExtraCaps(sender, sendBuffer, tag);
        caps = current_extra_caps;
        if (unlikely(status != EXCEPTION_NONE)) {
            caps.excaprefs[0] = NULL;
        }
    } else {
        caps = current_extra_caps;
        caps.excaprefs[0] = NULL;
    }

    msgTransferred = copyMRs(sender, sendBuffer, receiver, receiveBuffer,
                             seL4_MessageInfo_get_length(tag));

    tag = transferCaps(tag, caps, endpoint, receiver, receiveBuffer);

    tag = seL4_MessageInfo_set_length(tag, msgTransferred);
    setRegister(receiver, msgInfoRegister, wordFromMessageInfo(tag));
    setRegister(receiver, badgeRegister, badge);
}

void
doFaultTransfer(word_t badge, tcb_t *sender, tcb_t *receiver,
                word_t *receiverIPCBuffer)
{
    word_t sent;
    seL4_MessageInfo_t msgInfo;

    sent = setMRs_fault(sender, receiver, receiverIPCBuffer);
    msgInfo = seL4_MessageInfo_new(
                  seL4_Fault_get_seL4_FaultType(sender->tcbFault), 0, 0, sent);
    setRegister(receiver, msgInfoRegister, wordFromMessageInfo(msgInfo));
    setRegister(receiver, badgeRegister, badge);
}

/* Like getReceiveSlots, this is specialised for single-cap transfer. */
static seL4_MessageInfo_t
transferCaps(seL4_MessageInfo_t info, extra_caps_t caps,
             endpoint_t *endpoint, tcb_t *receiver,
             word_t *receiveBuffer)
{
    word_t i;
    cte_t* destSlot;

    info = seL4_MessageInfo_set_extraCaps(info, 0);
    info = seL4_MessageInfo_set_capsUnwrapped(info, 0);

    if (likely(!caps.excaprefs[0] || !receiveBuffer)) {
        return info;
    }

    destSlot = getReceiveSlots(receiver, receiveBuffer);

    for (i = 0; i < seL4_MsgMaxExtraCaps && caps.excaprefs[i] != NULL; i++) {
        cte_t *slot = caps.excaprefs[i];
        cap_t cap = slot->cap;

        if (cap_get_capType(cap) == cap_endpoint_cap &&
                EP_PTR(cap_endpoint_cap_get_capEPPtr(cap)) == endpoint) {
            /* If this is a cap to the endpoint on which the message was sent,
             * only transfer the badge, not the cap. */
            setExtraBadge(receiveBuffer,
                          cap_endpoint_cap_get_capEPBadge(cap), i);

            info = seL4_MessageInfo_set_capsUnwrapped(info,
                                                      seL4_MessageInfo_get_capsUnwrapped(info) | (1 << i));

        } else {
            deriveCap_ret_t dc_ret;

            if (!destSlot) {
                break;
            }

            dc_ret = deriveCap(slot, cap);

            if (dc_ret.status != EXCEPTION_NONE) {
                break;
            }
            if (cap_get_capType(dc_ret.cap) == cap_null_cap) {
                break;
            }

            cteInsert(dc_ret.cap, slot, destSlot);

            destSlot = NULL;
        }
    }

    return seL4_MessageInfo_set_extraCaps(info, i);
}

void doNBRecvFailedTransfer(tcb_t *thread)
{
    /* Set the badge register to 0 to indicate there was no message */
    setRegister(thread, badgeRegister, 0);
}

static void
nextDomain(void)
{
    ksDomScheduleIdx++;
    if (ksDomScheduleIdx >= ksDomScheduleLength) {
        ksDomScheduleIdx = 0;
    }
    ksWorkUnitsCompleted = 0;
    ksCurDomain = ksDomSchedule[ksDomScheduleIdx].domain;
    ksDomainTime = ksDomSchedule[ksDomScheduleIdx].length;
}

static void
scheduleChooseNewThread(void)
{
    if (ksDomainTime == 0) {
        nextDomain();
    }
    chooseThread();
}

void
schedule(void)
{
    if (NODE_STATE(ksSchedulerAction) != SchedulerAction_ResumeCurrentThread) {
        bool_t was_runnable;
        if (isRunnable(NODE_STATE(ksCurThread))) {
            was_runnable = true;
            SCHED_ENQUEUE_CURRENT_TCB;
        } else {
            was_runnable = false;
        }

        if (NODE_STATE(ksSchedulerAction) == SchedulerAction_ChooseNewThread) {
            scheduleChooseNewThread();
        } else {
            tcb_t *candidate = NODE_STATE(ksSchedulerAction);
            /* Avoid checking bitmap when ksCurThread is higher prio, to
             * match fast path.
             * Don't look at ksCurThread prio when it's idle, to respect
             * information flow in non-fastpath cases. */
            bool_t fastfail =
                NODE_STATE(ksCurThread) == NODE_STATE(ksIdleThread)
                || (candidate->tcbPriority < NODE_STATE(ksCurThread)->tcbPriority);
            if (fastfail &&
                    !isHighestPrio(ksCurDomain, candidate->tcbPriority)) {
                SCHED_ENQUEUE(candidate);
                /* we can't, need to reschedule */
                NODE_STATE(ksSchedulerAction) = SchedulerAction_ChooseNewThread;
                scheduleChooseNewThread();
            } else if (was_runnable && candidate->tcbPriority == NODE_STATE(ksCurThread)->tcbPriority) {
                /* We append the candidate at the end of the scheduling queue, that way the
                 * current thread, that was enqueued at the start of the scheduling queue
                 * will get picked during chooseNewThread */
                SCHED_APPEND(candidate);
                NODE_STATE(ksSchedulerAction) = SchedulerAction_ChooseNewThread;
                scheduleChooseNewThread();
            } else {
                assert(candidate != NODE_STATE(ksCurThread));
                switchToThread(candidate);
            }
        }
    }
    NODE_STATE(ksSchedulerAction) = SchedulerAction_ResumeCurrentThread;
#ifdef ENABLE_SMP_SUPPORT
    doMaskReschedule(ARCH_NODE_STATE(ipiReschedulePending));
    ARCH_NODE_STATE(ipiReschedulePending) = 0;
#endif /* ENABLE_SMP_SUPPORT */
}

void
chooseThread(void)
{
    word_t prio;
    word_t dom;
    tcb_t *thread;

    if (CONFIG_NUM_DOMAINS > 1) {
        dom = ksCurDomain;
    } else {
        dom = 0;
    }

    if (likely(NODE_STATE(ksReadyQueuesL1Bitmap[dom]))) {
        prio = getHighestPrio(dom);
        thread = NODE_STATE(ksReadyQueues)[ready_queues_index(dom, prio)].head;
        assert(thread);
        assert(isRunnable(thread));
        switchToThread(thread);
    } else {
        switchToIdleThread();
    }
}

void
switchToThread(tcb_t *thread)
{
#ifdef CONFIG_BENCHMARK_TRACK_UTILISATION
    benchmark_utilisation_switch(NODE_STATE(ksCurThread), thread);
#endif
    Arch_switchToThread(thread);
    tcbSchedDequeue(thread);
    NODE_STATE(ksCurThread) = thread;
}

void
switchToIdleThread(void)
{
#ifdef CONFIG_BENCHMARK_TRACK_UTILISATION
    benchmark_utilisation_switch(NODE_STATE(ksCurThread), NODE_STATE(ksIdleThread));
#endif
    Arch_switchToIdleThread();
    NODE_STATE(ksCurThread) = NODE_STATE(ksIdleThread);
}

void
setDomain(tcb_t *tptr, dom_t dom)
{
    tcbSchedDequeue(tptr);
    tptr->tcbDomain = dom;
    if (isRunnable(tptr)) {
        SCHED_ENQUEUE(tptr);
    }
    if (tptr == NODE_STATE(ksCurThread)) {
        rescheduleRequired();
    }
}

void
setMCPriority(tcb_t *tptr, prio_t mcp)
{
    tptr->tcbMCP = mcp;
}

void
setPriority(tcb_t *tptr, prio_t prio)
{
    tcbSchedDequeue(tptr);
    tptr->tcbPriority = prio;
    if (isRunnable(tptr)) {
        SCHED_ENQUEUE(tptr);
        rescheduleRequired();
    }
}

/* Note that this thread will possibly continue at the end of this kernel
 * entry. Do not queue it yet, since a queue+unqueue operation is wasteful
 * if it will be picked. Instead, it waits in the 'ksSchedulerAction' site
 * on which the scheduler will take action. */
void
possibleSwitchTo(tcb_t* target)
{
    if (ksCurDomain != target->tcbDomain
            SMP_COND_STATEMENT( || target->tcbAffinity != getCurrentCPUIndex())) {
        SCHED_ENQUEUE(target);
    } else if (NODE_STATE(ksSchedulerAction) != SchedulerAction_ResumeCurrentThread) {
        /* Too many threads want special treatment, use regular queues. */
        rescheduleRequired();
        SCHED_ENQUEUE(target);
    } else {
        NODE_STATE(ksSchedulerAction) = target;
    }
}

void
setThreadState(tcb_t *tptr, _thread_state_t ts)
{
    thread_state_ptr_set_tsType(&tptr->tcbState, ts);
    scheduleTCB(tptr);
}

void
scheduleTCB(tcb_t *tptr)
{
    if (tptr == NODE_STATE(ksCurThread) &&
            NODE_STATE(ksSchedulerAction) == SchedulerAction_ResumeCurrentThread &&
            !isRunnable(tptr)) {
        rescheduleRequired();
    }
}

void
timerTick(void)
{
    if (likely(thread_state_get_tsType(NODE_STATE(ksCurThread)->tcbState) ==
               ThreadState_Running)
#ifdef CONFIG_VTX
            || thread_state_get_tsType(NODE_STATE(ksCurThread)->tcbState) ==
            ThreadState_RunningVM
#endif
       ) {
        if (NODE_STATE(ksCurThread)->tcbTimeSlice > 1) {
            NODE_STATE(ksCurThread)->tcbTimeSlice--;
        } else {
            NODE_STATE(ksCurThread)->tcbTimeSlice = CONFIG_TIME_SLICE;
            SCHED_APPEND_CURRENT_TCB;
            rescheduleRequired();
        }
    }

    if (CONFIG_NUM_DOMAINS > 1) {
        ksDomainTime--;
        if (ksDomainTime == 0) {
            rescheduleRequired();
        }
    }
}

void
rescheduleRequired(void)
{
    if (NODE_STATE(ksSchedulerAction) != SchedulerAction_ResumeCurrentThread
            && NODE_STATE(ksSchedulerAction) != SchedulerAction_ChooseNewThread) {
        SCHED_ENQUEUE(NODE_STATE(ksSchedulerAction));
    }
    NODE_STATE(ksSchedulerAction) = SchedulerAction_ChooseNewThread;
}

#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/machine/fpu.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <machine/fpu.h>
#include <api/failures.h>
#include <model/statedata.h>
#include <arch/object/structures.h>

#ifdef CONFIG_HAVE_FPU
/* Switch the owner of the FPU to the given thread on local core. */
void switchLocalFpuOwner(user_fpu_state_t *new_owner)
{
    enableFpu();
    if (NODE_STATE(ksActiveFPUState)) {
        saveFpuState(NODE_STATE(ksActiveFPUState));
    }
    if (new_owner) {
        NODE_STATE(ksFPURestoresSinceSwitch) = 0;
        loadFpuState(new_owner);
    } else {
        disableFpu();
    }
    NODE_STATE(ksActiveFPUState) = new_owner;
}

void switchFpuOwner(user_fpu_state_t *new_owner, word_t cpu)
{
#ifdef ENABLE_SMP_SUPPORT
    if (cpu != getCurrentCPUIndex()) {
        doRemoteswitchFpuOwner(new_owner, cpu);
    } else
#endif /* ENABLE_SMP_SUPPORT */
    {
        switchLocalFpuOwner(new_owner);
    }
}

/* Handle an FPU fault.
 *
 * This CPU exception is thrown when userspace attempts to use the FPU while
 * it is disabled. We need to save the current state of the FPU, and hand
 * it over. */
exception_t
handleFPUFault(void)
{
    /* If we have already given the FPU to the user, we should not reach here.
     * This should only be able to occur on CPUs without an FPU at all, which
     * we presumably are happy to assume will not be running seL4. */
    assert(!nativeThreadUsingFPU(NODE_STATE(ksCurThread)));

    /* Otherwise, lazily switch over the FPU. */
    switchLocalFpuOwner(&NODE_STATE(ksCurThread)->tcbArch.tcbContext.fpuState);

    return EXCEPTION_NONE;
}

/* Prepare for the deletion of the given thread. */
void fpuThreadDelete(tcb_t *thread)
{
    /* If the thread being deleted currently owns the FPU, switch away from it
     * so that 'ksActiveFPUState' doesn't point to invalid memory. */
    if (nativeThreadUsingFPU(thread)) {
        switchFpuOwner(NULL, SMP_TERNARY(thread->tcbAffinity, 0));
    }
}
#endif /* CONFIG_HAVE_FPU */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/machine/io.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <machine/io.h>

#ifdef CONFIG_PRINTING

#include <stdarg.h>

void
putchar(char c)
{
    putConsoleChar(c);
    if (c == '\n') {
        putConsoleChar('\r');
    }
}

static unsigned int
print_spaces(int n)
{
    for (int i = 0; i < n; i++) {
        kernel_putchar(' ');
    }

    return n;
}

static unsigned int
print_string(const char *s)
{
    unsigned int n;

    for (n = 0; *s; s++, n++) {
        kernel_putchar(*s);
    }

    return n;
}

static unsigned long
xdiv(unsigned long x, unsigned int denom)
{
    switch (denom) {
    case 16:
        return x / 16;
    case 10:
        return x / 10;
    default:
        return 0;
    }
}

static unsigned long
xmod(unsigned long x, unsigned int denom)
{
    switch (denom) {
    case 16:
        return x % 16;
    case 10:
        return x % 10;
    default:
        return 0;
    }
}

word_t
print_unsigned_long(unsigned long x, word_t ui_base)
{
    char out[sizeof(unsigned long) * 2 + 3];
    word_t i, j;
    unsigned int d;

    /*
     * Only base 10 and 16 supported for now. We want to avoid invoking the
     * compiler's support libraries through doing arbitrary divisions.
     */
    if (ui_base != 10 && ui_base != 16) {
        return 0;
    }

    if (x == 0) {
        kernel_putchar('0');
        return 1;
    }

    for (i = 0; x; x = xdiv(x, ui_base), i++) {
        d = xmod(x, ui_base);

        if (d >= 10) {
            out[i] = 'a' + d - 10;
        } else {
            out[i] = '0' + d;
        }
    }

    for (j = i; j > 0; j--) {
        kernel_putchar(out[j - 1]);
    }

    return i;
}

/* The print_unsigned_long_long function assumes that an unsinged int
   is half the size of an unsigned long long */
compile_assert(print_unsigned_long_long_sizes, sizeof(unsigned int) * 2 == sizeof(unsigned long long))

static unsigned int
print_unsigned_long_long(unsigned long long x, unsigned int ui_base)
{
    unsigned int upper, lower;
    unsigned int n = 0;
    unsigned int mask = 0xF0000000u;
    unsigned int shifts = 0;

    /* only implemented for hex, decimal is harder without 64 bit division */
    if (ui_base != 16) {
        return 0;
    }

    /* we can't do 64 bit division so break it up into two hex numbers */
    upper = (unsigned int) (x >> 32llu);
    lower = (unsigned int) x & 0xffffffff;

    /* print first 32 bits if they exist */
    if (upper > 0) {
        n += print_unsigned_long(upper, ui_base);
        /* print leading 0s */
        while (!(mask & lower)) {
            kernel_putchar('0');
            n++;
            mask = mask >> 4;
            shifts++;
            if (shifts == 8) {
                break;
            }
        }
    }
    /* print last 32 bits */
    n += print_unsigned_long(lower, ui_base);

    return n;
}

static inline bool_t
isdigit(char c)
{
    return c >= '0' &&
           c <= '9';
}

static inline int
atoi(char c)
{
    return c - '0';
}

static int
vprintf(const char *format, va_list ap)
{
    unsigned int n;
    unsigned int formatting;
    int nspaces = 0;

    if (!format) {
        return 0;
    }

    n = 0;
    formatting = 0;
    while (*format) {
        if (formatting) {
            while (isdigit(*format)) {
                nspaces = nspaces * 10 + atoi(*format);
                format++;
                if (format == NULL) {
                    break;
                }
            }
            switch (*format) {
            case '%':
                kernel_putchar('%');
                n++;
                format++;
                break;

            case 'd': {
                int x = va_arg(ap, int);

                if (x < 0) {
                    kernel_putchar('-');
                    n++;
                    x = -x;
                }

                n += print_unsigned_long(x, 10);
                format++;
                break;
            }

            case 'u':
                n += print_unsigned_long(va_arg(ap, unsigned int), 10);
                format++;
                break;

            case 'x':
                n += print_unsigned_long(va_arg(ap, unsigned int), 16);
                format++;
                break;

            case 'p': {
                unsigned long p = va_arg(ap, unsigned long);
                if (p == 0) {
                    n += print_string("(nil)");
                } else {
                    n += print_string("0x");
                    n += print_unsigned_long(p, 16);
                }
                format++;
                break;
            }

            case 's':
                n += print_string(va_arg(ap, char *));
                format++;
                break;

            case 'l':
                format++;
                switch (*format) {
                case 'd': {
                    long x = va_arg(ap, long);

                    if (x < 0) {
                        kernel_putchar('-');
                        n++;
                        x = -x;
                    }

                    n += print_unsigned_long((unsigned long)x, 10);
                    format++;
                }
                break;
                case 'l':
                    if (*(format + 1) == 'x') {
                        n += print_unsigned_long_long(va_arg(ap, unsigned long long), 16);
                    }
                    format += 2;
                    break;
                case 'u':
                    n += print_unsigned_long(va_arg(ap, unsigned long), 10);
                    format++;
                    break;
                case 'x':
                    n += print_unsigned_long(va_arg(ap, unsigned long), 16);
                    format++;
                    break;

                default:
                    /* format not supported */
                    return -1;
                }
                break;
            default:
                /* format not supported */
                return -1;
            }

            n += print_spaces(nspaces - n);
            nspaces = 0;
            formatting = 0;
        } else {
            switch (*format) {
            case '%':
                formatting = 1;
                format++;
                break;

            default:
                kernel_putchar(*format);
                n++;
                format++;
                break;
            }
        }
    }

    return n;
}

word_t puts(const char *s)
{
    for (; *s; s++) {
        kernel_putchar(*s);
    }
    kernel_putchar('\n');
    return 0;
}

word_t
kprintf(const char *format, ...)
{
    va_list args;
    word_t i;

    va_start(args, format);
    i = vprintf(format, args);
    va_end(args);
    return i;
}

#endif /* CONFIG_PRINTING */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/machine/registerset.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */
#include <machine/registerset.h>

const register_t fault_messages[][MAX_MSG_SIZE] = {
    [MessageID_Syscall] = SYSCALL_MESSAGE,
    [MessageID_Exception] = EXCEPTION_MESSAGE
};
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/model/preemption.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <api/failures.h>
#include <model/preemption.h>
#include <model/statedata.h>
#include <plat/machine/hardware.h>
#include <config.h>

/*
 * Possibly preempt the current thread to allow an interrupt to be handled.
 */
exception_t
preemptionPoint(void)
{
    /* Record that we have performed some work. */
    ksWorkUnitsCompleted++;

    /*
     * If we have performed a non-trivial amount of work since last time we
     * checked for preemption, and there is an interrupt pending, handle the
     * interrupt.
     *
     * We avoid checking for pending IRQs every call, as our callers tend to
     * call us in a tight loop and checking for pending IRQs can be quite slow.
     */
    if (ksWorkUnitsCompleted >= CONFIG_MAX_NUM_WORK_UNITS_PER_PREEMPTION) {
        ksWorkUnitsCompleted = 0;
        if (isIRQPending()) {
            return EXCEPTION_PREEMPTED;
        }
    }

    return EXCEPTION_NONE;
}

#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/model/smp.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <model/smp.h>
#include <object/tcb.h>

#ifdef ENABLE_SMP_SUPPORT

void migrateTCB(tcb_t *tcb, word_t new_core)
{
#ifdef CONFIG_DEBUG_BUILD
    tcbDebugRemove(tcb);
#endif
    Arch_migrateTCB(tcb);
    tcb->tcbAffinity = new_core;
#ifdef CONFIG_DEBUG_BUILD
    tcbDebugAppend(tcb);
#endif
}

#endif /* ENABLE_SMP_SUPPORT */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/model/statedata.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <api/debug.h>
#include <types.h>
#include <plat/machine.h>
#include <model/statedata.h>
#include <model/smp.h>
#include <object/structures.h>
#include <object/tcb.h>
#include <benchmark/benchmark_track.h>

/* Collective cpu states, including both pre core architecture dependant and independent data */
SMP_STATE_DEFINE(smpStatedata_t, ksSMP[CONFIG_MAX_NUM_NODES] ALIGN(L1_CACHE_LINE_SIZE));

/* Global count of how many cpus there are */
word_t ksNumCPUs;

/* Pointer to the head of the scheduler queue for each priority */
UP_STATE_DEFINE(tcb_queue_t, ksReadyQueues[NUM_READY_QUEUES]);
UP_STATE_DEFINE(word_t, ksReadyQueuesL1Bitmap[CONFIG_NUM_DOMAINS]);
UP_STATE_DEFINE(word_t, ksReadyQueuesL2Bitmap[CONFIG_NUM_DOMAINS][L2_BITMAP_SIZE]);
compile_assert(ksReadyQueuesL1BitmapBigEnough, (L2_BITMAP_SIZE - 1) <= wordBits)

/* Current thread TCB pointer */
UP_STATE_DEFINE(tcb_t *, ksCurThread);

/* Idle thread TCB pointer */
UP_STATE_DEFINE(tcb_t *, ksIdleThread);

/* Values of 0 and ~0 encode ResumeCurrentThread and ChooseNewThread
 * respectively; other values encode SwitchToThread and must be valid
 * tcb pointers */
UP_STATE_DEFINE(tcb_t *, ksSchedulerAction);

#ifdef CONFIG_HAVE_FPU
/* Currently active FPU state, or NULL if there is no active FPU state */
UP_STATE_DEFINE(user_fpu_state_t *, ksActiveFPUState);

UP_STATE_DEFINE(word_t, ksFPURestoresSinceSwitch);
#endif /* CONFIG_HAVE_FPU */

#ifdef CONFIG_DEBUG_BUILD
UP_STATE_DEFINE(tcb_t *, ksDebugTCBs);
#endif /* CONFIG_DEBUG_BUILD */

/* Units of work we have completed since the last time we checked for
 * pending interrupts */
word_t ksWorkUnitsCompleted;

/* CNode containing interrupt handler endpoints */
irq_state_t intStateIRQTable[maxIRQ + 1];
cte_t *intStateIRQNode;

/* Currently active domain */
dom_t ksCurDomain;

/* Domain timeslice remaining */
word_t ksDomainTime;

/* An index into ksDomSchedule for active domain and length. */
word_t ksDomScheduleIdx;

/* Only used by lockTLBEntry */
word_t tlbLockCount = 0;

#if (defined CONFIG_DEBUG_BUILD || defined CONFIG_BENCHMARK_TRACK_KERNEL_ENTRIES)
kernel_entry_t ksKernelEntry;
#endif /* DEBUG */

#ifdef CONFIG_BENCHMARK_USE_KERNEL_LOG_BUFFER
paddr_t ksUserLogBuffer;
#endif /* CONFIG_BENCHMARK_USE_KERNEL_LOG_BUFFER */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/object/cnode.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <assert.h>
#include <types.h>
#include <api/failures.h>
#include <api/invocation.h>
#include <api/syscall.h>
#include <api/types.h>
#include <machine/io.h>
#include <object/structures.h>
#include <object/objecttype.h>
#include <object/cnode.h>
#include <object/interrupt.h>
#include <object/untyped.h>
#include <kernel/cspace.h>
#include <kernel/thread.h>
#include <model/preemption.h>
#include <model/statedata.h>
#include <util.h>

struct finaliseSlot_ret {
    exception_t status;
    bool_t success;
    cap_t cleanupInfo;
};
typedef struct finaliseSlot_ret finaliseSlot_ret_t;

static finaliseSlot_ret_t finaliseSlot(cte_t *slot, bool_t exposed);
static void emptySlot(cte_t *slot, cap_t cleanupInfo);
static exception_t reduceZombie(cte_t* slot, bool_t exposed);

exception_t
decodeCNodeInvocation(word_t invLabel, word_t length, cap_t cap,
                      extra_caps_t excaps, word_t *buffer)
{
    lookupSlot_ret_t lu_ret;
    cte_t *destSlot;
    word_t index, w_bits;
    exception_t status;

    /* Haskell error: "decodeCNodeInvocation: invalid cap" */
    assert(cap_get_capType(cap) == cap_cnode_cap);

    if (invLabel < CNodeRevoke || invLabel > CNodeSaveCaller) {
        userError("CNodeCap: Illegal Operation attempted.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (length < 2) {
        userError("CNode operation: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }
    index = getSyscallArg(0, buffer);
    w_bits = getSyscallArg(1, buffer);

    lu_ret = lookupTargetSlot(cap, index, w_bits);
    if (lu_ret.status != EXCEPTION_NONE) {
        userError("CNode operation: Target slot invalid.");
        return lu_ret.status;
    }
    destSlot = lu_ret.slot;

    if (invLabel >= CNodeCopy && invLabel <= CNodeMutate) {
        cte_t *srcSlot;
        word_t srcIndex, srcDepth, capData;
        bool_t isMove;
        seL4_CapRights_t cap_rights;
        cap_t srcRoot, newCap;
        deriveCap_ret_t dc_ret;
        cap_t srcCap;

        if (length < 4 || excaps.excaprefs[0] == NULL) {
            userError("CNode Copy/Mint/Move/Mutate: Truncated message.");
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }
        srcIndex = getSyscallArg(2, buffer);
        srcDepth = getSyscallArg(3, buffer);

        srcRoot = excaps.excaprefs[0]->cap;

        status = ensureEmptySlot(destSlot);
        if (status != EXCEPTION_NONE) {
            userError("CNode Copy/Mint/Move/Mutate: Destination not empty.");
            return status;
        }

        lu_ret = lookupSourceSlot(srcRoot, srcIndex, srcDepth);
        if (lu_ret.status != EXCEPTION_NONE) {
            userError("CNode Copy/Mint/Move/Mutate: Invalid source slot.");
            return lu_ret.status;
        }
        srcSlot = lu_ret.slot;

        if (cap_get_capType(srcSlot->cap) == cap_null_cap) {
            userError("CNode Copy/Mint/Move/Mutate: Source slot invalid or empty.");
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = 1;
            current_lookup_fault =
                lookup_fault_missing_capability_new(srcDepth);
            return EXCEPTION_SYSCALL_ERROR;
        }

        switch (invLabel) {
        case CNodeCopy:

            if (length < 5) {
                userError("Truncated message for CNode Copy operation.");
                current_syscall_error.type = seL4_TruncatedMessage;
                return EXCEPTION_SYSCALL_ERROR;
            }

            cap_rights = rightsFromWord(getSyscallArg(4, buffer));
            srcCap = maskCapRights(cap_rights, srcSlot->cap);
            dc_ret = deriveCap(srcSlot, srcCap);
            if (dc_ret.status != EXCEPTION_NONE) {
                userError("Error deriving cap for CNode Copy operation.");
                return dc_ret.status;
            }
            newCap = dc_ret.cap;
            isMove = false;

            break;

        case CNodeMint:
            if (length < 6) {
                userError("CNode Mint: Truncated message.");
                current_syscall_error.type = seL4_TruncatedMessage;
                return EXCEPTION_SYSCALL_ERROR;
            }

            cap_rights = rightsFromWord(getSyscallArg(4, buffer));
            capData = getSyscallArg(5, buffer);
            srcCap = maskCapRights(cap_rights, srcSlot->cap);
            dc_ret = deriveCap(srcSlot,
                               updateCapData(false, capData, srcCap));
            if (dc_ret.status != EXCEPTION_NONE) {
                userError("Error deriving cap for CNode Mint operation.");
                return dc_ret.status;
            }
            newCap = dc_ret.cap;
            isMove = false;

            break;

        case CNodeMove:
            newCap = srcSlot->cap;
            isMove = true;

            break;

        case CNodeMutate:
            if (length < 5) {
                userError("CNode Mutate: Truncated message.");
                current_syscall_error.type = seL4_TruncatedMessage;
                return EXCEPTION_SYSCALL_ERROR;
            }

            capData = getSyscallArg(4, buffer);
            newCap = updateCapData(true, capData, srcSlot->cap);
            isMove = true;

            break;

        default:
            assert (0);
            return EXCEPTION_NONE;
        }

        if (cap_get_capType(newCap) == cap_null_cap) {
            userError("CNode Copy/Mint/Move/Mutate: Mutated cap would be invalid.");
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        if (isMove) {
            return invokeCNodeMove(newCap, srcSlot, destSlot);
        } else {
            return invokeCNodeInsert(newCap, srcSlot, destSlot);
        }
    }

    if (invLabel == CNodeRevoke) {
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return invokeCNodeRevoke(destSlot);
    }

    if (invLabel == CNodeDelete) {
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return invokeCNodeDelete(destSlot);
    }

    if (invLabel == CNodeSaveCaller) {
        status = ensureEmptySlot(destSlot);
        if (status != EXCEPTION_NONE) {
            userError("CNode SaveCaller: Destination slot not empty.");
            return status;
        }

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return invokeCNodeSaveCaller(destSlot);
    }

    if (invLabel == CNodeCancelBadgedSends) {
        cap_t destCap;

        destCap = destSlot->cap;

        if (!hasCancelSendRights(destCap)) {
            userError("CNode CancelBadgedSends: Target cap invalid.");
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return invokeCNodeCancelBadgedSends(destCap);
    }

    if (invLabel == CNodeRotate) {
        word_t pivotNewData, pivotIndex, pivotDepth;
        word_t srcNewData, srcIndex, srcDepth;
        cte_t *pivotSlot, *srcSlot;
        cap_t pivotRoot, srcRoot, newSrcCap, newPivotCap;

        if (length < 8 || excaps.excaprefs[0] == NULL
                || excaps.excaprefs[1] == NULL) {
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }
        pivotNewData = getSyscallArg(2, buffer);
        pivotIndex   = getSyscallArg(3, buffer);
        pivotDepth   = getSyscallArg(4, buffer);
        srcNewData   = getSyscallArg(5, buffer);
        srcIndex     = getSyscallArg(6, buffer);
        srcDepth     = getSyscallArg(7, buffer);

        pivotRoot = excaps.excaprefs[0]->cap;
        srcRoot   = excaps.excaprefs[1]->cap;

        lu_ret = lookupSourceSlot(srcRoot, srcIndex, srcDepth);
        if (lu_ret.status != EXCEPTION_NONE) {
            return lu_ret.status;
        }
        srcSlot = lu_ret.slot;

        lu_ret = lookupPivotSlot(pivotRoot, pivotIndex, pivotDepth);
        if (lu_ret.status != EXCEPTION_NONE) {
            return lu_ret.status;
        }
        pivotSlot = lu_ret.slot;

        if (pivotSlot == srcSlot || pivotSlot == destSlot) {
            userError("CNode Rotate: Pivot slot the same as source or dest slot.");
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (srcSlot != destSlot) {
            status = ensureEmptySlot(destSlot);
            if (status != EXCEPTION_NONE) {
                return status;
            }
        }

        if (cap_get_capType(srcSlot->cap) == cap_null_cap) {
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = 1;
            current_lookup_fault = lookup_fault_missing_capability_new(srcDepth);
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (cap_get_capType(pivotSlot->cap) == cap_null_cap) {
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = 0;
            current_lookup_fault = lookup_fault_missing_capability_new(pivotDepth);
            return EXCEPTION_SYSCALL_ERROR;
        }

        newSrcCap = updateCapData(true, srcNewData, srcSlot->cap);
        newPivotCap = updateCapData(true, pivotNewData, pivotSlot->cap);

        if (cap_get_capType(newSrcCap) == cap_null_cap) {
            userError("CNode Rotate: Source cap invalid.");
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (cap_get_capType(newPivotCap) == cap_null_cap) {
            userError("CNode Rotate: Pivot cap invalid.");
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return invokeCNodeRotate(newSrcCap, newPivotCap,
                                 srcSlot, pivotSlot, destSlot);
    }

    return EXCEPTION_NONE;
}

exception_t
invokeCNodeRevoke(cte_t *destSlot)
{
    return cteRevoke(destSlot);
}

exception_t
invokeCNodeDelete(cte_t *destSlot)
{
    return cteDelete(destSlot, true);
}

exception_t
invokeCNodeCancelBadgedSends(cap_t cap)
{
    word_t badge = cap_endpoint_cap_get_capEPBadge(cap);
    if (badge) {
        endpoint_t* ep = (endpoint_t*)
                         cap_endpoint_cap_get_capEPPtr(cap);
        cancelBadgedSends(ep, badge);
    }
    return EXCEPTION_NONE;
}

exception_t
invokeCNodeInsert(cap_t cap, cte_t *srcSlot, cte_t *destSlot)
{
    cteInsert(cap, srcSlot, destSlot);

    return EXCEPTION_NONE;
}

exception_t
invokeCNodeMove(cap_t cap, cte_t *srcSlot, cte_t *destSlot)
{
    cteMove(cap, srcSlot, destSlot);

    return EXCEPTION_NONE;
}

exception_t
invokeCNodeRotate(cap_t cap1, cap_t cap2, cte_t *slot1,
                  cte_t *slot2, cte_t *slot3)
{
    if (slot1 == slot3) {
        cteSwap(cap1, slot1, cap2, slot2);
    } else {
        cteMove(cap2, slot2, slot3);
        cteMove(cap1, slot1, slot2);
    }

    return EXCEPTION_NONE;
}

exception_t
invokeCNodeSaveCaller(cte_t *destSlot)
{
    cap_t cap;
    cte_t *srcSlot;

    srcSlot = TCB_PTR_CTE_PTR(NODE_STATE(ksCurThread), tcbCaller);
    cap = srcSlot->cap;

    switch (cap_get_capType(cap)) {
    case cap_null_cap:
        userError("CNode SaveCaller: Reply cap not present.");
        break;

    case cap_reply_cap:
        if (!cap_reply_cap_get_capReplyMaster(cap)) {
            cteMove(cap, srcSlot, destSlot);
        }
        break;

    default:
        fail("caller capability must be null or reply");
        break;
    }

    return EXCEPTION_NONE;
}

/*
 * If creating a child UntypedCap, don't allow new objects to be created in the
 * parent.
 */
static void
setUntypedCapAsFull(cap_t srcCap, cap_t newCap, cte_t *srcSlot)
{
    if ((cap_get_capType(srcCap) == cap_untyped_cap)
            && (cap_get_capType(newCap) == cap_untyped_cap)) {
        if ((cap_untyped_cap_get_capPtr(srcCap)
                == cap_untyped_cap_get_capPtr(newCap))
                && (cap_untyped_cap_get_capBlockSize(newCap)
                    == cap_untyped_cap_get_capBlockSize(srcCap))) {
            cap_untyped_cap_ptr_set_capFreeIndex(&(srcSlot->cap),
                                                 MAX_FREE_INDEX(cap_untyped_cap_get_capBlockSize(srcCap)));
        }
    }
}

void
cteInsert(cap_t newCap, cte_t *srcSlot, cte_t *destSlot)
{
    mdb_node_t srcMDB, newMDB;
    cap_t srcCap;
    bool_t newCapIsRevocable;

    srcMDB = srcSlot->cteMDBNode;
    srcCap = srcSlot->cap;

    newCapIsRevocable = isCapRevocable(newCap, srcCap);

    newMDB = mdb_node_set_mdbPrev(srcMDB, CTE_REF(srcSlot));
    newMDB = mdb_node_set_mdbRevocable(newMDB, newCapIsRevocable);
    newMDB = mdb_node_set_mdbFirstBadged(newMDB, newCapIsRevocable);

    /* Haskell error: "cteInsert to non-empty destination" */
    assert(cap_get_capType(destSlot->cap) == cap_null_cap);
    /* Haskell error: "cteInsert: mdb entry must be empty" */
    assert((cte_t*)mdb_node_get_mdbNext(destSlot->cteMDBNode) == NULL &&
           (cte_t*)mdb_node_get_mdbPrev(destSlot->cteMDBNode) == NULL);

    /* Prevent parent untyped cap from being used again if creating a child
     * untyped from it. */
    setUntypedCapAsFull(srcCap, newCap, srcSlot);

    destSlot->cap = newCap;
    destSlot->cteMDBNode = newMDB;
    mdb_node_ptr_set_mdbNext(&srcSlot->cteMDBNode, CTE_REF(destSlot));
    if (mdb_node_get_mdbNext(newMDB)) {
        mdb_node_ptr_set_mdbPrev(
            &CTE_PTR(mdb_node_get_mdbNext(newMDB))->cteMDBNode,
            CTE_REF(destSlot));
    }
}

void
cteMove(cap_t newCap, cte_t *srcSlot, cte_t *destSlot)
{
    mdb_node_t mdb;
    word_t prev_ptr, next_ptr;

    /* Haskell error: "cteMove to non-empty destination" */
    assert(cap_get_capType(destSlot->cap) == cap_null_cap);
    /* Haskell error: "cteMove: mdb entry must be empty" */
    assert((cte_t*)mdb_node_get_mdbNext(destSlot->cteMDBNode) == NULL &&
           (cte_t*)mdb_node_get_mdbPrev(destSlot->cteMDBNode) == NULL);

    mdb = srcSlot->cteMDBNode;
    destSlot->cap = newCap;
    srcSlot->cap = cap_null_cap_new();
    destSlot->cteMDBNode = mdb;
    srcSlot->cteMDBNode = nullMDBNode;

    prev_ptr = mdb_node_get_mdbPrev(mdb);
    if (prev_ptr)
        mdb_node_ptr_set_mdbNext(
            &CTE_PTR(prev_ptr)->cteMDBNode,
            CTE_REF(destSlot));

    next_ptr = mdb_node_get_mdbNext(mdb);
    if (next_ptr)
        mdb_node_ptr_set_mdbPrev(
            &CTE_PTR(next_ptr)->cteMDBNode,
            CTE_REF(destSlot));
}

void
capSwapForDelete(cte_t *slot1, cte_t *slot2)
{
    cap_t cap1, cap2;

    if (slot1 == slot2) {
        return;
    }

    cap1 = slot1->cap;
    cap2 = slot2->cap;

    cteSwap(cap1, slot1, cap2, slot2);
}

void
cteSwap(cap_t cap1, cte_t *slot1, cap_t cap2, cte_t *slot2)
{
    mdb_node_t mdb1, mdb2;
    word_t next_ptr, prev_ptr;

    slot1->cap = cap2;
    slot2->cap = cap1;

    mdb1 = slot1->cteMDBNode;

    prev_ptr = mdb_node_get_mdbPrev(mdb1);
    if (prev_ptr)
        mdb_node_ptr_set_mdbNext(
            &CTE_PTR(prev_ptr)->cteMDBNode,
            CTE_REF(slot2));

    next_ptr = mdb_node_get_mdbNext(mdb1);
    if (next_ptr)
        mdb_node_ptr_set_mdbPrev(
            &CTE_PTR(next_ptr)->cteMDBNode,
            CTE_REF(slot2));

    mdb2 = slot2->cteMDBNode;
    slot1->cteMDBNode = mdb2;
    slot2->cteMDBNode = mdb1;

    prev_ptr = mdb_node_get_mdbPrev(mdb2);
    if (prev_ptr)
        mdb_node_ptr_set_mdbNext(
            &CTE_PTR(prev_ptr)->cteMDBNode,
            CTE_REF(slot1));

    next_ptr = mdb_node_get_mdbNext(mdb2);
    if (next_ptr)
        mdb_node_ptr_set_mdbPrev(
            &CTE_PTR(next_ptr)->cteMDBNode,
            CTE_REF(slot1));
}

exception_t
cteRevoke(cte_t *slot)
{
    cte_t *nextPtr;
    exception_t status;

    /* there is no need to check for a NullCap as NullCaps are
       always accompanied by null mdb pointers */
    for (nextPtr = CTE_PTR(mdb_node_get_mdbNext(slot->cteMDBNode));
            nextPtr && isMDBParentOf(slot, nextPtr);
            nextPtr = CTE_PTR(mdb_node_get_mdbNext(slot->cteMDBNode))) {
        status = cteDelete(nextPtr, true);
        if (status != EXCEPTION_NONE) {
            return status;
        }

        status = preemptionPoint();
        if (status != EXCEPTION_NONE) {
            return status;
        }
    }

    return EXCEPTION_NONE;
}

exception_t
cteDelete(cte_t *slot, bool_t exposed)
{
    finaliseSlot_ret_t fs_ret;

    fs_ret = finaliseSlot(slot, exposed);
    if (fs_ret.status != EXCEPTION_NONE) {
        return fs_ret.status;
    }

    if (exposed || fs_ret.success) {
        emptySlot(slot, fs_ret.cleanupInfo);
    }
    return EXCEPTION_NONE;
}

static void
emptySlot(cte_t *slot, cap_t cleanupInfo)
{
    if (cap_get_capType(slot->cap) != cap_null_cap) {
        mdb_node_t mdbNode;
        cte_t *prev, *next;

        mdbNode = slot->cteMDBNode;
        prev = CTE_PTR(mdb_node_get_mdbPrev(mdbNode));
        next = CTE_PTR(mdb_node_get_mdbNext(mdbNode));

        if (prev) {
            mdb_node_ptr_set_mdbNext(&prev->cteMDBNode, CTE_REF(next));
        }
        if (next) {
            mdb_node_ptr_set_mdbPrev(&next->cteMDBNode, CTE_REF(prev));
        }
        if (next)
            mdb_node_ptr_set_mdbFirstBadged(&next->cteMDBNode,
                                            mdb_node_get_mdbFirstBadged(next->cteMDBNode) ||
                                            mdb_node_get_mdbFirstBadged(mdbNode));
        slot->cap = cap_null_cap_new();
        slot->cteMDBNode = nullMDBNode;

        postCapDeletion(cleanupInfo);
    }
}

static inline bool_t CONST
capRemovable(cap_t cap, cte_t* slot)
{
    switch (cap_get_capType(cap)) {
    case cap_null_cap:
        return true;
    case cap_zombie_cap: {
        word_t n = cap_zombie_cap_get_capZombieNumber(cap);
        cte_t* z_slot = (cte_t*)cap_zombie_cap_get_capZombiePtr(cap);
        return (n == 0 || (n == 1 && slot == z_slot));
    }
    default:
        fail("finaliseCap should only return Zombie or NullCap");
    }
}

static inline bool_t CONST
capCyclicZombie(cap_t cap, cte_t *slot)
{
    return cap_get_capType(cap) == cap_zombie_cap &&
           CTE_PTR(cap_zombie_cap_get_capZombiePtr(cap)) == slot;
}

static finaliseSlot_ret_t
finaliseSlot(cte_t *slot, bool_t immediate)
{
    bool_t final;
    finaliseCap_ret_t fc_ret;
    exception_t status;
    finaliseSlot_ret_t ret;

    while (cap_get_capType(slot->cap) != cap_null_cap) {
        final = isFinalCapability(slot);
        fc_ret = finaliseCap(slot->cap, final, false);

        if (capRemovable(fc_ret.remainder, slot)) {
            ret.status = EXCEPTION_NONE;
            ret.success = true;
            ret.cleanupInfo = fc_ret.cleanupInfo;
            return ret;
        }

        slot->cap = fc_ret.remainder;

        if (!immediate && capCyclicZombie(fc_ret.remainder, slot)) {
            ret.status = EXCEPTION_NONE;
            ret.success = false;
            ret.cleanupInfo = fc_ret.cleanupInfo;
            return ret;
        }

        status = reduceZombie(slot, immediate);
        if (status != EXCEPTION_NONE) {
            ret.status = status;
            ret.success = false;
            ret.cleanupInfo = cap_null_cap_new();
            return ret;
        }

        status = preemptionPoint();
        if (status != EXCEPTION_NONE) {
            ret.status = status;
            ret.success = false;
            ret.cleanupInfo = cap_null_cap_new();
            return ret;
        }
    }
    ret.status = EXCEPTION_NONE;
    ret.success = true;
    ret.cleanupInfo = cap_null_cap_new();
    return ret;
}

static exception_t
reduceZombie(cte_t* slot, bool_t immediate)
{
    cte_t* ptr;
    word_t n, type;
    exception_t status;

    assert(cap_get_capType(slot->cap) == cap_zombie_cap);
    ptr = (cte_t*)cap_zombie_cap_get_capZombiePtr(slot->cap);
    n = cap_zombie_cap_get_capZombieNumber(slot->cap);
    type = cap_zombie_cap_get_capZombieType(slot->cap);

    /* Haskell error: "reduceZombie: expected unremovable zombie" */
    assert(n > 0);

    if (immediate) {
        cte_t* endSlot = &ptr[n - 1];

        status = cteDelete(endSlot, false);
        if (status != EXCEPTION_NONE) {
            return status;
        }

        switch (cap_get_capType(slot->cap)) {
        case cap_null_cap:
            break;

        case cap_zombie_cap: {
            cte_t* ptr2 =
                (cte_t*)cap_zombie_cap_get_capZombiePtr(slot->cap);

            if (ptr == ptr2 &&
                    cap_zombie_cap_get_capZombieNumber(slot->cap) == n &&
                    cap_zombie_cap_get_capZombieType(slot->cap) == type) {
                assert(cap_get_capType(endSlot->cap) == cap_null_cap);
                slot->cap =
                    cap_zombie_cap_set_capZombieNumber(slot->cap, n - 1);
            } else {
                /* Haskell error:
                 * "Expected new Zombie to be self-referential."
                 */
                assert(ptr2 == slot && ptr != slot);
            }
            break;
        }

        default:
            fail("Expected recursion to result in Zombie.");
        }
    } else {
        /* Haskell error: "Cyclic zombie passed to unexposed reduceZombie" */
        assert(ptr != slot);

        if (cap_get_capType(ptr->cap) == cap_zombie_cap) {
            /* Haskell error: "Moving self-referential Zombie aside." */
            assert(ptr != CTE_PTR(cap_zombie_cap_get_capZombiePtr(ptr->cap)));
        }

        capSwapForDelete(ptr, slot);
    }
    return EXCEPTION_NONE;
}

void
cteDeleteOne(cte_t* slot)
{
    word_t cap_type = cap_get_capType(slot->cap);
    if (cap_type != cap_null_cap) {
        bool_t final;
        finaliseCap_ret_t fc_ret UNUSED;

        /** GHOSTUPD: "(gs_get_assn cteDeleteOne_'proc \<acute>ghost'state = (-1)
            \<or> gs_get_assn cteDeleteOne_'proc \<acute>ghost'state = \<acute>cap_type, id)" */

        final = isFinalCapability(slot);
        fc_ret = finaliseCap(slot->cap, final, true);
        /* Haskell error: "cteDeleteOne: cap should be removable" */
        assert(capRemovable(fc_ret.remainder, slot) &&
               cap_get_capType(fc_ret.cleanupInfo) == cap_null_cap);
        emptySlot(slot, cap_null_cap_new());
    }
}

void
insertNewCap(cte_t *parent, cte_t *slot, cap_t cap)
{
    cte_t *next;

    next = CTE_PTR(mdb_node_get_mdbNext(parent->cteMDBNode));
    slot->cap = cap;
    slot->cteMDBNode = mdb_node_new(CTE_REF(next), true, true, CTE_REF(parent));
    if (next) {
        mdb_node_ptr_set_mdbPrev(&next->cteMDBNode, CTE_REF(slot));
    }
    mdb_node_ptr_set_mdbNext(&parent->cteMDBNode, CTE_REF(slot));
}

void
setupReplyMaster(tcb_t *thread)
{
    cte_t *slot;

    slot = TCB_PTR_CTE_PTR(thread, tcbReply);
    if (cap_get_capType(slot->cap) == cap_null_cap) {
        /* Haskell asserts that no reply caps exist for this thread here. This
         * cannot be translated. */
        slot->cap = cap_reply_cap_new(true, TCB_REF(thread));
        slot->cteMDBNode = nullMDBNode;
        mdb_node_ptr_set_mdbRevocable(&slot->cteMDBNode, true);
        mdb_node_ptr_set_mdbFirstBadged(&slot->cteMDBNode, true);
    }
}

bool_t PURE
isMDBParentOf(cte_t *cte_a, cte_t *cte_b)
{
    if (!mdb_node_get_mdbRevocable(cte_a->cteMDBNode)) {
        return false;
    }
    if (!sameRegionAs(cte_a->cap, cte_b->cap)) {
        return false;
    }
    switch (cap_get_capType(cte_a->cap)) {
    case cap_endpoint_cap: {
        word_t badge;

        badge = cap_endpoint_cap_get_capEPBadge(cte_a->cap);
        if (badge == 0) {
            return true;
        }
        return (badge == cap_endpoint_cap_get_capEPBadge(cte_b->cap)) &&
               !mdb_node_get_mdbFirstBadged(cte_b->cteMDBNode);
        break;
    }

    case cap_notification_cap: {
        word_t badge;

        badge = cap_notification_cap_get_capNtfnBadge(cte_a->cap);
        if (badge == 0) {
            return true;
        }
        return
            (badge == cap_notification_cap_get_capNtfnBadge(cte_b->cap)) &&
            !mdb_node_get_mdbFirstBadged(cte_b->cteMDBNode);
        break;
    }

    default:
        return true;
        break;
    }
}

exception_t
ensureNoChildren(cte_t *slot)
{
    if (mdb_node_get_mdbNext(slot->cteMDBNode) != 0) {
        cte_t *next;

        next = CTE_PTR(mdb_node_get_mdbNext(slot->cteMDBNode));
        if (isMDBParentOf(slot, next)) {
            current_syscall_error.type = seL4_RevokeFirst;
            return EXCEPTION_SYSCALL_ERROR;
        }
    }

    return EXCEPTION_NONE;
}

exception_t
ensureEmptySlot(cte_t *slot)
{
    if (cap_get_capType(slot->cap) != cap_null_cap) {
        current_syscall_error.type = seL4_DeleteFirst;
        return EXCEPTION_SYSCALL_ERROR;
    }

    return EXCEPTION_NONE;
}

bool_t PURE
isFinalCapability(cte_t *cte)
{
    mdb_node_t mdb;
    bool_t prevIsSameObject;

    mdb = cte->cteMDBNode;

    if (mdb_node_get_mdbPrev(mdb) == 0) {
        prevIsSameObject = false;
    } else {
        cte_t *prev;

        prev = CTE_PTR(mdb_node_get_mdbPrev(mdb));
        prevIsSameObject = sameObjectAs(prev->cap, cte->cap);
    }

    if (prevIsSameObject) {
        return false;
    } else {
        if (mdb_node_get_mdbNext(mdb) == 0) {
            return true;
        } else {
            cte_t *next;

            next = CTE_PTR(mdb_node_get_mdbNext(mdb));
            return !sameObjectAs(cte->cap, next->cap);
        }
    }
}

bool_t PURE
slotCapLongRunningDelete(cte_t *slot)
{
    if (cap_get_capType(slot->cap) == cap_null_cap) {
        return false;
    } else if (! isFinalCapability(slot)) {
        return false;
    }
    switch (cap_get_capType(slot->cap)) {
    case cap_thread_cap:
    case cap_zombie_cap:
    case cap_cnode_cap:
        return true;
    default:
        return false;
    }
}

/* This implementation is specialised to the (current) limit
 * of one cap receive slot. */
cte_t *
getReceiveSlots(tcb_t *thread, word_t *buffer)
{
    cap_transfer_t ct;
    cptr_t cptr;
    lookupCap_ret_t luc_ret;
    lookupSlot_ret_t lus_ret;
    cte_t *slot;
    cap_t cnode;

    if (!buffer) {
        return NULL;
    }

    ct = loadCapTransfer(buffer);
    cptr = ct.ctReceiveRoot;

    luc_ret = lookupCap(thread, cptr);
    if (luc_ret.status != EXCEPTION_NONE) {
        return NULL;
    }
    cnode = luc_ret.cap;

    lus_ret = lookupTargetSlot(cnode, ct.ctReceiveIndex, ct.ctReceiveDepth);
    if (lus_ret.status != EXCEPTION_NONE) {
        return NULL;
    }
    slot = lus_ret.slot;

    if (cap_get_capType(slot->cap) != cap_null_cap) {
        return NULL;
    }

    return slot;
}

cap_transfer_t PURE
loadCapTransfer(word_t *buffer)
{
    const int offset = seL4_MsgMaxLength + seL4_MsgMaxExtraCaps + 2;
    return capTransferFromWords(buffer + offset);
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/object/endpoint.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <types.h>
#include <kernel/thread.h>
#include <kernel/vspace.h>
#include <machine/registerset.h>
#include <model/statedata.h>
#include <object/notification.h>
#include <object/cnode.h>
#include <object/endpoint.h>
#include <object/tcb.h>

static inline tcb_queue_t PURE
ep_ptr_get_queue(endpoint_t *epptr)
{
    tcb_queue_t queue;

    queue.head = (tcb_t*)endpoint_ptr_get_epQueue_head(epptr);
    queue.end = (tcb_t*)endpoint_ptr_get_epQueue_tail(epptr);

    return queue;
}

static inline void
ep_ptr_set_queue(endpoint_t *epptr, tcb_queue_t queue)
{
    endpoint_ptr_set_epQueue_head(epptr, (word_t)queue.head);
    endpoint_ptr_set_epQueue_tail(epptr, (word_t)queue.end);
}

void
sendIPC(bool_t blocking, bool_t do_call, word_t badge,
        bool_t canGrant, tcb_t *thread, endpoint_t *epptr)
{
    switch (endpoint_ptr_get_state(epptr)) {
    case EPState_Idle:
    case EPState_Send:
        if (blocking) {
            tcb_queue_t queue;

            /* Set thread state to BlockedOnSend */
            thread_state_ptr_set_tsType(&thread->tcbState,
                                        ThreadState_BlockedOnSend);
            thread_state_ptr_set_blockingObject(
                &thread->tcbState, EP_REF(epptr));
            thread_state_ptr_set_blockingIPCBadge(
                &thread->tcbState, badge);
            thread_state_ptr_set_blockingIPCCanGrant(
                &thread->tcbState, canGrant);
            thread_state_ptr_set_blockingIPCIsCall(
                &thread->tcbState, do_call);

            scheduleTCB(thread);

            /* Place calling thread in endpoint queue */
            queue = ep_ptr_get_queue(epptr);
            queue = tcbEPAppend(thread, queue);
            endpoint_ptr_set_state(epptr, EPState_Send);
            ep_ptr_set_queue(epptr, queue);
        }
        break;

    case EPState_Recv: {
        tcb_queue_t queue;
        tcb_t *dest;

        /* Get the head of the endpoint queue. */
        queue = ep_ptr_get_queue(epptr);
        dest = queue.head;

        /* Haskell error "Receive endpoint queue must not be empty" */
        assert(dest);

        /* Dequeue the first TCB */
        queue = tcbEPDequeue(dest, queue);
        ep_ptr_set_queue(epptr, queue);

        if (!queue.head) {
            endpoint_ptr_set_state(epptr, EPState_Idle);
        }

        /* Do the transfer */
        doIPCTransfer(thread, epptr, badge, canGrant, dest);

        setThreadState(dest, ThreadState_Running);
        possibleSwitchTo(dest);

        if (do_call ||
                seL4_Fault_ptr_get_seL4_FaultType(&thread->tcbFault) != seL4_Fault_NullFault) {
            if (canGrant) {
                setupCallerCap(thread, dest);
            } else {
                setThreadState(thread, ThreadState_Inactive);
            }
        }

        break;
    }
    }
}

void
receiveIPC(tcb_t *thread, cap_t cap, bool_t isBlocking)
{
    endpoint_t *epptr;
    notification_t *ntfnPtr;

    /* Haskell error "receiveIPC: invalid cap" */
    assert(cap_get_capType(cap) == cap_endpoint_cap);

    epptr = EP_PTR(cap_endpoint_cap_get_capEPPtr(cap));

    /* Check for anything waiting in the notification */
    ntfnPtr = thread->tcbBoundNotification;
    if (ntfnPtr && notification_ptr_get_state(ntfnPtr) == NtfnState_Active) {
        completeSignal(ntfnPtr, thread);
    } else {
        switch (endpoint_ptr_get_state(epptr)) {
        case EPState_Idle:
        case EPState_Recv: {
            tcb_queue_t queue;

            if (isBlocking) {
                /* Set thread state to BlockedOnReceive */
                thread_state_ptr_set_tsType(&thread->tcbState,
                                            ThreadState_BlockedOnReceive);
                thread_state_ptr_set_blockingObject(
                    &thread->tcbState, EP_REF(epptr));

                scheduleTCB(thread);

                /* Place calling thread in endpoint queue */
                queue = ep_ptr_get_queue(epptr);
                queue = tcbEPAppend(thread, queue);
                endpoint_ptr_set_state(epptr, EPState_Recv);
                ep_ptr_set_queue(epptr, queue);
            } else {
                doNBRecvFailedTransfer(thread);
            }
            break;
        }

        case EPState_Send: {
            tcb_queue_t queue;
            tcb_t *sender;
            word_t badge;
            bool_t canGrant;
            bool_t do_call;

            /* Get the head of the endpoint queue. */
            queue = ep_ptr_get_queue(epptr);
            sender = queue.head;

            /* Haskell error "Send endpoint queue must not be empty" */
            assert(sender);

            /* Dequeue the first TCB */
            queue = tcbEPDequeue(sender, queue);
            ep_ptr_set_queue(epptr, queue);

            if (!queue.head) {
                endpoint_ptr_set_state(epptr, EPState_Idle);
            }

            /* Get sender IPC details */
            badge = thread_state_ptr_get_blockingIPCBadge(&sender->tcbState);
            canGrant =
                thread_state_ptr_get_blockingIPCCanGrant(&sender->tcbState);

            /* Do the transfer */
            doIPCTransfer(sender, epptr, badge,
                          canGrant, thread);

            do_call = thread_state_ptr_get_blockingIPCIsCall(&sender->tcbState);

            if (do_call ||
                    seL4_Fault_get_seL4_FaultType(sender->tcbFault) != seL4_Fault_NullFault) {
                if (canGrant) {
                    setupCallerCap(sender, thread);
                } else {
                    setThreadState(sender, ThreadState_Inactive);
                }
            } else {
                setThreadState(sender, ThreadState_Running);
                possibleSwitchTo(sender);
            }

            break;
        }
        }
    }
}

void
replyFromKernel_error(tcb_t *thread)
{
    word_t len;
    word_t *ipcBuffer;

    ipcBuffer = lookupIPCBuffer(true, thread);
    setRegister(thread, badgeRegister, 0);
    len = setMRs_syscall_error(thread, ipcBuffer);
    setRegister(thread, msgInfoRegister, wordFromMessageInfo(
                    seL4_MessageInfo_new(current_syscall_error.type, 0, 0, len)));
}

void
replyFromKernel_success_empty(tcb_t *thread)
{
    setRegister(thread, badgeRegister, 0);
    setRegister(thread, msgInfoRegister, wordFromMessageInfo(
                    seL4_MessageInfo_new(0, 0, 0, 0)));
}

void
cancelIPC(tcb_t *tptr)
{
    thread_state_t *state = &tptr->tcbState;

    switch (thread_state_ptr_get_tsType(state)) {
    case ThreadState_BlockedOnSend:
    case ThreadState_BlockedOnReceive: {
        /* blockedIPCCancel state */
        endpoint_t *epptr;
        tcb_queue_t queue;

        epptr = EP_PTR(thread_state_ptr_get_blockingObject(state));

        /* Haskell error "blockedIPCCancel: endpoint must not be idle" */
        assert(endpoint_ptr_get_state(epptr) != EPState_Idle);

        /* Dequeue TCB */
        queue = ep_ptr_get_queue(epptr);
        queue = tcbEPDequeue(tptr, queue);
        ep_ptr_set_queue(epptr, queue);

        if (!queue.head) {
            endpoint_ptr_set_state(epptr, EPState_Idle);
        }

        setThreadState(tptr, ThreadState_Inactive);
        break;
    }

    case ThreadState_BlockedOnNotification:
        cancelSignal(tptr,
                     NTFN_PTR(thread_state_ptr_get_blockingObject(state)));
        break;

    case ThreadState_BlockedOnReply: {
        cte_t *slot, *callerCap;

        tptr->tcbFault = seL4_Fault_NullFault_new();

        /* Get the reply cap slot */
        slot = TCB_PTR_CTE_PTR(tptr, tcbReply);

        callerCap = CTE_PTR(mdb_node_get_mdbNext(slot->cteMDBNode));
        if (callerCap) {
            /** GHOSTUPD: "(True,
                gs_set_assn cteDeleteOne_'proc (ucast cap_reply_cap))" */
            cteDeleteOne(callerCap);
        }

        break;
    }
    }
}

void
cancelAllIPC(endpoint_t *epptr)
{
    switch (endpoint_ptr_get_state(epptr)) {
    case EPState_Idle:
        break;

    default: {
        tcb_t *thread = TCB_PTR(endpoint_ptr_get_epQueue_head(epptr));

        /* Make endpoint idle */
        endpoint_ptr_set_state(epptr, EPState_Idle);
        endpoint_ptr_set_epQueue_head(epptr, 0);
        endpoint_ptr_set_epQueue_tail(epptr, 0);

        /* Set all blocked threads to restart */
        for (; thread; thread = thread->tcbEPNext) {
            setThreadState (thread, ThreadState_Restart);
            SCHED_ENQUEUE(thread);
        }

        rescheduleRequired();
        break;
    }
    }
}

void
cancelBadgedSends(endpoint_t *epptr, word_t badge)
{
    switch (endpoint_ptr_get_state(epptr)) {
    case EPState_Idle:
    case EPState_Recv:
        break;

    case EPState_Send: {
        tcb_t *thread, *next;
        tcb_queue_t queue = ep_ptr_get_queue(epptr);

        /* this is a de-optimisation for verification
         * reasons. it allows the contents of the endpoint
         * queue to be ignored during the for loop. */
        endpoint_ptr_set_state(epptr, EPState_Idle);
        endpoint_ptr_set_epQueue_head(epptr, 0);
        endpoint_ptr_set_epQueue_tail(epptr, 0);

        for (thread = queue.head; thread; thread = next) {
            word_t b = thread_state_ptr_get_blockingIPCBadge(
                           &thread->tcbState);
            next = thread->tcbEPNext;
            if (b == badge) {
                setThreadState(thread, ThreadState_Restart);
                SCHED_ENQUEUE(thread);
                queue = tcbEPDequeue(thread, queue);
            }
        }
        ep_ptr_set_queue(epptr, queue);

        if (queue.head) {
            endpoint_ptr_set_state(epptr, EPState_Send);
        }

        rescheduleRequired();

        break;
    }

    default:
        fail("invalid EP state");
    }
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/object/interrupt.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <assert.h>
#include <types.h>
#include <api/failures.h>
#include <api/invocation.h>
#include <api/syscall.h>
#include <machine/io.h>
#include <object/structures.h>
#include <object/interrupt.h>
#include <object/cnode.h>
#include <object/notification.h>
#include <kernel/cspace.h>
#include <kernel/thread.h>
#include <model/statedata.h>
#include <machine/timer.h>
#include <plat/machine/timer.h>
#include <smp/ipi.h>

exception_t
decodeIRQControlInvocation(word_t invLabel, word_t length,
                           cte_t *srcSlot, extra_caps_t excaps,
                           word_t *buffer)
{
    if (invLabel == IRQIssueIRQHandler) {
        word_t index, depth, irq_w;
        irq_t irq;
        cte_t *destSlot;
        cap_t cnodeCap;
        lookupSlot_ret_t lu_ret;
        exception_t status;

        if (length < 3 || excaps.excaprefs[0] == NULL) {
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }
        irq_w = getSyscallArg(0, buffer);
        irq = (irq_t) irq_w;
        index = getSyscallArg(1, buffer);
        depth = getSyscallArg(2, buffer);

        cnodeCap = excaps.excaprefs[0]->cap;

        status = Arch_checkIRQ(irq_w);
        if (status != EXCEPTION_NONE) {
            return status;
        }

        if (isIRQActive(irq)) {
            current_syscall_error.type = seL4_RevokeFirst;
            userError("Rejecting request for IRQ %u. Already active.", (int)irq);
            return EXCEPTION_SYSCALL_ERROR;
        }

        lu_ret = lookupTargetSlot(cnodeCap, index, depth);
        if (lu_ret.status != EXCEPTION_NONE) {
            userError("Target slot for new IRQ Handler cap invalid: cap %lu, IRQ %u.",
                      getExtraCPtr(buffer, 0), (int)irq);
            return lu_ret.status;
        }
        destSlot = lu_ret.slot;

        status = ensureEmptySlot(destSlot);
        if (status != EXCEPTION_NONE) {
            userError("Target slot for new IRQ Handler cap not empty: cap %lu, IRQ %u.",
                      getExtraCPtr(buffer, 0), (int)irq);
            return status;
        }

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return invokeIRQControl(irq, destSlot, srcSlot);
    } else {
        return Arch_decodeIRQControlInvocation(invLabel, length, srcSlot, excaps, buffer);
    }
}

exception_t
invokeIRQControl(irq_t irq, cte_t *handlerSlot, cte_t *controlSlot)
{
    setIRQState(IRQSignal, irq);
    cteInsert(cap_irq_handler_cap_new(irq), controlSlot, handlerSlot);

    return EXCEPTION_NONE;
}

exception_t
decodeIRQHandlerInvocation(word_t invLabel, irq_t irq,
                           extra_caps_t excaps)
{
    switch (invLabel) {
    case IRQAckIRQ:
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        invokeIRQHandler_AckIRQ(irq);
        return EXCEPTION_NONE;

    case IRQSetIRQHandler: {
        cap_t ntfnCap;
        cte_t *slot;

        if (excaps.excaprefs[0] == NULL) {
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }
        ntfnCap = excaps.excaprefs[0]->cap;
        slot = excaps.excaprefs[0];

        if (cap_get_capType(ntfnCap) != cap_notification_cap ||
                !cap_notification_cap_get_capNtfnCanSend(ntfnCap)) {
            if (cap_get_capType(ntfnCap) != cap_notification_cap) {
                userError("IRQSetHandler: provided cap is not an notification capability.");
            } else {
                userError("IRQSetHandler: caller does not have send rights on the endpoint.");
            }
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        invokeIRQHandler_SetIRQHandler(irq, ntfnCap, slot);
        return EXCEPTION_NONE;
    }

    case IRQClearIRQHandler:
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        invokeIRQHandler_ClearIRQHandler(irq);
        return EXCEPTION_NONE;

    default:
        userError("IRQHandler: Illegal operation.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
}

void
invokeIRQHandler_AckIRQ(irq_t irq)
{
    maskInterrupt(false, irq);
}

void
invokeIRQHandler_SetIRQHandler(irq_t irq, cap_t cap, cte_t *slot)
{
    cte_t *irqSlot;

    irqSlot = intStateIRQNode + irq;
    /** GHOSTUPD: "(True, gs_set_assn cteDeleteOne_'proc (-1))" */
    cteDeleteOne(irqSlot);
    cteInsert(cap, slot, irqSlot);
}

void
invokeIRQHandler_ClearIRQHandler(irq_t irq)
{
    cte_t *irqSlot;

    irqSlot = intStateIRQNode + irq;
    /** GHOSTUPD: "(True, gs_set_assn cteDeleteOne_'proc (-1))" */
    cteDeleteOne(irqSlot);
}

void
deletingIRQHandler(irq_t irq)
{
    cte_t *slot;

    slot = intStateIRQNode + irq;
    /** GHOSTUPD: "(True, gs_set_assn cteDeleteOne_'proc (ucast cap_notification_cap))" */
    cteDeleteOne(slot);
}

void
deletedIRQHandler(irq_t irq)
{
    setIRQState(IRQInactive, irq);
}

void
handleInterrupt(irq_t irq)
{
    if (unlikely(irq > maxIRQ)) {
        /* mask, ack and pretend it didn't happen. We assume that because
         * the interrupt controller for the platform returned this IRQ that
         * it is safe to use in mask and ack operations, even though it is
         * above the claimed maxIRQ. i.e. we're assuming maxIRQ is wrong */
        printf("Received IRQ %d, which is above the platforms maxIRQ of %d\n", (int)irq, (int)maxIRQ);
        maskInterrupt(true, irq);
        ackInterrupt(irq);
        return;
    }
    switch (intStateIRQTable[irq]) {
    case IRQSignal: {
        cap_t cap;

        cap = intStateIRQNode[irq].cap;

        if (cap_get_capType(cap) == cap_notification_cap &&
                cap_notification_cap_get_capNtfnCanSend(cap)) {
            sendSignal(NTFN_PTR(cap_notification_cap_get_capNtfnPtr(cap)),
                       cap_notification_cap_get_capNtfnBadge(cap));
        } else {
#ifdef CONFIG_IRQ_REPORTING
            printf("Undelivered IRQ: %d\n", (int)irq);
#endif
        }
        maskInterrupt(true, irq);
        break;
    }

    case IRQTimer:
        timerTick();
        resetTimer();
        break;

#ifdef ENABLE_SMP_SUPPORT
    case IRQIPI:
        handleIPI(irq, true);
        break;
#endif /* ENABLE_SMP_SUPPORT */

    case IRQReserved:
#ifdef CONFIG_IRQ_REPORTING
        printf("Received reserved IRQ: %d", (int)irq);
#endif
        handleReservedIRQ(irq);
        break;

    case IRQInactive:
        /*
         * This case shouldn't happen anyway unless the hardware or
         * platform code is broken. Hopefully masking it again should make
         * the interrupt go away.
         */
        maskInterrupt(true, irq);
#ifdef CONFIG_IRQ_REPORTING
        printf("Received disabled IRQ: %d\n", (int)irq);
#endif
        break;

    default:
        /* No corresponding haskell error */
        fail("Invalid IRQ state");
    }

    ackInterrupt(irq);
}

bool_t
isIRQActive(irq_t irq)
{
    return intStateIRQTable[irq] != IRQInactive;
}

void
setIRQState(irq_state_t irqState, irq_t irq)
{
    intStateIRQTable[irq] = irqState;
    maskInterrupt(irqState == IRQInactive, irq);
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/object/notification.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <assert.h>

#include <types.h>
#include <kernel/thread.h>
#include <object/structures.h>
#include <object/tcb.h>
#include <object/endpoint.h>
#include <model/statedata.h>
#include <machine/io.h>

#include <object/notification.h>

static inline tcb_queue_t PURE
ntfn_ptr_get_queue(notification_t *ntfnPtr)
{
    tcb_queue_t ntfn_queue;

    ntfn_queue.head = (tcb_t*)notification_ptr_get_ntfnQueue_head(ntfnPtr);
    ntfn_queue.end = (tcb_t*)notification_ptr_get_ntfnQueue_tail(ntfnPtr);

    return ntfn_queue;
}

static inline void
ntfn_ptr_set_queue(notification_t *ntfnPtr, tcb_queue_t ntfn_queue)
{
    notification_ptr_set_ntfnQueue_head(ntfnPtr, (word_t)ntfn_queue.head);
    notification_ptr_set_ntfnQueue_tail(ntfnPtr, (word_t)ntfn_queue.end);
}

static inline void
ntfn_set_active(notification_t *ntfnPtr, word_t badge)
{
    notification_ptr_set_state(ntfnPtr, NtfnState_Active);
    notification_ptr_set_ntfnMsgIdentifier(ntfnPtr, badge);
}


void
sendSignal(notification_t *ntfnPtr, word_t badge)
{
    switch (notification_ptr_get_state(ntfnPtr)) {
    case NtfnState_Idle: {
        tcb_t *tcb = (tcb_t*)notification_ptr_get_ntfnBoundTCB(ntfnPtr);
        /* Check if we are bound and that thread is waiting for a message */
        if (tcb) {
            if (thread_state_ptr_get_tsType(&tcb->tcbState) == ThreadState_BlockedOnReceive) {
                /* Send and start thread running */
                cancelIPC(tcb);
                setThreadState(tcb, ThreadState_Running);
                setRegister(tcb, badgeRegister, badge);
                possibleSwitchTo(tcb);
#ifdef CONFIG_VTX
            } else if (thread_state_ptr_get_tsType(&tcb->tcbState) == ThreadState_RunningVM) {
#ifdef ENABLE_SMP_SUPPORT
                if (tcb->tcbAffinity != getCurrentCPUIndex()) {
                    ntfn_set_active(ntfnPtr, badge);
                    doRemoteVMCheckBoundNotification(tcb->tcbAffinity, tcb);
                } else
#endif /* ENABLE_SMP_SUPPORT */
                {
                    setThreadState(tcb, ThreadState_Running);
                    setRegister(tcb, badgeRegister, badge);
                    Arch_leaveVMAsyncTransfer(tcb);
                    possibleSwitchTo(tcb);
                }
#endif /* CONFIG_VTX */
            } else {
                /* In particular, this path is taken when a thread
                 * is waiting on a reply cap since BlockedOnReply
                 * would also trigger this path. I.e, a thread
                 * with a bound notification will not be awakened
                 * by signals on that bound notification if it is
                 * in the middle of an seL4_Call.
                 */
                ntfn_set_active(ntfnPtr, badge);
            }
        } else {
            ntfn_set_active(ntfnPtr, badge);
        }
        break;
    }
    case NtfnState_Waiting: {
        tcb_queue_t ntfn_queue;
        tcb_t *dest;

        ntfn_queue = ntfn_ptr_get_queue(ntfnPtr);
        dest = ntfn_queue.head;

        /* Haskell error "WaitingNtfn Notification must have non-empty queue" */
        assert(dest);

        /* Dequeue TCB */
        ntfn_queue = tcbEPDequeue(dest, ntfn_queue);
        ntfn_ptr_set_queue(ntfnPtr, ntfn_queue);

        /* set the thread state to idle if the queue is empty */
        if (!ntfn_queue.head) {
            notification_ptr_set_state(ntfnPtr, NtfnState_Idle);
        }

        setThreadState(dest, ThreadState_Running);
        setRegister(dest, badgeRegister, badge);
        possibleSwitchTo(dest);
        break;
    }

    case NtfnState_Active: {
        word_t badge2;

        badge2 = notification_ptr_get_ntfnMsgIdentifier(ntfnPtr);
        badge2 |= badge;

        notification_ptr_set_ntfnMsgIdentifier(ntfnPtr, badge2);
        break;
    }
    }
}

void
receiveSignal(tcb_t *thread, cap_t cap, bool_t isBlocking)
{
    notification_t *ntfnPtr;

    ntfnPtr = NTFN_PTR(cap_notification_cap_get_capNtfnPtr(cap));

    switch (notification_ptr_get_state(ntfnPtr)) {
    case NtfnState_Idle:
    case NtfnState_Waiting: {
        tcb_queue_t ntfn_queue;

        if (isBlocking) {
            /* Block thread on notification object */
            thread_state_ptr_set_tsType(&thread->tcbState,
                                        ThreadState_BlockedOnNotification);
            thread_state_ptr_set_blockingObject(&thread->tcbState,
                                                NTFN_REF(ntfnPtr));
            scheduleTCB(thread);

            /* Enqueue TCB */
            ntfn_queue = ntfn_ptr_get_queue(ntfnPtr);
            ntfn_queue = tcbEPAppend(thread, ntfn_queue);

            notification_ptr_set_state(ntfnPtr, NtfnState_Waiting);
            ntfn_ptr_set_queue(ntfnPtr, ntfn_queue);
        } else {
            doNBRecvFailedTransfer(thread);
        }

        break;
    }

    case NtfnState_Active:
        setRegister(
            thread, badgeRegister,
            notification_ptr_get_ntfnMsgIdentifier(ntfnPtr));
        notification_ptr_set_state(ntfnPtr, NtfnState_Idle);
        break;
    }
}

void
cancelAllSignals(notification_t *ntfnPtr)
{
    if (notification_ptr_get_state(ntfnPtr) == NtfnState_Waiting) {
        tcb_t *thread = TCB_PTR(notification_ptr_get_ntfnQueue_head(ntfnPtr));

        notification_ptr_set_state(ntfnPtr, NtfnState_Idle);
        notification_ptr_set_ntfnQueue_head(ntfnPtr, 0);
        notification_ptr_set_ntfnQueue_tail(ntfnPtr, 0);

        /* Set all waiting threads to Restart */
        for (; thread; thread = thread->tcbEPNext) {
            setThreadState(thread, ThreadState_Restart);
            SCHED_ENQUEUE(thread);
        }
        rescheduleRequired();
    }
}

void
cancelSignal(tcb_t *threadPtr, notification_t *ntfnPtr)
{
    tcb_queue_t ntfn_queue;

    /* Haskell error "cancelSignal: notification object must be in a waiting" state */
    assert(notification_ptr_get_state(ntfnPtr) == NtfnState_Waiting);

    /* Dequeue TCB */
    ntfn_queue = ntfn_ptr_get_queue(ntfnPtr);
    ntfn_queue = tcbEPDequeue(threadPtr, ntfn_queue);
    ntfn_ptr_set_queue(ntfnPtr, ntfn_queue);

    /* Make notification object idle */
    if (!ntfn_queue.head) {
        notification_ptr_set_state(ntfnPtr, NtfnState_Idle);
    }

    /* Make thread inactive */
    setThreadState(threadPtr, ThreadState_Inactive);
}

void
completeSignal(notification_t *ntfnPtr, tcb_t *tcb)
{
    word_t badge;

    if (likely(tcb && notification_ptr_get_state(ntfnPtr) == NtfnState_Active)) {
        badge = notification_ptr_get_ntfnMsgIdentifier(ntfnPtr);
        setRegister(tcb, badgeRegister, badge);
        notification_ptr_set_state(ntfnPtr, NtfnState_Idle);
    } else {
        fail("tried to complete signal with inactive notification object");
    }
}

static inline void
doUnbindNotification(notification_t *ntfnPtr, tcb_t *tcbptr)
{
    notification_ptr_set_ntfnBoundTCB(ntfnPtr, (word_t) 0);
    tcbptr->tcbBoundNotification = NULL;
}

void
unbindMaybeNotification(notification_t *ntfnPtr)
{
    tcb_t *boundTCB;
    boundTCB = (tcb_t*)notification_ptr_get_ntfnBoundTCB(ntfnPtr);

    if (boundTCB) {
        doUnbindNotification(ntfnPtr, boundTCB);
    }
}

void
unbindNotification(tcb_t *tcb)
{
    notification_t *ntfnPtr;
    ntfnPtr = tcb->tcbBoundNotification;

    if (ntfnPtr) {
        doUnbindNotification(ntfnPtr, tcb);
    }
}

void
bindNotification(tcb_t *tcb, notification_t *ntfnPtr)
{
    notification_ptr_set_ntfnBoundTCB(ntfnPtr, (word_t)tcb);
    tcb->tcbBoundNotification = ntfnPtr;
}

#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/object/objecttype.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <assert.h>
#include <config.h>
#include <types.h>
#include <api/failures.h>
#include <api/syscall.h>
#include <arch/object/objecttype.h>
#include <machine/io.h>
#include <object/objecttype.h>
#include <object/structures.h>
#include <object/notification.h>
#include <object/endpoint.h>
#include <object/cnode.h>
#include <object/interrupt.h>
#include <object/tcb.h>
#include <object/untyped.h>
#include <model/statedata.h>
#include <kernel/thread.h>
#include <kernel/vspace.h>
#include <machine.h>
#include <util.h>
#include <string.h>

word_t getObjectSize(word_t t, word_t userObjSize)
{
    if (t >= seL4_NonArchObjectTypeCount) {
        return Arch_getObjectSize(t);
    } else {
        switch (t) {
        case seL4_TCBObject:
            return seL4_TCBBits;
        case seL4_EndpointObject:
            return seL4_EndpointBits;
        case seL4_NotificationObject:
            return seL4_NotificationBits;
        case seL4_CapTableObject:
            return seL4_SlotBits + userObjSize;
        case seL4_UntypedObject:
            return userObjSize;
        default:
            fail("Invalid object type");
            return 0;
        }
    }
}

deriveCap_ret_t
deriveCap(cte_t *slot, cap_t cap)
{
    deriveCap_ret_t ret;

    if (isArchCap(cap)) {
        return Arch_deriveCap(slot, cap);
    }

    switch (cap_get_capType(cap)) {
    case cap_zombie_cap:
        ret.status = EXCEPTION_NONE;
        ret.cap = cap_null_cap_new();
        break;

    case cap_irq_control_cap:
        ret.status = EXCEPTION_NONE;
        ret.cap = cap_null_cap_new();
        break;

    case cap_untyped_cap:
        ret.status = ensureNoChildren(slot);
        if (ret.status != EXCEPTION_NONE) {
            ret.cap = cap_null_cap_new();
        } else {
            ret.cap = cap;
        }
        break;

    case cap_reply_cap:
        ret.status = EXCEPTION_NONE;
        ret.cap = cap_null_cap_new();
        break;

    default:
        ret.status = EXCEPTION_NONE;
        ret.cap = cap;
    }

    return ret;
}

finaliseCap_ret_t
finaliseCap(cap_t cap, bool_t final, bool_t exposed)
{
    finaliseCap_ret_t fc_ret;

    if (isArchCap(cap)) {
        return Arch_finaliseCap(cap, final);
    }

    switch (cap_get_capType(cap)) {
    case cap_endpoint_cap:
        if (final) {
            cancelAllIPC(EP_PTR(cap_endpoint_cap_get_capEPPtr(cap)));
        }

        fc_ret.remainder = cap_null_cap_new();
        fc_ret.cleanupInfo = cap_null_cap_new();
        return fc_ret;

    case cap_notification_cap:
        if (final) {
            notification_t *ntfn = NTFN_PTR(cap_notification_cap_get_capNtfnPtr(cap));

            unbindMaybeNotification(ntfn);
            cancelAllSignals(ntfn);
        }
        fc_ret.remainder = cap_null_cap_new();
        fc_ret.cleanupInfo = cap_null_cap_new();
        return fc_ret;

    case cap_reply_cap:
    case cap_null_cap:
    case cap_domain_cap:
        fc_ret.remainder = cap_null_cap_new();
        fc_ret.cleanupInfo = cap_null_cap_new();
        return fc_ret;
    }

    if (exposed) {
        fail("finaliseCap: failed to finalise immediately.");
    }

    switch (cap_get_capType(cap)) {
    case cap_cnode_cap: {
        if (final) {
            fc_ret.remainder =
                Zombie_new(
                    1ul << cap_cnode_cap_get_capCNodeRadix(cap),
                    cap_cnode_cap_get_capCNodeRadix(cap),
                    cap_cnode_cap_get_capCNodePtr(cap)
                );
            fc_ret.cleanupInfo = cap_null_cap_new();
            return fc_ret;
        }
        break;
    }

    case cap_thread_cap: {
        if (final) {
            tcb_t *tcb;
            cte_t *cte_ptr;

            tcb = TCB_PTR(cap_thread_cap_get_capTCBPtr(cap));
            SMP_COND_STATEMENT(remoteTCBStall(tcb);)
            cte_ptr = TCB_PTR_CTE_PTR(tcb, tcbCTable);
            unbindNotification(tcb);
            suspend(tcb);
#ifdef CONFIG_DEBUG_BUILD
            tcbDebugRemove(tcb);
#endif
            Arch_prepareThreadDelete(tcb);
            fc_ret.remainder =
                Zombie_new(
                    tcbArchCNodeEntries,
                    ZombieType_ZombieTCB,
                    CTE_REF(cte_ptr)
                );
            fc_ret.cleanupInfo = cap_null_cap_new();
            return fc_ret;
        }
        break;
    }

    case cap_zombie_cap:
        fc_ret.remainder = cap;
        fc_ret.cleanupInfo = cap_null_cap_new();
        return fc_ret;

    case cap_irq_handler_cap:
        if (final) {
            irq_t irq = cap_irq_handler_cap_get_capIRQ(cap);

            deletingIRQHandler(irq);

            fc_ret.remainder = cap_null_cap_new();
            fc_ret.cleanupInfo = cap;
            return fc_ret;
        }
        break;
    }

    fc_ret.remainder = cap_null_cap_new();
    fc_ret.cleanupInfo = cap_null_cap_new();
    return fc_ret;
}

bool_t CONST
hasCancelSendRights(cap_t cap)
{
    switch (cap_get_capType(cap)) {
    case cap_endpoint_cap:
        return cap_endpoint_cap_get_capCanSend(cap) &&
               cap_endpoint_cap_get_capCanReceive(cap) &&
               cap_endpoint_cap_get_capCanGrant(cap);

    default:
        return false;
    }
}

bool_t CONST
sameRegionAs(cap_t cap_a, cap_t cap_b)
{
    switch (cap_get_capType(cap_a)) {
    case cap_untyped_cap:
        if (cap_get_capIsPhysical(cap_b)) {
            word_t aBase, bBase, aTop, bTop;

            aBase = (word_t)WORD_PTR(cap_untyped_cap_get_capPtr(cap_a));
            bBase = (word_t)cap_get_capPtr(cap_b);

            aTop = aBase + MASK(cap_untyped_cap_get_capBlockSize(cap_a));
            bTop = bBase + MASK(cap_get_capSizeBits(cap_b));

            return (aBase <= bBase) && (bTop <= aTop) && (bBase <= bTop);
        }
        break;

    case cap_endpoint_cap:
        if (cap_get_capType(cap_b) == cap_endpoint_cap) {
            return cap_endpoint_cap_get_capEPPtr(cap_a) ==
                   cap_endpoint_cap_get_capEPPtr(cap_b);
        }
        break;

    case cap_notification_cap:
        if (cap_get_capType(cap_b) == cap_notification_cap) {
            return cap_notification_cap_get_capNtfnPtr(cap_a) ==
                   cap_notification_cap_get_capNtfnPtr(cap_b);
        }
        break;

    case cap_cnode_cap:
        if (cap_get_capType(cap_b) == cap_cnode_cap) {
            return (cap_cnode_cap_get_capCNodePtr(cap_a) ==
                    cap_cnode_cap_get_capCNodePtr(cap_b)) &&
                   (cap_cnode_cap_get_capCNodeRadix(cap_a) ==
                    cap_cnode_cap_get_capCNodeRadix(cap_b));
        }
        break;

    case cap_thread_cap:
        if (cap_get_capType(cap_b) == cap_thread_cap) {
            return cap_thread_cap_get_capTCBPtr(cap_a) ==
                   cap_thread_cap_get_capTCBPtr(cap_b);
        }
        break;

    case cap_reply_cap:
        if (cap_get_capType(cap_b) == cap_reply_cap) {
            return cap_reply_cap_get_capTCBPtr(cap_a) ==
                   cap_reply_cap_get_capTCBPtr(cap_b);
        }
        break;

    case cap_domain_cap:
        if (cap_get_capType(cap_b) == cap_domain_cap) {
            return true;
        }
        break;

    case cap_irq_control_cap:
        if (cap_get_capType(cap_b) == cap_irq_control_cap ||
                cap_get_capType(cap_b) == cap_irq_handler_cap) {
            return true;
        }
        break;

    case cap_irq_handler_cap:
        if (cap_get_capType(cap_b) == cap_irq_handler_cap) {
            return (irq_t)cap_irq_handler_cap_get_capIRQ(cap_a) ==
                   (irq_t)cap_irq_handler_cap_get_capIRQ(cap_b);
        }
        break;

    default:
        if (isArchCap(cap_a) &&
                isArchCap(cap_b)) {
            return Arch_sameRegionAs(cap_a, cap_b);
        }
        break;
    }

    return false;
}

bool_t CONST
sameObjectAs(cap_t cap_a, cap_t cap_b)
{
    if (cap_get_capType(cap_a) == cap_untyped_cap) {
        return false;
    }
    if (cap_get_capType(cap_a) == cap_irq_control_cap &&
            cap_get_capType(cap_b) == cap_irq_handler_cap) {
        return false;
    }
    if (isArchCap(cap_a) && isArchCap(cap_b)) {
        return Arch_sameObjectAs(cap_a, cap_b);
    }
    return sameRegionAs(cap_a, cap_b);
}

cap_t CONST
updateCapData(bool_t preserve, word_t newData, cap_t cap)
{
    if (isArchCap(cap)) {
        return Arch_updateCapData(preserve, newData, cap);
    }

    switch (cap_get_capType(cap)) {
    case cap_endpoint_cap:
        if (!preserve && cap_endpoint_cap_get_capEPBadge(cap) == 0) {
            return cap_endpoint_cap_set_capEPBadge(cap, newData);
        } else {
            return cap_null_cap_new();
        }

    case cap_notification_cap:
        if (!preserve && cap_notification_cap_get_capNtfnBadge(cap) == 0) {
            return cap_notification_cap_set_capNtfnBadge(cap, newData);
        } else {
            return cap_null_cap_new();
        }

    case cap_cnode_cap: {
        word_t guard, guardSize;
        seL4_CNode_CapData_t w = { .words = { newData } };

        guardSize = seL4_CNode_CapData_get_guardSize(w);

        if (guardSize + cap_cnode_cap_get_capCNodeRadix(cap) > wordBits) {
            return cap_null_cap_new();
        } else {
            cap_t new_cap;

            guard = seL4_CNode_CapData_get_guard(w) & MASK(guardSize);
            new_cap = cap_cnode_cap_set_capCNodeGuard(cap, guard);
            new_cap = cap_cnode_cap_set_capCNodeGuardSize(new_cap,
                                                          guardSize);

            return new_cap;
        }
    }

    default:
        return cap;
    }
}

cap_t CONST
maskCapRights(seL4_CapRights_t cap_rights, cap_t cap)
{
    if (isArchCap(cap)) {
        return Arch_maskCapRights(cap_rights, cap);
    }

    switch (cap_get_capType(cap)) {
    case cap_null_cap:
    case cap_domain_cap:
    case cap_cnode_cap:
    case cap_untyped_cap:
    case cap_reply_cap:
    case cap_irq_control_cap:
    case cap_irq_handler_cap:
    case cap_zombie_cap:
    case cap_thread_cap:
        return cap;

    case cap_endpoint_cap: {
        cap_t new_cap;

        new_cap = cap_endpoint_cap_set_capCanSend(
                      cap, cap_endpoint_cap_get_capCanSend(cap) &
                      seL4_CapRights_get_capAllowWrite(cap_rights));
        new_cap = cap_endpoint_cap_set_capCanReceive(
                      new_cap, cap_endpoint_cap_get_capCanReceive(cap) &
                      seL4_CapRights_get_capAllowRead(cap_rights));
        new_cap = cap_endpoint_cap_set_capCanGrant(
                      new_cap, cap_endpoint_cap_get_capCanGrant(cap) &
                      seL4_CapRights_get_capAllowGrant(cap_rights));

        return new_cap;
    }

    case cap_notification_cap: {
        cap_t new_cap;

        new_cap = cap_notification_cap_set_capNtfnCanSend(
                      cap, cap_notification_cap_get_capNtfnCanSend(cap) &
                      seL4_CapRights_get_capAllowWrite(cap_rights));
        new_cap = cap_notification_cap_set_capNtfnCanReceive(new_cap,
                                                             cap_notification_cap_get_capNtfnCanReceive(cap) &
                                                             seL4_CapRights_get_capAllowRead(cap_rights));

        return new_cap;
    }

    default:
        fail("Invalid cap type"); /* Sentinel for invalid enums */
    }
}

cap_t
createObject(object_t t, void *regionBase, word_t userSize, bool_t deviceMemory)
{
    /* Handle architecture-specific objects. */
    if (t >= (object_t) seL4_NonArchObjectTypeCount) {
        return Arch_createObject(t, regionBase, userSize, deviceMemory);
    }

    /* Create objects. */
    switch ((api_object_t)t) {
    case seL4_TCBObject: {
        tcb_t *tcb;
        tcb = TCB_PTR((word_t)regionBase + TCB_OFFSET);
        /** AUXUPD: "(True, ptr_retyps 1
          (Ptr ((ptr_val \<acute>tcb) - ctcb_offset) :: (cte_C[5]) ptr)
            o (ptr_retyp \<acute>tcb))" */

        /* Setup non-zero parts of the TCB. */

        Arch_initContext(&tcb->tcbArch.tcbContext);
        tcb->tcbTimeSlice = CONFIG_TIME_SLICE;
        tcb->tcbDomain = ksCurDomain;

        /* Initialize the new TCB to the current core */
        SMP_COND_STATEMENT(tcb->tcbAffinity = getCurrentCPUIndex());

#ifdef CONFIG_DEBUG_BUILD
        strlcpy(tcb->tcbName, "child of: '", TCB_NAME_LENGTH);
        strlcat(tcb->tcbName, NODE_STATE(ksCurThread)->tcbName, TCB_NAME_LENGTH);
        strlcat(tcb->tcbName, "'", TCB_NAME_LENGTH);
        tcbDebugAppend(tcb);
#endif /* CONFIG_DEBUG_BUILD */

        return cap_thread_cap_new(TCB_REF(tcb));
    }

    case seL4_EndpointObject:
        /** AUXUPD: "(True, ptr_retyp
          (Ptr (ptr_val \<acute>regionBase) :: endpoint_C ptr))" */
        return cap_endpoint_cap_new(0, true, true, true,
                                    EP_REF(regionBase));

    case seL4_NotificationObject:
        /** AUXUPD: "(True, ptr_retyp
              (Ptr (ptr_val \<acute>regionBase) :: notification_C ptr))" */
        return cap_notification_cap_new(0, true, true,
                                        NTFN_REF(regionBase));

    case seL4_CapTableObject:
        /** AUXUPD: "(True, ptr_arr_retyps (2 ^ (unat \<acute>userSize))
          (Ptr (ptr_val \<acute>regionBase) :: cte_C ptr))" */
        /** GHOSTUPD: "(True, gs_new_cnodes (unat \<acute>userSize)
                                (ptr_val \<acute>regionBase)
                                (4 + unat \<acute>userSize))" */
        return cap_cnode_cap_new(userSize, 0, 0, CTE_REF(regionBase));

    case seL4_UntypedObject:
        /*
         * No objects need to be created; instead, just insert caps into
         * the destination slots.
         */
        return cap_untyped_cap_new(0, !!deviceMemory, userSize, WORD_REF(regionBase));

    default:
        fail("Invalid object type");
    }
}

void
createNewObjects(object_t t, cte_t *parent, slot_range_t slots,
                 void *regionBase, word_t userSize, bool_t deviceMemory)
{
    word_t objectSize;
    void *nextFreeArea;
    word_t i;
    word_t totalObjectSize UNUSED;

    /* ghost check that we're visiting less bytes than the max object size */
    objectSize = getObjectSize(t, userSize);
    totalObjectSize = slots.length << objectSize;
    /** GHOSTUPD: "(gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state = 0
        \<or> \<acute>totalObjectSize <= gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state, id)" */

    /* Create the objects. */
    nextFreeArea = regionBase;
    for (i = 0; i < slots.length; i++) {
        /* Create the object. */
        /** AUXUPD: "(True, typ_region_bytes (ptr_val \<acute> nextFreeArea + ((\<acute> i) << unat (\<acute> objectSize))) (unat (\<acute> objectSize)))" */
        cap_t cap = createObject(t, (void *)((word_t)nextFreeArea + (i << objectSize)), userSize, deviceMemory);

        /* Insert the cap into the user's cspace. */
        insertNewCap(parent, &slots.cnode[slots.offset + i], cap);

        /* Move along to the next region of memory. been merged into a formula of i */
    }
}

exception_t
decodeInvocation(word_t invLabel, word_t length,
                 cptr_t capIndex, cte_t *slot, cap_t cap,
                 extra_caps_t excaps, bool_t block, bool_t call,
                 word_t *buffer)
{
    if (isArchCap(cap)) {
        return Arch_decodeInvocation(invLabel, length, capIndex,
                                     slot, cap, excaps, call, buffer);
    }

    switch (cap_get_capType(cap)) {
    case cap_null_cap:
        userError("Attempted to invoke a null cap #%lu.", capIndex);
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;

    case cap_zombie_cap:
        userError("Attempted to invoke a zombie cap #%lu.", capIndex);
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;

    case cap_endpoint_cap:
        if (unlikely(!cap_endpoint_cap_get_capCanSend(cap))) {
            userError("Attempted to invoke a read-only endpoint cap #%lu.",
                      capIndex);
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performInvocation_Endpoint(
                   EP_PTR(cap_endpoint_cap_get_capEPPtr(cap)),
                   cap_endpoint_cap_get_capEPBadge(cap),
                   cap_endpoint_cap_get_capCanGrant(cap), block, call);

    case cap_notification_cap: {
        if (unlikely(!cap_notification_cap_get_capNtfnCanSend(cap))) {
            userError("Attempted to invoke a read-only notification cap #%lu.",
                      capIndex);
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performInvocation_Notification(
                   NTFN_PTR(cap_notification_cap_get_capNtfnPtr(cap)),
                   cap_notification_cap_get_capNtfnBadge(cap));
    }

    case cap_reply_cap:
        if (unlikely(cap_reply_cap_get_capReplyMaster(cap))) {
            userError("Attempted to invoke an invalid reply cap #%lu.",
                      capIndex);
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return performInvocation_Reply(
                   TCB_PTR(cap_reply_cap_get_capTCBPtr(cap)), slot);

    case cap_thread_cap:
        return decodeTCBInvocation(invLabel, length, cap,
                                   slot, excaps, call, buffer);

    case cap_domain_cap:
        return decodeDomainInvocation(invLabel, length, excaps, buffer);

    case cap_cnode_cap:
        return decodeCNodeInvocation(invLabel, length, cap, excaps, buffer);

    case cap_untyped_cap:
        return decodeUntypedInvocation(invLabel, length, slot, cap, excaps,
                                       call, buffer);

    case cap_irq_control_cap:
        return decodeIRQControlInvocation(invLabel, length, slot,
                                          excaps, buffer);

    case cap_irq_handler_cap:
        return decodeIRQHandlerInvocation(invLabel,
                                          cap_irq_handler_cap_get_capIRQ(cap), excaps);

    default:
        fail("Invalid cap type");
    }
}

exception_t
performInvocation_Endpoint(endpoint_t *ep, word_t badge,
                           bool_t canGrant, bool_t block,
                           bool_t call)
{
    sendIPC(block, call, badge, canGrant, NODE_STATE(ksCurThread), ep);

    return EXCEPTION_NONE;
}

exception_t
performInvocation_Notification(notification_t *ntfn, word_t badge)
{
    sendSignal(ntfn, badge);

    return EXCEPTION_NONE;
}

exception_t
performInvocation_Reply(tcb_t *thread, cte_t *slot)
{
    doReplyTransfer(NODE_STATE(ksCurThread), thread, slot);
    return EXCEPTION_NONE;
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/object/tcb.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <types.h>
#include <api/failures.h>
#include <api/invocation.h>
#include <api/syscall.h>
#include <api/shared_types.h>
#include <machine/io.h>
#include <object/structures.h>
#include <object/objecttype.h>
#include <object/cnode.h>
#include <object/tcb.h>
#include <kernel/cspace.h>
#include <kernel/thread.h>
#include <kernel/vspace.h>
#include <model/statedata.h>
#include <util.h>
#include <string.h>
#include <stdint.h>
#include <arch/smp/ipi_inline.h>

#define NULL_PRIO 0

static exception_t
checkPrio(prio_t prio, tcb_t *auth)
{
    prio_t mcp;

    mcp = auth->tcbMCP;

    /* system invariant: existing MCPs are bounded */
    assert(mcp <= seL4_MaxPrio);

    /* can't assign a priority greater than our own mcp */
    if (prio > mcp) {
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = seL4_MinPrio;
        current_syscall_error.rangeErrorMax = mcp;
        return EXCEPTION_SYSCALL_ERROR;
    }

    return EXCEPTION_NONE;
}

static inline void
addToBitmap(word_t cpu, word_t dom, word_t prio)
{
    word_t l1index;
    word_t l1index_inverted;

    l1index = prio_to_l1index(prio);
    l1index_inverted = invert_l1index(l1index);

    NODE_STATE_ON_CORE(ksReadyQueuesL1Bitmap[dom], cpu) |= BIT(l1index);
    /* we invert the l1 index when accessed the 2nd level of the bitmap in
       order to increase the liklihood that high prio threads l2 index word will
       be on the same cache line as the l1 index word - this makes sure the
       fastpath is fastest for high prio threads */
    NODE_STATE_ON_CORE(ksReadyQueuesL2Bitmap[dom][l1index_inverted], cpu) |= BIT(prio & MASK(wordRadix));
}

static inline void
removeFromBitmap(word_t cpu, word_t dom, word_t prio)
{
    word_t l1index;
    word_t l1index_inverted;

    l1index = prio_to_l1index(prio);
    l1index_inverted = invert_l1index(l1index);
    NODE_STATE_ON_CORE(ksReadyQueuesL2Bitmap[dom][l1index_inverted], cpu) &= ~BIT(prio & MASK(wordRadix));
    if (unlikely(!NODE_STATE_ON_CORE(ksReadyQueuesL2Bitmap[dom][l1index_inverted], cpu))) {
        NODE_STATE_ON_CORE(ksReadyQueuesL1Bitmap[dom], cpu) &= ~BIT(l1index);
    }
}

/* Add TCB to the head of a scheduler queue */
void
tcbSchedEnqueue(tcb_t *tcb)
{
    if (!thread_state_get_tcbQueued(tcb->tcbState)) {
        tcb_queue_t queue;
        dom_t dom;
        prio_t prio;
        word_t idx;

        dom = tcb->tcbDomain;
        prio = tcb->tcbPriority;
        idx = ready_queues_index(dom, prio);
        queue = NODE_STATE_ON_CORE(ksReadyQueues[idx], tcb->tcbAffinity);

        if (!queue.end) { /* Empty list */
            queue.end = tcb;
            addToBitmap(SMP_TERNARY(tcb->tcbAffinity, 0), dom, prio);
        } else {
            queue.head->tcbSchedPrev = tcb;
        }
        tcb->tcbSchedPrev = NULL;
        tcb->tcbSchedNext = queue.head;
        queue.head = tcb;

        NODE_STATE_ON_CORE(ksReadyQueues[idx], tcb->tcbAffinity) = queue;

        thread_state_ptr_set_tcbQueued(&tcb->tcbState, true);
    }
}

/* Add TCB to the end of a scheduler queue */
void
tcbSchedAppend(tcb_t *tcb)
{
    if (!thread_state_get_tcbQueued(tcb->tcbState)) {
        tcb_queue_t queue;
        dom_t dom;
        prio_t prio;
        word_t idx;

        dom = tcb->tcbDomain;
        prio = tcb->tcbPriority;
        idx = ready_queues_index(dom, prio);
        queue = NODE_STATE_ON_CORE(ksReadyQueues[idx], tcb->tcbAffinity);

        if (!queue.head) { /* Empty list */
            queue.head = tcb;
            addToBitmap(SMP_TERNARY(tcb->tcbAffinity, 0), dom, prio);
        } else {
            queue.end->tcbSchedNext = tcb;
        }
        tcb->tcbSchedPrev = queue.end;
        tcb->tcbSchedNext = NULL;
        queue.end = tcb;

        NODE_STATE_ON_CORE(ksReadyQueues[idx], tcb->tcbAffinity) = queue;

        thread_state_ptr_set_tcbQueued(&tcb->tcbState, true);
    }
}

/* Remove TCB from a scheduler queue */
void
tcbSchedDequeue(tcb_t *tcb)
{
    if (thread_state_get_tcbQueued(tcb->tcbState)) {
        tcb_queue_t queue;
        dom_t dom;
        prio_t prio;
        word_t idx;

        dom = tcb->tcbDomain;
        prio = tcb->tcbPriority;
        idx = ready_queues_index(dom, prio);
        queue = NODE_STATE_ON_CORE(ksReadyQueues[idx], tcb->tcbAffinity);

        if (tcb->tcbSchedPrev) {
            tcb->tcbSchedPrev->tcbSchedNext = tcb->tcbSchedNext;
        } else {
            queue.head = tcb->tcbSchedNext;
            if (likely(!tcb->tcbSchedNext)) {
                removeFromBitmap(SMP_TERNARY(tcb->tcbAffinity, 0), dom, prio);
            }
        }

        if (tcb->tcbSchedNext) {
            tcb->tcbSchedNext->tcbSchedPrev = tcb->tcbSchedPrev;
        } else {
            queue.end = tcb->tcbSchedPrev;
        }

        NODE_STATE_ON_CORE(ksReadyQueues[idx], tcb->tcbAffinity) = queue;

        thread_state_ptr_set_tcbQueued(&tcb->tcbState, false);
    }
}

#ifdef CONFIG_DEBUG_BUILD
void tcbDebugAppend(tcb_t *tcb)
{
    /* prepend to the list */
    tcb->tcbDebugPrev = NULL;

    tcb->tcbDebugNext = NODE_STATE_ON_CORE(ksDebugTCBs, tcb->tcbAffinity);

    if (NODE_STATE_ON_CORE(ksDebugTCBs, tcb->tcbAffinity)) {
        NODE_STATE_ON_CORE(ksDebugTCBs, tcb->tcbAffinity)->tcbDebugPrev = tcb;
    }

    NODE_STATE_ON_CORE(ksDebugTCBs, tcb->tcbAffinity) = tcb;
}

void tcbDebugRemove(tcb_t *tcb)
{
    assert(NODE_STATE_ON_CORE(ksDebugTCBs, tcb->tcbAffinity) != NULL);
    if (tcb == NODE_STATE_ON_CORE(ksDebugTCBs, tcb->tcbAffinity)) {
        NODE_STATE_ON_CORE(ksDebugTCBs, tcb->tcbAffinity) = NODE_STATE_ON_CORE(ksDebugTCBs, tcb->tcbAffinity)->tcbDebugNext;
    } else {
        assert(tcb->tcbDebugPrev);
        tcb->tcbDebugPrev->tcbDebugNext = tcb->tcbDebugNext;
    }

    if (tcb->tcbDebugNext) {
        tcb->tcbDebugNext->tcbDebugPrev = tcb->tcbDebugPrev;
    }

    tcb->tcbDebugPrev = NULL;
    tcb->tcbDebugNext = NULL;
}
#endif /* CONFIG_DEBUG_BUILD */

/* Add TCB to the end of an endpoint queue */
tcb_queue_t
tcbEPAppend(tcb_t *tcb, tcb_queue_t queue)
{
    if (!queue.head) { /* Empty list */
        queue.head = tcb;
    } else {
        queue.end->tcbEPNext = tcb;
    }
    tcb->tcbEPPrev = queue.end;
    tcb->tcbEPNext = NULL;
    queue.end = tcb;

    return queue;
}

/* Remove TCB from an endpoint queue */
tcb_queue_t
tcbEPDequeue(tcb_t *tcb, tcb_queue_t queue)
{
    if (tcb->tcbEPPrev) {
        tcb->tcbEPPrev->tcbEPNext = tcb->tcbEPNext;
    } else {
        queue.head = tcb->tcbEPNext;
    }

    if (tcb->tcbEPNext) {
        tcb->tcbEPNext->tcbEPPrev = tcb->tcbEPPrev;
    } else {
        queue.end = tcb->tcbEPPrev;
    }

    return queue;
}

cptr_t PURE
getExtraCPtr(word_t *bufferPtr, word_t i)
{
    return (cptr_t)bufferPtr[seL4_MsgMaxLength + 2 + i];
}

void
setExtraBadge(word_t *bufferPtr, word_t badge,
              word_t i)
{
    bufferPtr[seL4_MsgMaxLength + 2 + i] = badge;
}

void
setupCallerCap(tcb_t *sender, tcb_t *receiver)
{
    cte_t *replySlot, *callerSlot;
    cap_t masterCap UNUSED, callerCap UNUSED;

    setThreadState(sender, ThreadState_BlockedOnReply);
    replySlot = TCB_PTR_CTE_PTR(sender, tcbReply);
    masterCap = replySlot->cap;
    /* Haskell error: "Sender must have a valid master reply cap" */
    assert(cap_get_capType(masterCap) == cap_reply_cap);
    assert(cap_reply_cap_get_capReplyMaster(masterCap));
    assert(TCB_PTR(cap_reply_cap_get_capTCBPtr(masterCap)) == sender);
    callerSlot = TCB_PTR_CTE_PTR(receiver, tcbCaller);
    callerCap = callerSlot->cap;
    /* Haskell error: "Caller cap must not already exist" */
    assert(cap_get_capType(callerCap) == cap_null_cap);
    cteInsert(cap_reply_cap_new(false, TCB_REF(sender)),
              replySlot, callerSlot);
}

void
deleteCallerCap(tcb_t *receiver)
{
    cte_t *callerSlot;

    callerSlot = TCB_PTR_CTE_PTR(receiver, tcbCaller);
    /** GHOSTUPD: "(True, gs_set_assn cteDeleteOne_'proc (ucast cap_reply_cap))" */
    cteDeleteOne(callerSlot);
}

extra_caps_t current_extra_caps;

exception_t
lookupExtraCaps(tcb_t* thread, word_t *bufferPtr, seL4_MessageInfo_t info)
{
    lookupSlot_raw_ret_t lu_ret;
    cptr_t cptr;
    word_t i, length;

    if (!bufferPtr) {
        current_extra_caps.excaprefs[0] = NULL;
        return EXCEPTION_NONE;
    }

    length = seL4_MessageInfo_get_extraCaps(info);

    for (i = 0; i < length; i++) {
        cptr = getExtraCPtr(bufferPtr, i);

        lu_ret = lookupSlot(thread, cptr);
        if (lu_ret.status != EXCEPTION_NONE) {
            current_fault = seL4_Fault_CapFault_new(cptr, false);
            return lu_ret.status;
        }

        current_extra_caps.excaprefs[i] = lu_ret.slot;
    }
    if (i < seL4_MsgMaxExtraCaps) {
        current_extra_caps.excaprefs[i] = NULL;
    }

    return EXCEPTION_NONE;
}

/* Copy IPC MRs from one thread to another */
word_t
copyMRs(tcb_t *sender, word_t *sendBuf, tcb_t *receiver,
        word_t *recvBuf, word_t n)
{
    word_t i;

    /* Copy inline words */
    for (i = 0; i < n && i < n_msgRegisters; i++) {
        setRegister(receiver, msgRegisters[i],
                    getRegister(sender, msgRegisters[i]));
    }

    if (!recvBuf || !sendBuf) {
        return i;
    }

    /* Copy out-of-line words */
    for (; i < n; i++) {
        recvBuf[i + 1] = sendBuf[i + 1];
    }

    return i;
}

#ifdef ENABLE_SMP_SUPPORT
/* This checks if the current updated to scheduler queue is changing the previous scheduling
 * decision made by the scheduler. If its a case, an `irq_reschedule_ipi` is sent */
void
remoteQueueUpdate(tcb_t *tcb)
{
    /* only ipi if the target is for the current domain */
    if (tcb->tcbAffinity != getCurrentCPUIndex() && tcb->tcbDomain == ksCurDomain) {
        tcb_t *targetCurThread = NODE_STATE_ON_CORE(ksCurThread, tcb->tcbAffinity);

        /* reschedule if the target core is idle or we are waking a higher priority thread */
        if (targetCurThread == NODE_STATE_ON_CORE(ksIdleThread, tcb->tcbAffinity)  ||
                tcb->tcbPriority > targetCurThread->tcbPriority) {
            ARCH_NODE_STATE(ipiReschedulePending) |= BIT(tcb->tcbAffinity);
        }
    }
}

/* This makes sure the the TCB is not being run on other core.
 * It would request 'IpiRemoteCall_Stall' to switch the core from this TCB
 * We also request the 'irq_reschedule_ipi' to restore the state of target core */
void
remoteTCBStall(tcb_t *tcb)
{

    if (tcb->tcbAffinity != getCurrentCPUIndex() &&
            NODE_STATE_ON_CORE(ksCurThread, tcb->tcbAffinity) == tcb) {
        doRemoteStall(tcb->tcbAffinity);
        ARCH_NODE_STATE(ipiReschedulePending) |= BIT(tcb->tcbAffinity);
    }
}

static exception_t
invokeTCB_SetAffinity(tcb_t *thread, word_t affinity)
{
    /* remove the tcb from scheduler queue in case it is already in one
     * and add it to new queue if required */
    tcbSchedDequeue(thread);
    migrateTCB(thread, affinity);
    if (isRunnable(thread)) {
        SCHED_APPEND(thread);
    }
    /* reschedule current cpu if tcb moves itself */
    if (thread == NODE_STATE(ksCurThread)) {
        rescheduleRequired();
    }
    return EXCEPTION_NONE;
}

static exception_t
decodeSetAffinity(cap_t cap, word_t length, word_t *buffer)
{
    tcb_t *tcb;
    word_t affinity;

    if (length < 1) {
        userError("TCB SetAffinity: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tcb = TCB_PTR(cap_thread_cap_get_capTCBPtr(cap));

    affinity = getSyscallArg(0, buffer);
    if (affinity >= ksNumCPUs) {
        userError("TCB SetAffinity: Requested CPU does not exist.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeTCB_SetAffinity(tcb, affinity);
}
#endif /* ENABLE_SMP_SUPPORT */

#ifdef CONFIG_HARDWARE_DEBUG_API
static exception_t
invokeConfigureSingleStepping(word_t *buffer, tcb_t *t,
                              uint16_t bp_num, word_t n_instrs)
{
    bool_t bp_was_consumed;

    bp_was_consumed = configureSingleStepping(t, bp_num, n_instrs, false);
    if (n_instrs == 0) {
        unsetBreakpointUsedFlag(t, bp_num);
        setMR(NODE_STATE(ksCurThread), buffer, 0, false);
    } else {
        setBreakpointUsedFlag(t, bp_num);
        setMR(NODE_STATE(ksCurThread), buffer, 0, bp_was_consumed);
    }
    return EXCEPTION_NONE;
}

static exception_t
decodeConfigureSingleStepping(cap_t cap, word_t *buffer)
{
    uint16_t bp_num;
    word_t n_instrs;
    tcb_t *tcb;
    syscall_error_t syserr;

    tcb = TCB_PTR(cap_thread_cap_get_capTCBPtr(cap));

    bp_num = getSyscallArg(0, buffer);
    n_instrs = getSyscallArg(1, buffer);

    syserr = Arch_decodeConfigureSingleStepping(tcb, bp_num, n_instrs, false);
    if (syserr.type != seL4_NoError) {
        current_syscall_error = syserr;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeConfigureSingleStepping(buffer, tcb, bp_num, n_instrs);
}

static exception_t
invokeSetBreakpoint(tcb_t *tcb, uint16_t bp_num,
                    word_t vaddr, word_t type, word_t size, word_t rw)
{
    setBreakpoint(tcb, bp_num, vaddr, type, size, rw);
    /* Signal restore_user_context() to pop the breakpoint context on return. */
    setBreakpointUsedFlag(tcb, bp_num);
    return EXCEPTION_NONE;
}

static exception_t
decodeSetBreakpoint(cap_t cap, word_t *buffer)
{
    uint16_t bp_num;
    word_t vaddr, type, size, rw;
    tcb_t *tcb;
    syscall_error_t error;

    tcb = TCB_PTR(cap_thread_cap_get_capTCBPtr(cap));
    bp_num = getSyscallArg(0, buffer);
    vaddr = getSyscallArg(1, buffer);
    type = getSyscallArg(2, buffer);
    size = getSyscallArg(3, buffer);
    rw = getSyscallArg(4, buffer);

    /* We disallow the user to set breakpoint addresses that are in the kernel
     * vaddr range.
     */
    if (vaddr >= (word_t)kernelBase) {
        userError("Debug: Invalid address %lx: bp addresses must be userspace "
                  "addresses.",
                  vaddr);
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (type != seL4_InstructionBreakpoint && type != seL4_DataBreakpoint) {
        userError("Debug: Unknown breakpoint type %lx.", type);
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 2;
        return EXCEPTION_SYSCALL_ERROR;
    } else if (type == seL4_InstructionBreakpoint) {
        if (size != 0) {
            userError("Debug: Instruction bps must have size of 0.");
            current_syscall_error.type = seL4_InvalidArgument;
            current_syscall_error.invalidArgumentNumber = 3;
            return EXCEPTION_SYSCALL_ERROR;
        }
        if (rw != seL4_BreakOnRead) {
            userError("Debug: Instruction bps must be break-on-read.");
            current_syscall_error.type = seL4_InvalidArgument;
            current_syscall_error.invalidArgumentNumber = 4;
            return EXCEPTION_SYSCALL_ERROR;
        }
        if (bp_num >= seL4_FirstWatchpoint
                && seL4_FirstBreakpoint != seL4_FirstWatchpoint) {
            userError("Debug: Can't specify a watchpoint ID with type seL4_InstructionBreakpoint.");
            current_syscall_error.type = seL4_InvalidArgument;
            current_syscall_error.invalidArgumentNumber = 2;
            return EXCEPTION_SYSCALL_ERROR;
        }
    } else if (type == seL4_DataBreakpoint) {
        if (size == 0) {
            userError("Debug: Data bps cannot have size of 0.");
            current_syscall_error.type = seL4_InvalidArgument;
            current_syscall_error.invalidArgumentNumber = 3;
            return EXCEPTION_SYSCALL_ERROR;
        }
        if (bp_num < seL4_FirstWatchpoint) {
            userError("Debug: Data watchpoints cannot specify non-data watchpoint ID.");
            current_syscall_error.type = seL4_InvalidArgument;
            current_syscall_error.invalidArgumentNumber = 2;
            return EXCEPTION_SYSCALL_ERROR;
        }
    } else if (type == seL4_SoftwareBreakRequest) {
        userError("Debug: Use a software breakpoint instruction to trigger a "
                  "software breakpoint.");
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 2;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (rw != seL4_BreakOnRead && rw != seL4_BreakOnWrite
            && rw != seL4_BreakOnReadWrite) {
        userError("Debug: Unknown access-type %lu.", rw);
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 3;
        return EXCEPTION_SYSCALL_ERROR;
    }
    if (size != 0 && size != 1 && size != 2 && size != 4 && size != 8) {
        userError("Debug: Invalid size %lu.", size);
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 3;
        return EXCEPTION_SYSCALL_ERROR;
    }
    if (size > 0 && vaddr & (size - 1)) {
        /* Just Don't allow unaligned watchpoints. They are undefined
         * both ARM and x86.
         *
         * X86: Intel manuals, vol3, 17.2.5:
         *  "Two-byte ranges must be aligned on word boundaries; 4-byte
         *   ranges must be aligned on doubleword boundaries"
         *  "Unaligned data or I/O breakpoint addresses do not yield valid
         *   results"
         *
         * ARM: ARMv7 manual, C11.11.44:
         *  "A DBGWVR is programmed with a word-aligned address."
         */
        userError("Debug: Unaligned data watchpoint address %lx (size %lx) "
                  "rejected.\n",
                  vaddr, size);

        current_syscall_error.type = seL4_AlignmentError;
        return EXCEPTION_SYSCALL_ERROR;
    }

    error = Arch_decodeSetBreakpoint(tcb, bp_num, vaddr, type, size, rw);
    if (error.type != seL4_NoError) {
        current_syscall_error = error;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeSetBreakpoint(tcb, bp_num,
                               vaddr, type, size, rw);
}

static exception_t
invokeGetBreakpoint(word_t *buffer, tcb_t *tcb, uint16_t bp_num)
{
    getBreakpoint_t res;

    res = getBreakpoint(tcb, bp_num);
    setMR(NODE_STATE(ksCurThread), buffer, 0, res.vaddr);
    setMR(NODE_STATE(ksCurThread), buffer, 1, res.type);
    setMR(NODE_STATE(ksCurThread), buffer, 2, res.size);
    setMR(NODE_STATE(ksCurThread), buffer, 3, res.rw);
    setMR(NODE_STATE(ksCurThread), buffer, 4, res.is_enabled);
    return EXCEPTION_NONE;
}

static exception_t
decodeGetBreakpoint(cap_t cap, word_t *buffer)
{
    tcb_t *tcb;
    uint16_t bp_num;
    syscall_error_t error;

    tcb = TCB_PTR(cap_thread_cap_get_capTCBPtr(cap));
    bp_num = getSyscallArg(0, buffer);

    error = Arch_decodeGetBreakpoint(tcb, bp_num);
    if (error.type != seL4_NoError) {
        current_syscall_error = error;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeGetBreakpoint(buffer, tcb, bp_num);
}

static exception_t
invokeUnsetBreakpoint(tcb_t *tcb, uint16_t bp_num)
{
    /* Maintain the bitfield of in-use breakpoints. */
    unsetBreakpoint(tcb, bp_num);
    unsetBreakpointUsedFlag(tcb, bp_num);
    return EXCEPTION_NONE;
}

static exception_t
decodeUnsetBreakpoint(cap_t cap, word_t *buffer)
{
    tcb_t *tcb;
    uint16_t bp_num;
    syscall_error_t error;

    tcb = TCB_PTR(cap_thread_cap_get_capTCBPtr(cap));
    bp_num = getSyscallArg(0, buffer);

    error = Arch_decodeUnsetBreakpoint(tcb, bp_num);
    if (error.type != seL4_NoError) {
        current_syscall_error = error;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeUnsetBreakpoint(tcb, bp_num);
}
#endif /* CONFIG_HARDWARE_DEBUG_API */

static exception_t
invokeSetTLSBase(tcb_t *thread, word_t tls_base)
{
    setRegister(thread, TLS_BASE, tls_base);
    if (thread == NODE_STATE(ksCurThread)) {
        /* If this is the current thread force a reschedule to ensure that any changes
         * to the TLS_BASE are realized */
        rescheduleRequired();
    }

    return EXCEPTION_NONE;
}

static exception_t
decodeSetTLSBase(cap_t cap, word_t length, word_t *buffer)
{
    word_t tls_base;

    if (length < 1) {
        userError("TCB SetTLSBase: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tls_base = getSyscallArg(0, buffer);

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeSetTLSBase(TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)), tls_base);
}

/* The following functions sit in the syscall error monad, but include the
 * exception cases for the preemptible bottom end, as they call the invoke
 * functions directly.  This is a significant deviation from the Haskell
 * spec. */
exception_t
decodeTCBInvocation(word_t invLabel, word_t length, cap_t cap,
                    cte_t* slot, extra_caps_t excaps, bool_t call,
                    word_t *buffer)
{
    /* Stall the core if we are operating on a remote TCB that is currently running */
    SMP_COND_STATEMENT(remoteTCBStall(TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)));)

    switch (invLabel) {
    case TCBReadRegisters:
        /* Second level of decoding */
        return decodeReadRegisters(cap, length, call, buffer);

    case TCBWriteRegisters:
        return decodeWriteRegisters(cap, length, buffer);

    case TCBCopyRegisters:
        return decodeCopyRegisters(cap, length, excaps, buffer);

    case TCBSuspend:
        /* Jump straight to the invoke */
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return invokeTCB_Suspend(
                   TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)));

    case TCBResume:
        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        return invokeTCB_Resume(
                   TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)));

    case TCBConfigure:
        return decodeTCBConfigure(cap, length, slot, excaps, buffer);

    case TCBSetPriority:
        return decodeSetPriority(cap, length, excaps, buffer);

    case TCBSetMCPriority:
        return decodeSetMCPriority(cap, length, excaps, buffer);

    case TCBSetSchedParams:
        return decodeSetSchedParams(cap, length, excaps, buffer);

    case TCBSetIPCBuffer:
        return decodeSetIPCBuffer(cap, length, slot, excaps, buffer);

    case TCBSetSpace:
        return decodeSetSpace(cap, length, slot, excaps, buffer);

    case TCBBindNotification:
        return decodeBindNotification(cap, excaps);

    case TCBUnbindNotification:
        return decodeUnbindNotification(cap);

#ifdef ENABLE_SMP_SUPPORT
    case TCBSetAffinity:
        return decodeSetAffinity(cap, length, buffer);
#endif /* ENABLE_SMP_SUPPORT */

        /* There is no notion of arch specific TCB invocations so this needs to go here */
#ifdef CONFIG_VTX
    case TCBSetEPTRoot:
        return decodeSetEPTRoot(cap, excaps);
#endif

#ifdef CONFIG_HARDWARE_DEBUG_API
    case TCBConfigureSingleStepping:
        return decodeConfigureSingleStepping(cap, buffer);

    case TCBSetBreakpoint:
        return decodeSetBreakpoint(cap, buffer);

    case TCBGetBreakpoint:
        return decodeGetBreakpoint(cap, buffer);

    case TCBUnsetBreakpoint:
        return decodeUnsetBreakpoint(cap, buffer);
#endif

    case TCBSetTLSBase:
        return decodeSetTLSBase(cap, length, buffer);

    default:
        /* Haskell: "throw IllegalOperation" */
        userError("TCB: Illegal operation.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
}

enum CopyRegistersFlags {
    CopyRegisters_suspendSource = 0,
    CopyRegisters_resumeTarget = 1,
    CopyRegisters_transferFrame = 2,
    CopyRegisters_transferInteger = 3
};

exception_t
decodeCopyRegisters(cap_t cap, word_t length,
                    extra_caps_t excaps, word_t *buffer)
{
    word_t transferArch;
    tcb_t *srcTCB;
    cap_t source_cap;
    word_t flags;

    if (length < 1 || excaps.excaprefs[0] == NULL) {
        userError("TCB CopyRegisters: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    flags = getSyscallArg(0, buffer);

    transferArch = Arch_decodeTransfer(flags >> 8);

    source_cap = excaps.excaprefs[0]->cap;

    if (cap_get_capType(source_cap) == cap_thread_cap) {
        srcTCB = TCB_PTR(cap_thread_cap_get_capTCBPtr(source_cap));
    } else {
        userError("TCB CopyRegisters: Invalid source TCB.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeTCB_CopyRegisters(
               TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)), srcTCB,
               flags & BIT(CopyRegisters_suspendSource),
               flags & BIT(CopyRegisters_resumeTarget),
               flags & BIT(CopyRegisters_transferFrame),
               flags & BIT(CopyRegisters_transferInteger),
               transferArch);

}

enum ReadRegistersFlags {
    ReadRegisters_suspend = 0
};

exception_t
decodeReadRegisters(cap_t cap, word_t length, bool_t call,
                    word_t *buffer)
{
    word_t transferArch, flags, n;
    tcb_t* thread;

    if (length < 2) {
        userError("TCB ReadRegisters: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    flags = getSyscallArg(0, buffer);
    n     = getSyscallArg(1, buffer);

    if (n < 1 || n > n_frameRegisters + n_gpRegisters) {
        userError("TCB ReadRegisters: Attempted to read an invalid number of registers (%d).",
                  (int)n);
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 1;
        current_syscall_error.rangeErrorMax = n_frameRegisters +
                                              n_gpRegisters;
        return EXCEPTION_SYSCALL_ERROR;
    }

    transferArch = Arch_decodeTransfer(flags >> 8);

    thread = TCB_PTR(cap_thread_cap_get_capTCBPtr(cap));
    if (thread == NODE_STATE(ksCurThread)) {
        userError("TCB ReadRegisters: Attempted to read our own registers.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeTCB_ReadRegisters(
               TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)),
               flags & BIT(ReadRegisters_suspend),
               n, transferArch, call);
}

enum WriteRegistersFlags {
    WriteRegisters_resume = 0
};

exception_t
decodeWriteRegisters(cap_t cap, word_t length, word_t *buffer)
{
    word_t flags, w;
    word_t transferArch;
    tcb_t* thread;

    if (length < 2) {
        userError("TCB WriteRegisters: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    flags = getSyscallArg(0, buffer);
    w     = getSyscallArg(1, buffer);

    if (length - 2 < w) {
        userError("TCB WriteRegisters: Message too short for requested write size (%d/%d).",
                  (int)(length - 2), (int)w);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    transferArch = Arch_decodeTransfer(flags >> 8);

    thread = TCB_PTR(cap_thread_cap_get_capTCBPtr(cap));
    if (thread == NODE_STATE(ksCurThread)) {
        userError("TCB WriteRegisters: Attempted to write our own registers.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeTCB_WriteRegisters(thread,
                                    flags & BIT(WriteRegisters_resume),
                                    w, transferArch, buffer);
}

/* SetPriority, SetMCPriority, SetSchedParams, SetIPCBuffer and SetSpace are all
 * specialisations of TCBConfigure. */
exception_t
decodeTCBConfigure(cap_t cap, word_t length, cte_t* slot,
                   extra_caps_t rootCaps, word_t *buffer)
{
    cte_t *bufferSlot, *cRootSlot, *vRootSlot;
    cap_t bufferCap, cRootCap, vRootCap;
    deriveCap_ret_t dc_ret;
    cptr_t faultEP;
    word_t cRootData, vRootData, bufferAddr;

    if (length < 4 || rootCaps.excaprefs[0] == NULL
            || rootCaps.excaprefs[1] == NULL
            || rootCaps.excaprefs[2] == NULL) {
        userError("TCB Configure: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    faultEP       = getSyscallArg(0, buffer);
    cRootData     = getSyscallArg(1, buffer);
    vRootData     = getSyscallArg(2, buffer);
    bufferAddr    = getSyscallArg(3, buffer);

    cRootSlot  = rootCaps.excaprefs[0];
    cRootCap   = rootCaps.excaprefs[0]->cap;
    vRootSlot  = rootCaps.excaprefs[1];
    vRootCap   = rootCaps.excaprefs[1]->cap;
    bufferSlot = rootCaps.excaprefs[2];
    bufferCap  = rootCaps.excaprefs[2]->cap;

    if (bufferAddr == 0) {
        bufferSlot = NULL;
    } else {
        dc_ret = deriveCap(bufferSlot, bufferCap);
        if (dc_ret.status != EXCEPTION_NONE) {
            return dc_ret.status;
        }
        bufferCap = dc_ret.cap;

        exception_t e = checkValidIPCBuffer(bufferAddr, bufferCap);
        if (e != EXCEPTION_NONE) {
            return e;
        }
    }

    if (slotCapLongRunningDelete(
                TCB_PTR_CTE_PTR(cap_thread_cap_get_capTCBPtr(cap), tcbCTable)) ||
            slotCapLongRunningDelete(
                TCB_PTR_CTE_PTR(cap_thread_cap_get_capTCBPtr(cap), tcbVTable))) {
        userError("TCB Configure: CSpace or VSpace currently being deleted.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (cRootData != 0) {
        cRootCap = updateCapData(false, cRootData, cRootCap);
    }

    dc_ret = deriveCap(cRootSlot, cRootCap);
    if (dc_ret.status != EXCEPTION_NONE) {
        return dc_ret.status;
    }
    cRootCap = dc_ret.cap;

    if (cap_get_capType(cRootCap) != cap_cnode_cap) {
        userError("TCB Configure: CSpace cap is invalid.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (vRootData != 0) {
        vRootCap = updateCapData(false, vRootData, vRootCap);
    }

    dc_ret = deriveCap(vRootSlot, vRootCap);
    if (dc_ret.status != EXCEPTION_NONE) {
        return dc_ret.status;
    }
    vRootCap = dc_ret.cap;

    if (!isValidVTableRoot(vRootCap)) {
        userError("TCB Configure: VSpace cap is invalid.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeTCB_ThreadControl(
               TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)), slot,
               faultEP, NULL_PRIO, NULL_PRIO,
               cRootCap, cRootSlot,
               vRootCap, vRootSlot,
               bufferAddr, bufferCap,
               bufferSlot, thread_control_update_space |
               thread_control_update_ipc_buffer);
}

exception_t
decodeSetPriority(cap_t cap, word_t length, extra_caps_t excaps, word_t *buffer)
{
    if (length < 1 || excaps.excaprefs[0] == NULL) {
        userError("TCB SetPriority: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    prio_t newPrio = getSyscallArg(0, buffer);
    cap_t authCap = excaps.excaprefs[0]->cap;

    if (cap_get_capType(authCap) != cap_thread_cap) {
        userError("Set priority: authority cap not a TCB.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tcb_t *authTCB = TCB_PTR(cap_thread_cap_get_capTCBPtr(authCap));
    exception_t status = checkPrio(newPrio, authTCB);
    if (status != EXCEPTION_NONE) {
        userError("TCB SetPriority: Requested priority %lu too high (max %lu).",
                  (unsigned long) newPrio, (unsigned long) authTCB->tcbMCP);
        return status;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeTCB_ThreadControl(
               TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)), NULL,
               0, NULL_PRIO, newPrio,
               cap_null_cap_new(), NULL,
               cap_null_cap_new(), NULL,
               0, cap_null_cap_new(),
               NULL, thread_control_update_priority);
}

exception_t
decodeSetMCPriority(cap_t cap, word_t length, extra_caps_t excaps, word_t *buffer)
{
    if (length < 1 || excaps.excaprefs[0] == NULL) {
        userError("TCB SetMCPriority: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    prio_t newMcp = getSyscallArg(0, buffer);
    cap_t authCap = excaps.excaprefs[0]->cap;

    if (cap_get_capType(authCap) != cap_thread_cap) {
        userError("TCB SetMCPriority: authority cap not a TCB.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tcb_t *authTCB = TCB_PTR(cap_thread_cap_get_capTCBPtr(authCap));
    exception_t status = checkPrio(newMcp, authTCB);
    if (status != EXCEPTION_NONE) {
        userError("TCB SetMCPriority: Requested maximum controlled priority %lu too high (max %lu).",
                  (unsigned long) newMcp, (unsigned long) authTCB->tcbMCP);
        return status;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeTCB_ThreadControl(
               TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)), NULL,
               0, newMcp, NULL_PRIO,
               cap_null_cap_new(), NULL,
               cap_null_cap_new(), NULL,
               0, cap_null_cap_new(),
               NULL, thread_control_update_mcp);
}

exception_t
decodeSetSchedParams(cap_t cap, word_t length, extra_caps_t excaps, word_t *buffer)
{
    if (length < 2 || excaps.excaprefs[0] == NULL) {
        userError("TCB SetSchedParams: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    prio_t newMcp = getSyscallArg(0, buffer);
    prio_t newPrio = getSyscallArg(1, buffer);
    cap_t authCap = excaps.excaprefs[0]->cap;

    if (cap_get_capType(authCap) != cap_thread_cap) {
        userError("TCB SetSchedParams: authority cap not a TCB.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tcb_t *authTCB = TCB_PTR(cap_thread_cap_get_capTCBPtr(authCap));
    exception_t status = checkPrio(newMcp, authTCB);
    if (status != EXCEPTION_NONE) {
        userError("TCB SetSchedParams: Requested maximum controlled priority %lu too high (max %lu).",
                  (unsigned long) newMcp, (unsigned long) authTCB->tcbMCP);
        return status;
    }

    status = checkPrio(newPrio, authTCB);
    if (status != EXCEPTION_NONE) {
        userError("TCB SetSchedParams: Requested priority %lu too high (max %lu).",
                  (unsigned long) newMcp, (unsigned long) authTCB->tcbMCP);
        return status;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeTCB_ThreadControl(
               TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)), NULL,
               0, newMcp, newPrio,
               cap_null_cap_new(), NULL,
               cap_null_cap_new(), NULL,
               0, cap_null_cap_new(),
               NULL, thread_control_update_mcp |
               thread_control_update_priority);
}


exception_t
decodeSetIPCBuffer(cap_t cap, word_t length, cte_t* slot,
                   extra_caps_t excaps, word_t *buffer)
{
    cptr_t cptr_bufferPtr;
    cap_t bufferCap;
    cte_t *bufferSlot;

    if (length < 1 || excaps.excaprefs[0] == NULL) {
        userError("TCB SetIPCBuffer: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    cptr_bufferPtr  = getSyscallArg(0, buffer);
    bufferSlot = excaps.excaprefs[0];
    bufferCap  = excaps.excaprefs[0]->cap;

    if (cptr_bufferPtr == 0) {
        bufferSlot = NULL;
    } else {
        exception_t e;
        deriveCap_ret_t dc_ret;

        dc_ret = deriveCap(bufferSlot, bufferCap);
        if (dc_ret.status != EXCEPTION_NONE) {
            return dc_ret.status;
        }
        bufferCap = dc_ret.cap;
        e = checkValidIPCBuffer(cptr_bufferPtr, bufferCap);
        if (e != EXCEPTION_NONE) {
            return e;
        }
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeTCB_ThreadControl(
               TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)), slot,
               0, NULL_PRIO, NULL_PRIO,
               cap_null_cap_new(), NULL,
               cap_null_cap_new(), NULL,
               cptr_bufferPtr, bufferCap,
               bufferSlot, thread_control_update_ipc_buffer);
}

exception_t
decodeSetSpace(cap_t cap, word_t length, cte_t* slot,
               extra_caps_t excaps, word_t *buffer)
{
    cptr_t faultEP;
    word_t cRootData, vRootData;
    cte_t *cRootSlot, *vRootSlot;
    cap_t cRootCap, vRootCap;
    deriveCap_ret_t dc_ret;

    if (length < 3 || excaps.excaprefs[0] == NULL
            || excaps.excaprefs[1] == NULL) {
        userError("TCB SetSpace: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    faultEP   = getSyscallArg(0, buffer);
    cRootData = getSyscallArg(1, buffer);
    vRootData = getSyscallArg(2, buffer);

    cRootSlot  = excaps.excaprefs[0];
    cRootCap   = excaps.excaprefs[0]->cap;
    vRootSlot  = excaps.excaprefs[1];
    vRootCap   = excaps.excaprefs[1]->cap;

    if (slotCapLongRunningDelete(
                TCB_PTR_CTE_PTR(cap_thread_cap_get_capTCBPtr(cap), tcbCTable)) ||
            slotCapLongRunningDelete(
                TCB_PTR_CTE_PTR(cap_thread_cap_get_capTCBPtr(cap), tcbVTable))) {
        userError("TCB SetSpace: CSpace or VSpace currently being deleted.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (cRootData != 0) {
        cRootCap = updateCapData(false, cRootData, cRootCap);
    }

    dc_ret = deriveCap(cRootSlot, cRootCap);
    if (dc_ret.status != EXCEPTION_NONE) {
        return dc_ret.status;
    }
    cRootCap = dc_ret.cap;

    if (cap_get_capType(cRootCap) != cap_cnode_cap) {
        userError("TCB SetSpace: Invalid CNode cap.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (vRootData != 0) {
        vRootCap = updateCapData(false, vRootData, vRootCap);
    }

    dc_ret = deriveCap(vRootSlot, vRootCap);
    if (dc_ret.status != EXCEPTION_NONE) {
        return dc_ret.status;
    }
    vRootCap = dc_ret.cap;

    if (!isValidVTableRoot(vRootCap)) {
        userError("TCB SetSpace: Invalid VSpace cap.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeTCB_ThreadControl(
               TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)), slot,
               faultEP,
               NULL_PRIO, NULL_PRIO,
               cRootCap, cRootSlot,
               vRootCap, vRootSlot,
               0, cap_null_cap_new(), NULL, thread_control_update_space);
}

exception_t
decodeDomainInvocation(word_t invLabel, word_t length, extra_caps_t excaps, word_t *buffer)
{
    word_t domain;
    cap_t tcap;

    if (unlikely(invLabel != DomainSetSet)) {
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (unlikely(length == 0)) {
        userError("Domain Configure: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    } else {
        domain = getSyscallArg(0, buffer);
        if (domain >= CONFIG_NUM_DOMAINS) {
            userError("Domain Configure: invalid domain (%lu >= %u).",
                      domain, CONFIG_NUM_DOMAINS);
            current_syscall_error.type = seL4_InvalidArgument;
            current_syscall_error.invalidArgumentNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }
    }

    if (unlikely(excaps.excaprefs[0] == NULL)) {
        userError("Domain Configure: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tcap = excaps.excaprefs[0]->cap;
    if (unlikely(cap_get_capType(tcap) != cap_thread_cap)) {
        userError("Domain Configure: thread cap required.");
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    setDomain(TCB_PTR(cap_thread_cap_get_capTCBPtr(tcap)), domain);
    return EXCEPTION_NONE;
}

exception_t
decodeBindNotification(cap_t cap, extra_caps_t excaps)
{
    notification_t *ntfnPtr;
    tcb_t *tcb;
    cap_t ntfn_cap;

    if (excaps.excaprefs[0] == NULL) {
        userError("TCB BindNotification: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tcb = TCB_PTR(cap_thread_cap_get_capTCBPtr(cap));

    if (tcb->tcbBoundNotification) {
        userError("TCB BindNotification: TCB already has a bound notification.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    ntfn_cap = excaps.excaprefs[0]->cap;

    if (cap_get_capType(ntfn_cap) == cap_notification_cap) {
        ntfnPtr = NTFN_PTR(cap_notification_cap_get_capNtfnPtr(ntfn_cap));
    } else {
        userError("TCB BindNotification: Notification is invalid.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (!cap_notification_cap_get_capNtfnCanReceive(ntfn_cap)) {
        userError("TCB BindNotification: Insufficient access rights");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if ((tcb_t*)notification_ptr_get_ntfnQueue_head(ntfnPtr)
            || (tcb_t*)notification_ptr_get_ntfnBoundTCB(ntfnPtr)) {
        userError("TCB BindNotification: Notification cannot be bound.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }


    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeTCB_NotificationControl(tcb, ntfnPtr);
}

exception_t
decodeUnbindNotification(cap_t cap)
{
    tcb_t *tcb;

    tcb = TCB_PTR(cap_thread_cap_get_capTCBPtr(cap));

    if (!tcb->tcbBoundNotification) {
        userError("TCB UnbindNotification: TCB already has no bound Notification.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeTCB_NotificationControl(tcb, NULL);
}

/* The following functions sit in the preemption monad and implement the
 * preemptible, non-faulting bottom end of a TCB invocation. */
exception_t
invokeTCB_Suspend(tcb_t *thread)
{
    suspend(thread);
    return EXCEPTION_NONE;
}

exception_t
invokeTCB_Resume(tcb_t *thread)
{
    restart(thread);
    return EXCEPTION_NONE;
}

exception_t
invokeTCB_ThreadControl(tcb_t *target, cte_t* slot,
                        cptr_t faultep, prio_t mcp, prio_t priority,
                        cap_t cRoot_newCap, cte_t *cRoot_srcSlot,
                        cap_t vRoot_newCap, cte_t *vRoot_srcSlot,
                        word_t bufferAddr, cap_t bufferCap,
                        cte_t *bufferSrcSlot,
                        thread_control_flag_t updateFlags)
{
    exception_t e;
    cap_t tCap = cap_thread_cap_new((word_t)target);

    if (updateFlags & thread_control_update_space) {
        target->tcbFaultHandler = faultep;
    }

    if (updateFlags & thread_control_update_mcp) {
        setMCPriority(target, mcp);
    }

    if (updateFlags & thread_control_update_priority) {
        setPriority(target, priority);
    }

    if (updateFlags & thread_control_update_space) {
        cte_t *rootSlot;

        rootSlot = TCB_PTR_CTE_PTR(target, tcbCTable);
        e = cteDelete(rootSlot, true);
        if (e != EXCEPTION_NONE) {
            return e;
        }
        if (sameObjectAs(cRoot_newCap, cRoot_srcSlot->cap) &&
                sameObjectAs(tCap, slot->cap)) {
            cteInsert(cRoot_newCap, cRoot_srcSlot, rootSlot);
        }
    }

    if (updateFlags & thread_control_update_space) {
        cte_t *rootSlot;

        rootSlot = TCB_PTR_CTE_PTR(target, tcbVTable);
        e = cteDelete(rootSlot, true);
        if (e != EXCEPTION_NONE) {
            return e;
        }
        if (sameObjectAs(vRoot_newCap, vRoot_srcSlot->cap) &&
                sameObjectAs(tCap, slot->cap)) {
            cteInsert(vRoot_newCap, vRoot_srcSlot, rootSlot);
        }
    }

    if (updateFlags & thread_control_update_ipc_buffer) {
        cte_t *bufferSlot;

        bufferSlot = TCB_PTR_CTE_PTR(target, tcbBuffer);
        e = cteDelete(bufferSlot, true);
        if (e != EXCEPTION_NONE) {
            return e;
        }
        target->tcbIPCBuffer = bufferAddr;

        Arch_setTCBIPCBuffer(target, bufferAddr);

        if (bufferSrcSlot && sameObjectAs(bufferCap, bufferSrcSlot->cap) &&
                sameObjectAs(tCap, slot->cap)) {
            cteInsert(bufferCap, bufferSrcSlot, bufferSlot);
        }

        if (target == NODE_STATE(ksCurThread)) {
            rescheduleRequired();
        }
    }

    return EXCEPTION_NONE;
}

exception_t
invokeTCB_CopyRegisters(tcb_t *dest, tcb_t *tcb_src,
                        bool_t suspendSource, bool_t resumeTarget,
                        bool_t transferFrame, bool_t transferInteger,
                        word_t transferArch)
{
    if (suspendSource) {
        suspend(tcb_src);
    }

    if (resumeTarget) {
        restart(dest);
    }

    if (transferFrame) {
        word_t i;
        word_t v;
        word_t pc;

        for (i = 0; i < n_frameRegisters; i++) {
            v = getRegister(tcb_src, frameRegisters[i]);
            setRegister(dest, frameRegisters[i], v);
        }

        pc = getRestartPC(dest);
        setNextPC(dest, pc);
    }

    if (transferInteger) {
        word_t i;
        word_t v;

        for (i = 0; i < n_gpRegisters; i++) {
            v = getRegister(tcb_src, gpRegisters[i]);
            setRegister(dest, gpRegisters[i], v);
        }
    }

    Arch_postModifyRegisters(dest);

    if (dest == NODE_STATE(ksCurThread)) {
        /* If we modified the current thread we may need to reschedule
         * due to changing registers are only reloaded in Arch_switchToThread */
        rescheduleRequired();
    }

    return Arch_performTransfer(transferArch, tcb_src, dest);
}

/* ReadRegisters is a special case: replyFromKernel & setMRs are
 * unfolded here, in order to avoid passing the large reply message up
 * to the top level in a global (and double-copying). We prevent the
 * top-level replyFromKernel_success_empty() from running by setting the
 * thread state. Retype does this too.
 */
exception_t
invokeTCB_ReadRegisters(tcb_t *tcb_src, bool_t suspendSource,
                        word_t n, word_t arch, bool_t call)
{
    word_t i, j;
    exception_t e;
    tcb_t *thread;

    thread = NODE_STATE(ksCurThread);

    if (suspendSource) {
        suspend(tcb_src);
    }

    e = Arch_performTransfer(arch, tcb_src, NODE_STATE(ksCurThread));
    if (e != EXCEPTION_NONE) {
        return e;
    }

    if (call) {
        word_t *ipcBuffer;

        ipcBuffer = lookupIPCBuffer(true, thread);

        setRegister(thread, badgeRegister, 0);

        for (i = 0; i < n && i < n_frameRegisters && i < n_msgRegisters; i++) {
            setRegister(thread, msgRegisters[i],
                        getRegister(tcb_src, frameRegisters[i]));
        }

        if (ipcBuffer != NULL && i < n && i < n_frameRegisters) {
            for (; i < n && i < n_frameRegisters; i++) {
                ipcBuffer[i + 1] = getRegister(tcb_src, frameRegisters[i]);
            }
        }

        j = i;

        for (i = 0; i < n_gpRegisters && i + n_frameRegisters < n
                && i + n_frameRegisters < n_msgRegisters; i++) {
            setRegister(thread, msgRegisters[i + n_frameRegisters],
                        getRegister(tcb_src, gpRegisters[i]));
        }

        if (ipcBuffer != NULL && i < n_gpRegisters
                && i + n_frameRegisters < n) {
            for (; i < n_gpRegisters && i + n_frameRegisters < n; i++) {
                ipcBuffer[i + n_frameRegisters + 1] =
                    getRegister(tcb_src, gpRegisters[i]);
            }
        }

        setRegister(thread, msgInfoRegister, wordFromMessageInfo(
                        seL4_MessageInfo_new(0, 0, 0, i + j)));
    }
    setThreadState(thread, ThreadState_Running);

    return EXCEPTION_NONE;
}

exception_t
invokeTCB_WriteRegisters(tcb_t *dest, bool_t resumeTarget,
                         word_t n, word_t arch, word_t *buffer)
{
    word_t i;
    word_t pc;
    exception_t e;
    bool_t archInfo;

    e = Arch_performTransfer(arch, NODE_STATE(ksCurThread), dest);
    if (e != EXCEPTION_NONE) {
        return e;
    }

    if (n > n_frameRegisters + n_gpRegisters) {
        n = n_frameRegisters + n_gpRegisters;
    }

    archInfo = Arch_getSanitiseRegisterInfo(dest);

    for (i = 0; i < n_frameRegisters && i < n; i++) {
        /* Offset of 2 to get past the initial syscall arguments */
        setRegister(dest, frameRegisters[i],
                    sanitiseRegister(frameRegisters[i],
                                     getSyscallArg(i + 2, buffer), archInfo));
    }

    for (i = 0; i < n_gpRegisters && i + n_frameRegisters < n; i++) {
        setRegister(dest, gpRegisters[i],
                    sanitiseRegister(gpRegisters[i],
                                     getSyscallArg(i + n_frameRegisters + 2,
                                                   buffer), archInfo));
    }

    pc = getRestartPC(dest);
    setNextPC(dest, pc);

    Arch_postModifyRegisters(dest);

    if (resumeTarget) {
        restart(dest);
    }

    if (dest == NODE_STATE(ksCurThread)) {
        /* If we modified the current thread we may need to reschedule
         * due to changing registers are only reloaded in Arch_switchToThread */
        rescheduleRequired();
    }

    return EXCEPTION_NONE;
}

exception_t
invokeTCB_NotificationControl(tcb_t *tcb, notification_t *ntfnPtr)
{
    if (ntfnPtr) {
        bindNotification(tcb, ntfnPtr);
    } else {
        unbindNotification(tcb);
    }

    return EXCEPTION_NONE;
}

#ifdef CONFIG_DEBUG_BUILD
void
setThreadName(tcb_t *tcb, const char *name)
{
    strlcpy(tcb->tcbName, name, TCB_NAME_LENGTH);
}
#endif

word_t
setMRs_syscall_error(tcb_t *thread, word_t *receiveIPCBuffer)
{
    switch (current_syscall_error.type) {
    case seL4_InvalidArgument:
        return setMR(thread, receiveIPCBuffer, 0,
                     current_syscall_error.invalidArgumentNumber);

    case seL4_InvalidCapability:
        return setMR(thread, receiveIPCBuffer, 0,
                     current_syscall_error.invalidCapNumber);

    case seL4_IllegalOperation:
        return 0;

    case seL4_RangeError:
        setMR(thread, receiveIPCBuffer, 0,
              current_syscall_error.rangeErrorMin);
        return setMR(thread, receiveIPCBuffer, 1,
                     current_syscall_error.rangeErrorMax);

    case seL4_AlignmentError:
        return 0;

    case seL4_FailedLookup:
        setMR(thread, receiveIPCBuffer, 0,
              current_syscall_error.failedLookupWasSource ? 1 : 0);
        return setMRs_lookup_failure(thread, receiveIPCBuffer,
                                     current_lookup_fault, 1);

    case seL4_TruncatedMessage:
    case seL4_DeleteFirst:
    case seL4_RevokeFirst:
        return 0;
    case seL4_NotEnoughMemory:
        return setMR(thread, receiveIPCBuffer, 0,
                     current_syscall_error.memoryLeft);
    default:
        fail("Invalid syscall error");
    }
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/object/untyped.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <types.h>
#include <api/failures.h>
#include <api/syscall.h>
#include <api/invocation.h>
#include <machine/io.h>
#include <object/structures.h>
#include <object/untyped.h>
#include <object/objecttype.h>
#include <object/cnode.h>
#include <kernel/cspace.h>
#include <kernel/thread.h>
#include <util.h>

static word_t
alignUp(word_t baseValue, word_t alignment)
{
    return (baseValue + (BIT(alignment) - 1)) & ~MASK(alignment);
}

exception_t
decodeUntypedInvocation(word_t invLabel, word_t length, cte_t *slot,
                        cap_t cap, extra_caps_t excaps,
                        bool_t call, word_t *buffer)
{
    word_t newType, userObjSize, nodeIndex;
    word_t nodeDepth, nodeOffset, nodeWindow;
    cte_t *rootSlot UNUSED;
    exception_t status;
    cap_t nodeCap;
    lookupSlot_ret_t lu_ret;
    word_t nodeSize;
    word_t i;
    slot_range_t slots;
    word_t freeRef, alignedFreeRef, objectSize, untypedFreeBytes;
    word_t freeIndex;
    bool_t deviceMemory;
    bool_t reset;

    /* Ensure operation is valid. */
    if (invLabel != UntypedRetype) {
        userError("Untyped cap: Illegal operation attempted.");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* Ensure message length valid. */
    if (length < 6 || excaps.excaprefs[0] == NULL) {
        userError("Untyped invocation: Truncated message.");
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* Fetch arguments. */
    newType     = getSyscallArg(0, buffer);
    userObjSize = getSyscallArg(1, buffer);
    nodeIndex   = getSyscallArg(2, buffer);
    nodeDepth   = getSyscallArg(3, buffer);
    nodeOffset  = getSyscallArg(4, buffer);
    nodeWindow  = getSyscallArg(5, buffer);

    rootSlot = excaps.excaprefs[0];

    /* Is the requested object type valid? */
    if (newType >= seL4_ObjectTypeCount) {
        userError("Untyped Retype: Invalid object type.");
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    objectSize = getObjectSize(newType, userObjSize);

    /* Exclude impossibly large object sizes. getObjectSize can overflow if userObjSize
       is close to 2^wordBits, which is nonsensical in any case, so we check that this
       did not happen. userObjSize will always need to be less than wordBits. */
    if (userObjSize >= wordBits || objectSize > seL4_MaxUntypedBits) {
        userError("Untyped Retype: Invalid object size.");
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 0;
        current_syscall_error.rangeErrorMax = seL4_MaxUntypedBits;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* If the target object is a CNode, is it at least size 1? */
    if (newType == seL4_CapTableObject && userObjSize == 0) {
        userError("Untyped Retype: Requested CapTable size too small.");
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* If the target object is a Untyped, is it at least size 4? */
    if (newType == seL4_UntypedObject && userObjSize < seL4_MinUntypedBits) {
        userError("Untyped Retype: Requested UntypedItem size too small.");
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* Lookup the destination CNode (where our caps will be placed in). */
    if (nodeDepth == 0) {
        nodeCap = excaps.excaprefs[0]->cap;
    } else {
        cap_t rootCap = excaps.excaprefs[0]->cap;
        lu_ret = lookupTargetSlot(rootCap, nodeIndex, nodeDepth);
        if (lu_ret.status != EXCEPTION_NONE) {
            userError("Untyped Retype: Invalid destination address.");
            return lu_ret.status;
        }
        nodeCap = lu_ret.slot->cap;
    }

    /* Is the destination actually a CNode? */
    if (cap_get_capType(nodeCap) != cap_cnode_cap) {
        userError("Untyped Retype: Destination cap invalid or read-only.");
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = 0;
        current_lookup_fault = lookup_fault_missing_capability_new(nodeDepth);
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* Is the region where the user wants to put the caps valid? */
    nodeSize = 1ul << cap_cnode_cap_get_capCNodeRadix(nodeCap);
    if (nodeOffset > nodeSize - 1) {
        userError("Untyped Retype: Destination node offset #%d too large.",
                  (int)nodeOffset);
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 0;
        current_syscall_error.rangeErrorMax = nodeSize - 1;
        return EXCEPTION_SYSCALL_ERROR;
    }
    if (nodeWindow < 1 || nodeWindow > CONFIG_RETYPE_FAN_OUT_LIMIT) {
        userError("Untyped Retype: Number of requested objects (%d) too small or large.",
                  (int)nodeWindow);
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 1;
        current_syscall_error.rangeErrorMax = CONFIG_RETYPE_FAN_OUT_LIMIT;
        return EXCEPTION_SYSCALL_ERROR;
    }
    if (nodeWindow > nodeSize - nodeOffset) {
        userError("Untyped Retype: Requested destination window overruns size of node.");
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 1;
        current_syscall_error.rangeErrorMax = nodeSize - nodeOffset;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* Ensure that the destination slots are all empty. */
    slots.cnode = CTE_PTR(cap_cnode_cap_get_capCNodePtr(nodeCap));
    slots.offset = nodeOffset;
    slots.length = nodeWindow;
    for (i = nodeOffset; i < nodeOffset + nodeWindow; i++) {
        status = ensureEmptySlot(slots.cnode + i);
        if (status != EXCEPTION_NONE) {
            userError("Untyped Retype: Slot #%d in destination window non-empty.",
                      (int)i);
            return status;
        }
    }

    /*
     * Determine where in the Untyped region we should start allocating new
     * objects.
     *
     * If we have no children, we can start allocating from the beginning of
     * our untyped, regardless of what the "free" value in the cap states.
     * (This may happen if all of the objects beneath us got deleted).
     *
     * If we have children, we just keep allocating from the "free" value
     * recorded in the cap.
     */
    status = ensureNoChildren(slot);
    if (status != EXCEPTION_NONE) {
        freeIndex = cap_untyped_cap_get_capFreeIndex(cap);
        reset = false;
    } else {
        freeIndex = 0;
        reset = true;
    }
    freeRef = GET_FREE_REF(cap_untyped_cap_get_capPtr(cap), freeIndex);

    /*
     * Determine the maximum number of objects we can create, and return an
     * error if we don't have enough space.
     *
     * We don't need to worry about alignment in this case, because if anything
     * fits, it will also fit aligned up (by packing it on the right hand side
     * of the untyped).
     */
    untypedFreeBytes = BIT(cap_untyped_cap_get_capBlockSize(cap)) -
                       FREE_INDEX_TO_OFFSET(freeIndex);

    if ((untypedFreeBytes >> objectSize) < nodeWindow) {
        userError("Untyped Retype: Insufficient memory "
                  "(%lu * %lu bytes needed, %lu bytes available).",
                  (word_t)nodeWindow,
                  (objectSize >= wordBits ? -1 : (1ul << objectSize)),
                  (word_t)(untypedFreeBytes));
        current_syscall_error.type = seL4_NotEnoughMemory;
        current_syscall_error.memoryLeft = untypedFreeBytes;
        return EXCEPTION_SYSCALL_ERROR;
    }

    deviceMemory = cap_untyped_cap_get_capIsDevice(cap);
    if ((deviceMemory && !Arch_isFrameType(newType))
            && newType != seL4_UntypedObject) {
        userError("Untyped Retype: Creating kernel objects with device untyped");
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* Align up the free region so that it is aligned to the target object's
     * size. */
    alignedFreeRef = alignUp(freeRef, objectSize);

    /* Perform the retype. */
    setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
    return invokeUntyped_Retype(slot, reset,
                                (void*)alignedFreeRef, newType, userObjSize,
                                slots, deviceMemory);
}

static exception_t
resetUntypedCap(cte_t *srcSlot)
{
    cap_t prev_cap = srcSlot->cap;
    word_t block_size = cap_untyped_cap_get_capBlockSize(prev_cap);
    void *regionBase = WORD_PTR(cap_untyped_cap_get_capPtr(prev_cap));
    int chunk = CONFIG_RESET_CHUNK_BITS;
    word_t offset = FREE_INDEX_TO_OFFSET(cap_untyped_cap_get_capFreeIndex(prev_cap));
    exception_t status;
    bool_t deviceMemory = cap_untyped_cap_get_capIsDevice(prev_cap);

    if (offset == 0) {
        return EXCEPTION_NONE;
    }

    /** AUXUPD: "(True, typ_region_bytes (ptr_val \<acute>regionBase)
        (unat \<acute>block_size))" */
    /** GHOSTUPD: "(True, gs_clear_region (ptr_val \<acute>regionBase)
        (unat \<acute>block_size))" */

    if (deviceMemory || block_size < chunk) {
        if (! deviceMemory) {
            clearMemory(regionBase, block_size);
        }
        srcSlot->cap = cap_untyped_cap_set_capFreeIndex(prev_cap, 0);
    } else {
        for (offset = ROUND_DOWN(offset - 1, chunk);
                offset != - BIT (chunk); offset -= BIT (chunk)) {
            clearMemory(GET_OFFSET_FREE_PTR(regionBase, offset), chunk);
            srcSlot->cap = cap_untyped_cap_set_capFreeIndex(prev_cap, OFFSET_TO_FREE_INDEX(offset));
            status = preemptionPoint();
            if (status != EXCEPTION_NONE) {
                return status;
            }
        }
    }
    return EXCEPTION_NONE;
}

exception_t
invokeUntyped_Retype(cte_t *srcSlot,
                     bool_t reset, void* retypeBase,
                     object_t newType, word_t userSize,
                     slot_range_t destSlots, bool_t deviceMemory)
{
    word_t freeRef;
    word_t totalObjectSize;
    void *regionBase = WORD_PTR(cap_untyped_cap_get_capPtr(srcSlot->cap));
    exception_t status;

    freeRef = GET_FREE_REF(regionBase, cap_untyped_cap_get_capFreeIndex(srcSlot->cap));

    if (reset) {
        status = resetUntypedCap(srcSlot);
        if (status != EXCEPTION_NONE) {
            return status;
        }
    }

    /* Update the amount of free space left in this untyped cap. */
    totalObjectSize = destSlots.length << getObjectSize(newType, userSize);
    freeRef = (word_t)retypeBase + totalObjectSize;
    srcSlot->cap = cap_untyped_cap_set_capFreeIndex(srcSlot->cap,
                                                    GET_FREE_INDEX(regionBase, freeRef));

    /* Create new objects and caps. */
    createNewObjects(newType, srcSlot, destSlots, retypeBase, userSize,
                     deviceMemory);

    return EXCEPTION_NONE;
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/plat/pc99/machine/acpi.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <util.h>
#include <assert.h>
#include <machine/io.h>
#include <linker.h>
#include <plat/machine.h>
#include <plat/machine/acpi.h>
#include <plat/machine/devices.h>

enum acpi_type {
    ACPI_RSDP,
    ACPI_RSDT
};

/* DMA Remapping Reporting Table */
typedef struct acpi_dmar {
    acpi_header_t header;
    uint8_t       host_addr_width;
    uint8_t       flags;
    uint8_t       reserved[10];
} acpi_dmar_t;
compile_assert(acpi_dmar_packed,
               sizeof(acpi_dmar_t) == sizeof(acpi_header_t) + 12)

/* DMA Remapping Structure Header */
typedef struct acpi_dmar_header {
    uint16_t type;
    uint16_t length;
} acpi_dmar_header_t;
compile_assert(acpi_dmar_header_packed, sizeof(acpi_dmar_header_t) == 4)

/* DMA Remapping Structure Types */
enum acpi_table_dmar_struct_type {
    DMAR_DRHD = 0,
    DMAR_RMRR = 1,
    DMAR_ATSR = 2,
};

/* DMA Remapping Hardware unit Definition */
typedef struct acpi_dmar_drhd {
    acpi_dmar_header_t header;
    uint8_t            flags;
    uint8_t            reserved;
    uint16_t           segment;
    uint32_t           reg_base[2];
} acpi_dmar_drhd_t;
compile_assert(acpi_dmar_drhd_packed,
               sizeof(acpi_dmar_drhd_t) == sizeof(acpi_dmar_header_t) + 12)

/* Reserved Memory Region Reporting structure Definition */
typedef struct acpi_dmar_devscope {
    uint8_t  type;
    uint8_t  length;
    uint16_t reserved;
    uint8_t  enum_id;
    uint8_t  start_bus;
    struct {
        uint8_t dev;
        uint8_t fun;
    } path_0;
} acpi_dmar_devscope_t;
compile_assert(acpi_dmar_devscope_packed, sizeof(acpi_dmar_devscope_t) == 8)

/* Reserved Memory Region Reporting structure Definition */
typedef struct acpi_dmar_rmrr {
    acpi_dmar_header_t   header;
    uint16_t             reserved;
    uint16_t             segment;
    uint32_t             reg_base[2];
    uint32_t             reg_limit[2];
    acpi_dmar_devscope_t devscope_0;
} acpi_dmar_rmrr_t;
compile_assert(acpi_dmar_rmrr_packed, sizeof(acpi_dmar_rmrr_t) ==
               sizeof(acpi_dmar_header_t) + 20 + sizeof(acpi_dmar_devscope_t))

/* Fixed ACPI Description Table (FADT), partial as we only need flags */
typedef struct acpi_fadt {
    acpi_header_t  header;
    uint8_t        reserved[76];
    uint32_t       flags;
} acpi_fadt_t;
compile_assert(acpi_fadt_packed,
               sizeof(acpi_fadt_t) == sizeof(acpi_header_t) + 80)

/* Multiple APIC Description Table (MADT) */
typedef struct acpi_madt {
    acpi_header_t header;
    uint32_t      apic_addr;
    uint32_t      flags;
} acpi_madt_t;
compile_assert(acpi_madt_packed,
               sizeof(acpi_madt_t) == sizeof(acpi_header_t) + 8)

typedef struct acpi_madt_header {
    uint8_t type;
    uint8_t length;
} acpi_madt_header_t;
compile_assert(acpi_madt_header_packed, sizeof(acpi_madt_header_t) == 2)

enum acpi_table_madt_struct_type {
    MADT_APIC   = 0,
    MADT_IOAPIC = 1,
    MADT_ISO    = 2,
    MADT_x2APIC = 9
};

typedef struct acpi_madt_apic {
    acpi_madt_header_t header;
    uint8_t            cpu_id;
    uint8_t            apic_id;
    uint32_t           flags;
} acpi_madt_apic_t;
compile_assert(acpi_madt_apic_packed,
               sizeof(acpi_madt_apic_t) == sizeof(acpi_madt_header_t) + 6)

typedef struct acpi_madt_x2apic {
    acpi_madt_header_t  header;
    uint16_t            reserved;
    uint32_t            x2apic_id;
    uint32_t            flags;
    uint32_t            acpi_processor_uid;
} acpi_madt_x2apic_t;
compile_assert(acpi_madt_x2apic_packed,
               sizeof(acpi_madt_x2apic_t) == sizeof(acpi_madt_header_t) + 14)

typedef struct acpi_madt_ioapic {
    acpi_madt_header_t header;
    uint8_t            ioapic_id;
    uint8_t            reserved[1];
    uint32_t           ioapic_addr;
    uint32_t           gsib;
} acpi_madt_ioapic_t;
compile_assert(acpi_madt_ioapic_packed,
               sizeof(acpi_madt_ioapic_t) == sizeof(acpi_madt_header_t) + 10)

typedef struct acpi_madt_iso {
    acpi_madt_header_t header;
    uint8_t            bus; /* always 0 (ISA) */
    uint8_t            source;
    uint32_t           gsi;
    uint16_t           flags;
} acpi_madt_iso_t;
/* We can't assert on the sizeof acpi_madt_iso because it contains trailing
 * padding.
 */
unverified_compile_assert(acpi_madt_iso_packed,
                          OFFSETOF(acpi_madt_iso_t, flags) == sizeof(acpi_madt_header_t) + 6)

/* workaround because string literals are not supported by C parser */
const char acpi_str_rsd[]  = {'R', 'S', 'D', ' ', 'P', 'T', 'R', ' ', 0};
const char acpi_str_fadt[] = {'F', 'A', 'C', 'P', 0};
const char acpi_str_apic[] = {'A', 'P', 'I', 'C', 0};
const char acpi_str_dmar[] = {'D', 'M', 'A', 'R', 0};

BOOT_CODE static uint8_t
acpi_calc_checksum(char* start, uint32_t length)
{
    uint8_t checksum = 0;

    while (length > 0) {
        checksum += *start;
        start++;
        length--;
    }
    return checksum;
}

BOOT_CODE static acpi_rsdp_t*
acpi_get_rsdp(void)
{
    char* addr;

    for (addr = (char*)BIOS_PADDR_START; addr < (char*)BIOS_PADDR_END; addr += 16) {
        if (strncmp(addr, acpi_str_rsd, 8) == 0) {
            if (acpi_calc_checksum(addr, ACPI_V1_SIZE) == 0) {
                return (acpi_rsdp_t*)addr;
            }
        }
    }
    return NULL;
}

BOOT_CODE static void*
acpi_table_init(void* entry, enum acpi_type table_type)
{
    void* acpi_table;
    unsigned int pages_for_table;
    unsigned int pages_for_header = 1;

    /* if we need to map another page to read header */
    unsigned long offset_in_page = (unsigned long)entry & MASK(LARGE_PAGE_BITS);
    if (MASK(LARGE_PAGE_BITS) - offset_in_page < sizeof(acpi_rsdp_t)) {
        pages_for_header++;
    }

    /* map in table's header */
    acpi_table = map_temp_boot_page(entry, pages_for_header);

    switch (table_type) {
    case ACPI_RSDP: {
        acpi_rsdp_t *rsdp_entry = (acpi_rsdp_t*)entry;
        pages_for_table = (rsdp_entry->length + offset_in_page) / MASK(LARGE_PAGE_BITS) + 1;
        break;
    }
    case ACPI_RSDT: { // RSDT, MADT, DMAR etc.
        acpi_rsdt_t *rsdt_entry = (acpi_rsdt_t*)entry;
        pages_for_table = (rsdt_entry->header.length + offset_in_page) / MASK(LARGE_PAGE_BITS) + 1;
        break;
    }
    default:
        printf("Error: Mapping unknown ACPI table type\n");
        assert(false);
        return NULL;
    }

    /* map in full table */
    acpi_table = map_temp_boot_page(entry, pages_for_table);

    return acpi_table;
}

BOOT_CODE bool_t
acpi_init(acpi_rsdp_t *rsdp_data)
{
    acpi_rsdp_t* acpi_rsdp = acpi_get_rsdp();

    if (acpi_rsdp == NULL) {
        printf("BIOS: No ACPI support detected\n");
        return false;
    }
    printf("ACPI: RSDP paddr=%p\n", acpi_rsdp);
    acpi_rsdp = acpi_table_init(acpi_rsdp, ACPI_RSDP);
    printf("ACPI: RSDP vaddr=%p\n", acpi_rsdp);

    /* create a copy of the rsdp data */
    *rsdp_data = *acpi_rsdp;

    /* perform final validation */
    return acpi_validate_rsdp(rsdp_data);
}

BOOT_CODE bool_t
acpi_validate_rsdp(acpi_rsdp_t *acpi_rsdp)
{
    acpi_rsdt_t* acpi_rsdt;
    acpi_rsdt_t* acpi_rsdt_mapped;

    if (acpi_calc_checksum((char*)acpi_rsdp, ACPI_V1_SIZE) != 0) {
        printf("BIOS: ACPIv1 information corrupt\n");
        return false;
    }

    if (acpi_rsdp->revision > 0 && acpi_calc_checksum((char*)acpi_rsdp, sizeof(*acpi_rsdp)) != 0) {
        printf("BIOS: ACPIv2 information corrupt\n");
        return false;
    }

    /* verify the rsdt, even though we do not actually make use of the mapping right now */
    acpi_rsdt = (acpi_rsdt_t*)(word_t)acpi_rsdp->rsdt_address;
    printf("ACPI: RSDT paddr=%p\n", acpi_rsdt);
    acpi_rsdt_mapped = (acpi_rsdt_t*)acpi_table_init(acpi_rsdt, ACPI_RSDT);
    printf("ACPI: RSDT vaddr=%p\n", acpi_rsdt_mapped);

    assert(acpi_rsdt_mapped->header.length > 0);
    if (acpi_calc_checksum((char*)acpi_rsdt_mapped, acpi_rsdt_mapped->header.length) != 0) {
        printf("ACPI: RSDT checksum failure\n");
        return false;
    }

    return true;
}

BOOT_CODE uint32_t
acpi_madt_scan(
    acpi_rsdp_t* acpi_rsdp,
    cpu_id_t*    cpu_list,
    uint32_t*    num_ioapic,
    paddr_t*     ioapic_paddrs
)
{
    unsigned int entries;
    uint32_t            num_cpu;
    uint32_t            count;
    acpi_madt_t*        acpi_madt;
    acpi_madt_header_t* acpi_madt_header;

    acpi_rsdt_t* acpi_rsdt_mapped;
    acpi_madt_t* acpi_madt_mapped;
    acpi_rsdt_mapped = (acpi_rsdt_t*)acpi_table_init((acpi_rsdt_t*)(word_t)acpi_rsdp->rsdt_address, ACPI_RSDT);

    num_cpu = 0;
    *num_ioapic = 0;

    assert(acpi_rsdt_mapped->header.length >= sizeof(acpi_header_t));
    /* Divide by uint32_t explicitly as this is the size as mandated by the ACPI standard */
    entries = (acpi_rsdt_mapped->header.length - sizeof(acpi_header_t)) / sizeof(uint32_t);
    for (count = 0; count < entries; count++) {
        acpi_madt = (acpi_madt_t*)(word_t)acpi_rsdt_mapped->entry[count];
        acpi_madt_mapped = (acpi_madt_t*)acpi_table_init(acpi_madt, ACPI_RSDT);

        if (strncmp(acpi_str_apic, acpi_madt_mapped->header.signature, 4) == 0) {
            printf("ACPI: MADT paddr=%p\n", acpi_madt);
            printf("ACPI: MADT vaddr=%p\n", acpi_madt_mapped);
            printf("ACPI: MADT apic_addr=0x%x\n", acpi_madt_mapped->apic_addr);
            printf("ACPI: MADT flags=0x%x\n", acpi_madt_mapped->flags);

            acpi_madt_header = (acpi_madt_header_t*)(acpi_madt_mapped + 1);

            while ((char*)acpi_madt_header < (char*)acpi_madt_mapped + acpi_madt_mapped->header.length) {
                switch (acpi_madt_header->type) {
                /* ACPI specifies the following rules when listing APIC IDs:
                 *  - Boot processor is listed first
                 *  - For multi-threaded processors, BIOS should list the first logical
                 *    processor of each of the individual multi-threaded processors in MADT
                 *    before listing any of the second logical processors.
                 *  - APIC IDs < 0xFF should be listed in APIC subtable, APIC IDs >= 0xFF
                 *    should be listed in X2APIC subtable */
                case MADT_APIC: {
                    /* what Intel calls apic_id is what is called cpu_id in seL4! */
                    uint8_t  cpu_id = ((acpi_madt_apic_t*)acpi_madt_header)->apic_id;
                    uint32_t flags  = ((acpi_madt_apic_t*)acpi_madt_header)->flags;
                    if (flags == 1) {
                        printf("ACPI: MADT_APIC apic_id=0x%x\n", cpu_id);
                        if (num_cpu == CONFIG_MAX_NUM_NODES) {
                            printf("ACPI: Not recording this APIC, only support %d\n", CONFIG_MAX_NUM_NODES);
                        } else {
                            cpu_list[num_cpu] = cpu_id;
                            num_cpu++;
                        }
                    }
                    break;
                }
                case MADT_x2APIC: {
                    uint32_t cpu_id = ((acpi_madt_x2apic_t*)acpi_madt_header)->x2apic_id;
                    uint32_t flags  = ((acpi_madt_x2apic_t*)acpi_madt_header)->flags;
                    if (flags == 1) {
                        printf("ACPI: MADT_x2APIC apic_id=0x%x\n", cpu_id);
                        if (num_cpu == CONFIG_MAX_NUM_NODES) {
                            printf("ACPI: Not recording this APIC, only support %d\n", CONFIG_MAX_NUM_NODES);
                        } else {
                            cpu_list[num_cpu] = cpu_id;
                            num_cpu++;
                        }
                    }
                    break;
                }
                case MADT_IOAPIC:
                    printf(
                        "ACPI: MADT_IOAPIC ioapic_id=%d ioapic_addr=0x%x gsib=%d\n",
                        ((acpi_madt_ioapic_t*)acpi_madt_header)->ioapic_id,
                        ((acpi_madt_ioapic_t*)acpi_madt_header)->ioapic_addr,
                        ((acpi_madt_ioapic_t*)acpi_madt_header)->gsib
                    );
                    if (*num_ioapic == CONFIG_MAX_NUM_IOAPIC) {
                        printf("ACPI: Not recording this IOAPIC, only support %d\n", CONFIG_MAX_NUM_IOAPIC);
                    } else {
                        ioapic_paddrs[*num_ioapic] = ((acpi_madt_ioapic_t*)acpi_madt_header)->ioapic_addr;
                        (*num_ioapic)++;
                    }
                    break;
                case MADT_ISO:
                    printf("ACPI: MADT_ISO bus=%d source=%d gsi=%d flags=0x%x\n",
                           ((acpi_madt_iso_t*)acpi_madt_header)->bus,
                           ((acpi_madt_iso_t*)acpi_madt_header)->source,
                           ((acpi_madt_iso_t*)acpi_madt_header)->gsi,
                           ((acpi_madt_iso_t*)acpi_madt_header)->flags);
                    break;
                default:
                    break;
                }
                acpi_madt_header = (acpi_madt_header_t*)((char*)acpi_madt_header + acpi_madt_header->length);
            }
        }
    }

    printf("ACPI: %d CPU(s) detected\n", num_cpu);

    return num_cpu;
}

BOOT_CODE bool_t
acpi_fadt_scan(
    acpi_rsdp_t* acpi_rsdp
)
{
    unsigned int entries;
    uint32_t            count;
    acpi_fadt_t*        acpi_fadt;

    acpi_rsdt_t* acpi_rsdt_mapped;
    acpi_fadt_t* acpi_fadt_mapped;
    acpi_rsdt_mapped = (acpi_rsdt_t*)acpi_table_init((acpi_rsdt_t*)(word_t)acpi_rsdp->rsdt_address, ACPI_RSDT);

    assert(acpi_rsdt_mapped->header.length >= sizeof(acpi_header_t));
    /* Divide by uint32_t explicitly as this is the size as mandated by the ACPI standard */
    entries = (acpi_rsdt_mapped->header.length - sizeof(acpi_header_t)) / sizeof(uint32_t);
    for (count = 0; count < entries; count++) {
        acpi_fadt = (acpi_fadt_t*)(word_t)acpi_rsdt_mapped->entry[count];
        acpi_fadt_mapped = (acpi_fadt_t*)acpi_table_init(acpi_fadt, ACPI_RSDT);

        if (strncmp(acpi_str_fadt, acpi_fadt_mapped->header.signature, 4) == 0) {
            printf("ACPI: FADT paddr=%p\n", acpi_fadt);
            printf("ACPI: FADT vaddr=%p\n", acpi_fadt_mapped);
            printf("ACPI: FADT flags=0x%x\n", acpi_fadt_mapped->flags);

            if (config_set(CONFIG_USE_LOGICAL_IDS) &&
                    acpi_fadt_mapped->flags & BIT(19)) {
                printf("system requires apic physical mode\n");
                return false;
            }
        }
    }

    return true;
}

BOOT_CODE void
acpi_dmar_scan(
    acpi_rsdp_t* acpi_rsdp,
    paddr_t*     drhu_list,
    uint32_t*    num_drhu,
    uint32_t     max_drhu_list_len,
    acpi_rmrr_list_t *rmrr_list
)
{
    word_t i;
    unsigned int entries;
    uint32_t count;
    uint32_t reg_basel, reg_baseh;
    int rmrr_count;
    dev_id_t dev_id;

    acpi_dmar_t*          acpi_dmar;
    acpi_dmar_header_t*   acpi_dmar_header;
    acpi_dmar_rmrr_t*     acpi_dmar_rmrr;
    acpi_dmar_devscope_t* acpi_dmar_devscope;

    acpi_rsdt_t* acpi_rsdt_mapped;
    acpi_dmar_t* acpi_dmar_mapped;

    acpi_rsdt_mapped = (acpi_rsdt_t*)acpi_table_init((acpi_rsdt_t*)(word_t)acpi_rsdp->rsdt_address, ACPI_RSDT);

    *num_drhu = 0;
    rmrr_count = 0;

    assert(acpi_rsdt_mapped->header.length >= sizeof(acpi_header_t));
    entries = (acpi_rsdt_mapped->header.length - sizeof(acpi_header_t)) / sizeof(uint32_t);
    for (count = 0; count < entries; count++) {
        acpi_dmar = (acpi_dmar_t*)(word_t)acpi_rsdt_mapped->entry[count];
        acpi_dmar_mapped = (acpi_dmar_t*)acpi_table_init(acpi_dmar, ACPI_RSDT);

        if (strncmp(acpi_str_dmar, acpi_dmar_mapped->header.signature, 4) == 0) {
            printf("ACPI: DMAR paddr=%p\n", acpi_dmar);
            printf("ACPI: DMAR vaddr=%p\n", acpi_dmar_mapped);
            printf("ACPI: IOMMU host address width: %d\n", acpi_dmar_mapped->host_addr_width + 1);
            acpi_dmar_header = (acpi_dmar_header_t*)(acpi_dmar_mapped + 1);

            while ((char*)acpi_dmar_header < (char*)acpi_dmar_mapped + acpi_dmar_mapped->header.length) {
                switch (acpi_dmar_header->type) {

                case DMAR_DRHD:
                    if (*num_drhu == max_drhu_list_len) {
                        printf("ACPI: too many IOMMUs, disabling IOMMU support\n");
                        /* try to increase MAX_NUM_DRHU in config.h */
                        *num_drhu = 0; /* report zero IOMMUs */
                        return;
                    }
                    reg_basel = ((acpi_dmar_drhd_t*)acpi_dmar_header)->reg_base[0];
                    reg_baseh = ((acpi_dmar_drhd_t*)acpi_dmar_header)->reg_base[1];
                    /* check if value fits into uint32_t */
                    if (reg_baseh != 0) {
                        printf("ACPI: DMAR_DRHD reg_base exceeds 32 bit, disabling IOMMU support\n");
                        /* try to make BIOS map it below 4G */
                        *num_drhu = 0; /* report zero IOMMUs */
                        return;
                    }
                    drhu_list[*num_drhu] = (paddr_t)reg_basel;
                    (*num_drhu)++;
                    break;

                case DMAR_RMRR:
                    /* loop through all device scopes of this RMRR */
                    acpi_dmar_rmrr = (acpi_dmar_rmrr_t*)acpi_dmar_header;
                    if (acpi_dmar_rmrr->reg_base[1] != 0 ||
                            acpi_dmar_rmrr->reg_limit[1] != 0) {
                        printf("ACPI: RMRR device above 4GiB, disabling IOMMU support\n");
                        *num_drhu = 0;
                        return ;
                    }

                    for (i = 0; i <= (acpi_dmar_header->length - sizeof(acpi_dmar_rmrr_t)) / sizeof(acpi_dmar_devscope_t); i++) {
                        acpi_dmar_devscope = &acpi_dmar_rmrr->devscope_0 + i;

                        if (acpi_dmar_devscope->type != 1) {
                            /* FIXME - bugzilla bug 170 */
                            printf("ACPI: RMRR device scope: non-PCI-Endpoint-Devices not supported yet, disabling IOMMU support\n");
                            *num_drhu = 0; /* report zero IOMMUs */
                            return;
                        }

                        if (acpi_dmar_devscope->length > sizeof(acpi_dmar_devscope_t)) {
                            /* FIXME - bugzilla bug 170 */
                            printf("ACPI: RMRR device scope: devices behind bridges not supported yet, disabling IOMMU support\n");
                            *num_drhu = 0; /* report zero IOMMUs */
                            return;
                        }

                        dev_id =
                            get_dev_id(
                                acpi_dmar_devscope->start_bus,
                                acpi_dmar_devscope->path_0.dev,
                                acpi_dmar_devscope->path_0.fun
                            );

                        if (rmrr_count == CONFIG_MAX_RMRR_ENTRIES) {
                            printf("ACPI: Too many RMRR entries, disabling IOMMU support\n");
                            *num_drhu = 0;
                            return;
                        }
                        printf("\tACPI: registering RMRR entry for region for device: bus=0x%x dev=0x%x fun=0x%x\n",
                               acpi_dmar_devscope->start_bus,
                               acpi_dmar_devscope->path_0.dev,
                               acpi_dmar_devscope->path_0.fun
                              );

                        rmrr_list->entries[rmrr_count].device = dev_id;
                        rmrr_list->entries[rmrr_count].base = acpi_dmar_rmrr->reg_base[0];
                        rmrr_list->entries[rmrr_count].limit = acpi_dmar_rmrr->reg_limit[0];
                        rmrr_count++;
                    }
                    break;

                case DMAR_ATSR:
                    /* not implemented yet */
                    break;

                default:
                    printf("ACPI: Unknown DMA remapping structure type: %x\n", acpi_dmar_header->type);
                }
                acpi_dmar_header = (acpi_dmar_header_t*)((char*)acpi_dmar_header + acpi_dmar_header->length);
            }
        }
    }
    rmrr_list->num = rmrr_count;
    printf("ACPI: %d IOMMUs detected\n", *num_drhu);
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/plat/pc99/machine/hardware.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <machine/io.h>
#include <arch/kernel/apic.h>
#include <arch/model/statedata.h>
#include <linker.h>
#include <plat/machine/pic.h>
#include <plat/machine/ioapic.h>
#include <plat/machine.h>

#include <plat/machine/intel-vtd.h>

BOOT_CODE bool_t platAddDevices(void)
{
    /* remove the MSI region as poking at this is undefined and may allow for
     * the user to generate arbitrary MSI interrupts. Only need to consider
     * this if it would actually be in the user device region */
    if (PADDR_USER_DEVICE_TOP > 0xFFFFFFF8) {
        if (!add_allocated_p_region( (p_region_t) {
        (word_t)0xFFFFFFF8, (word_t)0xFFFFFFF8 + 8
        })) {
            return false;
        }
    }
    return true;
}

/* ============================== timer ============================== */

#define TSC_FREQ_RETRIES 10

BOOT_CODE static inline uint32_t
measure_tsc_khz(void)
{
    /* The frequency is repeatedly measured until the number of TSC
     * ticks in the pit wraparound interval (~50ms) fits in 32 bits.
     * On bare metal, this should succeed immediately, since x86
     * guarantees the number of TSC ticks in a second can be stored
     * in 32 bits. When running in a simulator, it's possible for
     * the emulation (or not) of the PIT and TSC to occasionally
     * allow too many TSC ticks per PIT wraparound. This loop
     * repeatedly measures the TSC ticks per PIT wraparound under
     * the expectation that it will eventually yield a sensible
     * result.
     */
    for (int i = 0; i < TSC_FREQ_RETRIES; i++) {

        /* read tsc */
        uint64_t old_ticks = x86_rdtsc();

        /* measure how many tsc cycles pass while PIT wraps around */
        pit_wait_wraparound();

        uint64_t new_ticks = x86_rdtsc();

        uint64_t diff = new_ticks - old_ticks;

        if ((uint32_t)diff == diff && new_ticks > old_ticks) {
            return (uint32_t)diff / PIT_WRAPAROUND_MS;
        }

        printf("warning: TSC frequency too high (%d retries remaining)\n",
               TSC_FREQ_RETRIES - i - 1);
    }

    fail("TSC frequency too high");

    /* should never get here */
    return 0;
}

BOOT_CODE uint32_t
tsc_init(void)
{

    x86_cpu_identity_t *model_info = x86_cpuid_get_model_info();
    uint32_t valid_models[] = {
        NEHALEM_1_MODEL_ID, NEHALEM_2_MODEL_ID, NEHALEM_3_MODEL_ID,
        SANDY_BRIDGE_1_MODEL_ID, SANDY_BRIDGE_2_MODEL_ID,
        HASWELL_1_MODEL_ID, HASWELL_2_MODEL_ID, HASWELL_3_MODEL_ID, HASWELL_4_MODEL_ID,
        IVY_BRIDGE_1_MODEL_ID, IVY_BRIDGE_2_MODEL_ID, IVY_BRIDGE_3_MODEL_ID,
        /* BROADWELL_1_MODEL_ID is an Atom that doesn't support the MSR */
        BROADWELL_2_MODEL_ID, BROADWELL_3_MODEL_ID, BROADWELL_4_MODEL_ID, BROADWELL_5_MODEL_ID,
        SKYLAKE_1_MODEL_ID, SKYLAKE_2_MODEL_ID
    };

    /* try to read the frequency from the platform info MSR */
    if (model_info->family == IA32_PREFETCHER_COMPATIBLE_FAMILIES_ID) {
        for (int i = 0; i < ARRAY_SIZE(valid_models); i++) {
            if (model_info->model == valid_models[i]) {

                /* read tsc freq from the platform info msr. Under some environments such
                 * as KVM this MSR will cause a GP fault even though it should be there.
                 * As such we perform a 'safe' rdmsr, which will catch a GP fault and
                 * tells through .success whether or not one happened */
                rdmsr_safe_result_t info = x86_rdmsr_safe(IA32_PLATFORM_INFO_MSR);
                if (info.success) {
                    uint32_t ratio = (((uint32_t) info.value) & 0xFF00) >> 8u;
                    /* Ignore hardware that claims a tsc frequency of zero */
                    if (ratio != 0) {
                        /* Convert to MHz */
                        if (model_info->model == NEHALEM_1_MODEL_ID ||
                                model_info->model == NEHALEM_2_MODEL_ID ||
                                model_info->model == NEHALEM_3_MODEL_ID) {
                            return ratio * 13333u / 100u;
                        } else {
                            return ratio * 100u;
                        }
                    }
                }
                /* We just found the matching model, so no point continuing the search */
                break;
            }
        }
    }

    /* otherwise use the pit to find out the tsc freq */
    pit_init();

    /* wait for pit to wraparound */
    pit_wait_wraparound();

    /* count tsc ticks per ms */
    uint32_t tsc_khz = measure_tsc_khz();

    /* finally, return mhz */
    return tsc_khz / 1000u;
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/plat/pc99/machine/intel-vtd.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>

#ifdef CONFIG_IOMMU

#include <kernel/boot.h>
#include <machine.h>
#include <machine/io.h>
#include <arch/kernel/apic.h>
#include <arch/model/statedata.h>
#include <linker.h>
#include <plat/machine/acpi.h>
#include <plat/machine/intel-vtd.h>
#include <util.h>

#define RTADDR_REG  0x20
#define GCMD_REG    0x18
#define GSTS_REG    0x1C
#define CCMD_REG    0x28
#define ECAP_REG    0x10
#define IOTLB_REG   0x08
#define FSTS_REG    0x34
#define FECTL_REG   0x38
#define FEDATA_REG  0x3C
#define FEADDR_REG  0x40
#define FEUADDR_REG 0x44
#define CAP_REG     0x08

/* Bit Positions within Registers */
#define SRTP        30  /* Set Root Table Pointer */
#define RTPS        30  /* Root Table Pointer Status */
#define TE          31  /* Translation Enable */
#define TES         31  /* Translation Enable Status */

/* ICC is 63rd bit in CCMD_REG, but since we will be
 * accessing this register as 4 byte word, ICC becomes
 * 31st bit in the upper 32bit word.
 */
#define ICC         (31 + 32)  /* Invalidate Context Cache */
#define CIRG        (29 + 32) /* Context Invalidation Request Granularity */
#define CAIG        27  /* Context Actual Invalidation Granularity */
#define CAIG_MASK   0x3
#define IVO_MASK    0x3FF
#define IVT         31  /* Invalidate IOTLB */
#define IIRG        28  /* IOTLB Invalidation Request Granularity */
#define IAIG        25  /* IOTLB Actual Invalidation Granularity */
#define IAIG_MASK   0x7
#define IP          30  /* Interrupt Pending */
#define FRI         0x8 /* Fault Recording Index */
#define FRI_MASK    0xFF
#define FRO         24
#define FRO_MASK    0xFF
#define FI          12
#define SID_MASK    0xFFFF
#define SID_BUS(a)  (MASK(8) & (a >> 8))
#define SID_DEV(a)  (MASK(5) & (a >> 3))
#define SID_FUNC(a) (MASK(3) & a)
#define FR_MASK     0xFF
#define FAULT_TYPE  30
#define FAULT       31
#define NFR         8   /* high word of CAP_REG */
#define NFR_MASK    0xff
#define PPF         1
#define PPF_MASK    1
#define PRESENT     1
#define WBF         27
#define WBFS        27
#define DID         8
#define RW          0x3

#define SAGAW         8
#define SAGAW_2_LEVEL 0x01
#define SAGAW_3_LEVEL 0x02
#define SAGAW_4_LEVEL 0x04
#define SAGAW_5_LEVEL 0x08
#define SAGAW_6_LEVEL 0x10

#define CONTEXT_GLOBAL_INVALIDATE 0x1
#define IOTLB_GLOBAL_INVALIDATE   0x1

#define DMA_TLB_READ_DRAIN  BIT(17)
#define DMA_TLB_WRITE_DRAIN BIT(16)

typedef uint32_t drhu_id_t;

static inline uint32_t vtd_read32(drhu_id_t drhu_id, uint32_t offset)
{
    return *(volatile uint32_t*)(PPTR_DRHU_START + (drhu_id << PAGE_BITS) + offset);
}

static inline void vtd_write32(drhu_id_t drhu_id, uint32_t offset, uint32_t value)
{
    *(volatile uint32_t*)(PPTR_DRHU_START + (drhu_id << PAGE_BITS) + offset) = value;
}


static inline uint64_t vtd_read64(drhu_id_t drhu_id, uint32_t offset)
{
    return *(volatile uint64_t *)(PPTR_DRHU_START + (drhu_id << PAGE_BITS) + offset);
}

static inline void vtd_write64(drhu_id_t drhu_id, uint32_t offset, uint64_t value)
{
    *(volatile uint64_t *)(PPTR_DRHU_START + (drhu_id << PAGE_BITS) + offset) = value;
}

static inline uint32_t get_ivo(drhu_id_t drhu_id)
{
    return ((vtd_read32(drhu_id, ECAP_REG) >> 8) & IVO_MASK) * 16;
}

static uint32_t get_fro_offset(drhu_id_t drhu_id)
{
    uint32_t fro_offset;

    /* Get bits 31 to 24 from lower Capability Register */
    fro_offset = (vtd_read32(drhu_id, CAP_REG) >> FRO) & FRO_MASK;

    /* Get bits 33 to 32 from higher Capability Register */
    fro_offset |= (vtd_read32(drhu_id, CAP_REG + 4) & 0x3) << 8;

    return fro_offset << 4;
}

void invalidate_context_cache(void)
{
    /* FIXME - bugzilla bug 172
     * 1. Instead of assuming global invalidation, this function should
     *    accept a parameter to control the granularity of invalidation
     *    request.
     * 2. Instead of doing invalidation for all the IOMMUs, it should
     *    only do it for the IOMMU responsible for the requesting PCI
     *    device.
     */

    drhu_id_t i;

    for (i = 0; i < x86KSnumDrhu; i++) {
        /* Wait till ICC bit is clear */
        uint64_t ccmd = 0;
        while ((vtd_read64(i, CCMD_REG) >> ICC) & 1);

        /* Program CIRG for Global Invalidation by setting bit 61 which
         * will be bit 29 in upper 32 bits of CCMD_REG
         */
        ccmd = ((uint64_t)CONTEXT_GLOBAL_INVALIDATE << CIRG) | (1ull << ICC);

        /* Invalidate Context Cache */
        vtd_write64(i, CCMD_REG, ccmd);

        /* Wait for the invalidation to complete */
        while ((vtd_read64(i, CCMD_REG) >> ICC) & 1);
    }
}

void invalidate_iotlb(void)
{
    /* FIXME - bugzilla bug 172
     * 1. Instead of assuming global invalidation, this function should
     *    accept a parameter to control the granularity of invalidation
     *    request.
     * 2. Instead of doing invalidation for all the IOMMUs, it should
     *    only do it for the IOMMU responsible for the requesting PCI
     *    device.
     */

    uint8_t   invalidate_command = IOTLB_GLOBAL_INVALIDATE;
    uint32_t  iotlb_reg_upper;
    uint32_t  ivo_offset;
    drhu_id_t i;

    for (i = 0; i < x86KSnumDrhu; i++) {
        ivo_offset = get_ivo(i);

        /* Wait till IVT bit is clear */
        while ((vtd_read32(i, ivo_offset + IOTLB_REG + 4) >> IVT) & 1);

        /* Program IIRG for Global Invalidation by setting bit 60 which
         * will be bit 28 in upper 32 bits of IOTLB_REG
         */
        iotlb_reg_upper = invalidate_command << IIRG;

        /* Invalidate IOTLB */
        iotlb_reg_upper |= BIT(IVT);
        iotlb_reg_upper |= DMA_TLB_READ_DRAIN | DMA_TLB_WRITE_DRAIN;

        vtd_write32(i, ivo_offset + IOTLB_REG, 0);
        vtd_write32(i, ivo_offset + IOTLB_REG + 4, iotlb_reg_upper);

        /* Wait for the invalidation to complete */
        while ((vtd_read32(i, ivo_offset + IOTLB_REG + 4) >> IVT) & 1);
    }
}

static void vtd_clear_fault(drhu_id_t i, word_t fr_reg)
{
    /* Clear the 'F' (Fault) bit to indicate that this fault is processed */
    vtd_write32(i, fr_reg + 12, BIT(FAULT));
}

static void vtd_process_faults(drhu_id_t i)
{
    /* Fault Recording register offset relative to the base register */
    uint32_t fro_offset;
    uint32_t source_id UNUSED;
    uint32_t fault_type UNUSED;
    uint32_t address[2] UNUSED;
    uint32_t reason UNUSED;
    uint32_t num_fault_regs;
    uint32_t fr_reg;
    uint32_t fault_status;
    uint32_t fault_record_index;

    /* Retrieves FRO by looking into Capability register bits 33 to 24 */
    fro_offset = get_fro_offset(i);
    fault_status = (vtd_read32(i, FSTS_REG) >> PPF) & PPF_MASK;

    if (fault_status) {
        num_fault_regs = ((vtd_read32(i, CAP_REG + 4) >> NFR) & NFR_MASK) + 1;
        fault_record_index = (vtd_read32(i, FSTS_REG) >> FRI) & FRI_MASK;
        fr_reg = fro_offset + 16 * fault_record_index;

        /* Traverse the fault register ring buffer */
        do {
            source_id = vtd_read32(i, fr_reg + 8) & SID_MASK;

            fault_type = (vtd_read32(i, fr_reg + 12) >> FAULT_TYPE) & 1;
            address[1] = vtd_read32(i, fr_reg + 4);
            address[0] = vtd_read32(i, fr_reg);
            reason = vtd_read32(i, fr_reg + 12) & FR_MASK;

            printf("IOMMU: DMA %s page fault ", fault_type ? "read" : "write");
            printf("from 0x%x (bus: 0x%lx/dev: 0x%lx/fun: 0x%lx) ", source_id,
                   SID_BUS(source_id), SID_DEV(source_id), SID_FUNC(source_id));
            printf("on address 0x%x:%x ", address[1], address[0]);
            printf("with reason code 0x%x\n", reason);

            vtd_clear_fault(i, fr_reg);

            fault_record_index = (fault_record_index + 1) % num_fault_regs;
            fr_reg = fro_offset + 16 * fault_record_index;
        } while ((vtd_read32(i, fr_reg + 12) >> FAULT) & 1);

        /* Check for Primary Fault Overflow */
        if (vtd_read32(i, FSTS_REG) & 1) {
            /* Clear PFO bit, so new faults will be generated again ! */
            vtd_write32(i, FSTS_REG, 1);
        }
    }
}

void vtd_handle_fault(void)
{
    drhu_id_t i;

    for (i = 0; i < x86KSnumDrhu; i++) {
        vtd_process_faults(i);
    }
}

BOOT_CODE static void
vtd_create_root_table(void)
{
    x86KSvtdRootTable = (void*)alloc_region(VTD_RT_SIZE_BITS);
    memzero((void*)x86KSvtdRootTable, BIT(VTD_RT_SIZE_BITS));
}

/* This function is a simplistic duplication of some of the logic
 * in iospace.c
 */
BOOT_CODE static void
vtd_map_reserved_page(vtd_cte_t *vtd_context_table, int context_index, paddr_t addr)
{
    int i;
    vtd_pte_t *iopt;
    vtd_pte_t *vtd_pte_slot;
    /* first check for the first page table */
    vtd_cte_t *vtd_context_slot = vtd_context_table + context_index;
    if (!vtd_cte_ptr_get_present(vtd_context_slot)) {
        iopt = (vtd_pte_t*)alloc_region(seL4_IOPageTableBits);
        if (!iopt) {
            fail("Failed to allocate IO page table");
        }
        memzero(iopt, BIT(seL4_IOPageTableBits));
        flushCacheRange(iopt, seL4_IOPageTableBits);

        *vtd_context_slot = vtd_cte_new(
                                x86KSFirstValidIODomain,  /* Domain ID                              */
                                true,                     /* RMRR Mapping                           */
                                x86KSnumIOPTLevels - 2,   /* Address Width                          */
                                pptr_to_paddr(iopt),      /* Address Space Root                     */
                                0,                        /* Translation Type                       */
                                true);                    /* Present                                */
        x86KSFirstValidIODomain++;
        flushCacheRange(vtd_context_slot, VTD_CTE_SIZE_BITS);
    } else {
        iopt = (vtd_pte_t*)paddr_to_pptr(vtd_cte_ptr_get_asr(vtd_context_slot));
    }
    /* now recursively find and map page tables */
    for (i = x86KSnumIOPTLevels - 1; i >= 0; i--) {
        uint32_t iopt_index;
        /* If we are still looking up bits beyond the 32bit of physical
         * that we support then we select entry 0 in the current PT */
        if (VTD_PT_INDEX_BITS * i >= 32) {
            iopt_index = 0;
        } else {
            iopt_index = ( (addr >> seL4_PageBits) >> (VTD_PT_INDEX_BITS * i)) & MASK(VTD_PT_INDEX_BITS);
        }
        vtd_pte_slot = iopt + iopt_index;
        if (i == 0) {
            /* Now put the mapping in */
            *vtd_pte_slot = vtd_pte_new(addr, 1, 1);
            flushCacheRange(vtd_pte_slot, VTD_PTE_SIZE_BITS);
        } else {
            if (!vtd_pte_ptr_get_write(vtd_pte_slot)) {
                iopt = (vtd_pte_t*)alloc_region(seL4_IOPageTableBits);
                if (!iopt) {
                    fail("Failed to allocate IO page table");
                }
                memzero(iopt, BIT(seL4_IOPageTableBits));
                flushCacheRange(iopt, seL4_IOPageTableBits);

                *vtd_pte_slot = vtd_pte_new(pptr_to_paddr(iopt), 1, 1);
                flushCacheRange(vtd_pte_slot, VTD_PTE_SIZE_BITS);
            } else {
                iopt = (vtd_pte_t*)paddr_to_pptr(vtd_pte_ptr_get_addr(vtd_pte_slot));
            }
        }
    }
}

BOOT_CODE static void
vtd_create_context_table(
    uint8_t   bus,
    uint32_t  max_num_iopt_levels,
    acpi_rmrr_list_t *rmrr_list
)
{
    word_t i;
    vtd_cte_t* vtd_context_table = (vtd_cte_t*)alloc_region(VTD_CT_SIZE_BITS);
    if (!vtd_context_table) {
        fail("Failed to allocate context table");
    }

    printf("IOMMU: Create VTD context table for PCI bus 0x%x (pptr=%p)\n", bus, vtd_context_table);
    memzero(vtd_context_table, BIT(VTD_CT_SIZE_BITS));
    flushCacheRange(vtd_context_table, VTD_CT_SIZE_BITS);

    x86KSvtdRootTable[bus] =
        vtd_rte_new(
            pptr_to_paddr(vtd_context_table), /* Context Table Pointer */
            true                                           /* Present               */
        );
    /* map in any RMRR regions */
    for (i = 0; i < rmrr_list->num; i++) {
        if (vtd_get_root_index(rmrr_list->entries[i].device) == bus) {
            uint32_t addr;
            for (addr = rmrr_list->entries[i].base; addr < rmrr_list->entries[i].limit; addr += BIT(seL4_PageBits)) {
                (void)vtd_map_reserved_page;
                vtd_map_reserved_page(vtd_context_table, vtd_get_context_index(rmrr_list->entries[i].device), addr);
            }
        }
    }
}

BOOT_CODE static bool_t
vtd_enable(cpu_id_t cpu_id)
{
    drhu_id_t i;
    uint32_t status = 0;

    for (i = 0; i < x86KSnumDrhu; i++) {
        pptr_t pa = (pptr_t)pptr_to_paddr((void *)x86KSvtdRootTable);

        /* Set the Root Table Register */
        vtd_write64(i, RTADDR_REG, pa);
        status = vtd_read32(i, GSTS_REG);
        status |= BIT(SRTP);
        /* Set SRTP bit in GCMD_REG */
        vtd_write32(i, GCMD_REG, status);

        /* Wait for SRTP operation to complete by polling
         * RTPS bit from GSTS_REG
         */
        while (!((vtd_read32(i, GSTS_REG) >> RTPS) & 1));
    }

    /* Globally invalidate context cache of all IOMMUs */
    invalidate_context_cache();

    /* Globally invalidate IOTLB of all IOMMUs */
    invalidate_iotlb();

    for (i = 0; i < x86KSnumDrhu; i++) {
        uint32_t data, addr;

        data = int_iommu;
        addr = apic_get_base_paddr();
        if (!addr) {
            return false;
        }
        addr |= (cpu_id << 12);

        vtd_process_faults(i);
        vtd_write32(i, FECTL_REG, 0);
        vtd_write32(i, FEDATA_REG, data);
        vtd_write32(i, FEADDR_REG, addr);
        vtd_write32(i, FEUADDR_REG, 0);
        status = vtd_read32(i, GSTS_REG);
        status |= BIT(WBF);
        /*flush IOMMU write buffer */
        vtd_write32(i, GCMD_REG, status);
        while (((vtd_read32(i, GSTS_REG) >> WBFS) & 1));

        printf("IOMMU 0x%x: enabling...", i);

        status = vtd_read32(i, GSTS_REG);
        status |= BIT(TE);
        /* Enable the DMA translation by setting TE bit in GCMD_REG */
        vtd_write32(i, GCMD_REG, status);

        /* Wait for Translation Enable operation to complete by polling
         * TES bit from GSTS_REG
         */
        while (!((vtd_read32(i, GSTS_REG) >> TES) & 1));

        printf(" enabled\n");
    }
    return true;
}

BOOT_CODE bool_t
vtd_init(
    cpu_id_t  cpu_id,
    uint32_t  num_drhu,
    acpi_rmrr_list_t *rmrr_list
)
{
    drhu_id_t i;
    uint32_t  bus;
    uint32_t  aw_bitmask = 0xffffffff;
    uint32_t  max_num_iopt_levels;
    /* Start the number of domains at 16 bits */
    uint32_t  num_domain_id_bits = 16;

    x86KSnumDrhu = num_drhu;
    x86KSFirstValidIODomain = 0;

    if (x86KSnumDrhu == 0) {
        return true;
    }

    for (i = 0; i < x86KSnumDrhu; i++) {
        uint32_t bits_supported = 4 + 2 * (vtd_read32(i, CAP_REG) & 7);
        aw_bitmask &= vtd_read32(i, CAP_REG) >> SAGAW;
        printf("IOMMU 0x%x: %d-bit domain IDs supported\n", i, bits_supported);
        if (bits_supported < num_domain_id_bits) {
            num_domain_id_bits = bits_supported;
        }
    }

    x86KSnumIODomainIDBits = num_domain_id_bits;

    if (aw_bitmask & SAGAW_6_LEVEL) {
        max_num_iopt_levels = 6;
    } else if (aw_bitmask & SAGAW_5_LEVEL) {
        max_num_iopt_levels = 5;
    } else if (aw_bitmask & SAGAW_4_LEVEL) {
        max_num_iopt_levels = 4;
    } else if (aw_bitmask & SAGAW_3_LEVEL) {
        max_num_iopt_levels = 3;
    } else if (aw_bitmask & SAGAW_2_LEVEL) {
        max_num_iopt_levels = 2;
    } else {
        printf("IOMMU: mismatch of supported number of PT levels between IOMMUs\n");
        return false;
    }

    if (aw_bitmask & SAGAW_3_LEVEL) {
        x86KSnumIOPTLevels = 3;
    } else if (aw_bitmask & SAGAW_4_LEVEL) {
        x86KSnumIOPTLevels = 4;
    } else if (aw_bitmask & SAGAW_5_LEVEL) {
        x86KSnumIOPTLevels = 5;
    } else if (aw_bitmask & SAGAW_6_LEVEL) {
        x86KSnumIOPTLevels = 6;
    } else if (aw_bitmask & SAGAW_2_LEVEL) {
        x86KSnumIOPTLevels = 2;
    } else {
        printf("IOMMU: mismatch of supported number of PT levels between IOMMUs\n");
        return false;
    }

    printf("IOMMU: Using %d page-table levels (max. supported: %d)\n", x86KSnumIOPTLevels, max_num_iopt_levels);

    vtd_create_root_table();

    for (bus = 0; bus < 256; bus++) {
        vtd_create_context_table(
            bus,
            max_num_iopt_levels,
            rmrr_list
        );
    }

    flushCacheRange(x86KSvtdRootTable, VTD_RT_SIZE_BITS);

    if (!vtd_enable(cpu_id)) {
        return false;
    }
    return true;
}

#endif /* CONFIG_IOMMU */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/plat/pc99/machine/io.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <arch/kernel/boot_sys.h>
#include <arch/model/statedata.h>
#include <machine/io.h>
#include <plat/machine/io.h>

#if defined(CONFIG_DEBUG_BUILD) || defined(CONFIG_PRINTING)
void
serial_init(uint16_t port)
{
    while (!(in8(port + 5) & 0x60)); /* wait until not busy */

    out8(port + 1, 0x00); /* disable generating interrupts */
    out8(port + 3, 0x80); /* line control register: command: set divisor */
    out8(port,     0x01); /* set low byte of divisor to 0x01 = 115200 baud */
    out8(port + 1, 0x00); /* set high byte of divisor to 0x00 */
    out8(port + 3, 0x03); /* line control register: set 8 bit, no parity, 1 stop bit */
    out8(port + 4, 0x0b); /* modem control register: set DTR/RTS/OUT2 */

    in8(port);     /* clear receiver port */
    in8(port + 5); /* clear line status port */
    in8(port + 6); /* clear modem status port */
}
#endif /* CONFIG_PRINTING || CONFIG_DEBUG_BUILD */

#ifdef CONFIG_PRINTING
void
putConsoleChar(unsigned char a)
{
    while (x86KSconsolePort && !(in8(x86KSconsolePort + 5) & 0x20));
    out8(x86KSconsolePort, a);
}
#endif /* CONFIG_PRINTING */

#ifdef CONFIG_DEBUG_BUILD
void
putDebugChar(unsigned char a)
{
    while (x86KSdebugPort && (in8(x86KSdebugPort + 5) & 0x20) == 0);
    out8(x86KSdebugPort, a);
}

unsigned char
getDebugChar(void)
{
    while ((in8(x86KSdebugPort + 5) & 1) == 0);
    return in8(x86KSdebugPort);
}
#endif /* CONFIG_DEBUG_BUILD */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/plat/pc99/machine/ioapic.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>

#include <linker.h>
#include <machine/io.h>
#include <plat/machine/hardware.h>
#include <plat/machine/ioapic.h>

#define IOAPIC_REGSEL 0x00
#define IOAPIC_WINDOW 0x10

#define IOAPIC_REG_IOAPICID 0x00
#define IOAPIC_REG_IOREDTBL 0x10

#define IOREDTBL_LOW(reg) (IOAPIC_REG_IOREDTBL + (reg) * 2)
#define IOREDTBL_HIGH(reg) (IOREDTBL_LOW(reg) + 1)

#define IOREDTBL_LOW_INTERRUPT_MASK BIT(16)
#define IOREDTBL_LOW_TRIGGER_MODE_LEVEL BIT(15)
#define IOREDTBL_LOW_TRIGGER_MODE_SHIFT    15
#define IOREDTBL_LOW_POLARITY_LOW BIT(13)
#define IOREDTBL_LOW_POLARITY_SHIFT         13
#define IOREDTBL_LOW_DEST_MODE_LOGCIAL BIT(11)

#define IOAPICID_ID_BITS 4
#define IOAPICID_ID_OFFSET 24

#define IOREDTBL_HIGH_RESERVED_BITS 24

/* Cache what we believe is in the low word of the IOREDTBL. This
 * has all the state of trigger modes etc etc */
static uint32_t ioredtbl_state[IOAPIC_IRQ_LINES * CONFIG_MAX_NUM_IOAPIC];

/* Number of IOAPICs in the system */
static uint32_t num_ioapics = 0;

static void ioapic_write(uint32_t ioapic, word_t reg, uint32_t value)
{
    *(volatile uint32_t*)((word_t)(PPTR_IOAPIC_START + ioapic * BIT(PAGE_BITS)) + reg) = value;
}

static uint32_t ioapic_read(uint32_t ioapic, word_t reg)
{
    return *(volatile uint32_t*)((word_t)(PPTR_IOAPIC_START + ioapic * BIT(PAGE_BITS)) + reg);
}

static void single_ioapic_init(word_t ioapic, cpu_id_t delivery_cpu)
{
    uint32_t i;

    /* Mask all the IRQs. In doing so we happen to set
     * the vector to 0, which we can assert against in
     * mask_interrupt to ensure a vector is assigned
     * before we unmask */
    for (i = 0; i < IOAPIC_IRQ_LINES; i++) {
        /* Send to desired cpu */
        ioapic_write(ioapic, IOAPIC_REGSEL, IOREDTBL_HIGH(i));
        ioapic_write(ioapic, IOAPIC_WINDOW, (ioapic_read(ioapic, IOAPIC_WINDOW) & MASK(IOREDTBL_HIGH_RESERVED_BITS)) | (delivery_cpu << IOREDTBL_HIGH_RESERVED_BITS));
        /* mask and set 0 vector */
        ioredtbl_state[i] = IOREDTBL_LOW_INTERRUPT_MASK;
        ioapic_write(ioapic, IOAPIC_REGSEL, IOREDTBL_LOW(i));
        /* The upper 16 bits are reserved, so we make sure to preserve them */
        ioredtbl_state[i] |= ioapic_read(ioapic, IOAPIC_WINDOW) & ~MASK(16);
        ioapic_write(ioapic, IOAPIC_WINDOW, ioredtbl_state[i]);
    }
}

static  cpu_id_t ioapic_target_cpu = 0;
void ioapic_init(uint32_t num_nodes, cpu_id_t *cpu_list, uint32_t num_ioapic)
{
    uint32_t ioapic;
    num_ioapics = num_ioapic;
    ioapic_target_cpu = cpu_list[0];

    for (ioapic = 0; ioapic < num_ioapic; ioapic++) {
        /* Init this ioapic */
        single_ioapic_init(ioapic, cpu_list[0]);
    }
}

void ioapic_mask(bool_t mask, uint32_t ioapic, uint32_t pin)
{
    int index = ioapic * IOAPIC_IRQ_LINES + pin;
    if (ioapic >= num_ioapics || pin >= IOAPIC_IRQ_LINES) {
        /* silently ignore requests to non existent parts of the interrupt space */
        return;
    }
    if (mask) {
        ioredtbl_state[index] |= IOREDTBL_LOW_INTERRUPT_MASK;
    } else {
        ioredtbl_state[index] &= ~IOREDTBL_LOW_INTERRUPT_MASK;
        /* it should not be possible to be unmasking an interrupt, without
         * it having been mapped to a vector, assert that this is the case */
        assert((ioredtbl_state[index] & 0xff) != 0);
    }
    ioapic_write(ioapic, IOAPIC_REGSEL, IOREDTBL_LOW(pin));
    ioapic_write(ioapic, IOAPIC_WINDOW, ioredtbl_state[index]);
}

exception_t ioapic_decode_map_pin_to_vector(word_t ioapic, word_t pin, word_t level,
                                            word_t polarity, word_t vector)
{
    if (num_ioapics == 0) {
        userError("System has no IOAPICs");
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
    if (ioapic >= num_ioapics) {
        userError("Invalid IOAPIC %ld, only have %ld", (long)ioapic, (long)num_ioapics);
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 0;
        current_syscall_error.rangeErrorMax = num_ioapics - 1;
        return EXCEPTION_SYSCALL_ERROR;
    }
    if (pin >= IOAPIC_IRQ_LINES) {
        userError("Invalid IOAPIC pin %ld, there are %d pins", (long)pin, IOAPIC_IRQ_LINES);
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 0;
        current_syscall_error.rangeErrorMax = IOAPIC_IRQ_LINES - 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (level != 0 && level != 1) {
        userError("Level should be 0 or 1, not %d", (int)level);
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 0;
        current_syscall_error.rangeErrorMax = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }
    if (polarity != 0 && polarity != 1) {
        userError("Polarity should be 0 or 1, not %d", (int)polarity);
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 0;
        current_syscall_error.rangeErrorMax = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }
    return EXCEPTION_NONE;
}

void ioapic_map_pin_to_vector(word_t ioapic, word_t pin, word_t level,
                              word_t polarity, word_t vector)
{
    uint32_t ioredtbl_high = 0;
    uint32_t index = 0;

    index = ioapic * IOAPIC_IRQ_LINES + pin;
    ioapic_write(ioapic, IOAPIC_REGSEL, IOREDTBL_HIGH(pin));
    ioredtbl_high = ioapic_read(ioapic, IOAPIC_WINDOW) & MASK(IOREDTBL_HIGH_RESERVED_BITS);
    /* delivery mode: physical mode only, using APIC ID */
    ioredtbl_high |= (ioapic_target_cpu << IOREDTBL_HIGH_RESERVED_BITS);
    ioapic_write(ioapic, IOAPIC_WINDOW, ioredtbl_high);
    /* we do not need to add IRQ_INT_OFFSET to the vector here */
    ioredtbl_state[index] = IOREDTBL_LOW_INTERRUPT_MASK |
                            (level << IOREDTBL_LOW_TRIGGER_MODE_SHIFT) |
                            (polarity << IOREDTBL_LOW_POLARITY_SHIFT) |
                            vector;

    ioapic_write(ioapic, IOAPIC_REGSEL, IOREDTBL_LOW(pin));
    /* the upper 16 bits are reserved */
    ioredtbl_state[index] |= ioapic_read(ioapic, IOAPIC_WINDOW) & ~MASK(16);
    ioapic_write(ioapic, IOAPIC_WINDOW, ioredtbl_state[index]);
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/plat/pc99/machine/pic.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <linker.h>
#include <machine/io.h>
#include <plat/machine/hardware.h>
#include <plat/machine/pic.h>

/* PIC (i8259) base registers */
#define PIC1_BASE 0x20
#define PIC2_BASE 0xa0

/* Program PIC (i8259) to remap IRQs 0-15 to interrupt vectors starting at 'interrupt' */
BOOT_CODE void
pic_remap_irqs(interrupt_t interrupt)
{
    out8(PIC1_BASE, 0x11);
    out8(PIC2_BASE, 0x11);
    out8(PIC1_BASE + 1, interrupt);
    out8(PIC2_BASE + 1, interrupt + 8);
    out8(PIC1_BASE + 1, 0x04);
    out8(PIC2_BASE + 1, 0x02);
    out8(PIC1_BASE + 1, 0x01);
    out8(PIC2_BASE + 1, 0x01);
    out8(PIC1_BASE + 1, 0x0);
    out8(PIC2_BASE + 1, 0x0);
}

BOOT_CODE void pic_disable(void)
{
    /* We assume that pic_remap_irqs has already been called and
     * just mask all the irqs */
    out8(PIC1_BASE + 1, 0xff);
    out8(PIC2_BASE + 1, 0xff);
}

void pic_mask_irq(bool_t mask, irq_t irq)
{
    uint8_t  bit_mask;
    uint16_t pic_port;

    assert(irq >= irq_isa_min);
    assert(irq <= irq_isa_max);

    if (irq < 8) {
        bit_mask = BIT(irq);
        pic_port = PIC1_BASE + 1;
    } else {
        bit_mask = BIT(irq - 8);
        pic_port = PIC2_BASE + 1;
    }

    if (mask) {
        /* Disables the interrupt */
        out8(pic_port, (in8(pic_port) | bit_mask));
    } else {
        /* Enables the interrupt */
        out8(pic_port, (in8(pic_port) & ~bit_mask));
    }
}

bool_t pic_is_irq_pending(void)
{
    /* Interrupt Request Register (IRR) - holds pending IRQs */
    uint8_t irr;

    /* Send to PIC1's OCW3, in order to read IRR from next inb instruction */
    out8(PIC1_BASE, 0x0a);

    /* Read IRR */
    irr = in8(PIC1_BASE);

    /* Since slave PIC is connected to IRQ2 of master PIC,
     * there is no need to check IRR of slave PIC.
     */
    return irr != 0;
}

static uint16_t pic_get_isr(void)
{
    out8(PIC1_BASE, 0x0b);
    out8(PIC2_BASE, 0x0b);
    return (((uint16_t)in8(PIC2_BASE)) << 8) | in8(PIC1_BASE);
}

void pic_ack_active_irq(void)
{
    irq_t irq = getActiveIRQ();
    if (irq >= irq_isa_min + 8) {
        /* ack slave PIC, unless we got a spurious irq 15
         * It is spurious if the bit is not set in the ISR
         * Even if it was spurious we will still need to
         * acknowledge the master PIC */
        if (irq != irq_isa_min + 15 || (pic_get_isr() & BIT(15))) {
            out8(PIC2_BASE, 0x20);
        }
    }
    /* ack master PIC, unless we got a spurious IRQ 7
     * It is spurious if the bit is not set in the ISR */
    if (irq != irq_isa_min + 7 || (pic_get_isr() & BIT(7))) {
        out8(PIC1_BASE, 0x20);
    }
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/plat/pc99/machine/pit.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <linker.h>
#include <machine/io.h>
#include <plat/machine/pit.h>

/* PIT (i8253) registers */
#define PIT_MODE 0x43
#define PIT_CH0  0x40

/* Count frequency in Hz */
#define PIT_HZ 1193182

BOOT_CODE void
pit_init(void)
{
    uint16_t divisor = (PIT_HZ * PIT_WRAPAROUND_MS) / 1000;

    out8(PIT_MODE, 0x34);          /* Set mode 2 and wait for divisor bytes */
    out8(PIT_CH0, divisor & 0xff); /* Set low byte of divisor */
    out8(PIT_CH0, divisor >> 8);   /* Set high byte of divisor */
}

BOOT_CODE void
pit_wait_wraparound(void)
{
    uint16_t count;
    uint16_t count_old;

    out8(PIT_MODE, 0x00);
    count = in8(PIT_CH0);
    count |= (in8(PIT_CH0) << 8);
    count_old = count;

    while (count <= count_old) {
        count_old = count;
        out8(PIT_MODE, 0x00);
        count = in8(PIT_CH0);
        count |= (in8(PIT_CH0) << 8);
    }
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/smp/ipi.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <mode/smp/ipi.h>
#include <smp/ipi.h>
#include <smp/lock.h>

#ifdef ENABLE_SMP_SUPPORT
/* This function switches the core it is called on to the idle thread,
 * in order to avoid IPI storms. If the core is waiting on the lock, the actual
 * switch will not occur until the core attempts to obtain the lock, at which
 * point the core will capture the pending IPI, which is discarded.

 * The core who triggered the store is responsible for triggering a reschedule,
 * or this call will idle forever */
void ipiStallCoreCallback(bool_t irqPath)
{
    if (clh_is_self_in_queue() && !irqPath) {
        /* The current thread is running as we would replace this thread with an idle thread
         *
         * The instruction should be re-executed if we are in kernel to handle syscalls.
         * Also, thread in 'ThreadState_RunningVM' should remain in same state.
         * Note that, 'ThreadState_Restart' does not always result in regenerating exception
         * if we are in kernel to handle them, e.g. hardware single step exception. */
        if (thread_state_ptr_get_tsType(&NODE_STATE(ksCurThread)->tcbState) == ThreadState_Running) {
            setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
        }

        SCHED_ENQUEUE_CURRENT_TCB;
        switchToIdleThread();
        NODE_STATE(ksSchedulerAction) = SchedulerAction_ResumeCurrentThread;

        /* Let the cpu requesting this IPI to continue while we waiting on lock */
        big_kernel_lock.node_owners[getCurrentCPUIndex()].ipi = 0;
        ipi_wait(totalCoreBarrier);

        /* Continue waiting on lock */
        while (big_kernel_lock.node_owners[getCurrentCPUIndex()].next->value != CLHState_Granted) {
            if (clh_is_ipi_pending(getCurrentCPUIndex())) {

                /* Multiple calls for similar reason could result in stack overflow */
                assert((IpiRemoteCall_t)remoteCall != IpiRemoteCall_Stall);
                handleIPI(irq_remote_call_ipi, irqPath);
            }
            arch_pause();
        }

        /* make sure no resource access passes from this point */
        asm volatile("" ::: "memory");

        /* Start idle thread to capture the pending IPI */
        activateThread();
        restore_user_context();
    } else {
        /* We get here either without grabbing the lock from normal interrupt path or from
         * inside the lock while waiting to grab the lock for handling pending interrupt.
         * In latter case, we return to the 'clh_lock_acquire' to grab the lock and
         * handle the pending interrupt. Its valid as interrups are async events! */
        SCHED_ENQUEUE_CURRENT_TCB;
        switchToIdleThread();

        NODE_STATE(ksSchedulerAction) = SchedulerAction_ResumeCurrentThread;
    }
}

void handleIPI(irq_t irq, bool_t irqPath)
{
    if (irq == irq_remote_call_ipi) {
        handleRemoteCall(remoteCall, get_ipi_arg(0), get_ipi_arg(1), get_ipi_arg(2), irqPath);
    } else if (irq == irq_reschedule_ipi) {
        rescheduleRequired();
    } else {
        fail("Invalid IPI");
    }
}

void doRemoteMaskOp(IpiRemoteCall_t func, word_t data1, word_t data2, word_t data3, word_t mask)
{
    /* make sure the current core is not set in the mask */
    mask &= ~BIT(getCurrentCPUIndex());

    /* this may happen, e.g. the caller tries to map a pagetable in
     * newly created PD which has not been run yet. Guard against them! */
    if (mask != 0) {
        init_ipi_args(func, data1, data2, data3, mask);

        /* make sure no resource access passes from this point */
        asm volatile("" ::: "memory");
        ipi_send_mask(irq_remote_call_ipi, mask, true);
        ipi_wait(totalCoreBarrier);
    }
}

void doMaskReschedule(word_t mask)
{
    /* make sure the current core is not set in the mask */
    mask &= ~BIT(getCurrentCPUIndex());
    if (mask != 0) {
        ipi_send_mask(irq_reschedule_ipi, mask, false);
    }
}

void generic_ipi_send_mask(irq_t ipi, word_t mask, bool_t isBlocking)
{
    word_t nr_target_cores = 0;
    uint16_t target_cores[CONFIG_MAX_NUM_NODES];

    while (mask) {
        int index = wordBits - 1 - clzl(mask);
        if (isBlocking) {
            big_kernel_lock.node_owners[index].ipi = 1;
            target_cores[nr_target_cores] = index;
            nr_target_cores++;
        } else {
            ipi_send_target(ipi, cpuIndexToID(index));
        }
        mask &= ~BIT(index);
    }

    if (nr_target_cores > 0) {
        /* sending IPIs... */
        IPI_MEM_BARRIER;
        for (int i = 0; i < nr_target_cores; i++) {
            ipi_send_target(ipi, cpuIndexToID(target_cores[i]));
        }
    }
}
#endif /* ENABLE_SMP_SUPPORT */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/smp/lock.c"
/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <config.h>
#include <smp/lock.h>

#ifdef ENABLE_SMP_SUPPORT

clh_lock_t big_kernel_lock ALIGN(L1_CACHE_LINE_SIZE);

BOOT_CODE void
clh_lock_init(void)
{
    for (int i = 0; i < CONFIG_MAX_NUM_NODES; i++) {
        big_kernel_lock.node_owners[i].node = &big_kernel_lock.nodes[i];
    }

    /* Initialize the CLH head */
    big_kernel_lock.nodes[CONFIG_MAX_NUM_NODES].value = CLHState_Granted;
    big_kernel_lock.head = &big_kernel_lock.nodes[CONFIG_MAX_NUM_NODES];
}

#endif /* ENABLE_SMP_SUPPORT */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/string.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <assert.h>
#include <string.h>

word_t strnlen(const char *s, word_t maxlen)
{
    word_t len;
    for (len = 0; len < maxlen && s[len]; len++);
    return len;
}

word_t strlcpy(char *dest, const char *src, word_t size)
{
    word_t len;
    for (len = 0; len + 1 < size && src[len]; len++) {
        dest[len] = src[len];
    }
    dest[len] = '\0';
    return len;
}

word_t strlcat(char *dest, const char *src, word_t size)
{
    word_t len;
    /* get to the end of dest */
    for (len = 0; len < size && dest[len]; len++);
    /* check that dest was at least 'size' length to prevent inserting
     * a null byte when we shouldn't */
    if (len < size) {
        for (; len + 1 < size && *src; len++, src++) {
            dest[len] = *src;
        }
        dest[len] = '\0';
    }
    return len;
}
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/util.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <assert.h>
#include <stdint.h>
#include <util.h>

/*
 * memzero needs a custom type that allows us to use a word
 * that has the aliasing properties of a char.
 */
typedef unsigned long __attribute__((__may_alias__)) ulong_alias;

/*
 * Zero 'n' bytes of memory starting from 's'.
 *
 * 'n' and 's' must be word aligned.
 */
void
memzero(void *s, unsigned long n)
{
    uint8_t *p = s;

    /* Ensure alignment constraints are met. */
    assert((unsigned long)s % sizeof(unsigned long) == 0);
    assert(n % sizeof(unsigned long) == 0);

    /* We will never memzero an area larger than the largest current
       live object */
    /** GHOSTUPD: "(gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state = 0
        \<or> \<acute>n <= gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state, id)" */

    /* Write out words. */
    while (n != 0) {
        *(ulong_alias *)p = 0;
        p += sizeof(ulong_alias);
        n -= sizeof(ulong_alias);
    }
}

void* VISIBLE
memset(void *s, unsigned long c, unsigned long n)
{
    uint8_t *p;

    /*
     * If we are only writing zeros and we are word aligned, we can
     * use the optimized 'memzero' function.
     */
    if (likely(c == 0 && ((unsigned long)s % sizeof(unsigned long)) == 0 && (n % sizeof(unsigned long)) == 0)) {
        memzero(s, n);
    } else {
        /* Otherwise, we use a slower, simple memset. */
        for (p = (uint8_t *)s; n > 0; n--, p++) {
            *p = (uint8_t)c;
        }
    }

    return s;
}

void* VISIBLE
memcpy(void* ptr_dst, const void* ptr_src, unsigned long n)
{
    uint8_t *p;
    const uint8_t *q;

    for (p = (uint8_t *)ptr_dst, q = (const uint8_t *)ptr_src; n; n--, p++, q++) {
        *p = *q;
    }

    return ptr_dst;
}

int PURE
strncmp(const char* s1, const char* s2, int n)
{
    word_t i;
    int diff;

    for (i = 0; i < n; i++) {
        diff = ((unsigned char*)s1)[i] - ((unsigned char*)s2)[i];
        if (diff != 0 || s1[i] == '\0') {
            return diff;
        }
    }

    return 0;
}

long CONST
char_to_long(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    return -1;
}

long PURE
str_to_long(const char* str)
{
    unsigned int base;
    long res;
    long val = 0;
    char c;

    /*check for "0x" */
    if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
        base = 16;
        str += 2;
    } else {
        base = 10;
    }

    if (!*str) {
        return -1;
    }

    c = *str;
    while (c != '\0') {
        res = char_to_long(c);
        if (res == -1 || res >= base) {
            return -1;
        }
        val = val * base + res;
        str++;
        c = *str;
    }

    return val;
}

#ifdef CONFIG_ARCH_RISCV
uint32_t __clzsi2(uint32_t x)
{
    uint32_t count = 0;
    while ( !(x & 0x80000000U) && count < 34) {
        x <<= 1;
        count++;
    }
    return count;
}

uint32_t __ctzsi2(uint32_t x)
{
    uint32_t count = 0;
    while ( !(x & 0x000000001) && count <= 32) {
        x >>= 1;
        count++;
    }
    return count;
}

uint32_t __clzdi2(uint64_t x)
{
    uint32_t count = 0;
    while ( !(x & 0x8000000000000000U) && count < 65) {
        x <<= 1;
        count++;
    }
    return count;
}

uint32_t __ctzdi2(uint64_t x)
{
    uint32_t count = 0;
    while ( !(x & 0x00000000000000001) && count <= 64) {
        x >>= 1;
        count++;
    }
    return count;
}
#endif /* CONFIG_ARCH_RISCV */
#line 1 "/home/sel4-training/sel4-tutorials-manifest/kernel/src/config/default_domain.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <object/structures.h>
#include <model/statedata.h>

/* Default schedule. */
const dschedule_t ksDomSchedule[] = {
    { .domain = 0, .length = 1 },
};

const word_t ksDomScheduleLength = sizeof(ksDomSchedule) / sizeof(dschedule_t);

