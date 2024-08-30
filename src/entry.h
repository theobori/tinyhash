#ifndef __TINYHASH_ENTRY_H__
#define __TINYHASH_ENTRY_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "hash.h"
#include "key.h"

typedef struct th_entry_s {
    th_key_t key;
    th_any_t value;
    struct th_entry_s *previous;
    struct th_entry_s *next;
} th_entry_t;


bool th_entry_add(th_entry_t **root, th_key_t *key, th_any_t value);

#endif
