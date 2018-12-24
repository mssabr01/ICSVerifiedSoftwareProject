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
#include <assert.h>
#include "cfg.h"
#include <clang-c/Index.h> /* -lclang */
#include "dict.h"
#include "set.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Visitor function for scanning a function for its callees. The set parameter
 * tracks the callee names of the function we're scanning.
 */
static enum CXChildVisitResult scan_fn(CXCursor cursor, CXCursor _, set_t *s) {
    /* Skip anything that's not a function call. */
    if (clang_getCursorKind(cursor) != CXCursor_CallExpr)
        return CXChildVisit_Recurse;

    /* Get the name of the callee. */
    CXString sym = clang_getCursorSpelling(cursor);
    char *name = strdup(clang_getCString(sym));
    clang_disposeString(sym);
    if (name == NULL)
        return CXChildVisit_Break;

    set_insert(s, name);

    return CXChildVisit_Recurse;
}

/* Representation of a function and its callees. */
typedef struct {
    CXCursor cursor;
    set_t *callees;
} fn_t;

/* Visitor function for recursively visiting a function's callees with the
 * user's provided visitor.
 */
static enum CXChildVisitResult visit_callees(cfg_t *c, fn_t *f,
        cfg_visitor_t visitor, void *data) {

    if (!f->callees) {
        /* We haven't yet looked inside this function. */
        f->callees = set();
        if (f->callees == NULL)
            return CXChildVisit_Break;
        if (clang_visitChildren(f->cursor, (CXCursorVisitor)scan_fn, f->callees) != 0)
            return CXChildVisit_Break;
    }

    CXString s = clang_getCursorSpelling(f->cursor);
    const char *name = clang_getCString(s);

    set_iter_t i;
    set_iter(f->callees, &i);

    while (true) {
        const char *current = set_iter_next(&i);
        if (current == NULL)
            /* Iterator exhausted. */
            break;

        switch (visitor(current, name, data)) {

            case CXChildVisit_Break:
                goto fail;

            case CXChildVisit_Recurse:;
                fn_t *callee = dict_get(c, current);

                if (callee == NULL) {
                    /* This function has no known definition. */
                    if (visitor(NULL, current, data) == CXChildVisit_Break)
                        goto fail;
                    break;
                }

                if (visit_callees(c, callee, visitor, data) == CXChildVisit_Break)
                    /* Abort traversal. */
                    goto fail;

                /* fall through */
        }
    }

    clang_disposeString(s);
    return CXChildVisit_Continue;

fail: clang_disposeString(s);
    return CXChildVisit_Break;
}

int cfg_visit_callees(cfg_t *c, const char *name, cfg_visitor_t visitor,
        void *data) {

    fn_t *f = dict_get(c, name);
    if (f == NULL) {
        /* Function not found. */
        visitor(NULL, name, data);
        return -1;
    }

    return visit_callees(c, f, visitor, data) == CXChildVisit_Break;
}

static enum CXChildVisitResult visit_tu(CXCursor cursor, CXCursor _, cfg_t *c) {

    /* Skip anything that's not a function. */
    if (clang_getCursorKind(cursor) != CXCursor_FunctionDecl)
        return CXChildVisit_Continue;

    /* Skip function declarations that are not definitions. */
    if (!clang_isCursorDefinition(cursor))
        return CXChildVisit_Continue;

    /* Determine the name of the current function. */
    CXString s = clang_getCursorSpelling(cursor);
    char *name = strdup(clang_getCString(s));
    clang_disposeString(s);
    if (name == NULL) {
        fprintf(stderr, "failed to allocate memory\n");
        goto fail;
    } else if (dict_contains(c, name)) {
        fprintf(stderr, "duplicate definition for function %s\n", name);
        goto fail;
    }

    /* Construct a lazy (uninitialised) representation of its callees. */
    fn_t *f = calloc(1, sizeof(*f));
    if (f == NULL)
        goto fail;
    f->cursor = cursor;

    /* Add this function to the CFG. */
    dict_set(c, name, f);

    return CXChildVisit_Continue;

fail: free(name);
    return CXChildVisit_Break;
}

cfg_t *cfg(CXTranslationUnit tu) {
    cfg_t *c = dict(NULL);
    if (c == NULL)
        return NULL;
    CXCursor cursor = clang_getTranslationUnitCursor(tu);
    if (clang_visitChildren(cursor, (CXCursorVisitor)visit_tu, c) != 0) {
        dict_destroy(c);
        return NULL;
    }
    return c;
}

void cfg_destroy(cfg_t *c) {
    dict_destroy(c);
}
