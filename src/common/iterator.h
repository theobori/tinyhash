#ifndef __TINYHASH_COMMON_ITERATOR_H__
#define __TINYHASH_COMMON_ITERATOR_H__

#include "key.h"
#include "types.h"

/**
 * @brief Represents an iterator that allow to iterate over a generic table.
 *
 */
typedef struct th_iterator_s {
  int index;
  th_any_t current;
  th_key_t *key;
  th_any_t value;
  th_generic_table_t generic_table;
  bool (*next)(struct th_iterator_s **);
} th_iterator_t;

/**
 * @brief Pointer on function that get the next element.
 *
 */
typedef bool (*th_iterator_next_func_t)(th_iterator_t **);

/**
 * @brief Allocate then init a new iterator.
 *
 * @param generic_table
 * @param next
 * @return th_iterator_t*
 */
th_iterator_t *th_iterator_create(th_generic_table_t generic_table,
                                  th_iterator_next_func_t next);

/**
 * @brief Free an iterator.
 *
 * @param it
 */
void th_iterator_free(th_iterator_t *it);

/**
 * @brief Try to get the next element.
 * Free the iterator if it reachs the end.
 *
 * @param ptr
 * @return true
 * @return false
 */
bool th_iterator_next(th_iterator_t **ptr);

#endif
