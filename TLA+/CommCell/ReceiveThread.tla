--------------------------- MODULE ReceiveThread ---------------------------

EXTENDS Sequences,
        Naturals,
        Modbus


(* --algorithm Transmit

variables   tx = FALSE,
            txBuf \in STRINGS,
            txReg = "", 
            txBufIndex = ""
begin


idle: if tx = TRUE
      then goto transmit;
      end if;

transmit:   if IsModbus(txBuf)
            then
            txBufIndex := Len(txBuf);
            \*empty the buffer into the register
            send: while txBufIndex > 0 do
                    a: txReg := txBuf[txBufIndex];
                    b: txBufIndex := txBufIndex - 1;
                end while;
            end if;
    t1:     tx := FALSE;
            goto idle;
                

end algorithm
*)
\* BEGIN TRANSLATION
VARIABLES tx, txBuf, txBufIndex, pc, txReg

vars == << tx, txBuf, txBufIndex, pc >>

Init == (* Global variables *)
        /\ tx = FALSE
        /\ txBuf \in STRING
        /\ txReg = ""
        /\ txBufIndex \in 1..513
        /\ pc = "idle"

idle == /\ pc = "idle"
        /\ IF tx = TRUE
              THEN /\ pc' = "transmit"
              ELSE /\ pc' = "transmit"
        /\ UNCHANGED << tx, txBuf, txBufIndex >>

transmit == /\ pc = "transmit"
            /\ IF IsModbus(txBuf)
                  THEN /\ txBufIndex' = Len(txBuf)
                       /\ pc' = "send"
                  ELSE /\ pc' = "t1"
                       /\ UNCHANGED txBufIndex
            /\ UNCHANGED << tx, txBuf >>

send == /\ pc = "send"
        /\ IF txBufIndex > 0
              THEN /\ pc' = "a"
              ELSE /\ pc' = "t1"
        /\ UNCHANGED << tx, txBuf, txBufIndex >>

a == /\ pc = "a"
     /\ txReg' = txBuf[txBufIndex]
     /\ pc' = "b"
     /\ UNCHANGED << tx, txBuf, txBufIndex >>

b == /\ pc = "b"
     /\ txBufIndex' = txBufIndex - 1
     /\ pc' = "send"
     /\ UNCHANGED << tx, txBuf >>

t1 == /\ pc = "t1"
      /\ tx' = FALSE
      /\ pc' = "idle"
      /\ UNCHANGED << txBuf, txBufIndex >>

Next == idle \/ transmit \/ send \/ a \/ b \/ t1
           \/ (* Disjunct to prevent deadlock on termination *)
              (pc = "Done" /\ UNCHANGED vars)

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* check that if valid modbus is in the buffer it gets sent
ALLSENT == tx = TRUE ~> txBufIndex = 0

NOTHANG == tx = TRUE ~> tx = FALSE

BUFFER_NOVERFLOW == []txBufIndex

\* END TRANSLATION

=============================================================================
\* Modification History
\* Last modified Fri May 04 12:35:53 EDT 2018 by SabraouM
\* Created Thu May 03 13:28:54 EDT 2018 by SabraouM
