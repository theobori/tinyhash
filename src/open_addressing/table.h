#ifndef __TINYHASH_OA_TABLE_H__
#define __TINYHASH_OA_TABLE_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../common/types.h"
#include "entry.h"

#define TH_OA_LOAD_FACTOR 0.75

typedef struct {
  uint32_t count;
  uint32_t capacity;
  th_oa_entry_t *entries;
} th_oa_table_t;

void th_oa_table_init(th_oa_table_t *table);

th_generic_table_t th_oa_table_create();

th_any_t th_oa_table_get(th_generic_table_t table, th_any_t data,
                         size_t data_size);

bool th_oa_table_put(th_generic_table_t table, th_any_t data, size_t data_size,
                     th_any_t value);

void th_oa_table_free(th_generic_table_t table);

bool th_oa_table_delete(th_generic_table_t table, th_any_t data,
                        size_t data_size);

#endif
