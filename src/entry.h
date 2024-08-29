#ifndef __TINYHASH_ENTRY_H__
#define __TINYHASH_ENTRY_H__

#include <stdint.h>
#include <stdlib.h>

#include "hash.h"

typedef void *th_any_t;

typedef struct {
    uint32_t hash;
    int size;
    th_any_t data;
} th_key_t;

typedef struct th_entry_s {
    th_key_t key;
    th_any_t value;
    struct th_entry_s *next;
} th_entry_t;


void th_entry_add(th_entry_t **root, th_key_t *key,
    th_any_t value);

th_key_t th_key_new(th_any_t data, size_t size,
    th_hash_func_t hash_func);

#endif
