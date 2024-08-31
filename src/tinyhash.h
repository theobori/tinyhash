#ifndef __TINYHASH_H__
#define __TINYHASH_H__

#include <stdbool.h>
#include <stdio.h>

#include "./common/types.h"

typedef enum {
    TH_SEPARATE_CHAINING,
    TH_OPEN_ADRESSING,
} th_kind_t;

typedef th_generic_table_t (*th_create_func_t)(void);

typedef th_any_t (*th_get_func_t)(th_generic_table_t, th_any_t, size_t);

typedef bool (*th_put_func_t)(th_generic_table_t, th_any_t, size_t, th_any_t);

typedef bool (*th_delete_func_t)(th_generic_table_t, th_any_t, size_t);

typedef void (*th_free_func_t)(th_generic_table_t);

typedef struct {
    th_create_func_t create;
    th_get_func_t get;
    th_put_func_t put;
    th_delete_func_t _delete;
    th_free_func_t _free;
} th_funcs_t;

typedef struct {
    th_kind_t kind;
    th_funcs_t funcs;
    void *table;
} th_t;

th_t th_create(th_kind_t kind);

th_t th_create_default();

th_any_t th_get(th_t *th, th_any_t data, size_t data_size);

bool th_put(th_t *th, th_any_t data, size_t data_size, th_any_t value);

bool th_delete(th_t *th, th_any_t data, size_t data_size);

void th_free(th_t *th);

#endif
