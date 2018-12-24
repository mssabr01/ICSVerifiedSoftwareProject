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
#ifndef _CFG_H_
#define _CFG_H_

/* Functionality related to creating and traversing a Control Flow Graph of a C
 * translation unit.
 */

#include <clang-c/Index.h> /* -lclang */
#include "dict.h"

typedef dict_t cfg_t;

/* Initialise a representation of the CFG. Note that the CFG is initialised
 * lazily, so we won't actually traverse a particular function (and derive its
 * callees) until we actually need to.
 *
 * Returns NULL on failure. */
cfg_t *cfg(CXTranslationUnit tu);

/* Destroy a CFG representation and deallocate associated resources. */
void cfg_destroy(cfg_t *c);

/* Visitor used when visiting CFG nodes below. */
typedef enum CXChildVisitResult (*cfg_visitor_t)(const char *callee,
    const char *caller, void *data);

/* Recursively visit all callees of a given function. user-provided visitor
 * function is invoked once per callee, with the caller function as the second
 * parameter (see cfg_visitor_t above). The visitor is invoked once per
 * undefined function with NULL as the callee function to give the user an
 * opportunity to detect and handle this.
 *
 * Returns non-zero on failure.
 */
int cfg_visit_callees(cfg_t *c, const char *name, cfg_visitor_t visitor,
    void *data);

#endif
