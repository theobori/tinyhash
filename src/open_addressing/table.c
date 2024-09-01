#include "../common/table.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entry.h"
#include "table.h"

static bool th_oa_table_put_with_key(th_oa_table_t *table, th_key_t *key,
                                     th_any_t value);

void th_oa_table_init(th_oa_table_t *table) {
  table->capacity = 0;
  table->count = 0;
  table->entries = NULL;
}

static th_oa_table_t *_th_oa_table_create() {
  th_oa_table_t *table = malloc(sizeof(th_oa_table_t));

  if (table == NULL)
    return NULL;

  th_oa_table_init(table);

  return table;
}

th_generic_table_t th_oa_table_create() {
  return (th_generic_table_t)_th_oa_table_create();
}

static bool th_oa_table_copy(th_oa_table_t *dest, th_oa_table_t *src) {
  bool success;

  for (int i = 0; i < src->capacity; i++) {
    th_oa_entry_t *entry = &src->entries[i];

    if (entry->key == NULL)
      continue;

    success = th_oa_table_put_with_key(dest, entry->key, entry->value);

    if (success == false)
      return false;
  }

  return true;
}

static bool th_oa_table_increase(th_oa_table_t *table) {
  th_oa_table_t new_table;
  bool success;

  th_oa_table_init(&new_table);

  new_table.capacity = TH_TABLE_NEXT_CAPACITY(table->capacity);

  size_t size = sizeof(th_oa_entry_t) * new_table.capacity;

  new_table.entries = malloc(size);
  if (new_table.entries == NULL)
    return false;

  memset(new_table.entries, 0, size);

  success = th_oa_table_copy(&new_table, table);
  if (success == false)
    return false;

  th_oa_table_free(table);

  *table = new_table;

  return true;
}

static th_oa_entry_t *th_oa_table_find(th_oa_table_t *table, th_key_t *key) {
  int index = key->hash % table->capacity;

  th_oa_entry_t *tombstone = NULL;
  for (;;) {
    th_oa_entry_t *entry = &table->entries[index];

    if (entry->key == NULL) {
      if (entry->is_tombstone == false) {
        return tombstone != NULL ? tombstone : entry;
      } else {
        if (tombstone == NULL)
          tombstone = entry;
      }
    } else if (th_key_is_equal(key, entry->key) == true) {
      return entry;
    }

    index = (index + 1) % table->capacity;
  }
}

th_any_t th_oa_table_get(th_generic_table_t generic_table, th_any_t data,
                         size_t data_size) {
  th_oa_table_t *table = (th_oa_table_t *)generic_table;
  if (table->capacity == 0)
    return NULL;

  th_key_t key = th_key_create(data, data_size);
  th_oa_entry_t *entry = th_oa_table_find(table, &key);
  if (entry->key == NULL)
    return NULL;

  return entry->value;
}

static bool th_oa_table_put_with_key(th_oa_table_t *table, th_key_t *key,
                                     th_any_t value) {
  if (table->count >= (table->capacity * TH_OA_LOAD_FACTOR)) {
    if (th_oa_table_increase(table) == false)
      return false;
  }

  th_oa_entry_t *entry = th_oa_table_find(table, key);

  if (entry->key == NULL) {
    if (entry->is_tombstone == false)
      table->count++;
  } else {
    free(entry->key);
  }

  entry->key = malloc(sizeof(th_key_t));
  *entry->key = *key;
  entry->value = value;
  entry->is_tombstone = false;

  return true;
}

bool th_oa_table_put(th_generic_table_t generic_table, th_any_t data,
                     size_t data_size, th_any_t value) {
  th_oa_table_t *table = (th_oa_table_t *)generic_table;
  th_key_t key = th_key_create(data, data_size);

  return th_oa_table_put_with_key(table, &key, value);
}

bool th_oa_table_delete(th_generic_table_t generic_table, th_any_t data,
                        size_t data_size) {
  th_oa_table_t *table = (th_oa_table_t *)generic_table;
  if (table->capacity == 0)
    return false;

  th_key_t key = th_key_create(data, data_size);

  th_oa_entry_t *entry = th_oa_table_find(table, &key);
  if (entry->key == NULL)
    return false;

  free(entry->key);

  entry->key = NULL;
  entry->is_tombstone = true;

  return true;
}

void th_oa_table_free(th_generic_table_t generic_table) {
  th_oa_table_t *table = (th_oa_table_t *)generic_table;

  for (int i = 0; i < table->capacity; i++) {
    th_oa_entry_t *entry = &table->entries[i];

    if (entry->key == NULL)
      continue;

    free(entry->key);
  }

  if (table->entries != NULL) {
    free(table->entries);
  }
}
