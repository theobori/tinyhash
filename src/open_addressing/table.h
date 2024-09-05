#ifndef __TINYHASH_OA_TABLE_H__
#define __TINYHASH_OA_TABLE_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../common/iterator.h"
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

/**
 * @brief Return a new iterator.
 *
 * If `is_begin` is true, it will initialize the iterator with the first
 * element. Otherwise, it will be empty.
 *
 * @param generic_table
 * @param is_begin
 * @return th_iterator_t*
 */
th_iterator_t *th_oa_iterator_begin(th_generic_table_t generic_table,
                                    bool is_begin);

/**
 * @brief Returns the table length.
 *
 * @param generic_table
 * @return int
 */
int th_oa_table_len(th_generic_table_t generic_table);

#endif
