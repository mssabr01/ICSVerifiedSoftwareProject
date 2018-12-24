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
#ifndef _SET_H_
#define _SET_H_

/* Implementation of a set. */

#include <glib.h>
#include <stdbool.h>

typedef GHashTable set_t;
set_t *set(void);
void set_insert(set_t *s, const char *item);
bool set_contains(set_t *s, const char *item);
void set_union(set_t *a, set_t *b);
void set_destroy(set_t *s);

typedef GHashTableIter set_iter_t;
void set_iter(set_t *s, set_iter_t *i);
const char *set_iter_next(set_iter_t *i);

void set_foreach(set_t *s, void (*f)(void *value));

#endif
