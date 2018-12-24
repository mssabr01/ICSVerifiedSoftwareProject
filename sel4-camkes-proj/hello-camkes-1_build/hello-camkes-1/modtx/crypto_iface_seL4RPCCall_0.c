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
    static camkes_error_handler_t crypto_iface_error_handler_fn UNUSED;

    camkes_error_handler_t crypto_iface_register_error_handler(
        camkes_error_handler_t handler) {
        camkes_error_handler_t old = crypto_iface_error_handler_fn;
        crypto_iface_error_handler_fn = handler;
        return old;
    }

    static camkes_error_action_t UNUSED crypto_iface_error_handler(camkes_error_t *error) {
        if (crypto_iface_error_handler_fn == NULL) {
            /* No registered handler; invoke the generic error handler. */
            return camkes_error(error);
        }
        return crypto_iface_error_handler_fn(error);
    }



    
    
    
        
        
            
                
        
  
  
  static void _camkes__52(void) NO_INLINE UNUSED
    WARNING("typedef char * looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__52(void) {
    /* We need something opaque here to prevent the compiler from optimising
     * away an invocation of (and hence the warning attached to) this function.
     * This is also why this function is marked noinline.
     */
    asm volatile ("");
  }
  static void CryptoIface_sign_text_array_typedef_check(char * x UNUSED)
    UNUSED;
  static void CryptoIface_sign_text_array_typedef_check(char * x UNUSED) {
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

      /* trigger a compile-time warning: */ _camkes__52(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
            
                
        
  
  
  static void _camkes__53(void) NO_INLINE UNUSED
    WARNING("typedef int looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__53(void) {
    /* We need something opaque here to prevent the compiler from optimising
     * away an invocation of (and hence the warning attached to) this function.
     * This is also why this function is marked noinline.
     */
    asm volatile ("");
  }
  static void CryptoIface_sign_id_array_typedef_check(int x UNUSED)
    UNUSED;
  static void CryptoIface_sign_id_array_typedef_check(int x UNUSED) {
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

      /* trigger a compile-time warning: */ _camkes__53(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
    
        
        
            
        
            
        
            
        
    



int crypto_iface__run(void) {
    /* This function is never actually executed, but we still emit it for the
     * purpose of type checking RPC parameters.
     */
    UNREACHABLE();

    
    
    
    
    
        
        
            
                
        
  
  static char * _camkes__54;
  CryptoIface_sign_text_array_typedef_check(_camkes__54);

    
                
            
        
            
                
        
  
  static int _camkes__55;
  CryptoIface_sign_id_array_typedef_check(_camkes__55);

    
                
            
        
    
        
        
            
        
            
        
            
        
    


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

    
        
        static int sign_id_from_1
        
        UNUSED;
    
        
        static int sign_id_from_2
        
        UNUSED;
    
        
        static int sign_id_from_3
        
        UNUSED;
    
        
        static int sign_id_from_4
        
        UNUSED;
    

    static int *
    
    get_sign_id_from(void) UNUSED;
    static int *
    
    get_sign_id_from(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & sign_id_from_1;
                    
            
                case 2:
                    
                        return & sign_id_from_2;
                    
            
                case 3:
                    
                        return & sign_id_from_3;
                    
            
                case 4:
                    
                        return & sign_id_from_4;
                    
            
            default:
                assert(!"invalid thread index");
                abort();
        }
    }

            
        
    
    

    
        
        
        static unsigned sign_marshal_inputs_text(unsigned _camkes_offset_56,
            
    
        
            const char *
        
        text
    

        ) {

        
        void * _camkes_buffer_base_57 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                const char * _camkes_ptr_str_60 = text;
            
        

        
            
            size_t _camkes_strlen_62 = strnlen(_camkes_ptr_str_60, (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_56);
            
            
    ERR_IF(_camkes_strlen_62 + 1 > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_56, crypto_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modtx",
        .interface = "crypto_iface",
        .description = "buffer exceeded while marshalling text in sign",
        .current_length = _camkes_offset_56,
        .target_length = _camkes_offset_56 + _camkes_strlen_62 + 1,
        }), ({
            return UINT_MAX;
    }));

            /* If we didn't trigger an error, we now know this strcpy is safe. */
            (void)strcpy(_camkes_buffer_base_57 + _camkes_offset_56, _camkes_ptr_str_60);
            _camkes_offset_56 += _camkes_strlen_62 + 1;
        
        return _camkes_offset_56;
    }
    
        
        
        static unsigned sign_marshal_inputs_id(unsigned _camkes_offset_63,
            
    
        
            int
        
        id
    

        ) {

        
        void * _camkes_buffer_base_64 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                int * _camkes_ptr_65 = TLS_PTR(sign_id_from, id);
                * _camkes_ptr_65 = id;
            
        

        
            
            
    ERR_IF(sizeof(* _camkes_ptr_65) > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_63, crypto_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modtx",
        .interface = "crypto_iface",
        .description = "buffer exceeded while marshalling id in sign",
        .current_length = _camkes_offset_63,
        .target_length = _camkes_offset_63 + sizeof(* _camkes_ptr_65),
        }), ({
            return UINT_MAX;
    }));

            memcpy(_camkes_buffer_base_64 + _camkes_offset_63, _camkes_ptr_65, sizeof(* _camkes_ptr_65));
            _camkes_offset_63 += sizeof(* _camkes_ptr_65);
        
        return _camkes_offset_63;
    }
    

    
        
        static const uint8_t _camkes_method_index_69 = 0;
    

    static unsigned sign_marshal_inputs(
    
    
        
        
    
        
            const char *
        
        text
    

        
            ,
        
    
        
        
    
        
            int
        
        id
    

        
    

    
    ) {

        
        unsigned _camkes_length_70 = 0;

        
        void * _camkes_buffer_base_71 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            /* Marshal the method index. */
            
            
    ERR_IF(sizeof(_camkes_method_index_69) > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_length_70, crypto_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modtx",
        .interface = "crypto_iface",
        .description = "buffer exceeded while marshalling sign in sign",
        .current_length = _camkes_length_70,
        .target_length = _camkes_length_70 + sizeof(_camkes_method_index_69),
        }), ({
            return UINT_MAX;
    }));

            memcpy(_camkes_buffer_base_71, & _camkes_method_index_69, sizeof(_camkes_method_index_69));
            _camkes_length_70 += sizeof(_camkes_method_index_69);
        

        /* Marshal the parameters. */
        
            
            _camkes_length_70 = sign_marshal_inputs_text(_camkes_length_70,
            
            text
            );
            if (unlikely(_camkes_length_70 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_70 = sign_marshal_inputs_id(_camkes_length_70,
            
            id
            );
            if (unlikely(_camkes_length_70 == UINT_MAX)) {
                return UINT_MAX;
            }
        

        assert(_camkes_length_70 <= (seL4_MsgMaxLength * sizeof(seL4_Word)) &&
            "uncaught buffer overflow while marshalling inputs for sign");

        return _camkes_length_70;
    }




    
    
    
    
    
    
    
    
    
    
    

    
    
    

    static int
    sign_unmarshal_outputs(
    
    unsigned _camkes_size_73
    
    
    

    
    

    ) {

        
        unsigned _camkes_length_75 UNUSED = 0;

        
        void * _camkes_buffer_base_76 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        

        /* Unmarshal the parameters. */
        

        
        ERR_IF(ROUND_UP_UNSAFE(_camkes_length_75, sizeof(seL4_Word)) != _camkes_size_73, crypto_iface_error_handler, ((camkes_error_t){
            .type = CE_MALFORMED_RPC_PAYLOAD,
            .instance = "modtx",
            .interface = "crypto_iface",
            .description = "excess trailing bytes after unmarshalling parameters for sign",
            .length = _camkes_size_73,
            .current_index = _camkes_length_75,
            }), ({
                
                
                return -1;
        }));
    

    return 0;
    }






    void

crypto_iface_sign(

    
        
        
    
        
            const char *
        
        text
    

        
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
    
    unsigned _camkes_length_80 = 
    
    
    

    sign_marshal_inputs(
    
        
        text
        
            ,
        
    
        
        id
        
    
    )
;
    if (unlikely(_camkes_length_80 == UINT_MAX)) {
        /* Error in marshalling; bail out. */
        
            return;
        
    }

    
    unsigned _camkes_size_81;
    
    /* Call the endpoint */
    
    seL4_MessageInfo_t _camkes_info_82 = seL4_MessageInfo_new(0, 0, 0,
        
                ROUND_UP_UNSAFE(_camkes_length_80, sizeof(seL4_Word)) / sizeof(seL4_Word)
        
        );
    _camkes_info_82 = seL4_Call(10, _camkes_info_82);

    _camkes_size_81 =
    
        seL4_MessageInfo_get_length(_camkes_info_82) * sizeof(seL4_Word);
        assert(_camkes_size_81 <= seL4_MsgMaxLength * sizeof(seL4_Word));
    


    /* Unmarshal the response */
    
    int _camkes_error_83 = 
    
    
    
    
    

    sign_unmarshal_outputs(
    _camkes_size_81
    
    
    
    )
;
    if (unlikely(_camkes_error_83 != 0)) {
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

            
        
    
        
            
        
    
    

    
        
        
        static unsigned verify_marshal_inputs_text(unsigned _camkes_offset_84,
            
    
        
            const char *
        
        text
    

        ) {

        
        void * _camkes_buffer_base_85 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                const char * _camkes_ptr_str_88 = text;
            
        

        
            
            size_t _camkes_strlen_90 = strnlen(_camkes_ptr_str_88, (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_84);
            
            
    ERR_IF(_camkes_strlen_90 + 1 > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_84, crypto_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modtx",
        .interface = "crypto_iface",
        .description = "buffer exceeded while marshalling text in verify",
        .current_length = _camkes_offset_84,
        .target_length = _camkes_offset_84 + _camkes_strlen_90 + 1,
        }), ({
            return UINT_MAX;
    }));

            /* If we didn't trigger an error, we now know this strcpy is safe. */
            (void)strcpy(_camkes_buffer_base_85 + _camkes_offset_84, _camkes_ptr_str_88);
            _camkes_offset_84 += _camkes_strlen_90 + 1;
        
        return _camkes_offset_84;
    }
    
        
        
        static unsigned verify_marshal_inputs_id(unsigned _camkes_offset_91,
            
    
        
            int
        
        id
    

        ) {

        
        void * _camkes_buffer_base_92 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                int * _camkes_ptr_93 = TLS_PTR(verify_id_from, id);
                * _camkes_ptr_93 = id;
            
        

        
            
            
    ERR_IF(sizeof(* _camkes_ptr_93) > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_91, crypto_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modtx",
        .interface = "crypto_iface",
        .description = "buffer exceeded while marshalling id in verify",
        .current_length = _camkes_offset_91,
        .target_length = _camkes_offset_91 + sizeof(* _camkes_ptr_93),
        }), ({
            return UINT_MAX;
    }));

            memcpy(_camkes_buffer_base_92 + _camkes_offset_91, _camkes_ptr_93, sizeof(* _camkes_ptr_93));
            _camkes_offset_91 += sizeof(* _camkes_ptr_93);
        
        return _camkes_offset_91;
    }
    
        
        
        static unsigned verify_marshal_inputs_hmac(unsigned _camkes_offset_97,
            
    
        
            const char *
        
        hmac
    

        ) {

        
        void * _camkes_buffer_base_98 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        /* Construct parameter pointers. We do this here to consolidate where we
         * are taking the address of local variables. In future, we need to avoid
         * doing this for verification.
         */
        
        
        
        
        
            
                const char * _camkes_ptr_str_101 = hmac;
            
        

        
            
            size_t _camkes_strlen_103 = strnlen(_camkes_ptr_str_101, (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_97);
            
            
    ERR_IF(_camkes_strlen_103 + 1 > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_offset_97, crypto_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modtx",
        .interface = "crypto_iface",
        .description = "buffer exceeded while marshalling hmac in verify",
        .current_length = _camkes_offset_97,
        .target_length = _camkes_offset_97 + _camkes_strlen_103 + 1,
        }), ({
            return UINT_MAX;
    }));

            /* If we didn't trigger an error, we now know this strcpy is safe. */
            (void)strcpy(_camkes_buffer_base_98 + _camkes_offset_97, _camkes_ptr_str_101);
            _camkes_offset_97 += _camkes_strlen_103 + 1;
        
        return _camkes_offset_97;
    }
    

    
        
        static const uint8_t _camkes_method_index_104 = 1;
    

    static unsigned verify_marshal_inputs(
    
    
        
        
    
        
            const char *
        
        text
    

        
            ,
        
    
        
        
    
        
            int
        
        id
    

        
            ,
        
    
        
        
    
        
            const char *
        
        hmac
    

        
    

    
    ) {

        
        unsigned _camkes_length_105 = 0;

        
        void * _camkes_buffer_base_106 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            /* Marshal the method index. */
            
            
    ERR_IF(sizeof(_camkes_method_index_104) > (seL4_MsgMaxLength * sizeof(seL4_Word)) - _camkes_length_105, crypto_iface_error_handler, ((camkes_error_t){
        .type = CE_BUFFER_LENGTH_EXCEEDED,
        .instance = "modtx",
        .interface = "crypto_iface",
        .description = "buffer exceeded while marshalling verify in verify",
        .current_length = _camkes_length_105,
        .target_length = _camkes_length_105 + sizeof(_camkes_method_index_104),
        }), ({
            return UINT_MAX;
    }));

            memcpy(_camkes_buffer_base_106, & _camkes_method_index_104, sizeof(_camkes_method_index_104));
            _camkes_length_105 += sizeof(_camkes_method_index_104);
        

        /* Marshal the parameters. */
        
            
            _camkes_length_105 = verify_marshal_inputs_text(_camkes_length_105,
            
            text
            );
            if (unlikely(_camkes_length_105 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_105 = verify_marshal_inputs_id(_camkes_length_105,
            
            id
            );
            if (unlikely(_camkes_length_105 == UINT_MAX)) {
                return UINT_MAX;
            }
        
            
            _camkes_length_105 = verify_marshal_inputs_hmac(_camkes_length_105,
            
            hmac
            );
            if (unlikely(_camkes_length_105 == UINT_MAX)) {
                return UINT_MAX;
            }
        

        assert(_camkes_length_105 <= (seL4_MsgMaxLength * sizeof(seL4_Word)) &&
            "uncaught buffer overflow while marshalling inputs for verify");

        return _camkes_length_105;
    }




    
    
    
    
    
    
    
    
    
    
    

    
    
    

    static int
    verify_unmarshal_outputs(
    
    unsigned _camkes_size_108
    
    
    

    
    

    ) {

        
        unsigned _camkes_length_110 UNUSED = 0;

        
        void * _camkes_buffer_base_111 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        

        /* Unmarshal the parameters. */
        

        
        ERR_IF(ROUND_UP_UNSAFE(_camkes_length_110, sizeof(seL4_Word)) != _camkes_size_108, crypto_iface_error_handler, ((camkes_error_t){
            .type = CE_MALFORMED_RPC_PAYLOAD,
            .instance = "modtx",
            .interface = "crypto_iface",
            .description = "excess trailing bytes after unmarshalling parameters for verify",
            .length = _camkes_size_108,
            .current_index = _camkes_length_110,
            }), ({
                
                
                return -1;
        }));
    

    return 0;
    }






    void

crypto_iface_verify(

    
        
        
    
        
            const char *
        
        text
    

        
            ,
        
    
        
        
    
        
            int
        
        id
    

        
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
    
    unsigned _camkes_length_115 = 
    
    
    

    verify_marshal_inputs(
    
        
        text
        
            ,
        
    
        
        id
        
            ,
        
    
        
        hmac
        
    
    )
;
    if (unlikely(_camkes_length_115 == UINT_MAX)) {
        /* Error in marshalling; bail out. */
        
            return;
        
    }

    
    unsigned _camkes_size_116;
    
    /* Call the endpoint */
    
    seL4_MessageInfo_t _camkes_info_117 = seL4_MessageInfo_new(0, 0, 0,
        
                ROUND_UP_UNSAFE(_camkes_length_115, sizeof(seL4_Word)) / sizeof(seL4_Word)
        
        );
    _camkes_info_117 = seL4_Call(10, _camkes_info_117);

    _camkes_size_116 =
    
        seL4_MessageInfo_get_length(_camkes_info_117) * sizeof(seL4_Word);
        assert(_camkes_size_116 <= seL4_MsgMaxLength * sizeof(seL4_Word));
    


    /* Unmarshal the response */
    
    int _camkes_error_118 = 
    
    
    
    
    

    verify_unmarshal_outputs(
    _camkes_size_116
    
    
    
    )
;
    if (unlikely(_camkes_error_118 != 0)) {
        /* Error in unmarshalling; bail out. */
        
            return;
        
    }

    
    


    
}
