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
#include <errno.h>
#include <getopt.h>
#include "set.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG 1

/* We want to implement a rewriter (or source-to-source translator). The
 * standard way of doing this would be to sub-class RecursiveASTVisitor and go
 * from there. After several attempts I gave up on getting either of the Clang
 * C++ or Python bindings to compile and link and resorted to the below in C.
 */

/* Determine whether a given cursor is in our list of entities to never emit. */
static bool is_blacklisted(set_t *blacklist, CXCursor cursor) {
    CXString s = clang_getCursorSpelling(cursor);
    const char *name = clang_getCString(s);
    bool blacklisted = set_contains(blacklist, name);
    clang_disposeString(s);
    return blacklisted;
}

/* Dump a given cursor to the passed stream. */
static void emit(FILE* stream, CXTranslationUnit tu, CXCursor cursor, set_t *attribs) {
    /* Transform the cursor into a list of text tokens. */
    CXSourceRange range = clang_getCursorExtent(cursor);
    CXToken *tokens;
    unsigned int tokens_sz;
    clang_tokenize(tu, range, &tokens, &tokens_sz);

    /* Bail out early if possible to reduce complexity in the follow on logic.
     */
    if (tokens_sz == 0) {
        clang_disposeTokens(tu, tokens, tokens_sz);
        return;
    }

    /* Now time to deal with Clang's quirks. */

    /* Grab the last token. */
    CXString cxlast = clang_getTokenSpelling(tu, tokens[tokens_sz - 1]);
    const char *last = clang_getCString(cxlast);

    /* Grab the first token. */
    CXString cxfirst = clang_getTokenSpelling(tu, tokens[0]);
    const char *first = clang_getCString(cxfirst);

    enum CXCursorKind kind = clang_getCursorKind(cursor);

#ifdef DEBUG
    CXString cxname = clang_getCursorSpelling(cursor);
    const char *name = clang_getCString(cxname);
    CXString cxkind = clang_getTypeKindSpelling(kind);
    const char *k = clang_getCString(cxkind);
    fprintf(stderr, "Cursor %s of kind %s\n", name, k);
    clang_disposeString(cxkind);
    clang_disposeString(cxname);
#endif

    switch (kind) {

        /* XXX: If the cursor is an empty `;`, its extent covers the
         * (unrelated) following token as well. Libclang bug?
         * We could potentially just return here, but for now we will emit
         * the ';' anyway.  Decreasing the tokens_sz prevents us from also
         * emitting the unrelated following token.
         */
        case CXCursor_UnexposedDecl:
            if (!strcmp(first, ";")) {
                tokens_sz--;
            }
            break;

        /* XXX: If the cursor is a function definition, its extent covers the
         * (unrelated) following token as well. Libclang bug? An exception is
         * that a function appearing at the end of the translation unit will not
         * have an extra appended token. To cope with this, assume we never want to strip
         * closing braces.
         */
        case CXCursor_FunctionDecl:
            if (clang_isCursorDefinition(cursor) && strcmp(last, "}"))
                tokens_sz--;
            break;

        /* XXX: In code like 'typedef struct foo {...} foo_t', Clang considers
         * foo and foo_t siblings. We end up visiting foo, then foo_t. In my
         * mind, foo is a child of foo_t, but maybe Clang's outlook makes more
         * sense from a scoping point of view. Either way, it helpfully covers
         * an extra token in the foo cursor, so we can play the same trick as
         * above to elide the (excess) struct definition.
         */
        case CXCursor_StructDecl:
        case CXCursor_UnionDecl:
        case CXCursor_EnumDecl:
            if (strcmp(last, ";") && strcmp(last, "}")) {
                clang_disposeString(cxlast);
                clang_disposeString(cxfirst);
                clang_disposeTokens(tu, tokens, tokens_sz);
                return;
            }
            break;

        /* XXX: When multiple variables are declared in a single statement:
         *  int x, y;
         * the declaration appears once per variable. Only the final instance
         * is terminated with a semi-colon and only it is valid.
         */
        case CXCursor_TypedefDecl:
        case CXCursor_VarDecl:
            /* To add insult to injury, typedefed structs with trailing
             * __attribute__s come out with nothing following the
             * __attribute__. Why? Who knows. In this case we actually *do*
             * want to emit them. Probably. Of course this logic breaks down in
             * the case of code like:
             *  typedef struct f { int x; } y, z __attribute__(...);
             * but I don't easily see how to resolve situations like this.
             */
            if (!strcmp(last, "__attribute__"))
                break;
            if (strcmp(last, ";")) {
                clang_disposeString(cxlast);
                clang_disposeString(cxfirst);
                clang_disposeTokens(tu, tokens, tokens_sz);
                return;
            }

        default: /* shut -Wswitch warnings up */
            break;
    }

    clang_disposeString(cxlast);
    clang_disposeString(cxfirst);

    /* Dump all the tokens, not trying to preserve white space. */
    for (unsigned int i = 0; i < tokens_sz; i++) {
        CXString s = clang_getTokenSpelling(tu, tokens[i]);
        const char *token = clang_getCString(s);
        if (i == tokens_sz - 1 && attribs != NULL) {
            /* Precede the last token with any extra attributes. */
            void print_attribute(const char *attrib) {
                fprintf(stream, "__attribute__((%s))\n", attrib);
            }
            set_foreach(attribs, (void(*)(void*))print_attribute);
        }
        if (i == tokens_sz - 1 &&
                (kind == CXCursor_TypedefDecl || kind == CXCursor_VarDecl) &&
                !strcmp(token, "__attribute__"))
            /* XXX: Yet more hackery. Libclang misparses a trailing attribute
             * on a typedef. This should appear in the AST as an UnexposedDecl,
             * but for whatever reason it doesn't. No idea from whence this
             * behaviour stems as Clang itself just removes the attribute from
             * the AST altogether entirely.
             */
            fprintf(stream, "; ");
        else
            fprintf(stream, "%s\n", token);
        clang_disposeString(s);
    }
    clang_disposeTokens(tu, tokens, tokens_sz);
}

/* State data that we'll pass around while visiting the AST. */
typedef struct {
    set_t *keep;
    set_t *blacklist;
    dict_t *extra_attributes;
    CXTranslationUnit *tu;
    FILE *out;
} state_t;

/* Visit a node in the AST. */
enum CXChildVisitResult visitor(CXCursor cursor, CXCursor _, state_t *state) {

    CXString s = clang_getCursorSpelling(cursor);
    const char *name = clang_getCString(s);

    bool retain = true;

    if (clang_getCursorKind(cursor) == CXCursor_FunctionDecl) {
        /* Determine whether the function was one of those the user requested
         * to keep. */
        retain = set_contains(state->keep, name);
    }

    /* Get any extra attributes we need to apply to this symbol. */
    set_t *attribs = dict_get(state->extra_attributes, name);

    /* Don't need the symbol name any more. */
    clang_disposeString(s);

    if (!retain)
        return CXChildVisit_Continue;

    if (is_blacklisted(state->blacklist, cursor))
        return CXChildVisit_Continue;

    /* If we reached here, the current cursor is one we do want in the output.
     */
    emit(state->out, *state->tu, cursor, attribs);

    /* Never recurse (in the AST). We're only visiting top-level nodes. */
    return CXChildVisit_Continue;
}

typedef struct {
    const char *input;
    const char *output;
    set_t *keep;
    set_t *blacklist;
    dict_t *extra_attributes;
} options_t;

static options_t *parse_args(int argc, char **argv) {
    const struct option opts[] = {
        {"add-attribute", required_argument, NULL, 'a'},
        {"blacklist", required_argument, NULL, 'b'},
        {"help", no_argument, NULL, '?'},
        {"keep", required_argument, NULL, 'k'},
        {"output", required_argument, NULL, 'o'},
        {NULL, 0, NULL, 0},
    };

    options_t *o = calloc(1, sizeof(*o));
    if (o == NULL)
        goto fail1;

    /* defaults */
    o->output = "/dev/stdout";
    o->keep = set();
    if (o->keep == NULL)
        goto fail2;

    o->blacklist = set();
    if (o->blacklist == NULL)
        goto fail3;

    o->extra_attributes = dict((void(*)(void*))set_destroy);
    if (o->extra_attributes == NULL)
        goto fail4;

    while (true) {
        int index = 0;
        int c = getopt_long(argc, argv, "a:b:k:o:?", opts, &index);

        if (c == -1)
            /* end of defined options */
            break;

        switch (c) {
            case 'a':; /* --add-attribute */
                char *attrib = strstr(optarg, ":");
                if (attrib == NULL) {
                    fprintf(stderr, "illegal argument %s to --add-attribute\n", optarg);
                    goto fail4;
                }
                *attrib = '\0';/* NUL-terminate the symbol name */
                attrib++; /* move on to the attribute */
                set_t *s = dict_get(o->extra_attributes, optarg);
                if (s == NULL) {
                    s = set();
                    if (s == NULL)
                        goto fail4;
                    dict_set(o->extra_attributes, optarg, s);
                }
                set_insert(s, attrib);
                break;

            case 'b': /* --blacklist */
                set_insert(o->blacklist, optarg);
                break;

            case 'k': /* --keep */
                set_insert(o->keep, optarg);
                break;

            case 'o': /* --output */
                o->output = optarg;
                break;

            case '?': /* --help */
                printf("Usage: %s options... input_file\n"
                       "Trims a C file by discarding unwanted functions.\n"
                       "\n"
                       " Options:\n"
                       "  --add-attribute symbol:attrib\n"
                       "  -a symbol:attrib                Annotate a symbol with a GCC attribute.\n"
                       "  --blacklist symbol | -b symbol  Drop a given typedef or variable.\n"
                       "  --help | -?                     Print this information.\n"
                       "  --keep symbol | -k symbol       Retain a particular function.\n"
                       "  --output file | -o file         Write output to file, rather than stdout.\n",
                    argv[0]);
                goto fail5;

            default:
                goto fail5;
        }
    }

    /* Hopefully we still have an input file remaining. */
    if (optind == argc - 1)
        o->input = argv[optind];
    else if (optind < argc) {
        fprintf(stderr, "multiple input files are not supported\n");
        goto fail5;
    }

    return o;

fail5: dict_destroy(o->extra_attributes);
fail4: set_destroy(o->blacklist);
fail3: set_destroy(o->keep);
fail2: free(o);
fail1: exit(EXIT_FAILURE);
}

/* Use the passed CFG to recursively enumerate callees of the passed "to-keep"
 * symbols and accumulate these. Returns non-zero on failure.
 */
static int merge_callees(set_t *keeps, cfg_t *graph) {

    /* A set for tracking the callees. We need to use a separate set and then
     * post-merge this into the keeps set because we cannot insert into the
     * keeps set while iterating through it.
     */
    set_t *callees = set();
    if (callees == NULL)
        return -1;

    /* Visitor for appending each callee to the "keeps" set. */
    enum CXChildVisitResult visitor(const char *callee, const char *caller,
            void *_) {

        /* The CFG callee visitation calls us once per undefined function with
         * NULL as the callee. This is useful for warning the user when the
         * input file is incomplete and we may be pruning it too agressively.
         */
        if (callee == NULL) {
            fprintf(stderr, "Warning: no definition for called function %s\n", caller);
            return CXChildVisit_Continue;
        }

        set_insert(callees, callee);

        return CXChildVisit_Recurse;
    }

    set_iter_t i;
    set_iter(keeps, &i);

    while (true) {
        const char *caller = set_iter_next(&i);
        if (caller == NULL)
            break;

        if (cfg_visit_callees(graph, caller, visitor, NULL) == 1) {
            /* Traversal of this particular caller's callees failed. */
            set_destroy(callees);
            return -1;
        }
    }
    set_union(keeps, callees);
    return 0;
}

int main(int argc, char **argv) {
    options_t *opts = parse_args(argc, argv);

    if (opts == NULL) {
        perror("failed to parse arguments");
        return EXIT_FAILURE;
    } else if (opts->input == NULL) {
        fprintf(stderr, "no input file provided\n");
        return EXIT_FAILURE;
    }

    /* Test whether we can read from the file. */
    FILE *check = fopen(opts->input, "r");
    if (check == NULL) {
        fprintf(stderr, "input file does not exist or is unreadable\n");
        return EXIT_FAILURE;
    }
    fclose(check);

    /* Flags to tell Clang that input is C. */
    const char *const args[] = {
        "-x",
        "c",
    };

    /* Parse the source file into a translation unit */
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit tu = clang_parseTranslationUnit(index, opts->input, args,
        sizeof(args) / sizeof(args[0]), NULL, 0, CXTranslationUnit_None);
    if (tu == NULL) {
        fprintf(stderr, "failed to parse source file\n");
        return EXIT_FAILURE;
    }

    FILE *f = fopen(opts->output, "w");
    if (f == NULL) {
        perror("failed to open output");
        return EXIT_FAILURE;
    }

    /* Derive the Control Flow Graph of the TU. We then use this CFG to expand
     * the kept symbols set to include callees of the kept symbols.
     */
    cfg_t *graph = cfg(tu);
    if (graph == NULL) {
        fprintf(stderr, "failed to form CFG");
        if (errno != 0) {
            perror(": ");
        } else {
            fprintf(stderr, "\n");
        }
        return EXIT_FAILURE;
    }
    if (merge_callees(opts->keep, graph) != 0) {
        fprintf(stderr, "Failed to traverse CFG\n");
        return EXIT_FAILURE;
    }
    cfg_destroy(graph); /* no longer needed */

    state_t st = {
        .keep = opts->keep,
        .blacklist = opts->blacklist,
        .extra_attributes = opts->extra_attributes,
        .tu = &tu,
        .out = f,
    };

    /* Now traverse the AST */
    CXCursor cursor = clang_getTranslationUnitCursor(tu);
    clang_visitChildren(cursor, (CXCursorVisitor)visitor, &st);

    clang_disposeTranslationUnit(tu);
    clang_disposeIndex(index);

    return 0;
}
