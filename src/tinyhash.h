#ifndef __TINYHASH_H__
#define __TINYHASH_H__

#include <stdbool.h>
#include <stdio.h>

#include "./common/iterator.h"
#include "./common/types.h"

/**
 * @brief Implementation methods.
 *
 */
typedef enum {
  TH_SEPARATE_CHAINING,
  TH_OPEN_ADRESSING,
} th_method_t;

/**
 * @brief Pointer on generic function that create a table.
 *
 */
typedef th_generic_table_t (*th_create_func_t)(void);

/**
 * @brief Pointer on generic function that get a value from a table.
 *
 */
typedef th_any_t (*th_get_func_t)(th_generic_table_t, th_any_t, size_t);

/**
 * @brief Pointer on generic function that insert a value into a table.
 *
 */
typedef bool (*th_put_func_t)(th_generic_table_t, th_any_t, size_t, th_any_t);

/**
 * @brief Pointer on generic function that delete a value from a table.
 *
 */
typedef bool (*th_delete_func_t)(th_generic_table_t, th_any_t, size_t);

/**
 * @brief Pointer on generic function that free a table.
 *
 */
typedef void (*th_free_func_t)(th_generic_table_t);

typedef th_iterator_t *(*th_begin_iterator_func_t)(th_generic_table_t, bool);
typedef int (*th_len_func_t)(th_generic_table_t);

/**
 * @brief Centralizing every function associated with
 * an unique implementation method.
 *
 */
typedef struct {
  th_create_func_t create;
  th_get_func_t get;
  th_put_func_t put;
  th_delete_func_t _delete;
  th_free_func_t _free;
  th_begin_iterator_func_t begin_iterator;
  th_len_func_t len;
} th_funcs_t;

/**
 * @brief Represent a hashmap controller.
 *
 */
typedef struct {
  th_method_t method;
  th_funcs_t funcs;
  th_generic_table_t table;
} th_t;

/**
 * @brief Allocate then initialize a hashmap controller.
 * based on the given method.
 *
 * @param method
 * @return th_t
 */
th_t th_create(th_method_t method);

/**
 * @brief Allocate then initialize a hashmap controller
 * with its default values.
 *
 * @return th_t
 */
th_t th_create_default();

/**
 * @brief Returns a value from a hashmap.
 * Return NULL if it doest not exist.
 *
 * @param th
 * @param data
 * @param data_size
 * @return th_any_t
 */
th_any_t th_get(th_t *th, th_any_t data, size_t data_size);

/**
 * @brief Insert element within the hashmap.
 * Return true on success.
 *
 * @param th
 * @param data
 * @param data_size
 * @param value
 * @return true
 * @return false
 */
bool th_put(th_t *th, th_any_t data, size_t data_size, th_any_t value);

/**
 * @brief Delete a key value pair from a hashmap.
 * Return true on success.
 *
 * @param th
 * @param data
 * @param data_size
 * @return true
 * @return false
 */
bool th_delete(th_t *th, th_any_t data, size_t data_size);

/**
 * @brief Clear a hashmap.
 *
 * @param th
 */
void th_clear(th_t *th);

/**
 * @brief Free a hashmap.
 *
 * @param th
 */
void th_free(th_t *th);

/**
 * @brief Return a pointer on an iterator with the first element.
 *
 * @param th
 * @return th_iterator_t*
 */
th_iterator_t *th_begin_iterator(th_t *th);

/**
 * @brief Return an empty iterator.
 *
 * @param th
 * @return th_iterator_t*
 */
th_iterator_t *th_empty_iterator(th_t *th);

/**
 * @brief Get the hashmap length (total amount of key value pairs).
 *
 * @param th
 * @return int
 */
int th_len(th_t *th);

#endif
