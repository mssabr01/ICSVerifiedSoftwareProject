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



    
    
    
        
        
            
                
        
  
  
  static void _camkes__360(void) NO_INLINE UNUSED
    WARNING("typedef char * looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__360(void) {
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

      /* trigger a compile-time warning: */ _camkes__360(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
            
        
            
                
        
  
  
  static void _camkes__361(void) NO_INLINE UNUSED
    WARNING("typedef int looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__361(void) {
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

      /* trigger a compile-time warning: */ _camkes__361(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
            
        
    



int modtx_iface__run(void) {
    /* This function is never actually executed, but we still emit it for the
     * purpose of type checking RPC parameters.
     */
    UNREACHABLE();

    
    
    
    
    
        
        
            
                
        
  
  static char * _camkes__362;
  ModtxIface_print_text_array_typedef_check(_camkes__362);

    
                
            
        
            
        
            
                
        
  
  static int _camkes__363;
  ModtxIface_print_id_array_typedef_check(_camkes__363);

    
                
            
        
            
        
    


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

    
        
        static int print_id_from_1
        
        UNUSED;
    
        
        static int print_id_from_2
        
        UNUSED;
    
        
        static int print_id_from_3
        
        UNUSED;
    
        
        static int print_id_from_4
        
        UNUSED;
    

    static int *
    
    get_print_id_from(void) UNUSED;
    static int *
    
    get_print_id_from(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_id_from_1;
                    
            
                case 2:
                    
                        return & print_id_from_2;
                    
            
                case 3:
                    
                        return & print_id_from_3;
                    
            
                case 4:
                    
                        return & print_id_from_4;
                    
            
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

    
        
        static int print_isValid_from_1
        
        UNUSED;
    
        
        static int print_isValid_from_2
        
        UNUSED;
    
        
        static int print_isValid_from_3
        
        UNUSED;
    
        
        static int print_isValid_from_4
        
        UNUSED;
    

    static int *
    
    get_print_isValid_from(void) UNUSED;
    static int *
    
    get_print_isValid_from(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_isValid_from_1;
                    
            
                case 2:
                    
                        return & print_isValid_from_2;
                    
            
                case 3:
                    
                        return & print_isValid_from_3;
                    
            
                case 4:
                    
                        return & print_isValid_from_4;
                    
            
            default:
                assert(!"invalid thread index");
                abort();
        }
    }

            
        
    
    

    
        
        
        static unsigned print_marshal_inputs_text(unsigned _camkes_offset_364,
            
    
        
            const char *
        
        text
    

        ) {

        
        void * _camkes_buffer_base_365 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                const char * _camkes_ptr_str_368 = text;
            
        

        
            
            size_t _camkes_strlen_370 = strnlen(_camkes_ptr_str_368, (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_364);
            
            
    ERR_IF(_camkes_strlen_370 + 1 > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_364, modtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "crypto",
        .interface = "modtx_iface",
        .description = "buffer exceeded while marshalling text in print",
        .current_length = _camkes_offset_364,
        .target_length = _camkes_offset_364 + _camkes_strlen_370 + 1,
        }), ({
            return UINT_MAX;
    }));

            /* If we didn't trigger an error, we now know this strcpy is safe. */
            (void)strcpy(_camkes_buffer_base_365 + _camkes_offset_364, _camkes_ptr_str_368);
            _camkes_offset_364 += _camkes_strlen_370 + 1;
        
        return _camkes_offset_364;
    }
    
        
        
        static unsigned print_marshal_inputs_source(unsigned _camkes_offset_371,
            
    
        
            const char *
        
        source
    

        ) {

        
        void * _camkes_buffer_base_372 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                const char * _camkes_ptr_str_375 = source;
            
        

        
            
            size_t _camkes_strlen_377 = strnlen(_camkes_ptr_str_375, (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_371);
            
            
    ERR_IF(_camkes_strlen_377 + 1 > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_371, modtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "crypto",
        .interface = "modtx_iface",
        .description = "buffer exceeded while marshalling source in print",
        .current_length = _camkes_offset_371,
        .target_length = _camkes_offset_371 + _camkes_strlen_377 + 1,
        }), ({
            return UINT_MAX;
    }));

            /* If we didn't trigger an error, we now know this strcpy is safe. */
            (void)strcpy(_camkes_buffer_base_372 + _camkes_offset_371, _camkes_ptr_str_375);
            _camkes_offset_371 += _camkes_strlen_377 + 1;
        
        return _camkes_offset_371;
    }
    
        
        
        static unsigned print_marshal_inputs_id(unsigned _camkes_offset_378,
            
    
        
            int
        
        id
    

        ) {

        
        void * _camkes_buffer_base_379 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                int * _camkes_ptr_380 = TLS_PTR(print_id_from, id);
                * _camkes_ptr_380 = id;
            
        

        
            
            
    ERR_IF(sizeof(* _camkes_ptr_380) > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_378, modtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "crypto",
        .interface = "modtx_iface",
        .description = "buffer exceeded while marshalling id in print",
        .current_length = _camkes_offset_378,
        .target_length = _camkes_offset_378 + sizeof(* _camkes_ptr_380),
        }), ({
            return UINT_MAX;
    }));

            memcpy(_camkes_buffer_base_379 + _camkes_offset_378, _camkes_ptr_380, sizeof(* _camkes_ptr_380));
            _camkes_offset_378 += sizeof(* _camkes_ptr_380);
        
        return _camkes_offset_378;
    }
    
        
        
        static unsigned print_marshal_inputs_isValid(unsigned _camkes_offset_384,
            
    
        
            int
        
        isValid
    

        ) {

        
        void * _camkes_buffer_base_385 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                int * _camkes_ptr_386 = TLS_PTR(print_isValid_from, isValid);
                * _camkes_ptr_386 = isValid;
            
        

        
            
            
    ERR_IF(sizeof(* _camkes_ptr_386) > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_384, modtx_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "crypto",
        .interface = "modtx_iface",
        .description = "buffer exceeded while marshalling isValid in print",
        .current_length = _camkes_offset_384,
        .target_length = _camkes_offset_384 + sizeof(* _camkes_ptr_386),
        }), ({
            return UINT_MAX;
    }));

            memcpy(_camkes_buffer_base_385 + _camkes_offset_384, _camkes_ptr_386, sizeof(* _camkes_ptr_386));
            _camkes_offset_384 += sizeof(* _camkes_ptr_386);
        
        return _camkes_offset_384;
    }
    

    

    static unsigned print_marshal_inputs(
    
    
        
        
    
        
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

        
        unsigned _camkes_length_390 = 0;

        
        void * _camkes_buffer_base_391 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        

        /* Marshal the parameters. */
        
            
            _camkes_length_390 = print_marshal_inputs_text(_camkes_length_390,
            
            text
            );
            if (unlikely(_camkes_length_390 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_390 = print_marshal_inputs_source(_camkes_length_390,
            
            source
            );
            if (unlikely(_camkes_length_390 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_390 = print_marshal_inputs_id(_camkes_length_390,
            
            id
            );
            if (unlikely(_camkes_length_390 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_390 = print_marshal_inputs_isValid(_camkes_length_390,
            
            isValid
            );
            if (unlikely(_camkes_length_390 == UINT_MAX)) {
                return UINT_MAX;
            }
        

        assert(_camkes_length_390 <= (seL4_MsgMaxLength * sizeof(seL4_Word)) &&
            "uncaught buffer overflow while marshalling inputs for print");

        return _camkes_length_390;
    }




    
    
    
    
    
    
    
    
    
    
    

    
    
    

    static int
    print_unmarshal_outputs(
    
    unsigned _camkes_size_393
    
    
    

    
    

    ) {

        
        unsigned _camkes_length_395 UNUSED = 0;

        
        void * _camkes_buffer_base_396 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        

        /* Unmarshal the parameters. */
        

        
        ERR_IF(ROUND_UP_UNSAFE(_camkes_length_395, sizeof(seL4_Word)) != _camkes_size_393, modtx_iface_error_handler, ((camkes_error_t){
            .type = CE_MALFORMED_RPC_PAYLOAD,
            .instance = "crypto",
            .interface = "modtx_iface",
            .description = "excess trailing bytes after unmarshalling parameters for print",
            .length = _camkes_size_393,
            .current_index = _camkes_length_395,
            }), ({
                
                
                return -1;
        }));
    

    return 0;
    }






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
    

        
    

) {

    

    
    /* Save any pending reply cap as we'll eventually call seL4_Call which
     * could overwrite it. Note that we do this here before marshalling
     * parameters to ensure we don't inadvertently overwrite any marshalled
     * data with this call.
     */
    
        camkes_protect_reply_cap();
    
    


    
    
    

    /* Marshal all the parameters */
    
    unsigned _camkes_length_400 = 
    
    
    

    print_marshal_inputs(
    
        
        text
        
            ,
        
    
        
        source
        
            ,
        
    
        
        id
        
            ,
        
    
        
        isValid
        
    
    )
;
    if (unlikely(_camkes_length_400 == UINT_MAX)) {
        /* Error in marshalling; bail out. */
        
            return;
        
    }

    
    unsigned _camkes_size_401;
    
    /* Call the endpoint */
    
    seL4_MessageInfo_t _camkes_info_402 = seL4_MessageInfo_new(0, 0, 0,
        
                ROUND_UP_UNSAFE(_camkes_length_400, sizeof(seL4_Word)) / sizeof(seL4_Word)
        
        );
    _camkes_info_402 = seL4_Call(13, _camkes_info_402);

    _camkes_size_401 =
    
        seL4_MessageInfo_get_length(_camkes_info_402) * sizeof(seL4_Word);
        assert(_camkes_size_401 <= seL4_MsgMaxLength * sizeof(seL4_Word));
    


    /* Unmarshal the response */
    
    int _camkes_error_403 = 
    
    
    
    
    

    print_unmarshal_outputs(
    _camkes_size_401
    
    
    
    )
;
    if (unlikely(_camkes_error_403 != 0)) {
        /* Error in unmarshalling; bail out. */
        
            return;
        
    }

    
    


    
}
