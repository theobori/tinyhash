#ifndef __TINYHASH_SC_TABLE_H__
#define __TINYHASH_SC_TABLE_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "entry.h"
#include "../common/types.h"

typedef struct {
    uint32_t count;
    uint32_t capacity;
    th_sc_entry_t **entries;
} th_sc_table_t;

void th_sc_table_init(th_sc_table_t *table);

th_generic_table_t th_sc_table_create();

th_any_t th_sc_table_get(th_generic_table_t table, th_any_t data,
    size_t data_size);

bool th_sc_table_put(th_generic_table_t table, th_any_t data,
    size_t data_size, th_any_t value);

void th_sc_table_free(th_generic_table_t table);

bool th_sc_table_delete(th_generic_table_t table, th_any_t data,
    size_t data_size);

#endif
