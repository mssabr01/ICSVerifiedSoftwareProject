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







  
    
  

  
    
  







  
    
    
    
    
    
        
            
            
            
            
        
    
    
    
    
    
    

    

    
    
    

    
    
    
    
        
        
        
            
        
    
        
        
        
            
        
    

    
    
    
        
            
                
            
                
            
            
        
    
        
            
                
                    
                
            
                
            
            
        
    


    
        
    
    #include <sel4/sel4.h>
    static seL4_Word modtx_iface_badge = 0;

    seL4_Word modtx_iface_get_sender_id(void) {
        return modtx_iface_badge;
    }

    

    
    
        
            
            
            
        
    
    
    



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








#include <autoconf.h>
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <camkes/error.h>
#include <camkes/tls.h>
#include <sel4/sel4.h>
#include <camkes/dataport.h>
#include <utils/util.h>









/* Interface-specific error handling */


    
    
    

    /* The currently active error handler. This variable is marked UNUSED to squash
     * compiler warnings generated when the user's build configuration causes the
     * two following functions to be pruned from the final source.
    */
    static camkes_error_handler_t modtx_iface_error_handler_fn UNUSED;

    camkes_error_handler_t modtx_iface_register_error_handler(
        camkes_error_handler_t handler) {
        camkes_error_handler_t old = modtx_iface_error_handler_fn;
        modtx_iface_error_handler_fn = handler;
        return old;
    }

    static camkes_error_action_t UNUSED modtx_iface_error_handler(camkes_error_t *error) {
        if (modtx_iface_error_handler_fn == NULL) {
            /* No registered handler; invoke the generic error handler. */
            return camkes_error(error);
        }
        return modtx_iface_error_handler_fn(error);
    }





    
    
    

    
    
    





    
    
        extern
        
            void
        
            modtx_iface_print(
                
    
        
        
    
        
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
    

        
    

                
            );

        
        
    
    
    
    
    
    
    
    

    
    
    
    static unsigned print_unmarshal_inputs_text(unsigned _camkes_size_448, unsigned _camkes_offset_449,
        
    
        char * * text
    

    ) {

        
        void * _camkes_buffer_base_450 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            
            size_t _camkes_strlen_451 = strnlen(_camkes_buffer_base_450 + _camkes_offset_449, _camkes_size_448 - _camkes_offset_449);
            ERR_IF(_camkes_strlen_451 >= _camkes_size_448 - _camkes_offset_449, modtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "modtx",
                .interface = "modtx_iface",
                .description = "truncated message encountered while unmarshalling text in print",
                .length = _camkes_size_448,
                .current_index = _camkes_offset_449 + _camkes_strlen_451 + 1,
                }), ({
                    return UINT_MAX;
            }));
            * text = strdup(_camkes_buffer_base_450 + _camkes_offset_449);
            ERR_IF(* text == NULL, modtx_iface_error_handler, ((camkes_error_t){
                .type = CE_ALLOCATION_FAILURE,
                .instance = "modtx",
                .interface = "modtx_iface",
                .description = "out of memory while unmarshalling text in print",
                .alloc_bytes = _camkes_strlen_451 + 1,
                }), ({
                    return UINT_MAX;
            }));
            _camkes_offset_449 += _camkes_strlen_451 + 1;
        

        return _camkes_offset_449;
    }
    
    
    
    static unsigned print_unmarshal_inputs_source(unsigned _camkes_size_452, unsigned _camkes_offset_453,
        
    
        char * * source
    

    ) {

        
        void * _camkes_buffer_base_454 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            
            size_t _camkes_strlen_455 = strnlen(_camkes_buffer_base_454 + _camkes_offset_453, _camkes_size_452 - _camkes_offset_453);
            ERR_IF(_camkes_strlen_455 >= _camkes_size_452 - _camkes_offset_453, modtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "modtx",
                .interface = "modtx_iface",
                .description = "truncated message encountered while unmarshalling source in print",
                .length = _camkes_size_452,
                .current_index = _camkes_offset_453 + _camkes_strlen_455 + 1,
                }), ({
                    return UINT_MAX;
            }));
            * source = strdup(_camkes_buffer_base_454 + _camkes_offset_453);
            ERR_IF(* source == NULL, modtx_iface_error_handler, ((camkes_error_t){
                .type = CE_ALLOCATION_FAILURE,
                .instance = "modtx",
                .interface = "modtx_iface",
                .description = "out of memory while unmarshalling source in print",
                .alloc_bytes = _camkes_strlen_455 + 1,
                }), ({
                    return UINT_MAX;
            }));
            _camkes_offset_453 += _camkes_strlen_455 + 1;
        

        return _camkes_offset_453;
    }
    
    
    
    static unsigned print_unmarshal_inputs_id(unsigned _camkes_size_456, unsigned _camkes_offset_457,
        
    
        int * id
    

    ) {

        
        void * _camkes_buffer_base_458 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            ERR_IF(_camkes_offset_457 + sizeof(* id) > _camkes_size_456, modtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "modtx",
                .interface = "modtx_iface",
                .description = "truncated message encountered while unmarshalling id in print",
                .length = _camkes_size_456,
                .current_index = _camkes_offset_457 + sizeof(* id),
                }), ({
                    return UINT_MAX;
            }));
            memcpy(id, _camkes_buffer_base_458 + _camkes_offset_457, sizeof(* id));
            _camkes_offset_457 += sizeof(* id);
        

        return _camkes_offset_457;
    }
    
    
    
    static unsigned print_unmarshal_inputs_isValid(unsigned _camkes_size_459, unsigned _camkes_offset_460,
        
    
        int * isValid
    

    ) {

        
        void * _camkes_buffer_base_461 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            ERR_IF(_camkes_offset_460 + sizeof(* isValid) > _camkes_size_459, modtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "modtx",
                .interface = "modtx_iface",
                .description = "truncated message encountered while unmarshalling isValid in print",
                .length = _camkes_size_459,
                .current_index = _camkes_offset_460 + sizeof(* isValid),
                }), ({
                    return UINT_MAX;
            }));
            memcpy(isValid, _camkes_buffer_base_461 + _camkes_offset_460, sizeof(* isValid));
            _camkes_offset_460 += sizeof(* isValid);
        

        return _camkes_offset_460;
    }
    

    static int print_unmarshal_inputs(
    
    unsigned _camkes_size_462
    
        ,
    
    
    
        
    
        char * * text
    

        
            ,
        
    
        
    
        char * * source
    

        
            ,
        
    
        
    
        int * id
    

        
            ,
        
    
        
    
        int * isValid
    

        
    

    ) {

        
        unsigned _camkes_length_463 UNUSED = 0;

        
        void * _camkes_buffer_base_464 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        

        /* Unmarshal input parameters. */
        
            
            _camkes_length_463 = print_unmarshal_inputs_text(_camkes_size_462, _camkes_length_463,
            
            text
            );
            if (unlikely(_camkes_length_463 == UINT_MAX)) {
            
            return -1;
        }
        
            
            _camkes_length_463 = print_unmarshal_inputs_source(_camkes_size_462, _camkes_length_463,
            
            source
            );
            if (unlikely(_camkes_length_463 == UINT_MAX)) {
            
                
                    free(* text);
                
            
            return -1;
        }
        
            
            _camkes_length_463 = print_unmarshal_inputs_id(_camkes_size_462, _camkes_length_463,
            
            id
            );
            if (unlikely(_camkes_length_463 == UINT_MAX)) {
            
                
                    free(* text);
                
            
                
                    free(* source);
                
            
            return -1;
        }
        
            
            _camkes_length_463 = print_unmarshal_inputs_isValid(_camkes_size_462, _camkes_length_463,
            
            isValid
            );
            if (unlikely(_camkes_length_463 == UINT_MAX)) {
            
                
                    free(* text);
                
            
                
                    free(* source);
                
            
                
            
            return -1;
        }
        

        
            ERR_IF(ROUND_UP_UNSAFE(_camkes_length_463, sizeof(seL4_Word)) != _camkes_size_462, modtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "modtx",
                .interface = "modtx_iface",
                .description = "excess trailing bytes after unmarshalling parameters for print",
                .length = _camkes_size_462,
                .current_index = _camkes_length_463,
                }), ({
                    
                        
                            free(* text);
                        
                    
                        
                            free(* source);
                        
                    
                        
                    
                        
                    
                    return -1;
            }));
        

        return 0;
    }


        
        
    
    
    
    
    
    
    
    
    
    

    
    
    

    static unsigned print_marshal_outputs(
    
    
    
    

    
        void
    
    ) {

        
        unsigned _camkes_length_467 = 0;

        

        /* Marshal output parameters. */
        

        assert(_camkes_length_467 <= (seL4_MsgMaxLength * sizeof(seL4_Word)) &&
            "uncaught buffer overflow while marshalling outputs for print");

        return _camkes_length_467;
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

    
        
        static char * print_text_to_1
        
        UNUSED;
    
        
        static char * print_text_to_2
        
        UNUSED;
    
        
        static char * print_text_to_3
        
        UNUSED;
    
        
        static char * print_text_to_4
        
        UNUSED;
    

    static char * *
    
    get_print_text_to(void) UNUSED;
    static char * *
    
    get_print_text_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_text_to_1;
                    
            
                case 2:
                    
                        return & print_text_to_2;
                    
            
                case 3:
                    
                        return & print_text_to_3;
                    
            
                case 4:
                    
                        return & print_text_to_4;
                    
            
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

    
        
        static char * print_source_to_1
        
        UNUSED;
    
        
        static char * print_source_to_2
        
        UNUSED;
    
        
        static char * print_source_to_3
        
        UNUSED;
    
        
        static char * print_source_to_4
        
        UNUSED;
    

    static char * *
    
    get_print_source_to(void) UNUSED;
    static char * *
    
    get_print_source_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_source_to_1;
                    
            
                case 2:
                    
                        return & print_source_to_2;
                    
            
                case 3:
                    
                        return & print_source_to_3;
                    
            
                case 4:
                    
                        return & print_source_to_4;
                    
            
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

    
        
        static int print_id_to_1
        
        UNUSED;
    
        
        static int print_id_to_2
        
        UNUSED;
    
        
        static int print_id_to_3
        
        UNUSED;
    
        
        static int print_id_to_4
        
        UNUSED;
    

    static int *
    
    get_print_id_to(void) UNUSED;
    static int *
    
    get_print_id_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_id_to_1;
                    
            
                case 2:
                    
                        return & print_id_to_2;
                    
            
                case 3:
                    
                        return & print_id_to_3;
                    
            
                case 4:
                    
                        return & print_id_to_4;
                    
            
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

    
        
        static int print_isValid_to_1
        
        UNUSED;
    
        
        static int print_isValid_to_2
        
        UNUSED;
    
        
        static int print_isValid_to_3
        
        UNUSED;
    
        
        static int print_isValid_to_4
        
        UNUSED;
    

    static int *
    
    get_print_isValid_to(void) UNUSED;
    static int *
    
    get_print_isValid_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_isValid_to_1;
                    
            
                case 2:
                    
                        return & print_isValid_to_2;
                    
            
                case 3:
                    
                        return & print_isValid_to_3;
                    
            
                case 4:
                    
                        return & print_isValid_to_4;
                    
            
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

    
        
        static uint8_t _camkes_call_tls_var_to_468_1
        
        UNUSED;
    
        
        static uint8_t _camkes_call_tls_var_to_468_2
        
        UNUSED;
    
        
        static uint8_t _camkes_call_tls_var_to_468_3
        
        UNUSED;
    
        
        static uint8_t _camkes_call_tls_var_to_468_4
        
        UNUSED;
    

    static uint8_t *
    
    get__camkes_call_tls_var_to_468(void) UNUSED;
    static uint8_t *
    
    get__camkes_call_tls_var_to_468(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & _camkes_call_tls_var_to_468_1;
                    
            
                case 2:
                    
                        return & _camkes_call_tls_var_to_468_2;
                    
            
                case 3:
                    
                        return & _camkes_call_tls_var_to_468_3;
                    
            
                case 4:
                    
                        return & _camkes_call_tls_var_to_468_4;
                    
            
            default:
                assert(!"invalid thread index");
                abort();
        }
    }

    



    
    
    
        
        
            
                
        
  
  
  static void _camkes__469(void) NO_INLINE UNUSED
    WARNING("typedef char * looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__469(void) {
    /* We need something opaque here to prevent the compiler from optimising
     * away an invocation of (and hence the warning attached to) this function.
     * This is also why this function is marked noinline.
     */
    asm volatile ("");
  }
  static void ModtxIface_print_text_array_typedef_check(char * x UNUSED)
    UNUSED;
  static void ModtxIface_print_text_array_typedef_check(char * x UNUSED) {
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

      /* trigger a compile-time warning: */ _camkes__469(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
            
        
            
                
        
  
  
  static void _camkes__470(void) NO_INLINE UNUSED
    WARNING("typedef int looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__470(void) {
    /* We need something opaque here to prevent the compiler from optimising
     * away an invocation of (and hence the warning attached to) this function.
     * This is also why this function is marked noinline.
     */
    asm volatile ("");
  }
  static void ModtxIface_print_id_array_typedef_check(int x UNUSED)
    UNUSED;
  static void ModtxIface_print_id_array_typedef_check(int x UNUSED) {
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

      /* trigger a compile-time warning: */ _camkes__470(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
            
        
    







int

    modtx_iface__run(void)

{

    
    
    
    
    
        
        
            
                
        
  
  static char * _camkes__471;
  ModtxIface_print_text_array_typedef_check(_camkes__471);

    
                
            
        
            
        
            
                
        
  
  static int _camkes__472;
  ModtxIface_print_id_array_typedef_check(_camkes__472);

    
                
            
        
            
        
    



    
    unsigned _camkes_size_473 UNUSED;
    
        
    
        
            camkes_get_tls()->cnode_cap = 13;
        
    
    
        
        
            /* This interface has an active thread, just wait for an RPC */
            seL4_MessageInfo_t _camkes_info_474 = seL4_Recv(12, &modtx_iface_badge);
        
        
    _camkes_size_473 =
        
            seL4_MessageInfo_get_length(_camkes_info_474) * sizeof(seL4_Word);
            assert(_camkes_size_473 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    


    

    while (1) {
        
        
            
            
            

            
            
            
                unsigned _camkes_call_475 UNUSED;
                unsigned * _camkes_call_ptr_476 = TLS_PTR(_camkes_call_tls_var_to_468, _camkes_call_475);
                * _camkes_call_ptr_476 = 0;
            
            

            switch (* _camkes_call_ptr_476) {
                
                    case 0: { /* print */
                        
                        

                            
                                char * text UNUSED = NULL;
                                char ** text_ptr = TLS_PTR(print_text_to, text);
                            
                        

                            
                                char * source UNUSED = NULL;
                                char ** source_ptr = TLS_PTR(print_source_to, source);
                            
                        

                            
                                int id UNUSED;
                                int * id_ptr = TLS_PTR(print_id_to, id);
                            
                        

                            
                                int isValid UNUSED;
                                int * isValid_ptr = TLS_PTR(print_isValid_to, isValid);
                            
                        

                        /* Unmarshal parameters */
                        
                        
                        int _camkes_error_477 = 
    
    
    
    

    print_unmarshal_inputs(
    _camkes_size_473
    
        ,
    
    
        
        text_ptr
        
            ,
        
    
        
        source_ptr
        
            ,
        
    
        
        id_ptr
        
            ,
        
    
        
        isValid_ptr
        
    
    )
;
                        if (unlikely(_camkes_error_477 != 0)) {
                            /* Error in unmarshalling; return to event loop. */
                            
    

                            
    
    seL4_MessageInfo_t _camkes_info_478 = seL4_Recv(12, &modtx_iface_badge);
    
    _camkes_size_473 =
        
            seL4_MessageInfo_get_length(_camkes_info_478) * sizeof(seL4_Word);
            assert(_camkes_size_473 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    


                            continue;
                        }

                        /* Call the implementation */
                        
                        
                        
                        
                        
                        modtx_iface_print(
                            
                                
                                
                                    *
                                
                                text_ptr
                                ,
                            
                                
                                
                                    *
                                
                                source_ptr
                                ,
                            
                                
                                
                                    *
                                
                                id_ptr
                                ,
                            
                                
                                
                                    *
                                
                                isValid_ptr
                                
                            
                        );

                        
    

                        
    


                        /* Marshal the response */
                        
                        
                        unsigned _camkes_length_483 = 
    
    
    
    

    print_marshal_outputs(
    
    
    )
;

                        
                        
                        
                            
                                free(* text_ptr);
                            
                        
                            
                                free(* source_ptr);
                            
                        
                            
                        
                            
                        

                        /* Check if there was an error during marshalling. We do
                         * this after freeing internal parameter variables to avoid
                         * leaking memory on errors.
                         */
                        if (unlikely(_camkes_length_483 == UINT_MAX)) {
                            
    

                            
    
    seL4_MessageInfo_t _camkes_info_484 = seL4_Recv(12, &modtx_iface_badge);
    
    _camkes_size_473 =
        
            seL4_MessageInfo_get_length(_camkes_info_484) * sizeof(seL4_Word);
            assert(_camkes_size_473 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    


                            continue;
                        }

                        
    
        
        seL4_MessageInfo_t _camkes_info_485 = seL4_MessageInfo_new(0, 0, 0, /* length */
            
                ROUND_UP_UNSAFE(_camkes_length_483, sizeof(seL4_Word)) / sizeof(seL4_Word)
            
        );

        /* Send the response */
        
            
            camkes_tls_t * _camkes__486 UNUSED = camkes_get_tls();
            assert(_camkes__486 != NULL);
            if (_camkes__486->reply_cap_in_tcb) {
                _camkes__486->reply_cap_in_tcb = false;
                _camkes_info_485 = seL4_ReplyRecv(12, _camkes_info_485, &modtx_iface_badge);
            } else {
                camkes_unprotect_reply_cap();
                seL4_Send(14, _camkes_info_485);
                _camkes_info_485 = seL4_Recv(12, &modtx_iface_badge);
            }
        
        
    _camkes_size_473 =
        
            seL4_MessageInfo_get_length(_camkes_info_485) * sizeof(seL4_Word);
            assert(_camkes_size_473 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    



                        break;
                    }
                
                default: {
                    ERR(modtx_iface_error_handler, ((camkes_error_t){
                        .type = CE_INVALID_METHOD_INDEX,
                        .instance = "modtx",
                        .interface = "modtx_iface",
                        .description = "invalid method index received in modtx_iface",
                        .lower_bound = 0,
                        .upper_bound = 1 - 1,
                        .invalid_index = * _camkes_call_ptr_476,
                    }), ({
                        
    

                        
    
    seL4_MessageInfo_t _camkes_info_487 = seL4_Recv(12, &modtx_iface_badge);
    
    _camkes_size_473 =
        
            seL4_MessageInfo_get_length(_camkes_info_487) * sizeof(seL4_Word);
            assert(_camkes_size_473 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    


                        continue;
                    }));
                }
            }
            
        
        
    }

    UNREACHABLE();
}

