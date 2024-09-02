#ifndef __TINYHASH_OA_TABLE_H__
#define __TINYHASH_OA_TABLE_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../common/types.h"
#include "entry.h"

/**
 * @brief Load factor.
 *
 */
#define TH_OA_LOAD_FACTOR 0.75

typedef struct {
  uint32_t count;
  uint32_t capacity;
  th_oa_entry_t *entries;
} th_oa_table_t;

/**
 * @brief Initialize open adressing table values.
 *
 * @param table
 */
void th_oa_table_init(th_oa_table_t *table);

/**
 * @brief Return an allocated open addressing table struct.
 *
 * @return th_generic_table_t
 */
th_generic_table_t th_oa_table_create();

/**
 * @brief Get a value from an open addressing table.
 * Return NULL if it does exist.
 *
 * @param table
 * @param data
 * @param data_size
 * @return th_any_t
 */
th_any_t th_oa_table_get(th_generic_table_t table, th_any_t data,
                         size_t data_size);

/**
 * @brief Insert a value within an open addressing table.
 * Return true on success.
 *
 * @param table
 * @param data
 * @param data_size
 * @param value
 * @return true
 * @return false
 */
bool th_oa_table_put(th_generic_table_t table, th_any_t data, size_t data_size,
                     th_any_t value);

/**
 * @brief Free an open addressing table.
 *
 * @param table
 */
void th_oa_table_free(th_generic_table_t table);

/**
 * @brief Delete a key value pair in an open addressing table.
 * Return true on success.
 *
 * @param table
 * @param data
 * @param data_size
 * @return true
 * @return false
 */
bool th_oa_table_delete(th_generic_table_t table, th_any_t data,
                        size_t data_size);

#endif
