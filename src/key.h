#ifndef __TINYHASH_KEY_H__
#define __TINYHASH_KEY_H__

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "types.h"

typedef struct {
    uint32_t hash;
    int size;
    th_any_t data;
} th_key_t;

th_key_t th_key_new(th_any_t data, size_t size);

bool th_key_is_equal(th_key_t *first, th_key_t *second);

#endif
