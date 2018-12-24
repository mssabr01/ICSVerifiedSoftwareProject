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

#pragma once

#include <camkes/dataport.h>
#include <camkes/error.h>
#include <stdint.h>
#include <stdlib.h>
#include <utils/util.h>
#include <platsupport/io.h>



    

    


    




    
        
    
        
    
    
        
    

    
        
    
        
    
    
        
    

    
        
    
        
    
    
        
    

    
        
    
        
    
    
        
    


const char *get_instance_name(void);

/* Attributes */





    
        
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
              
              
            
            
        ) NONNULL_ALL ;
    

    
        
            void
        
        crypto_iface_sign(
            
              
                
                  const char *
                
                text
              
              
                ,
              
            
              
                
                  int
                
                id
              
              
            
            
        ) NONNULL_ALL ;
    
        
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
              
              
            
            
        ) NONNULL_ALL ;
    

    
        
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
              
              
            
            
        ) NONNULL_ALL ;
    














/* Entry point expected to be provided by the user. */
int run(void);



/* Optional init functions provided by the user. */
void pre_init(void) WEAK;
void post_init(void) WEAK;

    void modtx_iface__init(void) WEAK;

    void modtx_iface_timing_get_points(char ***points, size_t *size);
    uint64_t modtx_iface_timing_get_entry(unsigned iteration, char *point);
    void modtx_iface_timing_reset(void);

    void modchk_iface__init(void) WEAK;

    void modchk_iface_timing_get_points(char ***points, size_t *size);
    uint64_t modchk_iface_timing_get_entry(unsigned iteration, char *point);
    void modchk_iface_timing_reset(void);

    void crypto_iface__init(void) WEAK;

    void crypto_iface_timing_get_points(char ***points, size_t *size);
    uint64_t crypto_iface_timing_get_entry(unsigned iteration, char *point);
    void crypto_iface_timing_reset(void);


void set_putchar(void (*putchar)(int c));


  camkes_error_handler_t modtx_iface_register_error_handler(
    camkes_error_handler_t handler);

  camkes_error_handler_t modchk_iface_register_error_handler(
    camkes_error_handler_t handler);

  camkes_error_handler_t crypto_iface_register_error_handler(
    camkes_error_handler_t handler);
