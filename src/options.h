#ifndef __TINYHASH_OPTIONS_H__
#define __TINYHASH_OPTIONS_H__

#include <stdint.h>

#include "hash.h"

typedef struct {
    th_hash_func_t hash_func;
} th_options_t;

#endif
