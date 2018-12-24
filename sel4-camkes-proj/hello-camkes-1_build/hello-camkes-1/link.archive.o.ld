SECTIONS { ._archive_cpio : ALIGN(4) { _capdl_archive = . ; *(.*) ; _capdl_archive_end = . ; } }
