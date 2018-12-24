<!--
     Copyright 2017, Data61
     Commonwealth Scientific and Industrial Research Organisation (CSIRO)
     ABN 41 687 119 230.

     This software may be distributed and modified according to the terms of
     the BSD 2-Clause license. Note that NO WARRANTY is provided.
     See "LICENSE_BSD2.txt" for details.

     @TAG(DATA61_BSD)
-->
# Prune

This is a tool for removing excess functions from C code. It is possible to
dramatically reduce the runtime of the C parser and friends (and your
resulting find_theorems search space) by removing functions you are not
calling before parsing.

## Usage

You will need the libclang and glib headers available to build this. I have not
located a packaged version of libclang and LLVM that work together, so I
recommend you build these from source as described on the
[Clang getting started page](http://clang.llvm.org/get_started.html). I have
successfully built this tool using r207601 of all the LLVM pieces.

Run `prune --help` for options. For anything more, read the source code.

## Caveats

No attempt is made to automatically prune anything other than functions. Other
entities don't cost us much in parsing. If you do want to explicitly prune
other things you can use the `--blacklist` option.

Some tricky C is clever enough to even baffle Clang (e.g. seL4_IPCBuffer
alignment). Report anything serious, but minor issues like this will have to be
worked around yourself.

## Issues

Email Matthew Fernandez with questions or problems.
