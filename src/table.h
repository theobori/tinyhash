#ifndef __TINYHASH_TABLE_H__
#define __TINYHASH_TABLE_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "entry.h"
#include "options.h"

typedef struct {
    uint32_t count;
    uint32_t capacity;
    th_entry_t **entries;
    th_options_t options;
} th_table_t;

#define TABLE_NEXT_CAPACITY(capacity) \
    (capacity) == 0 ? 8 : (capacity) * 2

void th_table_init(th_table_t *table);

th_any_t th_table_get(th_table_t *table, th_any_t data, size_t key_data_size);

void th_table_put(th_table_t *table, th_any_t data, size_t key_data_size,
    th_any_t value);

void th_table_destroy(th_table_t *table);

#endif
