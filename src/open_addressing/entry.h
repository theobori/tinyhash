#ifndef __TINYHASH_OA_ENTRY_H__
#define __TINYHASH_OA_ENTRY_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../common/hash.h"
#include "../common/key.h"

/**
 * @brief Represent an entry within a bucket.
 *
 */
typedef struct th_oa_entry_s {
  th_key_t *key;
  th_any_t value;
  bool is_tombstone;
} th_oa_entry_t;

#endif
