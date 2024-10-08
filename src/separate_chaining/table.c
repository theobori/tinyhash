#include "../common/table.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"

static bool th_sc_table_put_with_key(th_sc_table_t *table, th_key_t *key,
                                     th_any_t value);

void th_sc_table_init(th_sc_table_t *table) {
  table->capacity = 0;
  table->count = 0;
  table->entries = NULL;
}

/**
 * @brief Allocate then return a new table.
 *
 * @return th_sc_table_t*
 */
static th_sc_table_t *_th_sc_table_create() {
  th_sc_table_t *table = malloc(sizeof(th_sc_table_t));

  if (table == NULL) {
    return NULL;
  }

  th_sc_table_init(table);

  return table;
}

th_generic_table_t th_sc_table_create() {
  return (th_generic_table_t)_th_sc_table_create();
}

/**
 * @brief Copy and rehash every value from a table to another.
 * Return true on success.
 *
 * @param dest
 * @param src
 * @return true
 * @return false
 */
static bool th_sc_table_copy(th_sc_table_t *dest, th_sc_table_t *src) {
  bool success;

  for (int i = 0; i < src->capacity; i++) {
    th_sc_entry_t *entry = src->entries[i];

    while (entry != NULL) {
      success = th_sc_table_put_with_key(dest, &entry->key, entry->value);

      if (success == false) {
        return false;
      }

      entry = entry->next;
    }
  }

  return true;
}

/**
 * @brief Increase the size of a table.
 *
 * @param table
 * @return true
 * @return false
 */
static bool th_sc_table_increase(th_sc_table_t *table) {
  th_sc_table_t new_table;
  bool success;

  th_sc_table_init(&new_table);

  new_table.capacity = TH_TABLE_NEXT_CAPACITY(table->capacity);

  size_t size = sizeof(th_sc_entry_t *) * new_table.capacity;
  new_table.entries = malloc(size);

  if (new_table.entries == NULL) {
    return false;
  }

  memset(new_table.entries, 0, size);

  success = th_sc_table_copy(&new_table, table);
  if (success == false) {
    return false;
  }

  th_sc_table_free((th_generic_table_t)table);

  *table = new_table;

  return true;
}

/**
 * @brief Returns a bucket (entry) depending on a key.
 * Return NULL if the entry does not exist.
 *
 * @param table
 * @param key
 * @return th_sc_entry_t*
 */
static th_sc_entry_t *th_sc_table_find(th_sc_table_t *table, th_key_t *key) {
  // Avoid division by 0
  if (table->capacity == 0) {
    return NULL;
  }

  int index = key->hash % table->capacity;
  th_sc_entry_t *entry = table->entries[index];

  while (entry != NULL) {
    if (th_key_is_equal(key, &entry->key)) {
      return entry;
    }

    entry = entry->next;
  }

  return NULL;
}

th_any_t th_sc_table_get(th_generic_table_t generic_table, th_any_t data,
                         size_t data_size) {
  th_sc_table_t *table = (th_sc_table_t *)generic_table;
  th_key_t key = th_key_create(data, data_size);

  th_sc_entry_t *entry = th_sc_table_find(table, &key);
  if (entry == NULL) {
    return NULL;
  }

  return entry->value;
}

/**
 * @brief Insert a value within the table with an already existing key.
 *
 * @param table
 * @param key
 * @param value
 * @return true
 * @return false
 */
static bool th_sc_table_put_with_key(th_sc_table_t *table, th_key_t *key,
                                     th_any_t value) {
  if (table->count >= table->capacity) {
    if (th_sc_table_increase(table) == false) {
      return false;
    }
  }

  th_sc_entry_t *entry = th_sc_table_find(table, key);

  if (entry == NULL) {
    int index = key->hash % table->capacity;
    th_sc_entry_t **bucket = &table->entries[index];

    if (*bucket == NULL) {
      table->count++;
    }

    if (th_sc_entry_add(bucket, key, value) == false) {
      return false;
    }
  } else {
    entry->value = value;
  }

  return true;
}

bool th_sc_table_put(th_generic_table_t generic_table, th_any_t data,
                     size_t data_size, th_any_t value) {
  th_sc_table_t *table = (th_sc_table_t *)generic_table;
  th_key_t key = th_key_create(data, data_size);

  return th_sc_table_put_with_key(table, &key, value);
}

bool th_sc_table_delete(th_generic_table_t generic_table, th_any_t data,
                        size_t data_size) {
  th_sc_table_t *table = (th_sc_table_t *)generic_table;
  th_key_t key = th_key_create(data, data_size);

  th_sc_entry_t *entry = th_sc_table_find(table, &key);
  if (entry == NULL) {
    return false;
  }

  int index = entry->key.hash % table->capacity;
  th_sc_entry_t **bucket = &table->entries[index];

  if (entry->next == NULL && entry->previous == NULL) {
    *bucket = NULL;
    table->count--;
  } else if (entry->previous == NULL) {
    *bucket = entry->next;
    (*bucket)->previous = NULL;
  } else if (entry->next == NULL) {
    entry->previous->next = entry->next;
  } else {
    entry->previous->next = entry->next;
    entry->next->previous = entry->previous;
  }

  free(entry);

  return true;
}

void th_sc_table_free(th_generic_table_t generic_table) {
  th_sc_table_t *table = (th_sc_table_t *)generic_table;
  th_sc_entry_t *entry;
  th_sc_entry_t *previous;

  for (int i = 0; i < table->capacity; i++) {
    entry = table->entries[i];

    while (entry != NULL) {
      previous = entry;
      entry = entry->next;

      free(previous);
    }
  }

  if (table->entries != NULL) {
    free(table->entries);
  }

  th_sc_table_init(table);
}

static void th_sc_iterator_copy_entry(th_iterator_t *it, th_sc_entry_t *entry) {
  it->current = entry;
  it->key = &entry->key;
  it->value = entry->value;
}

/**
 * @brief Get the next key value pair if it exists.
 *
 * @param ptr
 * @return true
 * @return false
 */
static bool th_sc_iterator_next(th_iterator_t **ptr) {
  th_iterator_t *it = *ptr;
  th_sc_table_t *table = (th_sc_table_t *)it->generic_table;
  th_sc_entry_t *current = (th_sc_entry_t *)it->current;

  if (current != NULL && current->next != NULL) {
    th_sc_iterator_copy_entry(it, current->next);
    return true;
  }

  it->index++;

  th_sc_entry_t *entry;
  for (; it->index < table->capacity; it->index++) {
    entry = table->entries[it->index];

    if (entry == NULL) {
      continue;
    }

    th_sc_iterator_copy_entry(it, entry);
    return true;
  }

  *ptr = NULL;

  return false;
}

th_iterator_t *th_sc_iterator_begin(th_generic_table_t generic_table,
                                    bool is_begin) {
  th_iterator_t *it = th_iterator_create(generic_table, th_sc_iterator_next);

  if (it == NULL) {
    return NULL;
  }

  it->index--;

  if (is_begin == true) {
    th_sc_iterator_next(&it);
  }

  return it;
}

int th_sc_table_len(th_generic_table_t generic_table) {
  return (((th_sc_table_t *)generic_table)->count);
}
