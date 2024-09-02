#ifndef __TINYHASH_SC_ENTRY_H__
#define __TINYHASH_SC_ENTRY_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../common/hash.h"
#include "../common/key.h"

/**
 * @brief Represents a separate chaining entry.
 *
 */
typedef struct th_sc_entry_s {
  th_key_t key;
  th_any_t value;
  struct th_sc_entry_s *previous;
  struct th_sc_entry_s *next;
} th_sc_entry_t;

/**
 * @brief Add an a separate chaining entry to the beginning of a linked list.
 * Return true on success.
 *
 * @param root
 * @param key
 * @param value
 * @return true
 * @return false
 */
bool th_sc_entry_add(th_sc_entry_t **root, th_key_t *key, th_any_t value);

#endif
