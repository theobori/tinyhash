#ifndef __TINYHASH_COMMON_KEY_H__
#define __TINYHASH_COMMON_KEY_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "types.h"

/**
 * @brief Represent an entry key.
 *
 */
typedef struct {
  uint32_t hash;
  size_t size;
  th_any_t data;
} th_key_t;

/**
 * @brief Create a key struct from data and size, it will automatically
 * compute its hash.
 *
 * @param data
 * @param size
 * @return th_key_t
 */
th_key_t th_key_create(th_any_t data, size_t size);

/**
 * @brief Key comparator function.
 *
 * @param first
 * @param second
 * @return true
 * @return false
 */
bool th_key_is_equal(th_key_t *first, th_key_t *second);

#endif
