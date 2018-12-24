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



    
    
    
        
        
            
                
        
  
  
  static void _camkes__247(void) NO_INLINE UNUSED
    WARNING("typedef char * looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__247(void) {
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

      /* trigger a compile-time warning: */ _camkes__247(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
            
        
            
                
        
  
  
  static void _camkes__248(void) NO_INLINE UNUSED
    WARNING("typedef int looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__248(void) {
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

      /* trigger a compile-time warning: */ _camkes__248(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
    



int modchk_iface__run(void) {
    /* This function is never actually executed, but we still emit it for the
     * purpose of type checking RPC parameters.
     */
    UNREACHABLE();

    
    
    
    
    
        
        
            
                
        
  
  static char * _camkes__249;
  ModchkIface_verify_text_array_typedef_check(_camkes__249);

    
                
            
        
            
        
            
                
        
  
  static int _camkes__250;
  ModchkIface_verify_id_array_typedef_check(_camkes__250);

    
                
            
        
    


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

    
        
        static int verify_id_from_1
        
        UNUSED;
    
        
        static int verify_id_from_2
        
        UNUSED;
    
        
        static int verify_id_from_3
        
        UNUSED;
    
        
        static int verify_id_from_4
        
        UNUSED;
    

    static int *
    
    get_verify_id_from(void) UNUSED;
    static int *
    
    get_verify_id_from(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & verify_id_from_1;
                    
            
                case 2:
                    
                        return & verify_id_from_2;
                    
            
                case 3:
                    
                        return & verify_id_from_3;
                    
            
                case 4:
                    
                        return & verify_id_from_4;
                    
            
            default:
                assert(!"invalid thread index");
                abort();
        }
    }

            
        
    
    

    
        
        
        static unsigned verify_marshal_inputs_text(unsigned _camkes_offset_251,
            
    
        
            const char *
        
        text
    

        ) {

        
        void * _camkes_buffer_base_252 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                const char * _camkes_ptr_str_255 = text;
            
        

        
            
            size_t _camkes_strlen_257 = strnlen(_camkes_ptr_str_255, (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_251);
            
            
    ERR_IF(_camkes_strlen_257 + 1 > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_251, modchk_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modtx",
        .interface = "modchk_iface",
        .description = "buffer exceeded while marshalling text in verify",
        .current_length = _camkes_offset_251,
        .target_length = _camkes_offset_251 + _camkes_strlen_257 + 1,
        }), ({
            return UINT_MAX;
    }));

            /* If we didn't trigger an error, we now know this strcpy is safe. */
            (void)strcpy(_camkes_buffer_base_252 + _camkes_offset_251, _camkes_ptr_str_255);
            _camkes_offset_251 += _camkes_strlen_257 + 1;
        
        return _camkes_offset_251;
    }
    
        
        
        static unsigned verify_marshal_inputs_source(unsigned _camkes_offset_258,
            
    
        
            const char *
        
        source
    

        ) {

        
        void * _camkes_buffer_base_259 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                const char * _camkes_ptr_str_262 = source;
            
        

        
            
            size_t _camkes_strlen_264 = strnlen(_camkes_ptr_str_262, (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_258);
            
            
    ERR_IF(_camkes_strlen_264 + 1 > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_258, modchk_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modtx",
        .interface = "modchk_iface",
        .description = "buffer exceeded while marshalling source in verify",
        .current_length = _camkes_offset_258,
        .target_length = _camkes_offset_258 + _camkes_strlen_264 + 1,
        }), ({
            return UINT_MAX;
    }));

            /* If we didn't trigger an error, we now know this strcpy is safe. */
            (void)strcpy(_camkes_buffer_base_259 + _camkes_offset_258, _camkes_ptr_str_262);
            _camkes_offset_258 += _camkes_strlen_264 + 1;
        
        return _camkes_offset_258;
    }
    
        
        
        static unsigned verify_marshal_inputs_id(unsigned _camkes_offset_265,
            
    
        
            int
        
        id
    

        ) {

        
        void * _camkes_buffer_base_266 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                int * _camkes_ptr_267 = TLS_PTR(verify_id_from, id);
                * _camkes_ptr_267 = id;
            
        

        
            
            
    ERR_IF(sizeof(* _camkes_ptr_267) > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_265, modchk_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modtx",
        .interface = "modchk_iface",
        .description = "buffer exceeded while marshalling id in verify",
        .current_length = _camkes_offset_265,
        .target_length = _camkes_offset_265 + sizeof(* _camkes_ptr_267),
        }), ({
            return UINT_MAX;
    }));

            memcpy(_camkes_buffer_base_266 + _camkes_offset_265, _camkes_ptr_267, sizeof(* _camkes_ptr_267));
            _camkes_offset_265 += sizeof(* _camkes_ptr_267);
        
        return _camkes_offset_265;
    }
    

    

    static unsigned verify_marshal_inputs(
    
    
        
        
    
        
            const char *
        
        text
    

        
            ,
        
    
        
        
    
        
            const char *
        
        source
    

        
            ,
        
    
        
        
    
        
            int
        
        id
    

        
    

    
    ) {

        
        unsigned _camkes_length_271 = 0;

        
        void * _camkes_buffer_base_272 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        

        /* Marshal the parameters. */
        
            
            _camkes_length_271 = verify_marshal_inputs_text(_camkes_length_271,
            
            text
            );
            if (unlikely(_camkes_length_271 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_271 = verify_marshal_inputs_source(_camkes_length_271,
            
            source
            );
            if (unlikely(_camkes_length_271 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_271 = verify_marshal_inputs_id(_camkes_length_271,
            
            id
            );
            if (unlikely(_camkes_length_271 == UINT_MAX)) {
                return UINT_MAX;
            }
        

        assert(_camkes_length_271 <= (seL4_MsgMaxLength * sizeof(seL4_Word)) &&
            "uncaught buffer overflow while marshalling inputs for verify");

        return _camkes_length_271;
    }




    
    
    
    
    
    
    
    
    
    
    

    
    
    

    static int
    verify_unmarshal_outputs(
    
    unsigned _camkes_size_274
    
    
    

    
    

    ) {

        
        unsigned _camkes_length_276 UNUSED = 0;

        
        void * _camkes_buffer_base_277 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        

        /* Unmarshal the parameters. */
        

        
        ERR_IF(ROUND_UP_UNSAFE(_camkes_length_276, sizeof(seL4_Word)) != _camkes_size_274, modchk_iface_error_handler, ((camkes_error_t){
            .type = CE_MALFORMED_RPC_PAYLOAD,
            .instance = "modtx",
            .interface = "modchk_iface",
            .description = "excess trailing bytes after unmarshalling parameters for verify",
            .length = _camkes_size_274,
            .current_index = _camkes_length_276,
            }), ({
                
                
                return -1;
        }));
    

    return 0;
    }






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
    

        
    

) {

    

    
    /* Save any pending reply cap as we'll eventually call seL4_Call which
     * could overwrite it. Note that we do this here before marshalling
     * parameters to ensure we don't inadvertently overwrite any marshalled
     * data with this call.
     */
    
        camkes_protect_reply_cap();
    
    


    
    
    

    /* Marshal all the parameters */
    
    unsigned _camkes_length_281 = 
    
    
    

    verify_marshal_inputs(
    
        
        text
        
            ,
        
    
        
        source
        
            ,
        
    
        
        id
        
    
    )
;
    if (unlikely(_camkes_length_281 == UINT_MAX)) {
        /* Error in marshalling; bail out. */
        
            return;
        
    }

    
    unsigned _camkes_size_282;
    
    /* Call the endpoint */
    
    seL4_MessageInfo_t _camkes_info_283 = seL4_MessageInfo_new(0, 0, 0,
        
                ROUND_UP_UNSAFE(_camkes_length_281, sizeof(seL4_Word)) / sizeof(seL4_Word)
        
        );
    _camkes_info_283 = seL4_Call(11, _camkes_info_283);

    _camkes_size_282 =
    
        seL4_MessageInfo_get_length(_camkes_info_283) * sizeof(seL4_Word);
        assert(_camkes_size_282 <= seL4_MsgMaxLength * sizeof(seL4_Word));
    


    /* Unmarshal the response */
    
    int _camkes_error_284 = 
    
    
    
    
    

    verify_unmarshal_outputs(
    _camkes_size_282
    
    
    
    )
;
    if (unlikely(_camkes_error_284 != 0)) {
        /* Error in unmarshalling; bail out. */
        
            return;
        
    }

    
    


    
}
