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
#include <glib.h>
#include "set.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

set_t *set(void) {
    return g_hash_table_new(g_str_hash, g_str_equal);
}

void set_insert(set_t *s, const char *item) {
    g_hash_table_add(s, (gpointer)item);
}

bool set_contains(set_t *s, const char *item) {
    return (bool)g_hash_table_contains(s, item);
}

void set_union(set_t *a, set_t *b) {
    GHashTableIter i;
    g_hash_table_iter_init(&i, b);
    const char *entry;
    while (g_hash_table_iter_next(&i, (void**)&entry, NULL))
        g_hash_table_add(a, (gpointer)entry);
    g_hash_table_destroy(b);
}
void set_destroy(set_t *s) {
    g_hash_table_destroy(s);
}

void set_iter(set_t *s, set_iter_t *i) {
    g_hash_table_iter_init(i, s);
}

const char *set_iter_next(set_iter_t *i) {
    const char *item;
    if (!g_hash_table_iter_next(i, (void**)&item, NULL))
        return NULL;
    return item;
}

void set_foreach(set_t *s, void (*f)(void *value)) {
    void f_wrapper(void *key __attribute__((unused)), void *value,
            void *user_data __attribute__((unused))) {
        f(value);
    }
    g_hash_table_foreach(s, f_wrapper, NULL);
}
