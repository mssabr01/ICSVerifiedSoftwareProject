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
    static seL4_Word crypto_iface_badge = 0;

    seL4_Word crypto_iface_get_sender_id(void) {
        return crypto_iface_badge;
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





    
    
    

    
    
    





    
    
        extern
        
            void
        
            crypto_iface_sign(
                
    
        
        
    
        
            const char *
        
        text
    

        
            ,
        
    
        
        
    
        
            int
        
        id
    

        
    

                
            );

        
        
    
    
    
    
    
    
    
    

    
    
    
    static unsigned sign_unmarshal_inputs_text(unsigned _camkes_size_186, unsigned _camkes_offset_187,
        
    
        char * * text
    

    ) {

        
        void * _camkes_buffer_base_188 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            
            size_t _camkes_strlen_189 = strnlen(_camkes_buffer_base_188 + _camkes_offset_187, _camkes_size_186 - _camkes_offset_187);
            ERR_IF(_camkes_strlen_189 >= _camkes_size_186 - _camkes_offset_187, crypto_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "crypto",
                .interface = "crypto_iface",
                .description = "truncated message encountered while unmarshalling text in sign",
                .length = _camkes_size_186,
                .current_index = _camkes_offset_187 + _camkes_strlen_189 + 1,
                }), ({
                    return UINT_MAX;
            }));
            * text = strdup(_camkes_buffer_base_188 + _camkes_offset_187);
            ERR_IF(* text == NULL, crypto_iface_error_handler, ((camkes_error_t){
                .type = CE_ALLOCATION_FAILURE,
                .instance = "crypto",
                .interface = "crypto_iface",
                .description = "out of memory while unmarshalling text in sign",
                .alloc_bytes = _camkes_strlen_189 + 1,
                }), ({
                    return UINT_MAX;
            }));
            _camkes_offset_187 += _camkes_strlen_189 + 1;
        

        return _camkes_offset_187;
    }
    
    
    
    static unsigned sign_unmarshal_inputs_id(unsigned _camkes_size_190, unsigned _camkes_offset_191,
        
    
        int * id
    

    ) {

        
        void * _camkes_buffer_base_192 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            ERR_IF(_camkes_offset_191 + sizeof(* id) > _camkes_size_190, crypto_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "crypto",
                .interface = "crypto_iface",
                .description = "truncated message encountered while unmarshalling id in sign",
                .length = _camkes_size_190,
                .current_index = _camkes_offset_191 + sizeof(* id),
                }), ({
                    return UINT_MAX;
            }));
            memcpy(id, _camkes_buffer_base_192 + _camkes_offset_191, sizeof(* id));
            _camkes_offset_191 += sizeof(* id);
        

        return _camkes_offset_191;
    }
    

    static int sign_unmarshal_inputs(
    
    unsigned _camkes_size_193
    
        ,
    
    
    
        
    
        char * * text
    

        
            ,
        
    
        
    
        int * id
    

        
    

    ) {

        
        unsigned _camkes_length_194 UNUSED = 0;

        
        void * _camkes_buffer_base_195 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            /* Step over the method index. */
            _camkes_length_194 += sizeof(uint8_t);
        

        /* Unmarshal input parameters. */
        
            
            _camkes_length_194 = sign_unmarshal_inputs_text(_camkes_size_193, _camkes_length_194,
            
            text
            );
            if (unlikely(_camkes_length_194 == UINT_MAX)) {
            
            return -1;
        }
        
            
            _camkes_length_194 = sign_unmarshal_inputs_id(_camkes_size_193, _camkes_length_194,
            
            id
            );
            if (unlikely(_camkes_length_194 == UINT_MAX)) {
            
                
                    free(* text);
                
            
            return -1;
        }
        

        
            ERR_IF(ROUND_UP_UNSAFE(_camkes_length_194, sizeof(seL4_Word)) != _camkes_size_193, crypto_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "crypto",
                .interface = "crypto_iface",
                .description = "excess trailing bytes after unmarshalling parameters for sign",
                .length = _camkes_size_193,
                .current_index = _camkes_length_194,
                }), ({
                    
                        
                            free(* text);
                        
                    
                        
                    
                    return -1;
            }));
        

        return 0;
    }


        
        
    
    
    
    
    
    
    
    
    
    

    
    
    

    static unsigned sign_marshal_outputs(
    
    
    
    

    
        void
    
    ) {

        
        unsigned _camkes_length_198 = 0;

        

        /* Marshal output parameters. */
        

        assert(_camkes_length_198 <= (seL4_MsgMaxLength * sizeof(seL4_Word)) &&
            "uncaught buffer overflow while marshalling outputs for sign");

        return _camkes_length_198;
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

    
        
        static char * sign_text_to_1
        
        UNUSED;
    
        
        static char * sign_text_to_2
        
        UNUSED;
    
        
        static char * sign_text_to_3
        
        UNUSED;
    
        
        static char * sign_text_to_4
        
        UNUSED;
    

    static char * *
    
    get_sign_text_to(void) UNUSED;
    static char * *
    
    get_sign_text_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & sign_text_to_1;
                    
            
                case 2:
                    
                        return & sign_text_to_2;
                    
            
                case 3:
                    
                        return & sign_text_to_3;
                    
            
                case 4:
                    
                        return & sign_text_to_4;
                    
            
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

    
        
        static int sign_id_to_1
        
        UNUSED;
    
        
        static int sign_id_to_2
        
        UNUSED;
    
        
        static int sign_id_to_3
        
        UNUSED;
    
        
        static int sign_id_to_4
        
        UNUSED;
    

    static int *
    
    get_sign_id_to(void) UNUSED;
    static int *
    
    get_sign_id_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & sign_id_to_1;
                    
            
                case 2:
                    
                        return & sign_id_to_2;
                    
            
                case 3:
                    
                        return & sign_id_to_3;
                    
            
                case 4:
                    
                        return & sign_id_to_4;
                    
            
            default:
                assert(!"invalid thread index");
                abort();
        }
    }

            
        

    
        extern
        
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
    

        
    

                
            );

        
        
    
    
    
    
    
    
    
    

    
    
    
    static unsigned verify_unmarshal_inputs_text(unsigned _camkes_size_199, unsigned _camkes_offset_200,
        
    
        char * * text
    

    ) {

        
        void * _camkes_buffer_base_201 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            
            size_t _camkes_strlen_202 = strnlen(_camkes_buffer_base_201 + _camkes_offset_200, _camkes_size_199 - _camkes_offset_200);
            ERR_IF(_camkes_strlen_202 >= _camkes_size_199 - _camkes_offset_200, crypto_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "crypto",
                .interface = "crypto_iface",
                .description = "truncated message encountered while unmarshalling text in verify",
                .length = _camkes_size_199,
                .current_index = _camkes_offset_200 + _camkes_strlen_202 + 1,
                }), ({
                    return UINT_MAX;
            }));
            * text = strdup(_camkes_buffer_base_201 + _camkes_offset_200);
            ERR_IF(* text == NULL, crypto_iface_error_handler, ((camkes_error_t){
                .type = CE_ALLOCATION_FAILURE,
                .instance = "crypto",
                .interface = "crypto_iface",
                .description = "out of memory while unmarshalling text in verify",
                .alloc_bytes = _camkes_strlen_202 + 1,
                }), ({
                    return UINT_MAX;
            }));
            _camkes_offset_200 += _camkes_strlen_202 + 1;
        

        return _camkes_offset_200;
    }
    
    
    
    static unsigned verify_unmarshal_inputs_id(unsigned _camkes_size_203, unsigned _camkes_offset_204,
        
    
        int * id
    

    ) {

        
        void * _camkes_buffer_base_205 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            ERR_IF(_camkes_offset_204 + sizeof(* id) > _camkes_size_203, crypto_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "crypto",
                .interface = "crypto_iface",
                .description = "truncated message encountered while unmarshalling id in verify",
                .length = _camkes_size_203,
                .current_index = _camkes_offset_204 + sizeof(* id),
                }), ({
                    return UINT_MAX;
            }));
            memcpy(id, _camkes_buffer_base_205 + _camkes_offset_204, sizeof(* id));
            _camkes_offset_204 += sizeof(* id);
        

        return _camkes_offset_204;
    }
    
    
    
    static unsigned verify_unmarshal_inputs_hmac(unsigned _camkes_size_206, unsigned _camkes_offset_207,
        
    
        char * * hmac
    

    ) {

        
        void * _camkes_buffer_base_208 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            
            size_t _camkes_strlen_209 = strnlen(_camkes_buffer_base_208 + _camkes_offset_207, _camkes_size_206 - _camkes_offset_207);
            ERR_IF(_camkes_strlen_209 >= _camkes_size_206 - _camkes_offset_207, crypto_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "crypto",
                .interface = "crypto_iface",
                .description = "truncated message encountered while unmarshalling hmac in verify",
                .length = _camkes_size_206,
                .current_index = _camkes_offset_207 + _camkes_strlen_209 + 1,
                }), ({
                    return UINT_MAX;
            }));
            * hmac = strdup(_camkes_buffer_base_208 + _camkes_offset_207);
            ERR_IF(* hmac == NULL, crypto_iface_error_handler, ((camkes_error_t){
                .type = CE_ALLOCATION_FAILURE,
                .instance = "crypto",
                .interface = "crypto_iface",
                .description = "out of memory while unmarshalling hmac in verify",
                .alloc_bytes = _camkes_strlen_209 + 1,
                }), ({
                    return UINT_MAX;
            }));
            _camkes_offset_207 += _camkes_strlen_209 + 1;
        

        return _camkes_offset_207;
    }
    

    static int verify_unmarshal_inputs(
    
    unsigned _camkes_size_210
    
        ,
    
    
    
        
    
        char * * text
    

        
            ,
        
    
        
    
        int * id
    

        
            ,
        
    
        
    
        char * * hmac
    

        
    

    ) {

        
        unsigned _camkes_length_211 UNUSED = 0;

        
        void * _camkes_buffer_base_212 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            /* Step over the method index. */
            _camkes_length_211 += sizeof(uint8_t);
        

        /* Unmarshal input parameters. */
        
            
            _camkes_length_211 = verify_unmarshal_inputs_text(_camkes_size_210, _camkes_length_211,
            
            text
            );
            if (unlikely(_camkes_length_211 == UINT_MAX)) {
            
            return -1;
        }
        
            
            _camkes_length_211 = verify_unmarshal_inputs_id(_camkes_size_210, _camkes_length_211,
            
            id
            );
            if (unlikely(_camkes_length_211 == UINT_MAX)) {
            
                
                    free(* text);
                
            
            return -1;
        }
        
            
            _camkes_length_211 = verify_unmarshal_inputs_hmac(_camkes_size_210, _camkes_length_211,
            
            hmac
            );
            if (unlikely(_camkes_length_211 == UINT_MAX)) {
            
                
                    free(* text);
                
            
                
            
            return -1;
        }
        

        
            ERR_IF(ROUND_UP_UNSAFE(_camkes_length_211, sizeof(seL4_Word)) != _camkes_size_210, crypto_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "crypto",
                .interface = "crypto_iface",
                .description = "excess trailing bytes after unmarshalling parameters for verify",
                .length = _camkes_size_210,
                .current_index = _camkes_length_211,
                }), ({
                    
                        
                            free(* text);
                        
                    
                        
                    
                        
                            free(* hmac);
                        
                    
                    return -1;
            }));
        

        return 0;
    }


        
        
    
    
    
    
    
    
    
    
    
    

    
    
    

    static unsigned verify_marshal_outputs(
    
    
    
    

    
        void
    
    ) {

        
        unsigned _camkes_length_215 = 0;

        

        /* Marshal output parameters. */
        

        assert(_camkes_length_215 <= (seL4_MsgMaxLength * sizeof(seL4_Word)) &&
            "uncaught buffer overflow while marshalling outputs for verify");

        return _camkes_length_215;
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

    
        
        static char * verify_hmac_to_1
        
        UNUSED;
    
        
        static char * verify_hmac_to_2
        
        UNUSED;
    
        
        static char * verify_hmac_to_3
        
        UNUSED;
    
        
        static char * verify_hmac_to_4
        
        UNUSED;
    

    static char * *
    
    get_verify_hmac_to(void) UNUSED;
    static char * *
    
    get_verify_hmac_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & verify_hmac_to_1;
                    
            
                case 2:
                    
                        return & verify_hmac_to_2;
                    
            
                case 3:
                    
                        return & verify_hmac_to_3;
                    
            
                case 4:
                    
                        return & verify_hmac_to_4;
                    
            
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

    
        
        static uint8_t _camkes_call_tls_var_to_216_1
        
        UNUSED;
    
        
        static uint8_t _camkes_call_tls_var_to_216_2
        
        UNUSED;
    
        
        static uint8_t _camkes_call_tls_var_to_216_3
        
        UNUSED;
    
        
        static uint8_t _camkes_call_tls_var_to_216_4
        
        UNUSED;
    

    static uint8_t *
    
    get__camkes_call_tls_var_to_216(void) UNUSED;
    static uint8_t *
    
    get__camkes_call_tls_var_to_216(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & _camkes_call_tls_var_to_216_1;
                    
            
                case 2:
                    
                        return & _camkes_call_tls_var_to_216_2;
                    
            
                case 3:
                    
                        return & _camkes_call_tls_var_to_216_3;
                    
            
                case 4:
                    
                        return & _camkes_call_tls_var_to_216_4;
                    
            
            default:
                assert(!"invalid thread index");
                abort();
        }
    }

    



    
    
    
        
        
            
                
        
  
  
  static void _camkes__217(void) NO_INLINE UNUSED
    WARNING("typedef char * looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__217(void) {
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

      /* trigger a compile-time warning: */ _camkes__217(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
            
                
        
  
  
  static void _camkes__218(void) NO_INLINE UNUSED
    WARNING("typedef int looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__218(void) {
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

      /* trigger a compile-time warning: */ _camkes__218(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
    
        
        
            
        
            
        
            
        
    







int

    crypto_iface__run(void)

{

    
    
    
    
    
        
        
            
                
        
  
  static char * _camkes__219;
  CryptoIface_sign_text_array_typedef_check(_camkes__219);

    
                
            
        
            
                
        
  
  static int _camkes__220;
  CryptoIface_sign_id_array_typedef_check(_camkes__220);

    
                
            
        
    
        
        
            
        
            
        
            
        
    



    
    unsigned _camkes_size_221 UNUSED;
    
        
    
        
            camkes_get_tls()->cnode_cap = 11;
        
    
    
        
        
            /* This interface has an active thread, just wait for an RPC */
            seL4_MessageInfo_t _camkes_info_222 = seL4_Recv(10, &crypto_iface_badge);
        
        
    _camkes_size_221 =
        
            seL4_MessageInfo_get_length(_camkes_info_222) * sizeof(seL4_Word);
            assert(_camkes_size_221 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    


    

    while (1) {
        
        
            
            
            

            
            
            
                
                uint8_t _camkes_call_223 UNUSED;
                uint8_t * _camkes_call_ptr_224 = TLS_PTR(_camkes_call_tls_var_to_216, _camkes_call_223);
            
            
                ERR_IF(sizeof(* _camkes_call_ptr_224) > _camkes_size_221, crypto_iface_error_handler, ((camkes_error_t){
                    .type = CE_MALFORMED_RPC_PAYLOAD,
                    .instance = "crypto",
                    .interface = "crypto_iface",
                    .description = "truncated message encountered while unmarshalling method index in crypto_iface",
                    .length = _camkes_size_221,
                    .current_index = sizeof(* _camkes_call_ptr_224),
                    }), ({
                        
    

                        
    
    seL4_MessageInfo_t _camkes_info_225 = seL4_Recv(10, &crypto_iface_badge);
    
    _camkes_size_221 =
        
            seL4_MessageInfo_get_length(_camkes_info_225) * sizeof(seL4_Word);
            assert(_camkes_size_221 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    


                        continue;
                }));

                memcpy(_camkes_call_ptr_224, ((void*)&seL4_GetIPCBuffer()->msg[0]), sizeof(* _camkes_call_ptr_224));
            

            switch (* _camkes_call_ptr_224) {
                
                    case 0: { /* sign */
                        
                        

                            
                                char * text UNUSED = NULL;
                                char ** text_ptr = TLS_PTR(sign_text_to, text);
                            
                        

                            
                                int id UNUSED;
                                int * id_ptr = TLS_PTR(sign_id_to, id);
                            
                        

                        /* Unmarshal parameters */
                        
                        
                        int _camkes_error_226 = 
    
    
    
    

    sign_unmarshal_inputs(
    _camkes_size_221
    
        ,
    
    
        
        text_ptr
        
            ,
        
    
        
        id_ptr
        
    
    )
;
                        if (unlikely(_camkes_error_226 != 0)) {
                            /* Error in unmarshalling; return to event loop. */
                            
    

                            
    
    seL4_MessageInfo_t _camkes_info_227 = seL4_Recv(10, &crypto_iface_badge);
    
    _camkes_size_221 =
        
            seL4_MessageInfo_get_length(_camkes_info_227) * sizeof(seL4_Word);
            assert(_camkes_size_221 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    


                            continue;
                        }

                        /* Call the implementation */
                        
                        
                        
                        
                        
                        crypto_iface_sign(
                            
                                
                                
                                    *
                                
                                text_ptr
                                ,
                            
                                
                                
                                    *
                                
                                id_ptr
                                
                            
                        );

                        
    

                        
    


                        /* Marshal the response */
                        
                        
                        unsigned _camkes_length_232 = 
    
    
    
    

    sign_marshal_outputs(
    
    
    )
;

                        
                        
                        
                            
                                free(* text_ptr);
                            
                        
                            
                        

                        /* Check if there was an error during marshalling. We do
                         * this after freeing internal parameter variables to avoid
                         * leaking memory on errors.
                         */
                        if (unlikely(_camkes_length_232 == UINT_MAX)) {
                            
    

                            
    
    seL4_MessageInfo_t _camkes_info_233 = seL4_Recv(10, &crypto_iface_badge);
    
    _camkes_size_221 =
        
            seL4_MessageInfo_get_length(_camkes_info_233) * sizeof(seL4_Word);
            assert(_camkes_size_221 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    


                            continue;
                        }

                        
    
        
        seL4_MessageInfo_t _camkes_info_234 = seL4_MessageInfo_new(0, 0, 0, /* length */
            
                ROUND_UP_UNSAFE(_camkes_length_232, sizeof(seL4_Word)) / sizeof(seL4_Word)
            
        );

        /* Send the response */
        
            
            camkes_tls_t * _camkes__235 UNUSED = camkes_get_tls();
            assert(_camkes__235 != NULL);
            if (_camkes__235->reply_cap_in_tcb) {
                _camkes__235->reply_cap_in_tcb = false;
                _camkes_info_234 = seL4_ReplyRecv(10, _camkes_info_234, &crypto_iface_badge);
            } else {
                camkes_unprotect_reply_cap();
                seL4_Send(12, _camkes_info_234);
                _camkes_info_234 = seL4_Recv(10, &crypto_iface_badge);
            }
        
        
    _camkes_size_221 =
        
            seL4_MessageInfo_get_length(_camkes_info_234) * sizeof(seL4_Word);
            assert(_camkes_size_221 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    



                        break;
                    }
                
                    case 1: { /* verify */
                        
                        

                            
                                char * text UNUSED = NULL;
                                char ** text_ptr = TLS_PTR(verify_text_to, text);
                            
                        

                            
                                int id UNUSED;
                                int * id_ptr = TLS_PTR(verify_id_to, id);
                            
                        

                            
                                char * hmac UNUSED = NULL;
                                char ** hmac_ptr = TLS_PTR(verify_hmac_to, hmac);
                            
                        

                        /* Unmarshal parameters */
                        
                        
                        int _camkes_error_236 = 
    
    
    
    

    verify_unmarshal_inputs(
    _camkes_size_221
    
        ,
    
    
        
        text_ptr
        
            ,
        
    
        
        id_ptr
        
            ,
        
    
        
        hmac_ptr
        
    
    )
;
                        if (unlikely(_camkes_error_236 != 0)) {
                            /* Error in unmarshalling; return to event loop. */
                            
    

                            
    
    seL4_MessageInfo_t _camkes_info_237 = seL4_Recv(10, &crypto_iface_badge);
    
    _camkes_size_221 =
        
            seL4_MessageInfo_get_length(_camkes_info_237) * sizeof(seL4_Word);
            assert(_camkes_size_221 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    


                            continue;
                        }

                        /* Call the implementation */
                        
                        
                        
                        
                        
                        crypto_iface_verify(
                            
                                
                                
                                    *
                                
                                text_ptr
                                ,
                            
                                
                                
                                    *
                                
                                id_ptr
                                ,
                            
                                
                                
                                    *
                                
                                hmac_ptr
                                
                            
                        );

                        
    

                        
    


                        /* Marshal the response */
                        
                        
                        unsigned _camkes_length_242 = 
    
    
    
    

    verify_marshal_outputs(
    
    
    )
;

                        
                        
                        
                            
                                free(* text_ptr);
                            
                        
                            
                        
                            
                                free(* hmac_ptr);
                            
                        

                        /* Check if there was an error during marshalling. We do
                         * this after freeing internal parameter variables to avoid
                         * leaking memory on errors.
                         */
                        if (unlikely(_camkes_length_242 == UINT_MAX)) {
                            
    

                            
    
    seL4_MessageInfo_t _camkes_info_243 = seL4_Recv(10, &crypto_iface_badge);
    
    _camkes_size_221 =
        
            seL4_MessageInfo_get_length(_camkes_info_243) * sizeof(seL4_Word);
            assert(_camkes_size_221 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    


                            continue;
                        }

                        
    
        
        seL4_MessageInfo_t _camkes_info_244 = seL4_MessageInfo_new(0, 0, 0, /* length */
            
                ROUND_UP_UNSAFE(_camkes_length_242, sizeof(seL4_Word)) / sizeof(seL4_Word)
            
        );

        /* Send the response */
        
            
            camkes_tls_t * _camkes__245 UNUSED = camkes_get_tls();
            assert(_camkes__245 != NULL);
            if (_camkes__245->reply_cap_in_tcb) {
                _camkes__245->reply_cap_in_tcb = false;
                _camkes_info_244 = seL4_ReplyRecv(10, _camkes_info_244, &crypto_iface_badge);
            } else {
                camkes_unprotect_reply_cap();
                seL4_Send(12, _camkes_info_244);
                _camkes_info_244 = seL4_Recv(10, &crypto_iface_badge);
            }
        
        
    _camkes_size_221 =
        
            seL4_MessageInfo_get_length(_camkes_info_244) * sizeof(seL4_Word);
            assert(_camkes_size_221 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    



                        break;
                    }
                
                default: {
                    ERR(crypto_iface_error_handler, ((camkes_error_t){
                        .type = CE_INVALID_METHOD_INDEX,
                        .instance = "crypto",
                        .interface = "crypto_iface",
                        .description = "invalid method index received in crypto_iface",
                        .lower_bound = 0,
                        .upper_bound = 2 - 1,
                        .invalid_index = * _camkes_call_ptr_224,
                    }), ({
                        
    

                        
    
    seL4_MessageInfo_t _camkes_info_246 = seL4_Recv(10, &crypto_iface_badge);
    
    _camkes_size_221 =
        
            seL4_MessageInfo_get_length(_camkes_info_246) * sizeof(seL4_Word);
            assert(_camkes_size_221 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(12);
        
    


                        continue;
                    }));
                }
            }
            
        
        
    }

    UNREACHABLE();
}

