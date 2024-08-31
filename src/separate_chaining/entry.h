#ifndef __TINYHASH_SC_ENTRY_H__
#define __TINYHASH_SC_ENTRY_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../common/hash.h"
#include "../common/key.h"

typedef struct th_sc_entry_s {
    th_key_t key;
    th_any_t value;
    struct th_sc_entry_s *previous;
    struct th_sc_entry_s *next;
} th_sc_entry_t;

bool th_sc_entry_add(th_sc_entry_t **root, th_key_t *key, th_any_t value);

#endif
