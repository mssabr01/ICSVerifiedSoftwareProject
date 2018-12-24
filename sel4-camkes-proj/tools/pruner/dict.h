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
#ifndef _DICT_H_
#define _DICT_H_

/* Implementation of a dictionary. */

#include <glib.h>
#include <stdbool.h>

typedef GHashTable dict_t;

dict_t *dict(void (*value_destroyer)(void *value));
void dict_set(dict_t *d, const char *key, void *value);
void *dict_get(dict_t *d, const char *key);
bool dict_contains(dict_t *d, const char *key);
void dict_destroy(dict_t *d);

#endif
