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
    static seL4_Word modchk_iface_badge = 0;

    seL4_Word modchk_iface_get_sender_id(void) {
        return modchk_iface_badge;
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
    static camkes_error_handler_t modchk_iface_error_handler_fn UNUSED;

    camkes_error_handler_t modchk_iface_register_error_handler(
        camkes_error_handler_t handler) {
        camkes_error_handler_t old = modchk_iface_error_handler_fn;
        modchk_iface_error_handler_fn = handler;
        return old;
    }

    static camkes_error_action_t UNUSED modchk_iface_error_handler(camkes_error_t *error) {
        if (modchk_iface_error_handler_fn == NULL) {
            /* No registered handler; invoke the generic error handler. */
            return camkes_error(error);
        }
        return modchk_iface_error_handler_fn(error);
    }





    
    
    

    
    
    





    
    
        extern
        
            void
        
            modchk_iface_verify(
                
    
        
        
    
        
            const char *
        
        text
    

        
            ,
        
    
        
        
    
        
            const char *
        
        source
    

        
            ,
        
    
        
        
    
        
            int
        
        id
    

        
    

                
            );

        
        
    
    
    
    
    
    
    
    

    
    
    
    static unsigned verify_unmarshal_inputs_text(unsigned _camkes_size_323, unsigned _camkes_offset_324,
        
    
        char * * text
    

    ) {

        
        void * _camkes_buffer_base_325 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            
            size_t _camkes_strlen_326 = strnlen(_camkes_buffer_base_325 + _camkes_offset_324, _camkes_size_323 - _camkes_offset_324);
            ERR_IF(_camkes_strlen_326 >= _camkes_size_323 - _camkes_offset_324, modchk_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "modchk",
                .interface = "modchk_iface",
                .description = "truncated message encountered while unmarshalling text in verify",
                .length = _camkes_size_323,
                .current_index = _camkes_offset_324 + _camkes_strlen_326 + 1,
                }), ({
                    return UINT_MAX;
            }));
            * text = strdup(_camkes_buffer_base_325 + _camkes_offset_324);
            ERR_IF(* text == NULL, modchk_iface_error_handler, ((camkes_error_t){
                .type = CE_ALLOCATION_FAILURE,
                .instance = "modchk",
                .interface = "modchk_iface",
                .description = "out of memory while unmarshalling text in verify",
                .alloc_bytes = _camkes_strlen_326 + 1,
                }), ({
                    return UINT_MAX;
            }));
            _camkes_offset_324 += _camkes_strlen_326 + 1;
        

        return _camkes_offset_324;
    }
    
    
    
    static unsigned verify_unmarshal_inputs_source(unsigned _camkes_size_327, unsigned _camkes_offset_328,
        
    
        char * * source
    

    ) {

        
        void * _camkes_buffer_base_329 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            
            size_t _camkes_strlen_330 = strnlen(_camkes_buffer_base_329 + _camkes_offset_328, _camkes_size_327 - _camkes_offset_328);
            ERR_IF(_camkes_strlen_330 >= _camkes_size_327 - _camkes_offset_328, modchk_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "modchk",
                .interface = "modchk_iface",
                .description = "truncated message encountered while unmarshalling source in verify",
                .length = _camkes_size_327,
                .current_index = _camkes_offset_328 + _camkes_strlen_330 + 1,
                }), ({
                    return UINT_MAX;
            }));
            * source = strdup(_camkes_buffer_base_329 + _camkes_offset_328);
            ERR_IF(* source == NULL, modchk_iface_error_handler, ((camkes_error_t){
                .type = CE_ALLOCATION_FAILURE,
                .instance = "modchk",
                .interface = "modchk_iface",
                .description = "out of memory while unmarshalling source in verify",
                .alloc_bytes = _camkes_strlen_330 + 1,
                }), ({
                    return UINT_MAX;
            }));
            _camkes_offset_328 += _camkes_strlen_330 + 1;
        

        return _camkes_offset_328;
    }
    
    
    
    static unsigned verify_unmarshal_inputs_id(unsigned _camkes_size_331, unsigned _camkes_offset_332,
        
    
        int * id
    

    ) {

        
        void * _camkes_buffer_base_333 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            ERR_IF(_camkes_offset_332 + sizeof(* id) > _camkes_size_331, modchk_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "modchk",
                .interface = "modchk_iface",
                .description = "truncated message encountered while unmarshalling id in verify",
                .length = _camkes_size_331,
                .current_index = _camkes_offset_332 + sizeof(* id),
                }), ({
                    return UINT_MAX;
            }));
            memcpy(id, _camkes_buffer_base_333 + _camkes_offset_332, sizeof(* id));
            _camkes_offset_332 += sizeof(* id);
        

        return _camkes_offset_332;
    }
    

    static int verify_unmarshal_inputs(
    
    unsigned _camkes_size_334
    
        ,
    
    
    
        
    
        char * * text
    

        
            ,
        
    
        
    
        char * * source
    

        
            ,
        
    
        
    
        int * id
    

        
    

    ) {

        
        unsigned _camkes_length_335 UNUSED = 0;

        
        void * _camkes_buffer_base_336 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        

        /* Unmarshal input parameters. */
        
            
            _camkes_length_335 = verify_unmarshal_inputs_text(_camkes_size_334, _camkes_length_335,
            
            text
            );
            if (unlikely(_camkes_length_335 == UINT_MAX)) {
            
            return -1;
        }
        
            
            _camkes_length_335 = verify_unmarshal_inputs_source(_camkes_size_334, _camkes_length_335,
            
            source
            );
            if (unlikely(_camkes_length_335 == UINT_MAX)) {
            
                
                    free(* text);
                
            
            return -1;
        }
        
            
            _camkes_length_335 = verify_unmarshal_inputs_id(_camkes_size_334, _camkes_length_335,
            
            id
            );
            if (unlikely(_camkes_length_335 == UINT_MAX)) {
            
                
                    free(* text);
                
            
                
                    free(* source);
                
            
            return -1;
        }
        

        
            ERR_IF(ROUND_UP_UNSAFE(_camkes_length_335, sizeof(seL4_Word)) != _camkes_size_334, modchk_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "modchk",
                .interface = "modchk_iface",
                .description = "excess trailing bytes after unmarshalling parameters for verify",
                .length = _camkes_size_334,
                .current_index = _camkes_length_335,
                }), ({
                    
                        
                            free(* text);
                        
                    
                        
                            free(* source);
                        
                    
                        
                    
                    return -1;
            }));
        

        return 0;
    }


        
        
    
    
    
    
    
    
    
    
    
    

    
    
    

    static unsigned verify_marshal_outputs(
    
    
    
    

    
        void
    
    ) {

        
        unsigned _camkes_length_339 = 0;

        

        /* Marshal output parameters. */
        

        assert(_camkes_length_339 <= (seL4_MsgMaxLength * sizeof(seL4_Word)) &&
            "uncaught buffer overflow while marshalling outputs for verify");

        return _camkes_length_339;
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

    
        
        static char * verify_text_to_1
        
        UNUSED;
    
        
        static char * verify_text_to_2
        
        UNUSED;
    
        
        static char * verify_text_to_3
        
        UNUSED;
    
        
        static char * verify_text_to_4
        
        UNUSED;
    

    static char * *
    
    get_verify_text_to(void) UNUSED;
    static char * *
    
    get_verify_text_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & verify_text_to_1;
                    
            
                case 2:
                    
                        return & verify_text_to_2;
                    
            
                case 3:
                    
                        return & verify_text_to_3;
                    
            
                case 4:
                    
                        return & verify_text_to_4;
                    
            
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

    
        
        static char * verify_source_to_1
        
        UNUSED;
    
        
        static char * verify_source_to_2
        
        UNUSED;
    
        
        static char * verify_source_to_3
        
        UNUSED;
    
        
        static char * verify_source_to_4
        
        UNUSED;
    

    static char * *
    
    get_verify_source_to(void) UNUSED;
    static char * *
    
    get_verify_source_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & verify_source_to_1;
                    
            
                case 2:
                    
                        return & verify_source_to_2;
                    
            
                case 3:
                    
                        return & verify_source_to_3;
                    
            
                case 4:
                    
                        return & verify_source_to_4;
                    
            
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

    
        
        static int verify_id_to_1
        
        UNUSED;
    
        
        static int verify_id_to_2
        
        UNUSED;
    
        
        static int verify_id_to_3
        
        UNUSED;
    
        
        static int verify_id_to_4
        
        UNUSED;
    

    static int *
    
    get_verify_id_to(void) UNUSED;
    static int *
    
    get_verify_id_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & verify_id_to_1;
                    
            
                case 2:
                    
                        return & verify_id_to_2;
                    
            
                case 3:
                    
                        return & verify_id_to_3;
                    
            
                case 4:
                    
                        return & verify_id_to_4;
                    
            
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

    
        
        static uint8_t _camkes_call_tls_var_to_340_1
        
        UNUSED;
    
        
        static uint8_t _camkes_call_tls_var_to_340_2
        
        UNUSED;
    
        
        static uint8_t _camkes_call_tls_var_to_340_3
        
        UNUSED;
    
        
        static uint8_t _camkes_call_tls_var_to_340_4
        
        UNUSED;
    

    static uint8_t *
    
    get__camkes_call_tls_var_to_340(void) UNUSED;
    static uint8_t *
    
    get__camkes_call_tls_var_to_340(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & _camkes_call_tls_var_to_340_1;
                    
            
                case 2:
                    
                        return & _camkes_call_tls_var_to_340_2;
                    
            
                case 3:
                    
                        return & _camkes_call_tls_var_to_340_3;
                    
            
                case 4:
                    
                        return & _camkes_call_tls_var_to_340_4;
                    
            
            default:
                assert(!"invalid thread index");
                abort();
        }
    }

    



    
    
    
        
        
            
                
        
  
  
  static void _camkes__341(void) NO_INLINE UNUSED
    WARNING("typedef char * looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__341(void) {
    /* We need something opaque here to prevent the compiler from optimising
     * away an invocation of (and hence the warning attached to) this function.
     * This is also why this function is marked noinline.
     */
    asm volatile ("");
  }
  static void ModchkIface_verify_text_array_typedef_check(char * x UNUSED)
    UNUSED;
  static void ModchkIface_verify_text_array_typedef_check(char * x UNUSED) {
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

      /* trigger a compile-time warning: */ _camkes__341(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
            
        
            
                
        
  
  
  static void _camkes__342(void) NO_INLINE UNUSED
    WARNING("typedef int looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__342(void) {
    /* We need something opaque here to prevent the compiler from optimising
     * away an invocation of (and hence the warning attached to) this function.
     * This is also why this function is marked noinline.
     */
    asm volatile ("");
  }
  static void ModchkIface_verify_id_array_typedef_check(int x UNUSED)
    UNUSED;
  static void ModchkIface_verify_id_array_typedef_check(int x UNUSED) {
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

      /* trigger a compile-time warning: */ _camkes__342(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
    







int

    modchk_iface__run(void)

{

    
    
    
    
    
        
        
            
                
        
  
  static char * _camkes__343;
  ModchkIface_verify_text_array_typedef_check(_camkes__343);

    
                
            
        
            
        
            
                
        
  
  static int _camkes__344;
  ModchkIface_verify_id_array_typedef_check(_camkes__344);

    
                
            
        
    



    
    unsigned _camkes_size_345 UNUSED;
    
        
    
        
            camkes_get_tls()->cnode_cap = 11;
        
    
    
        
        
            /* This interface has an active thread, just wait for an RPC */
            seL4_MessageInfo_t _camkes_info_346 = seL4_Recv(10, &modchk_iface_badge);
        
        
    _camkes_size_345 =
        
            seL4_MessageInfo_get_length(_camkes_info_346) * sizeof(seL4_Word);
            assert(_camkes_size_345 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    


    

    while (1) {
        
        
            
            
            

            
            
            
                unsigned _camkes_call_347 UNUSED;
                unsigned * _camkes_call_ptr_348 = TLS_PTR(_camkes_call_tls_var_to_340, _camkes_call_347);
                * _camkes_call_ptr_348 = 0;
            
            

            switch (* _camkes_call_ptr_348) {
                
                    case 0: { /* verify */
                        
                        

                            
                                char * text UNUSED = NULL;
                                char ** text_ptr = TLS_PTR(verify_text_to, text);
                            
                        

                            
                                char * source UNUSED = NULL;
                                char ** source_ptr = TLS_PTR(verify_source_to, source);
                            
                        

                            
                                int id UNUSED;
                                int * id_ptr = TLS_PTR(verify_id_to, id);
                            
                        

                        /* Unmarshal parameters */
                        
                        
                        int _camkes_error_349 = 
    
    
    
    

    verify_unmarshal_inputs(
    _camkes_size_345
    
        ,
    
    
        
        text_ptr
        
            ,
        
    
        
        source_ptr
        
            ,
        
    
        
        id_ptr
        
    
    )
;
                        if (unlikely(_camkes_error_349 != 0)) {
                            /* Error in unmarshalling; return to event loop. */
                            
    

                            
    
    seL4_MessageInfo_t _camkes_info_350 = seL4_Recv(10, &modchk_iface_badge);
    
    _camkes_size_345 =
        
            seL4_MessageInfo_get_length(_camkes_info_350) * sizeof(seL4_Word);
            assert(_camkes_size_345 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    


                            continue;
                        }

                        /* Call the implementation */
                        
                        
                        
                        
                        
                        modchk_iface_verify(
                            
                                
                                
                                    *
                                
                                text_ptr
                                ,
                            
                                
                                
                                    *
                                
                                source_ptr
                                ,
                            
                                
                                
                                    *
                                
                                id_ptr
                                
                            
                        );

                        
    

                        
    


                        /* Marshal the response */
                        
                        
                        unsigned _camkes_length_355 = 
    
    
    
    

    verify_marshal_outputs(
    
    
    )
;

                        
                        
                        
                            
                                free(* text_ptr);
                            
                        
                            
                                free(* source_ptr);
                            
                        
                            
                        

                        /* Check if there was an error during marshalling. We do
                         * this after freeing internal parameter variables to avoid
                         * leaking memory on errors.
                         */
                        if (unlikely(_camkes_length_355 == UINT_MAX)) {
                            
    

                            
    
    seL4_MessageInfo_t _camkes_info_356 = seL4_Recv(10, &modchk_iface_badge);
    
    _camkes_size_345 =
        
            seL4_MessageInfo_get_length(_camkes_info_356) * sizeof(seL4_Word);
            assert(_camkes_size_345 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    


                            continue;
                        }

                        
    
        
        seL4_MessageInfo_t _camkes_info_357 = seL4_MessageInfo_new(0, 0, 0, /* length */
            
                ROUND_UP_UNSAFE(_camkes_length_355, sizeof(seL4_Word)) / sizeof(seL4_Word)
            
        );

        /* Send the response */
        
            
            camkes_tls_t * _camkes__358 UNUSED = camkes_get_tls();
            assert(_camkes__358 != NULL);
            if (_camkes__358->reply_cap_in_tcb) {
                _camkes__358->reply_cap_in_tcb = false;
                _camkes_info_357 = seL4_ReplyRecv(10, _camkes_info_357, &modchk_iface_badge);
            } else {
                camkes_unprotect_reply_cap();
                seL4_Send(12, _camkes_info_357);
                _camkes_info_357 = seL4_Recv(10, &modchk_iface_badge);
            }
        
        
    _camkes_size_345 =
        
            seL4_MessageInfo_get_length(_camkes_info_357) * sizeof(seL4_Word);
            assert(_camkes_size_345 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    



                        break;
                    }
                
                default: {
                    ERR(modchk_iface_error_handler, ((camkes_error_t){
                        .type = CE_INVALID_METHOD_INDEX,
                        .instance = "modchk",
                        .interface = "modchk_iface",
                        .description = "invalid method index received in modchk_iface",
                        .lower_bound = 0,
                        .upper_bound = 1 - 1,
                        .invalid_index = * _camkes_call_ptr_348,
                    }), ({
                        
    

                        
    
    seL4_MessageInfo_t _camkes_info_359 = seL4_Recv(10, &modchk_iface_badge);
    
    _camkes_size_345 =
        
            seL4_MessageInfo_get_length(_camkes_info_359) * sizeof(seL4_Word);
            assert(_camkes_size_345 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    


                        continue;
                    }));
                }
            }
            
        
        
    }

    UNREACHABLE();
}

