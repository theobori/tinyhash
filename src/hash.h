#ifndef __TINYHASH_HASH_H__
#define __TINYHASH_HASH_H__

#include <stdint.h>
#include <stdio.h>

typedef uint32_t (*th_hash_func_t)(uint8_t *bytes, size_t size);

uint32_t th_hash(uint8_t *bytes, size_t size);

#endif
