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

/* Linker script for CAmkES components. */






  

  

  

  



SECTIONS {


  

      

      align_12bit (NOLOAD) : ALIGN(4096) {
          KEEP (*(align_12bit))
      }

  

      

      align_21bit (NOLOAD) : ALIGN(2097152) {
          KEEP (*(align_21bit))
      }

  

      

      align_30bit (NOLOAD) : ALIGN(1073741824) {
          KEEP (*(align_30bit))
      }

  
}
INSERT AFTER .bss;