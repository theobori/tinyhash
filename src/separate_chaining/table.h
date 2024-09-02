#ifndef __TINYHASH_SC_TABLE_H__
#define __TINYHASH_SC_TABLE_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../common/types.h"
#include "entry.h"

/**
 * @brief Represent a separate chaining table.
 *
 */
typedef struct {
  uint32_t count;
  uint32_t capacity;
  th_sc_entry_t **entries;
} th_sc_table_t;

/**
 * @brief Initialize a separate chaining table.
 *
 * @param table
 */
void th_sc_table_init(th_sc_table_t *table);

/**
 * @brief Return an allocated separate chaining table.
 *
 * @return th_generic_table_t
 */
th_generic_table_t th_sc_table_create();

/**
 * @brief Get a value from an separate chaining table.
 * Return NULL if it does exist.
 *
 * @param table
 * @param data
 * @param data_size
 * @return th_any_t
 */
th_any_t th_sc_table_get(th_generic_table_t table, th_any_t data,
                         size_t data_size);

/**
 * @brief Insert a value within an separate chaining table.
 * Return true on success.
 *
 * @param table
 * @param data
 * @param data_size
 * @param value
 * @return true
 * @return false
 */
bool th_sc_table_put(th_generic_table_t table, th_any_t data, size_t data_size,
                     th_any_t value);

/**
 * @brief Free an separate chaining table.
 *
 * @param table
 */
void th_sc_table_free(th_generic_table_t table);

/**
 * @brief Delete a key value pair in an separate chaining table.
 * Return true on success.
 *
 * @param table
 * @param data
 * @param data_size
 * @return true
 * @return false
 */
bool th_sc_table_delete(th_generic_table_t table, th_any_t data,
                        size_t data_size);

#endif
