#ifndef __TINYHASH_COMMON_HASH_H__
#define __TINYHASH_COMMON_HASH_H__

#include <stdint.h>
#include <stdio.h>

/**
 * @brief Compute an unsigned int from bytes.
 *
 * @param bytes
 * @param size
 * @return uint32_t
 */
uint32_t th_hash(uint8_t *bytes, size_t size);

#endif
