/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */



#include <camkes/dataport.h>











  
    
    
    
    
        
            
            
            
            
        
    
    
    
    
    
    

    

    
    
    

    
    
    
    
        
        
        
            
        
    
        
        
        
            
        
    

    
    
    
        
            
                
            
                
            
            
        
    
        
            
                
                    
                
            
                
            
            
        
    

    
    

    
    



/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */








#include <sel4/sel4.h>
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sync/sem-bare.h>
#include <camkes/dataport.h>
#include <camkes/error.h>
#include <camkes/tls.h>









/* Interface-specific error handling */


    
    
    

    /* The currently active error handler. This variable is marked UNUSED to squash
     * compiler warnings generated when the user's build configuration causes the
     * two following functions to be pruned from the final source.
    */
    static camkes_error_handler_t signtx_iface_error_handler_fn UNUSED;

    camkes_error_handler_t signtx_iface_register_error_handler(
        camkes_error_handler_t handler) {
        camkes_error_handler_t old = signtx_iface_error_handler_fn;
        signtx_iface_error_handler_fn = handler;
        return old;
    }

    static camkes_error_action_t UNUSED signtx_iface_error_handler(camkes_error_t *error) {
        if (signtx_iface_error_handler_fn == NULL) {
            /* No registered handler; invoke the generic error handler. */
            return camkes_error(error);
        }
        return signtx_iface_error_handler_fn(error);
    }



    
    
    
        
        
            
                
        
  
  
  static void _camkes__581(void) NO_INLINE UNUSED
    WARNING("typedef char * looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__581(void) {
    /* We need something opaque here to prevent the compiler from optimising
     * away an invocation of (and hence the warning attached to) this function.
     * This is also why this function is marked noinline.
     */
    asm volatile ("");
  }
  static void SigntxIface_print_sign_text_array_typedef_check(char * x UNUSED)
    UNUSED;
  static void SigntxIface_print_sign_text_array_typedef_check(char * x UNUSED) {
    __builtin_choose_expr(

      
      sizeof(x) != sizeof(char *) ||

      
      (sizeof(char *) == sizeof(void*) &&
        (__builtin_types_compatible_p(char[sizeof(void*)], char *) ||
         __builtin_types_compatible_p(signed char[sizeof(void*)], char *) ||
         __builtin_types_compatible_p(unsigned char[sizeof(void*)], char *) ||
         __builtin_types_compatible_p(short[sizeof(void*) / sizeof(short)], char *) ||
         __builtin_types_compatible_p(unsigned short[sizeof(void*) / sizeof(unsigned short)], char *) ||
         __builtin_types_compatible_p(int[sizeof(void*) / sizeof(int)], char *) ||
         __builtin_types_compatible_p(unsigned[sizeof(void*) / sizeof(unsigned)], char *) ||
         __builtin_types_compatible_p(long[sizeof(void*) / sizeof(long)], char *) ||
         __builtin_types_compatible_p(unsigned long[sizeof(void*) / sizeof(unsigned long)], char *) ||
         (sizeof(void*) / sizeof(long long) > 0 &&
           __builtin_types_compatible_p(long long[sizeof(void*) / sizeof(long long)], char *)) ||
         (sizeof(void*) / sizeof(unsigned long long) > 0 &&
           __builtin_types_compatible_p(unsigned long long[sizeof(void*) / sizeof(unsigned long long)], char *)) ||
         (sizeof(void*) / sizeof(double) > 0 &&
           __builtin_types_compatible_p(double[sizeof(void*) / sizeof(double)], char *)) ||
         (sizeof(void*) / sizeof(long double) > 0 &&
           __builtin_types_compatible_p(long double[sizeof(void*) / sizeof(long double)], char *)) ||
         (sizeof(void*) / sizeof(float) > 0 &&
           __builtin_types_compatible_p(float[sizeof(void*) / sizeof(float)], char *)))),

      /* trigger a compile-time warning: */ _camkes__581(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
            
        
            
                
        
  
  
  static void _camkes__582(void) NO_INLINE UNUSED
    WARNING("typedef int looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__582(void) {
    /* We need something opaque here to prevent the compiler from optimising
     * away an invocation of (and hence the warning attached to) this function.
     * This is also why this function is marked noinline.
     */
    asm volatile ("");
  }
  static void SigntxIface_print_sign_id_array_typedef_check(int x UNUSED)
    UNUSED;
  static void SigntxIface_print_sign_id_array_typedef_check(int x UNUSED) {
    __builtin_choose_expr(

      
      sizeof(x) != sizeof(int) ||

      
      (sizeof(int) == sizeof(void*) &&
        (__builtin_types_compatible_p(char[sizeof(void*)], int) ||
         __builtin_types_compatible_p(signed char[sizeof(void*)], int) ||
         __builtin_types_compatible_p(unsigned char[sizeof(void*)], int) ||
         __builtin_types_compatible_p(short[sizeof(void*) / sizeof(short)], int) ||
         __builtin_types_compatible_p(unsigned short[sizeof(void*) / sizeof(unsigned short)], int) ||
         __builtin_types_compatible_p(int[sizeof(void*) / sizeof(int)], int) ||
         __builtin_types_compatible_p(unsigned[sizeof(void*) / sizeof(unsigned)], int) ||
         __builtin_types_compatible_p(long[sizeof(void*) / sizeof(long)], int) ||
         __builtin_types_compatible_p(unsigned long[sizeof(void*) / sizeof(unsigned long)], int) ||
         (sizeof(void*) / sizeof(long long) > 0 &&
           __builtin_types_compatible_p(long long[sizeof(void*) / sizeof(long long)], int)) ||
         (sizeof(void*) / sizeof(unsigned long long) > 0 &&
           __builtin_types_compatible_p(unsigned long long[sizeof(void*) / sizeof(unsigned long long)], int)) ||
         (sizeof(void*) / sizeof(double) > 0 &&
           __builtin_types_compatible_p(double[sizeof(void*) / sizeof(double)], int)) ||
         (sizeof(void*) / sizeof(long double) > 0 &&
           __builtin_types_compatible_p(long double[sizeof(void*) / sizeof(long double)], int)) ||
         (sizeof(void*) / sizeof(float) > 0 &&
           __builtin_types_compatible_p(float[sizeof(void*) / sizeof(float)], int)))),

      /* trigger a compile-time warning: */ _camkes__582(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
            
        
            
        
    
        
        
            
        
            
        
            
        
            
        
    



int signtx_iface__run(void) {
    /* This function is never actually executed, but we still emit it for the
     * purpose of type checking RPC parameters.
     */
    UNREACHABLE();

    
    
    
    
    
        
        
            
                
        
  
  static char * _camkes__583;
  SigntxIface_print_sign_text_array_typedef_check(_camkes__583);

    
                
            
        
            
        
            
                
        
  
  static int _camkes__584;
  SigntxIface_print_sign_id_array_typedef_check(_camkes__584);

    
                
            
        
            
        
            
        
    
        
        
            
        
            
        
            
        
            
        
    


    return 0;
}





    
    
    
    
    
    
    
    
    
    
    
    

    
    
        
            
        
    
        
            
        
    
        
            
                
    /* The TLS_PTR macro is for acquiring a pointer to a local variable. The first
     * argument is the corresponding TLS global and the second is the local
     * variable you are taking the address of. The purpose of this abstraction is
     * to allow for varying TLS models.
     */
    #ifdef CONFIG_CAMKES_TLS_STANDARD

    #ifndef TLS_PTR
        #define TLS_PTR(tls_var, name) (&(name))
    #endif

    #elif defined(CONFIG_CAMKES_TLS_PTG)

    #ifndef TLS_PTR
        #define TLS_PTR(tls_var, name) (get_##tls_var())
    #endif

    #else

        #error undefined TLS model

    #endif

    
        
        static int print_sign_id_from_1
        
        UNUSED;
    
        
        static int print_sign_id_from_2
        
        UNUSED;
    
        
        static int print_sign_id_from_3
        
        UNUSED;
    
        
        static int print_sign_id_from_4
        
        UNUSED;
    

    static int *
    
    get_print_sign_id_from(void) UNUSED;
    static int *
    
    get_print_sign_id_from(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_sign_id_from_1;
                    
            
                case 2:
                    
                        return & print_sign_id_from_2;
                    
            
                case 3:
                    
                        return & print_sign_id_from_3;
                    
            
                case 4:
                    
                        return & print_sign_id_from_4;
                    
            
            default:
                assert(!"invalid thread index");
                abort();
        }
    }

            
        
    
        
            
                
    /* The TLS_PTR macro is for acquiring a pointer to a local variable. The first
     * argument is the corresponding TLS global and the second is the local
     * variable you are taking the address of. The purpose of this abstraction is
     * to allow for varying TLS models.
     */
    #ifdef CONFIG_CAMKES_TLS_STANDARD

    #ifndef TLS_PTR
        #define TLS_PTR(tls_var, name) (&(name))
    #endif

    #elif defined(CONFIG_CAMKES_TLS_PTG)

    #ifndef TLS_PTR
        #define TLS_PTR(tls_var, name) (get_##tls_var())
    #endif

    #else

        #error undefined TLS model

    #endif

    
        
        static int print_sign_isValid_from_1
        
        UNUSED;
    
        
        static int print_sign_isValid_from_2
        
        UNUSED;
    
        
        static int print_sign_isValid_from_3
        
        UNUSED;
    
        
        static int print_sign_isValid_from_4
        
        UNUSED;
    

    static int *
    
    get_print_sign_isValid_from(void) UNUSED;
    static int *
    
    get_print_sign_isValid_from(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_sign_isValid_from_1;
                    
            
                case 2:
                    
                        return & print_sign_isValid_from_2;
                    
            
                case 3:
                    
                        return & print_sign_isValid_from_3;
                    
            
                case 4:
                    
                        return & print_sign_isValid_from_4;
                    
            
            default:
                assert(!"invalid thread index");
                abort();
        }
    }

            
        
    
        
            
        
    
    

    
        
        
        static unsigned print_sign_marshal_inputs_text(unsigned _camkes_offset_585,
            
    
        
            const char *
        
        text
    

        ) {

        
        void * _camkes_buffer_base_586 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                const char * _camkes_ptr_str_589 = text;
            
        

        
            
            size_t _camkes_strlen_591 = strnlen(_camkes_ptr_str_589, (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_585);
            
            
    ERR_IF(_camkes_strlen_591 + 1 > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_585, signtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modchk",
        .interface = "signtx_iface",
        .description = "buffer exceeded while marshalling text in print_sign",
        .current_length = _camkes_offset_585,
        .target_length = _camkes_offset_585 + _camkes_strlen_591 + 1,
        }), ({
            return UINT_MAX;
    }));

            /* If we didn't trigger an error, we now know this strcpy is safe. */
            (void)strcpy(_camkes_buffer_base_586 + _camkes_offset_585, _camkes_ptr_str_589);
            _camkes_offset_585 += _camkes_strlen_591 + 1;
        
        return _camkes_offset_585;
    }
    
        
        
        static unsigned print_sign_marshal_inputs_source(unsigned _camkes_offset_592,
            
    
        
            const char *
        
        source
    

        ) {

        
        void * _camkes_buffer_base_593 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                const char * _camkes_ptr_str_596 = source;
            
        

        
            
            size_t _camkes_strlen_598 = strnlen(_camkes_ptr_str_596, (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_592);
            
            
    ERR_IF(_camkes_strlen_598 + 1 > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_592, signtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modchk",
        .interface = "signtx_iface",
        .description = "buffer exceeded while marshalling source in print_sign",
        .current_length = _camkes_offset_592,
        .target_length = _camkes_offset_592 + _camkes_strlen_598 + 1,
        }), ({
            return UINT_MAX;
    }));

            /* If we didn't trigger an error, we now know this strcpy is safe. */
            (void)strcpy(_camkes_buffer_base_593 + _camkes_offset_592, _camkes_ptr_str_596);
            _camkes_offset_592 += _camkes_strlen_598 + 1;
        
        return _camkes_offset_592;
    }
    
        
        
        static unsigned print_sign_marshal_inputs_id(unsigned _camkes_offset_599,
            
    
        
            int
        
        id
    

        ) {

        
        void * _camkes_buffer_base_600 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                int * _camkes_ptr_601 = TLS_PTR(print_sign_id_from, id);
                * _camkes_ptr_601 = id;
            
        

        
            
            
    ERR_IF(sizeof(* _camkes_ptr_601) > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_599, signtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modchk",
        .interface = "signtx_iface",
        .description = "buffer exceeded while marshalling id in print_sign",
        .current_length = _camkes_offset_599,
        .target_length = _camkes_offset_599 + sizeof(* _camkes_ptr_601),
        }), ({
            return UINT_MAX;
    }));

            memcpy(_camkes_buffer_base_600 + _camkes_offset_599, _camkes_ptr_601, sizeof(* _camkes_ptr_601));
            _camkes_offset_599 += sizeof(* _camkes_ptr_601);
        
        return _camkes_offset_599;
    }
    
        
        
        static unsigned print_sign_marshal_inputs_isValid(unsigned _camkes_offset_605,
            
    
        
            int
        
        isValid
    

        ) {

        
        void * _camkes_buffer_base_606 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                int * _camkes_ptr_607 = TLS_PTR(print_sign_isValid_from, isValid);
                * _camkes_ptr_607 = isValid;
            
        

        
            
            
    ERR_IF(sizeof(* _camkes_ptr_607) > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_605, signtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modchk",
        .interface = "signtx_iface",
        .description = "buffer exceeded while marshalling isValid in print_sign",
        .current_length = _camkes_offset_605,
        .target_length = _camkes_offset_605 + sizeof(* _camkes_ptr_607),
        }), ({
            return UINT_MAX;
    }));

            memcpy(_camkes_buffer_base_606 + _camkes_offset_605, _camkes_ptr_607, sizeof(* _camkes_ptr_607));
            _camkes_offset_605 += sizeof(* _camkes_ptr_607);
        
        return _camkes_offset_605;
    }
    
        
        
        static unsigned print_sign_marshal_inputs_hmac(unsigned _camkes_offset_611,
            
    
        
            const char *
        
        hmac
    

        ) {

        
        void * _camkes_buffer_base_612 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                const char * _camkes_ptr_str_615 = hmac;
            
        

        
            
            size_t _camkes_strlen_617 = strnlen(_camkes_ptr_str_615, (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_611);
            
            
    ERR_IF(_camkes_strlen_617 + 1 > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_611, signtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modchk",
        .interface = "signtx_iface",
        .description = "buffer exceeded while marshalling hmac in print_sign",
        .current_length = _camkes_offset_611,
        .target_length = _camkes_offset_611 + _camkes_strlen_617 + 1,
        }), ({
            return UINT_MAX;
    }));

            /* If we didn't trigger an error, we now know this strcpy is safe. */
            (void)strcpy(_camkes_buffer_base_612 + _camkes_offset_611, _camkes_ptr_str_615);
            _camkes_offset_611 += _camkes_strlen_617 + 1;
        
        return _camkes_offset_611;
    }
    

    
        
        static const uint8_t _camkes_method_index_618 = 0;
    

    static unsigned print_sign_marshal_inputs(
    
    
        
        
    
        
            const char *
        
        text
    

        
            ,
        
    
        
        
    
        
            const char *
        
        source
    

        
            ,
        
    
        
        
    
        
            int
        
        id
    

        
            ,
        
    
        
        
    
        
            int
        
        isValid
    

        
            ,
        
    
        
        
    
        
            const char *
        
        hmac
    

        
    

    
    ) {

        
        unsigned _camkes_length_619 = 0;

        
        void * _camkes_buffer_base_620 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            /* Marshal the method index. */
            
            
    ERR_IF(sizeof(_camkes_method_index_618) > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_length_619, signtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modchk",
        .interface = "signtx_iface",
        .description = "buffer exceeded while marshalling print_sign in print_sign",
        .current_length = _camkes_length_619,
        .target_length = _camkes_length_619 + sizeof(_camkes_method_index_618),
        }), ({
            return UINT_MAX;
    }));

            memcpy(_camkes_buffer_base_620, & _camkes_method_index_618, sizeof(_camkes_method_index_618));
            _camkes_length_619 += sizeof(_camkes_method_index_618);
        

        /* Marshal the parameters. */
        
            
            _camkes_length_619 = print_sign_marshal_inputs_text(_camkes_length_619,
            
            text
            );
            if (unlikely(_camkes_length_619 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_619 = print_sign_marshal_inputs_source(_camkes_length_619,
            
            source
            );
            if (unlikely(_camkes_length_619 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_619 = print_sign_marshal_inputs_id(_camkes_length_619,
            
            id
            );
            if (unlikely(_camkes_length_619 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_619 = print_sign_marshal_inputs_isValid(_camkes_length_619,
            
            isValid
            );
            if (unlikely(_camkes_length_619 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_619 = print_sign_marshal_inputs_hmac(_camkes_length_619,
            
            hmac
            );
            if (unlikely(_camkes_length_619 == UINT_MAX)) {
                return UINT_MAX;
            }
        

        assert(_camkes_length_619 <= (seL4_MsgMaxLength * sizeof(seL4_Word)) &&
            "uncaught buffer overflow while marshalling inputs for print_sign");

        return _camkes_length_619;
    }




    
    
    
    
    
    
    
    
    
    
    

    
    
    

    static int
    print_sign_unmarshal_outputs(
    
    unsigned _camkes_size_622
    
    
    

    
    

    ) {

        
        unsigned _camkes_length_624 UNUSED = 0;

        
        void * _camkes_buffer_base_625 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        

        /* Unmarshal the parameters. */
        

        
        ERR_IF(ROUND_UP_UNSAFE(_camkes_length_624, sizeof(seL4_Word)) != _camkes_size_622, signtx_iface_error_handler, ((camkes_error_t){
            .type = CE_MALFORMED_RPC_PAYLOAD,
            .instance = "modchk",
            .interface = "signtx_iface",
            .description = "excess trailing bytes after unmarshalling parameters for print_sign",
            .length = _camkes_size_622,
            .current_index = _camkes_length_624,
            }), ({
                
                
                return -1;
        }));
    

    return 0;
    }






    void

signtx_iface_print_sign(

    
        
        
    
        
            const char *
        
        text
    

        
            ,
        
    
        
        
    
        
            const char *
        
        source
    

        
            ,
        
    
        
        
    
        
            int
        
        id
    

        
            ,
        
    
        
        
    
        
            int
        
        isValid
    

        
            ,
        
    
        
        
    
        
            const char *
        
        hmac
    

        
    

) {

    

    
    /* Save any pending reply cap as we'll eventually call seL4_Call which
     * could overwrite it. Note that we do this here before marshalling
     * parameters to ensure we don't inadvertently overwrite any marshalled
     * data with this call.
     */
    
        camkes_protect_reply_cap();
    
    


    
    
    

    /* Marshal all the parameters */
    
    unsigned _camkes_length_629 = 
    
    
    

    print_sign_marshal_inputs(
    
        
        text
        
            ,
        
    
        
        source
        
            ,
        
    
        
        id
        
            ,
        
    
        
        isValid
        
            ,
        
    
        
        hmac
        
    
    )
;
    if (unlikely(_camkes_length_629 == UINT_MAX)) {
        /* Error in marshalling; bail out. */
        
            return;
        
    }

    
    unsigned _camkes_size_630;
    
    /* Call the endpoint */
    
    seL4_MessageInfo_t _camkes_info_631 = seL4_MessageInfo_new(0, 0, 0,
        
                ROUND_UP_UNSAFE(_camkes_length_629, sizeof(seL4_Word)) / sizeof(seL4_Word)
        
        );
    _camkes_info_631 = seL4_Call(14, _camkes_info_631);

    _camkes_size_630 =
    
        seL4_MessageInfo_get_length(_camkes_info_631) * sizeof(seL4_Word);
        assert(_camkes_size_630 <= seL4_MsgMaxLength * sizeof(seL4_Word));
    


    /* Unmarshal the response */
    
    int _camkes_error_632 = 
    
    
    
    
    

    print_sign_unmarshal_outputs(
    _camkes_size_630
    
    
    
    )
;
    if (unlikely(_camkes_error_632 != 0)) {
        /* Error in unmarshalling; bail out. */
        
            return;
        
    }

    
    


    
}




    
    
    
    
    
    
    
    
    
    
    
    

    
    
        
            
        
    
        
            
        
    
        
            
                
    /* The TLS_PTR macro is for acquiring a pointer to a local variable. The first
     * argument is the corresponding TLS global and the second is the local
     * variable you are taking the address of. The purpose of this abstraction is
     * to allow for varying TLS models.
     */
    #ifdef CONFIG_CAMKES_TLS_STANDARD

    #ifndef TLS_PTR
        #define TLS_PTR(tls_var, name) (&(name))
    #endif

    #elif defined(CONFIG_CAMKES_TLS_PTG)

    #ifndef TLS_PTR
        #define TLS_PTR(tls_var, name) (get_##tls_var())
    #endif

    #else

        #error undefined TLS model

    #endif

    
        
        static int print_mod_id_from_1
        
        UNUSED;
    
        
        static int print_mod_id_from_2
        
        UNUSED;
    
        
        static int print_mod_id_from_3
        
        UNUSED;
    
        
        static int print_mod_id_from_4
        
        UNUSED;
    

    static int *
    
    get_print_mod_id_from(void) UNUSED;
    static int *
    
    get_print_mod_id_from(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_mod_id_from_1;
                    
            
                case 2:
                    
                        return & print_mod_id_from_2;
                    
            
                case 3:
                    
                        return & print_mod_id_from_3;
                    
            
                case 4:
                    
                        return & print_mod_id_from_4;
                    
            
            default:
                assert(!"invalid thread index");
                abort();
        }
    }

            
        
    
        
            
                
    /* The TLS_PTR macro is for acquiring a pointer to a local variable. The first
     * argument is the corresponding TLS global and the second is the local
     * variable you are taking the address of. The purpose of this abstraction is
     * to allow for varying TLS models.
     */
    #ifdef CONFIG_CAMKES_TLS_STANDARD

    #ifndef TLS_PTR
        #define TLS_PTR(tls_var, name) (&(name))
    #endif

    #elif defined(CONFIG_CAMKES_TLS_PTG)

    #ifndef TLS_PTR
        #define TLS_PTR(tls_var, name) (get_##tls_var())
    #endif

    #else

        #error undefined TLS model

    #endif

    
        
        static int print_mod_isValid_from_1
        
        UNUSED;
    
        
        static int print_mod_isValid_from_2
        
        UNUSED;
    
        
        static int print_mod_isValid_from_3
        
        UNUSED;
    
        
        static int print_mod_isValid_from_4
        
        UNUSED;
    

    static int *
    
    get_print_mod_isValid_from(void) UNUSED;
    static int *
    
    get_print_mod_isValid_from(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_mod_isValid_from_1;
                    
            
                case 2:
                    
                        return & print_mod_isValid_from_2;
                    
            
                case 3:
                    
                        return & print_mod_isValid_from_3;
                    
            
                case 4:
                    
                        return & print_mod_isValid_from_4;
                    
            
            default:
                assert(!"invalid thread index");
                abort();
        }
    }

            
        
    
    

    
        
        
        static unsigned print_mod_marshal_inputs_text(unsigned _camkes_offset_633,
            
    
        
            const char *
        
        text
    

        ) {

        
        void * _camkes_buffer_base_634 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                const char * _camkes_ptr_str_637 = text;
            
        

        
            
            size_t _camkes_strlen_639 = strnlen(_camkes_ptr_str_637, (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_633);
            
            
    ERR_IF(_camkes_strlen_639 + 1 > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_633, signtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modchk",
        .interface = "signtx_iface",
        .description = "buffer exceeded while marshalling text in print_mod",
        .current_length = _camkes_offset_633,
        .target_length = _camkes_offset_633 + _camkes_strlen_639 + 1,
        }), ({
            return UINT_MAX;
    }));

            /* If we didn't trigger an error, we now know this strcpy is safe. */
            (void)strcpy(_camkes_buffer_base_634 + _camkes_offset_633, _camkes_ptr_str_637);
            _camkes_offset_633 += _camkes_strlen_639 + 1;
        
        return _camkes_offset_633;
    }
    
        
        
        static unsigned print_mod_marshal_inputs_source(unsigned _camkes_offset_640,
            
    
        
            const char *
        
        source
    

        ) {

        
        void * _camkes_buffer_base_641 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                const char * _camkes_ptr_str_644 = source;
            
        

        
            
            size_t _camkes_strlen_646 = strnlen(_camkes_ptr_str_644, (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_640);
            
            
    ERR_IF(_camkes_strlen_646 + 1 > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_640, signtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modchk",
        .interface = "signtx_iface",
        .description = "buffer exceeded while marshalling source in print_mod",
        .current_length = _camkes_offset_640,
        .target_length = _camkes_offset_640 + _camkes_strlen_646 + 1,
        }), ({
            return UINT_MAX;
    }));

            /* If we didn't trigger an error, we now know this strcpy is safe. */
            (void)strcpy(_camkes_buffer_base_641 + _camkes_offset_640, _camkes_ptr_str_644);
            _camkes_offset_640 += _camkes_strlen_646 + 1;
        
        return _camkes_offset_640;
    }
    
        
        
        static unsigned print_mod_marshal_inputs_id(unsigned _camkes_offset_647,
            
    
        
            int
        
        id
    

        ) {

        
        void * _camkes_buffer_base_648 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                int * _camkes_ptr_649 = TLS_PTR(print_mod_id_from, id);
                * _camkes_ptr_649 = id;
            
        

        
            
            
    ERR_IF(sizeof(* _camkes_ptr_649) > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_647, signtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modchk",
        .interface = "signtx_iface",
        .description = "buffer exceeded while marshalling id in print_mod",
        .current_length = _camkes_offset_647,
        .target_length = _camkes_offset_647 + sizeof(* _camkes_ptr_649),
        }), ({
            return UINT_MAX;
    }));

            memcpy(_camkes_buffer_base_648 + _camkes_offset_647, _camkes_ptr_649, sizeof(* _camkes_ptr_649));
            _camkes_offset_647 += sizeof(* _camkes_ptr_649);
        
        return _camkes_offset_647;
    }
    
        
        
        static unsigned print_mod_marshal_inputs_isValid(unsigned _camkes_offset_653,
            
    
        
            int
        
        isValid
    

        ) {

        
        void * _camkes_buffer_base_654 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                int * _camkes_ptr_655 = TLS_PTR(print_mod_isValid_from, isValid);
                * _camkes_ptr_655 = isValid;
            
        

        
            
            
    ERR_IF(sizeof(* _camkes_ptr_655) > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_653, signtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modchk",
        .interface = "signtx_iface",
        .description = "buffer exceeded while marshalling isValid in print_mod",
        .current_length = _camkes_offset_653,
        .target_length = _camkes_offset_653 + sizeof(* _camkes_ptr_655),
        }), ({
            return UINT_MAX;
    }));

            memcpy(_camkes_buffer_base_654 + _camkes_offset_653, _camkes_ptr_655, sizeof(* _camkes_ptr_655));
            _camkes_offset_653 += sizeof(* _camkes_ptr_655);
        
        return _camkes_offset_653;
    }
    

    
        
        static const uint8_t _camkes_method_index_659 = 1;
    

    static unsigned print_mod_marshal_inputs(
    
    
        
        
    
        
            const char *
        
        text
    

        
            ,
        
    
        
        
    
        
            const char *
        
        source
    

        
            ,
        
    
        
        
    
        
            int
        
        id
    

        
            ,
        
    
        
        
    
        
            int
        
        isValid
    

        
    

    
    ) {

        
        unsigned _camkes_length_660 = 0;

        
        void * _camkes_buffer_base_661 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            /* Marshal the method index. */
            
            
    ERR_IF(sizeof(_camkes_method_index_659) > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_length_660, signtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modchk",
        .interface = "signtx_iface",
        .description = "buffer exceeded while marshalling print_mod in print_mod",
        .current_length = _camkes_length_660,
        .target_length = _camkes_length_660 + sizeof(_camkes_method_index_659),
        }), ({
            return UINT_MAX;
    }));

            memcpy(_camkes_buffer_base_661, & _camkes_method_index_659, sizeof(_camkes_method_index_659));
            _camkes_length_660 += sizeof(_camkes_method_index_659);
        

        /* Marshal the parameters. */
        
            
            _camkes_length_660 = print_mod_marshal_inputs_text(_camkes_length_660,
            
            text
            );
            if (unlikely(_camkes_length_660 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_660 = print_mod_marshal_inputs_source(_camkes_length_660,
            
            source
            );
            if (unlikely(_camkes_length_660 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_660 = print_mod_marshal_inputs_id(_camkes_length_660,
            
            id
            );
            if (unlikely(_camkes_length_660 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_660 = print_mod_marshal_inputs_isValid(_camkes_length_660,
            
            isValid
            );
            if (unlikely(_camkes_length_660 == UINT_MAX)) {
                return UINT_MAX;
            }
        

        assert(_camkes_length_660 <= (seL4_MsgMaxLength * sizeof(seL4_Word)) &&
            "uncaught buffer overflow while marshalling inputs for print_mod");

        return _camkes_length_660;
    }




    
    
    
    
    
    
    
    
    
    
    

    
    
    

    static int
    print_mod_unmarshal_outputs(
    
    unsigned _camkes_size_663
    
    
    

    
    

    ) {

        
        unsigned _camkes_length_665 UNUSED = 0;

        
        void * _camkes_buffer_base_666 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        

        /* Unmarshal the parameters. */
        

        
        ERR_IF(ROUND_UP_UNSAFE(_camkes_length_665, sizeof(seL4_Word)) != _camkes_size_663, signtx_iface_error_handler, ((camkes_error_t){
            .type = CE_MALFORMED_RPC_PAYLOAD,
            .instance = "modchk",
            .interface = "signtx_iface",
            .description = "excess trailing bytes after unmarshalling parameters for print_mod",
            .length = _camkes_size_663,
            .current_index = _camkes_length_665,
            }), ({
                
                
                return -1;
        }));
    

    return 0;
    }






    void

signtx_iface_print_mod(

    
        
        
    
        
            const char *
        
        text
    

        
            ,
        
    
        
        
    
        
            const char *
        
        source
    

        
            ,
        
    
        
        
    
        
            int
        
        id
    

        
            ,
        
    
        
        
    
        
            int
        
        isValid
    

        
    

) {

    

    
    /* Save any pending reply cap as we'll eventually call seL4_Call which
     * could overwrite it. Note that we do this here before marshalling
     * parameters to ensure we don't inadvertently overwrite any marshalled
     * data with this call.
     */
    
        camkes_protect_reply_cap();
    
    


    
    
    

    /* Marshal all the parameters */
    
    unsigned _camkes_length_670 = 
    
    
    

    print_mod_marshal_inputs(
    
        
        text
        
            ,
        
    
        
        source
        
            ,
        
    
        
        id
        
            ,
        
    
        
        isValid
        
    
    )
;
    if (unlikely(_camkes_length_670 == UINT_MAX)) {
        /* Error in marshalling; bail out. */
        
            return;
        
    }

    
    unsigned _camkes_size_671;
    
    /* Call the endpoint */
    
    seL4_MessageInfo_t _camkes_info_672 = seL4_MessageInfo_new(0, 0, 0,
        
                ROUND_UP_UNSAFE(_camkes_length_670, sizeof(seL4_Word)) / sizeof(seL4_Word)
        
        );
    _camkes_info_672 = seL4_Call(14, _camkes_info_672);

    _camkes_size_671 =
    
        seL4_MessageInfo_get_length(_camkes_info_672) * sizeof(seL4_Word);
        assert(_camkes_size_671 <= seL4_MsgMaxLength * sizeof(seL4_Word));
    


    /* Unmarshal the response */
    
    int _camkes_error_673 = 
    
    
    
    
    

    print_mod_unmarshal_outputs(
    _camkes_size_671
    
    
    
    )
;
    if (unlikely(_camkes_error_673 != 0)) {
        /* Error in unmarshalling; bail out. */
        
            return;
        
    }

    
    


    
}
