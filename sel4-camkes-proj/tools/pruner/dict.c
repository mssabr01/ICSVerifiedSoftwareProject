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
#include "dict.h"
#include <glib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

dict_t *dict(void (*value_destroyer)(void *value)) {
    return g_hash_table_new_full(g_str_hash, g_str_equal, NULL, value_destroyer);
}

void dict_set(dict_t *d, const char *key, void *value) {
    g_hash_table_insert(d, (gpointer)key, value);
}

void *dict_get(dict_t *d, const char *key) {
    return g_hash_table_lookup(d, key);
}

bool dict_contains(dict_t *d, const char *key) {
    return g_hash_table_contains(d, key);
}

void dict_destroy(dict_t *d) {
    g_hash_table_destroy(d);
}
