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
    static seL4_Word signtx_iface_badge = 0;

    seL4_Word signtx_iface_get_sender_id(void) {
        return signtx_iface_badge;
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





    
    
    

    
    
    





    
    
        extern
        
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
    

        
    

                
            );

        
        
    
    
    
    
    
    
    
    

    
    
    
    static unsigned print_sign_unmarshal_inputs_text(unsigned _camkes_size_674, unsigned _camkes_offset_675,
        
    
        char * * text
    

    ) {

        
        void * _camkes_buffer_base_676 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            
            size_t _camkes_strlen_677 = strnlen(_camkes_buffer_base_676 + _camkes_offset_675, _camkes_size_674 - _camkes_offset_675);
            ERR_IF(_camkes_strlen_677 >= _camkes_size_674 - _camkes_offset_675, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "truncated message encountered while unmarshalling text in print_sign",
                .length = _camkes_size_674,
                .current_index = _camkes_offset_675 + _camkes_strlen_677 + 1,
                }), ({
                    return UINT_MAX;
            }));
            * text = strdup(_camkes_buffer_base_676 + _camkes_offset_675);
            ERR_IF(* text == NULL, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_ALLOCATION_FAILURE,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "out of memory while unmarshalling text in print_sign",
                .alloc_bytes = _camkes_strlen_677 + 1,
                }), ({
                    return UINT_MAX;
            }));
            _camkes_offset_675 += _camkes_strlen_677 + 1;
        

        return _camkes_offset_675;
    }
    
    
    
    static unsigned print_sign_unmarshal_inputs_source(unsigned _camkes_size_678, unsigned _camkes_offset_679,
        
    
        char * * source
    

    ) {

        
        void * _camkes_buffer_base_680 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            
            size_t _camkes_strlen_681 = strnlen(_camkes_buffer_base_680 + _camkes_offset_679, _camkes_size_678 - _camkes_offset_679);
            ERR_IF(_camkes_strlen_681 >= _camkes_size_678 - _camkes_offset_679, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "truncated message encountered while unmarshalling source in print_sign",
                .length = _camkes_size_678,
                .current_index = _camkes_offset_679 + _camkes_strlen_681 + 1,
                }), ({
                    return UINT_MAX;
            }));
            * source = strdup(_camkes_buffer_base_680 + _camkes_offset_679);
            ERR_IF(* source == NULL, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_ALLOCATION_FAILURE,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "out of memory while unmarshalling source in print_sign",
                .alloc_bytes = _camkes_strlen_681 + 1,
                }), ({
                    return UINT_MAX;
            }));
            _camkes_offset_679 += _camkes_strlen_681 + 1;
        

        return _camkes_offset_679;
    }
    
    
    
    static unsigned print_sign_unmarshal_inputs_id(unsigned _camkes_size_682, unsigned _camkes_offset_683,
        
    
        int * id
    

    ) {

        
        void * _camkes_buffer_base_684 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            ERR_IF(_camkes_offset_683 + sizeof(* id) > _camkes_size_682, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "truncated message encountered while unmarshalling id in print_sign",
                .length = _camkes_size_682,
                .current_index = _camkes_offset_683 + sizeof(* id),
                }), ({
                    return UINT_MAX;
            }));
            memcpy(id, _camkes_buffer_base_684 + _camkes_offset_683, sizeof(* id));
            _camkes_offset_683 += sizeof(* id);
        

        return _camkes_offset_683;
    }
    
    
    
    static unsigned print_sign_unmarshal_inputs_isValid(unsigned _camkes_size_685, unsigned _camkes_offset_686,
        
    
        int * isValid
    

    ) {

        
        void * _camkes_buffer_base_687 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            ERR_IF(_camkes_offset_686 + sizeof(* isValid) > _camkes_size_685, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "truncated message encountered while unmarshalling isValid in print_sign",
                .length = _camkes_size_685,
                .current_index = _camkes_offset_686 + sizeof(* isValid),
                }), ({
                    return UINT_MAX;
            }));
            memcpy(isValid, _camkes_buffer_base_687 + _camkes_offset_686, sizeof(* isValid));
            _camkes_offset_686 += sizeof(* isValid);
        

        return _camkes_offset_686;
    }
    
    
    
    static unsigned print_sign_unmarshal_inputs_hmac(unsigned _camkes_size_688, unsigned _camkes_offset_689,
        
    
        char * * hmac
    

    ) {

        
        void * _camkes_buffer_base_690 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            
            size_t _camkes_strlen_691 = strnlen(_camkes_buffer_base_690 + _camkes_offset_689, _camkes_size_688 - _camkes_offset_689);
            ERR_IF(_camkes_strlen_691 >= _camkes_size_688 - _camkes_offset_689, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "truncated message encountered while unmarshalling hmac in print_sign",
                .length = _camkes_size_688,
                .current_index = _camkes_offset_689 + _camkes_strlen_691 + 1,
                }), ({
                    return UINT_MAX;
            }));
            * hmac = strdup(_camkes_buffer_base_690 + _camkes_offset_689);
            ERR_IF(* hmac == NULL, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_ALLOCATION_FAILURE,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "out of memory while unmarshalling hmac in print_sign",
                .alloc_bytes = _camkes_strlen_691 + 1,
                }), ({
                    return UINT_MAX;
            }));
            _camkes_offset_689 += _camkes_strlen_691 + 1;
        

        return _camkes_offset_689;
    }
    

    static int print_sign_unmarshal_inputs(
    
    unsigned _camkes_size_692
    
        ,
    
    
    
        
    
        char * * text
    

        
            ,
        
    
        
    
        char * * source
    

        
            ,
        
    
        
    
        int * id
    

        
            ,
        
    
        
    
        int * isValid
    

        
            ,
        
    
        
    
        char * * hmac
    

        
    

    ) {

        
        unsigned _camkes_length_693 UNUSED = 0;

        
        void * _camkes_buffer_base_694 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            /* Step over the method index. */
            _camkes_length_693 += sizeof(uint8_t);
        

        /* Unmarshal input parameters. */
        
            
            _camkes_length_693 = print_sign_unmarshal_inputs_text(_camkes_size_692, _camkes_length_693,
            
            text
            );
            if (unlikely(_camkes_length_693 == UINT_MAX)) {
            
            return -1;
        }
        
            
            _camkes_length_693 = print_sign_unmarshal_inputs_source(_camkes_size_692, _camkes_length_693,
            
            source
            );
            if (unlikely(_camkes_length_693 == UINT_MAX)) {
            
                
                    free(* text);
                
            
            return -1;
        }
        
            
            _camkes_length_693 = print_sign_unmarshal_inputs_id(_camkes_size_692, _camkes_length_693,
            
            id
            );
            if (unlikely(_camkes_length_693 == UINT_MAX)) {
            
                
                    free(* text);
                
            
                
                    free(* source);
                
            
            return -1;
        }
        
            
            _camkes_length_693 = print_sign_unmarshal_inputs_isValid(_camkes_size_692, _camkes_length_693,
            
            isValid
            );
            if (unlikely(_camkes_length_693 == UINT_MAX)) {
            
                
                    free(* text);
                
            
                
                    free(* source);
                
            
                
            
            return -1;
        }
        
            
            _camkes_length_693 = print_sign_unmarshal_inputs_hmac(_camkes_size_692, _camkes_length_693,
            
            hmac
            );
            if (unlikely(_camkes_length_693 == UINT_MAX)) {
            
                
                    free(* text);
                
            
                
                    free(* source);
                
            
                
            
                
            
            return -1;
        }
        

        
            ERR_IF(ROUND_UP_UNSAFE(_camkes_length_693, sizeof(seL4_Word)) != _camkes_size_692, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "excess trailing bytes after unmarshalling parameters for print_sign",
                .length = _camkes_size_692,
                .current_index = _camkes_length_693,
                }), ({
                    
                        
                            free(* text);
                        
                    
                        
                            free(* source);
                        
                    
                        
                    
                        
                    
                        
                            free(* hmac);
                        
                    
                    return -1;
            }));
        

        return 0;
    }


        
        
    
    
    
    
    
    
    
    
    
    

    
    
    

    static unsigned print_sign_marshal_outputs(
    
    
    
    

    
        void
    
    ) {

        
        unsigned _camkes_length_697 = 0;

        

        /* Marshal output parameters. */
        

        assert(_camkes_length_697 <= (seL4_MsgMaxLength * sizeof(seL4_Word)) &&
            "uncaught buffer overflow while marshalling outputs for print_sign");

        return _camkes_length_697;
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

    
        
        static char * print_sign_text_to_1
        
        UNUSED;
    
        
        static char * print_sign_text_to_2
        
        UNUSED;
    
        
        static char * print_sign_text_to_3
        
        UNUSED;
    
        
        static char * print_sign_text_to_4
        
        UNUSED;
    

    static char * *
    
    get_print_sign_text_to(void) UNUSED;
    static char * *
    
    get_print_sign_text_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_sign_text_to_1;
                    
            
                case 2:
                    
                        return & print_sign_text_to_2;
                    
            
                case 3:
                    
                        return & print_sign_text_to_3;
                    
            
                case 4:
                    
                        return & print_sign_text_to_4;
                    
            
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

    
        
        static char * print_sign_source_to_1
        
        UNUSED;
    
        
        static char * print_sign_source_to_2
        
        UNUSED;
    
        
        static char * print_sign_source_to_3
        
        UNUSED;
    
        
        static char * print_sign_source_to_4
        
        UNUSED;
    

    static char * *
    
    get_print_sign_source_to(void) UNUSED;
    static char * *
    
    get_print_sign_source_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_sign_source_to_1;
                    
            
                case 2:
                    
                        return & print_sign_source_to_2;
                    
            
                case 3:
                    
                        return & print_sign_source_to_3;
                    
            
                case 4:
                    
                        return & print_sign_source_to_4;
                    
            
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

    
        
        static int print_sign_id_to_1
        
        UNUSED;
    
        
        static int print_sign_id_to_2
        
        UNUSED;
    
        
        static int print_sign_id_to_3
        
        UNUSED;
    
        
        static int print_sign_id_to_4
        
        UNUSED;
    

    static int *
    
    get_print_sign_id_to(void) UNUSED;
    static int *
    
    get_print_sign_id_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_sign_id_to_1;
                    
            
                case 2:
                    
                        return & print_sign_id_to_2;
                    
            
                case 3:
                    
                        return & print_sign_id_to_3;
                    
            
                case 4:
                    
                        return & print_sign_id_to_4;
                    
            
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

    
        
        static int print_sign_isValid_to_1
        
        UNUSED;
    
        
        static int print_sign_isValid_to_2
        
        UNUSED;
    
        
        static int print_sign_isValid_to_3
        
        UNUSED;
    
        
        static int print_sign_isValid_to_4
        
        UNUSED;
    

    static int *
    
    get_print_sign_isValid_to(void) UNUSED;
    static int *
    
    get_print_sign_isValid_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_sign_isValid_to_1;
                    
            
                case 2:
                    
                        return & print_sign_isValid_to_2;
                    
            
                case 3:
                    
                        return & print_sign_isValid_to_3;
                    
            
                case 4:
                    
                        return & print_sign_isValid_to_4;
                    
            
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

    
        
        static char * print_sign_hmac_to_1
        
        UNUSED;
    
        
        static char * print_sign_hmac_to_2
        
        UNUSED;
    
        
        static char * print_sign_hmac_to_3
        
        UNUSED;
    
        
        static char * print_sign_hmac_to_4
        
        UNUSED;
    

    static char * *
    
    get_print_sign_hmac_to(void) UNUSED;
    static char * *
    
    get_print_sign_hmac_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_sign_hmac_to_1;
                    
            
                case 2:
                    
                        return & print_sign_hmac_to_2;
                    
            
                case 3:
                    
                        return & print_sign_hmac_to_3;
                    
            
                case 4:
                    
                        return & print_sign_hmac_to_4;
                    
            
            default:
                assert(!"invalid thread index");
                abort();
        }
    }

            
        

    
        extern
        
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
    

        
    

                
            );

        
        
    
    
    
    
    
    
    
    

    
    
    
    static unsigned print_mod_unmarshal_inputs_text(unsigned _camkes_size_698, unsigned _camkes_offset_699,
        
    
        char * * text
    

    ) {

        
        void * _camkes_buffer_base_700 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            
            size_t _camkes_strlen_701 = strnlen(_camkes_buffer_base_700 + _camkes_offset_699, _camkes_size_698 - _camkes_offset_699);
            ERR_IF(_camkes_strlen_701 >= _camkes_size_698 - _camkes_offset_699, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "truncated message encountered while unmarshalling text in print_mod",
                .length = _camkes_size_698,
                .current_index = _camkes_offset_699 + _camkes_strlen_701 + 1,
                }), ({
                    return UINT_MAX;
            }));
            * text = strdup(_camkes_buffer_base_700 + _camkes_offset_699);
            ERR_IF(* text == NULL, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_ALLOCATION_FAILURE,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "out of memory while unmarshalling text in print_mod",
                .alloc_bytes = _camkes_strlen_701 + 1,
                }), ({
                    return UINT_MAX;
            }));
            _camkes_offset_699 += _camkes_strlen_701 + 1;
        

        return _camkes_offset_699;
    }
    
    
    
    static unsigned print_mod_unmarshal_inputs_source(unsigned _camkes_size_702, unsigned _camkes_offset_703,
        
    
        char * * source
    

    ) {

        
        void * _camkes_buffer_base_704 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            
            size_t _camkes_strlen_705 = strnlen(_camkes_buffer_base_704 + _camkes_offset_703, _camkes_size_702 - _camkes_offset_703);
            ERR_IF(_camkes_strlen_705 >= _camkes_size_702 - _camkes_offset_703, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "truncated message encountered while unmarshalling source in print_mod",
                .length = _camkes_size_702,
                .current_index = _camkes_offset_703 + _camkes_strlen_705 + 1,
                }), ({
                    return UINT_MAX;
            }));
            * source = strdup(_camkes_buffer_base_704 + _camkes_offset_703);
            ERR_IF(* source == NULL, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_ALLOCATION_FAILURE,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "out of memory while unmarshalling source in print_mod",
                .alloc_bytes = _camkes_strlen_705 + 1,
                }), ({
                    return UINT_MAX;
            }));
            _camkes_offset_703 += _camkes_strlen_705 + 1;
        

        return _camkes_offset_703;
    }
    
    
    
    static unsigned print_mod_unmarshal_inputs_id(unsigned _camkes_size_706, unsigned _camkes_offset_707,
        
    
        int * id
    

    ) {

        
        void * _camkes_buffer_base_708 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            ERR_IF(_camkes_offset_707 + sizeof(* id) > _camkes_size_706, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "truncated message encountered while unmarshalling id in print_mod",
                .length = _camkes_size_706,
                .current_index = _camkes_offset_707 + sizeof(* id),
                }), ({
                    return UINT_MAX;
            }));
            memcpy(id, _camkes_buffer_base_708 + _camkes_offset_707, sizeof(* id));
            _camkes_offset_707 += sizeof(* id);
        

        return _camkes_offset_707;
    }
    
    
    
    static unsigned print_mod_unmarshal_inputs_isValid(unsigned _camkes_size_709, unsigned _camkes_offset_710,
        
    
        int * isValid
    

    ) {

        
        void * _camkes_buffer_base_711 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            ERR_IF(_camkes_offset_710 + sizeof(* isValid) > _camkes_size_709, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "truncated message encountered while unmarshalling isValid in print_mod",
                .length = _camkes_size_709,
                .current_index = _camkes_offset_710 + sizeof(* isValid),
                }), ({
                    return UINT_MAX;
            }));
            memcpy(isValid, _camkes_buffer_base_711 + _camkes_offset_710, sizeof(* isValid));
            _camkes_offset_710 += sizeof(* isValid);
        

        return _camkes_offset_710;
    }
    

    static int print_mod_unmarshal_inputs(
    
    unsigned _camkes_size_712
    
        ,
    
    
    
        
    
        char * * text
    

        
            ,
        
    
        
    
        char * * source
    

        
            ,
        
    
        
    
        int * id
    

        
            ,
        
    
        
    
        int * isValid
    

        
    

    ) {

        
        unsigned _camkes_length_713 UNUSED = 0;

        
        void * _camkes_buffer_base_714 UNUSED = (void*)(((void*)&seL4_GetIPCBuffer()->msg[0]));

        
            /* Step over the method index. */
            _camkes_length_713 += sizeof(uint8_t);
        

        /* Unmarshal input parameters. */
        
            
            _camkes_length_713 = print_mod_unmarshal_inputs_text(_camkes_size_712, _camkes_length_713,
            
            text
            );
            if (unlikely(_camkes_length_713 == UINT_MAX)) {
            
            return -1;
        }
        
            
            _camkes_length_713 = print_mod_unmarshal_inputs_source(_camkes_size_712, _camkes_length_713,
            
            source
            );
            if (unlikely(_camkes_length_713 == UINT_MAX)) {
            
                
                    free(* text);
                
            
            return -1;
        }
        
            
            _camkes_length_713 = print_mod_unmarshal_inputs_id(_camkes_size_712, _camkes_length_713,
            
            id
            );
            if (unlikely(_camkes_length_713 == UINT_MAX)) {
            
                
                    free(* text);
                
            
                
                    free(* source);
                
            
            return -1;
        }
        
            
            _camkes_length_713 = print_mod_unmarshal_inputs_isValid(_camkes_size_712, _camkes_length_713,
            
            isValid
            );
            if (unlikely(_camkes_length_713 == UINT_MAX)) {
            
                
                    free(* text);
                
            
                
                    free(* source);
                
            
                
            
            return -1;
        }
        

        
            ERR_IF(ROUND_UP_UNSAFE(_camkes_length_713, sizeof(seL4_Word)) != _camkes_size_712, signtx_iface_error_handler, ((camkes_error_t){
                .type = CE_MALFORMED_RPC_PAYLOAD,
                .instance = "signtx",
                .interface = "signtx_iface",
                .description = "excess trailing bytes after unmarshalling parameters for print_mod",
                .length = _camkes_size_712,
                .current_index = _camkes_length_713,
                }), ({
                    
                        
                            free(* text);
                        
                    
                        
                            free(* source);
                        
                    
                        
                    
                        
                    
                    return -1;
            }));
        

        return 0;
    }


        
        
    
    
    
    
    
    
    
    
    
    

    
    
    

    static unsigned print_mod_marshal_outputs(
    
    
    
    

    
        void
    
    ) {

        
        unsigned _camkes_length_717 = 0;

        

        /* Marshal output parameters. */
        

        assert(_camkes_length_717 <= (seL4_MsgMaxLength * sizeof(seL4_Word)) &&
            "uncaught buffer overflow while marshalling outputs for print_mod");

        return _camkes_length_717;
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

    
        
        static char * print_mod_text_to_1
        
        UNUSED;
    
        
        static char * print_mod_text_to_2
        
        UNUSED;
    
        
        static char * print_mod_text_to_3
        
        UNUSED;
    
        
        static char * print_mod_text_to_4
        
        UNUSED;
    

    static char * *
    
    get_print_mod_text_to(void) UNUSED;
    static char * *
    
    get_print_mod_text_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_mod_text_to_1;
                    
            
                case 2:
                    
                        return & print_mod_text_to_2;
                    
            
                case 3:
                    
                        return & print_mod_text_to_3;
                    
            
                case 4:
                    
                        return & print_mod_text_to_4;
                    
            
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

    
        
        static char * print_mod_source_to_1
        
        UNUSED;
    
        
        static char * print_mod_source_to_2
        
        UNUSED;
    
        
        static char * print_mod_source_to_3
        
        UNUSED;
    
        
        static char * print_mod_source_to_4
        
        UNUSED;
    

    static char * *
    
    get_print_mod_source_to(void) UNUSED;
    static char * *
    
    get_print_mod_source_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_mod_source_to_1;
                    
            
                case 2:
                    
                        return & print_mod_source_to_2;
                    
            
                case 3:
                    
                        return & print_mod_source_to_3;
                    
            
                case 4:
                    
                        return & print_mod_source_to_4;
                    
            
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

    
        
        static int print_mod_id_to_1
        
        UNUSED;
    
        
        static int print_mod_id_to_2
        
        UNUSED;
    
        
        static int print_mod_id_to_3
        
        UNUSED;
    
        
        static int print_mod_id_to_4
        
        UNUSED;
    

    static int *
    
    get_print_mod_id_to(void) UNUSED;
    static int *
    
    get_print_mod_id_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_mod_id_to_1;
                    
            
                case 2:
                    
                        return & print_mod_id_to_2;
                    
            
                case 3:
                    
                        return & print_mod_id_to_3;
                    
            
                case 4:
                    
                        return & print_mod_id_to_4;
                    
            
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

    
        
        static int print_mod_isValid_to_1
        
        UNUSED;
    
        
        static int print_mod_isValid_to_2
        
        UNUSED;
    
        
        static int print_mod_isValid_to_3
        
        UNUSED;
    
        
        static int print_mod_isValid_to_4
        
        UNUSED;
    

    static int *
    
    get_print_mod_isValid_to(void) UNUSED;
    static int *
    
    get_print_mod_isValid_to(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & print_mod_isValid_to_1;
                    
            
                case 2:
                    
                        return & print_mod_isValid_to_2;
                    
            
                case 3:
                    
                        return & print_mod_isValid_to_3;
                    
            
                case 4:
                    
                        return & print_mod_isValid_to_4;
                    
            
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

    
        
        static uint8_t _camkes_call_tls_var_to_718_1
        
        UNUSED;
    
        
        static uint8_t _camkes_call_tls_var_to_718_2
        
        UNUSED;
    
        
        static uint8_t _camkes_call_tls_var_to_718_3
        
        UNUSED;
    
        
        static uint8_t _camkes_call_tls_var_to_718_4
        
        UNUSED;
    

    static uint8_t *
    
    get__camkes_call_tls_var_to_718(void) UNUSED;
    static uint8_t *
    
    get__camkes_call_tls_var_to_718(void) {
        switch (camkes_get_tls()->thread_index) {
            
                case 1:
                    
                        return & _camkes_call_tls_var_to_718_1;
                    
            
                case 2:
                    
                        return & _camkes_call_tls_var_to_718_2;
                    
            
                case 3:
                    
                        return & _camkes_call_tls_var_to_718_3;
                    
            
                case 4:
                    
                        return & _camkes_call_tls_var_to_718_4;
                    
            
            default:
                assert(!"invalid thread index");
                abort();
        }
    }

    



    
    
    
        
        
            
                
        
  
  
  static void _camkes__719(void) NO_INLINE UNUSED
    WARNING("typedef char * looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__719(void) {
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

      /* trigger a compile-time warning: */ _camkes__719(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
            
        
            
                
        
  
  
  static void _camkes__720(void) NO_INLINE UNUSED
    WARNING("typedef int looks like an array (unsupported) and should be wrapped in a struct");
  static void _camkes__720(void) {
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

      /* trigger a compile-time warning: */ _camkes__720(),
      /* do nothing: */ (void)0);
  }

    
                
            
        
            
        
            
        
    
        
        
            
        
            
        
            
        
            
        
    







int

    signtx_iface__run(void)

{

    
    
    
    
    
        
        
            
                
        
  
  static char * _camkes__721;
  SigntxIface_print_sign_text_array_typedef_check(_camkes__721);

    
                
            
        
            
        
            
                
        
  
  static int _camkes__722;
  SigntxIface_print_sign_id_array_typedef_check(_camkes__722);

    
                
            
        
            
        
            
        
    
        
        
            
        
            
        
            
        
            
        
    



    
    unsigned _camkes_size_723 UNUSED;
    
        
    
        
            camkes_get_tls()->cnode_cap = 13;
        
    
    
        
        
            /* This interface has an active thread, just wait for an RPC */
            seL4_MessageInfo_t _camkes_info_724 = seL4_Recv(12, &signtx_iface_badge);
        
        
    _camkes_size_723 =
        
            seL4_MessageInfo_get_length(_camkes_info_724) * sizeof(seL4_Word);
            assert(_camkes_size_723 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    


    

    while (1) {
        
        
            
            
            

            
            
            
                
                uint8_t _camkes_call_725 UNUSED;
                uint8_t * _camkes_call_ptr_726 = TLS_PTR(_camkes_call_tls_var_to_718, _camkes_call_725);
            
            
                ERR_IF(sizeof(* _camkes_call_ptr_726) > _camkes_size_723, signtx_iface_error_handler, ((camkes_error_t){
                    .type = CE_MALFORMED_RPC_PAYLOAD,
                    .instance = "signtx",
                    .interface = "signtx_iface",
                    .description = "truncated message encountered while unmarshalling method index in signtx_iface",
                    .length = _camkes_size_723,
                    .current_index = sizeof(* _camkes_call_ptr_726),
                    }), ({
                        
    

                        
    
    seL4_MessageInfo_t _camkes_info_727 = seL4_Recv(12, &signtx_iface_badge);
    
    _camkes_size_723 =
        
            seL4_MessageInfo_get_length(_camkes_info_727) * sizeof(seL4_Word);
            assert(_camkes_size_723 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    


                        continue;
                }));

                memcpy(_camkes_call_ptr_726, ((void*)&seL4_GetIPCBuffer()->msg[0]), sizeof(* _camkes_call_ptr_726));
            

            switch (* _camkes_call_ptr_726) {
                
                    case 0: { /* print_sign */
                        
                        

                            
                                char * text UNUSED = NULL;
                                char ** text_ptr = TLS_PTR(print_sign_text_to, text);
                            
                        

                            
                                char * source UNUSED = NULL;
                                char ** source_ptr = TLS_PTR(print_sign_source_to, source);
                            
                        

                            
                                int id UNUSED;
                                int * id_ptr = TLS_PTR(print_sign_id_to, id);
                            
                        

                            
                                int isValid UNUSED;
                                int * isValid_ptr = TLS_PTR(print_sign_isValid_to, isValid);
                            
                        

                            
                                char * hmac UNUSED = NULL;
                                char ** hmac_ptr = TLS_PTR(print_sign_hmac_to, hmac);
                            
                        

                        /* Unmarshal parameters */
                        
                        
                        int _camkes_error_728 = 
    
    
    
    

    print_sign_unmarshal_inputs(
    _camkes_size_723
    
        ,
    
    
        
        text_ptr
        
            ,
        
    
        
        source_ptr
        
            ,
        
    
        
        id_ptr
        
            ,
        
    
        
        isValid_ptr
        
            ,
        
    
        
        hmac_ptr
        
    
    )
;
                        if (unlikely(_camkes_error_728 != 0)) {
                            /* Error in unmarshalling; return to event loop. */
                            
    

                            
    
    seL4_MessageInfo_t _camkes_info_729 = seL4_Recv(12, &signtx_iface_badge);
    
    _camkes_size_723 =
        
            seL4_MessageInfo_get_length(_camkes_info_729) * sizeof(seL4_Word);
            assert(_camkes_size_723 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    


                            continue;
                        }

                        /* Call the implementation */
                        
                        
                        
                        
                        
                        signtx_iface_print_sign(
                            
                                
                                
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
                                ,
                            
                                
                                
                                    *
                                
                                hmac_ptr
                                
                            
                        );

                        
    

                        
    


                        /* Marshal the response */
                        
                        
                        unsigned _camkes_length_734 = 
    
    
    
    

    print_sign_marshal_outputs(
    
    
    )
;

                        
                        
                        
                            
                                free(* text_ptr);
                            
                        
                            
                                free(* source_ptr);
                            
                        
                            
                        
                            
                        
                            
                                free(* hmac_ptr);
                            
                        

                        /* Check if there was an error during marshalling. We do
                         * this after freeing internal parameter variables to avoid
                         * leaking memory on errors.
                         */
                        if (unlikely(_camkes_length_734 == UINT_MAX)) {
                            
    

                            
    
    seL4_MessageInfo_t _camkes_info_735 = seL4_Recv(12, &signtx_iface_badge);
    
    _camkes_size_723 =
        
            seL4_MessageInfo_get_length(_camkes_info_735) * sizeof(seL4_Word);
            assert(_camkes_size_723 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    


                            continue;
                        }

                        
    
        
        seL4_MessageInfo_t _camkes_info_736 = seL4_MessageInfo_new(0, 0, 0, /* length */
            
                ROUND_UP_UNSAFE(_camkes_length_734, sizeof(seL4_Word)) / sizeof(seL4_Word)
            
        );

        /* Send the response */
        
            
            camkes_tls_t * _camkes__737 UNUSED = camkes_get_tls();
            assert(_camkes__737 != NULL);
            if (_camkes__737->reply_cap_in_tcb) {
                _camkes__737->reply_cap_in_tcb = false;
                _camkes_info_736 = seL4_ReplyRecv(12, _camkes_info_736, &signtx_iface_badge);
            } else {
                camkes_unprotect_reply_cap();
                seL4_Send(14, _camkes_info_736);
                _camkes_info_736 = seL4_Recv(12, &signtx_iface_badge);
            }
        
        
    _camkes_size_723 =
        
            seL4_MessageInfo_get_length(_camkes_info_736) * sizeof(seL4_Word);
            assert(_camkes_size_723 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    



                        break;
                    }
                
                    case 1: { /* print_mod */
                        
                        

                            
                                char * text UNUSED = NULL;
                                char ** text_ptr = TLS_PTR(print_mod_text_to, text);
                            
                        

                            
                                char * source UNUSED = NULL;
                                char ** source_ptr = TLS_PTR(print_mod_source_to, source);
                            
                        

                            
                                int id UNUSED;
                                int * id_ptr = TLS_PTR(print_mod_id_to, id);
                            
                        

                            
                                int isValid UNUSED;
                                int * isValid_ptr = TLS_PTR(print_mod_isValid_to, isValid);
                            
                        

                        /* Unmarshal parameters */
                        
                        
                        int _camkes_error_738 = 
    
    
    
    

    print_mod_unmarshal_inputs(
    _camkes_size_723
    
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
                        if (unlikely(_camkes_error_738 != 0)) {
                            /* Error in unmarshalling; return to event loop. */
                            
    

                            
    
    seL4_MessageInfo_t _camkes_info_739 = seL4_Recv(12, &signtx_iface_badge);
    
    _camkes_size_723 =
        
            seL4_MessageInfo_get_length(_camkes_info_739) * sizeof(seL4_Word);
            assert(_camkes_size_723 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    


                            continue;
                        }

                        /* Call the implementation */
                        
                        
                        
                        
                        
                        signtx_iface_print_mod(
                            
                                
                                
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
                        
                        
                        unsigned _camkes_length_744 = 
    
    
    
    

    print_mod_marshal_outputs(
    
    
    )
;

                        
                        
                        
                            
                                free(* text_ptr);
                            
                        
                            
                                free(* source_ptr);
                            
                        
                            
                        
                            
                        

                        /* Check if there was an error during marshalling. We do
                         * this after freeing internal parameter variables to avoid
                         * leaking memory on errors.
                         */
                        if (unlikely(_camkes_length_744 == UINT_MAX)) {
                            
    

                            
    
    seL4_MessageInfo_t _camkes_info_745 = seL4_Recv(12, &signtx_iface_badge);
    
    _camkes_size_723 =
        
            seL4_MessageInfo_get_length(_camkes_info_745) * sizeof(seL4_Word);
            assert(_camkes_size_723 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    


                            continue;
                        }

                        
    
        
        seL4_MessageInfo_t _camkes_info_746 = seL4_MessageInfo_new(0, 0, 0, /* length */
            
                ROUND_UP_UNSAFE(_camkes_length_744, sizeof(seL4_Word)) / sizeof(seL4_Word)
            
        );

        /* Send the response */
        
            
            camkes_tls_t * _camkes__747 UNUSED = camkes_get_tls();
            assert(_camkes__747 != NULL);
            if (_camkes__747->reply_cap_in_tcb) {
                _camkes__747->reply_cap_in_tcb = false;
                _camkes_info_746 = seL4_ReplyRecv(12, _camkes_info_746, &signtx_iface_badge);
            } else {
                camkes_unprotect_reply_cap();
                seL4_Send(14, _camkes_info_746);
                _camkes_info_746 = seL4_Recv(12, &signtx_iface_badge);
            }
        
        
    _camkes_size_723 =
        
            seL4_MessageInfo_get_length(_camkes_info_746) * sizeof(seL4_Word);
            assert(_camkes_size_723 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    



                        break;
                    }
                
                default: {
                    ERR(signtx_iface_error_handler, ((camkes_error_t){
                        .type = CE_INVALID_METHOD_INDEX,
                        .instance = "signtx",
                        .interface = "signtx_iface",
                        .description = "invalid method index received in signtx_iface",
                        .lower_bound = 0,
                        .upper_bound = 2 - 1,
                        .invalid_index = * _camkes_call_ptr_726,
                    }), ({
                        
    

                        
    
    seL4_MessageInfo_t _camkes_info_748 = seL4_Recv(12, &signtx_iface_badge);
    
    _camkes_size_723 =
        
            seL4_MessageInfo_get_length(_camkes_info_748) * sizeof(seL4_Word);
            assert(_camkes_size_723 <= seL4_MsgMaxLength * sizeof(seL4_Word))
        
        ;

    
    
        
        
        
            camkes_declare_reply_cap(14);
        
    


                        continue;
                    }));
                }
            }
            
        
        
    }

    UNREACHABLE();
}

