#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"
#include "entry.h"
#include "hash.h"
#include "options.h"

void static th_table_put_with_key(th_table_t *table, th_key_t *key,
    th_any_t value);

void th_table_init(th_table_t *table)
{
    table->capacity = 0;
    table->count = 0;
    table->entries = NULL;

    table->options = (th_options_t) {
        .hash_func = th_hash
    };
}

static void th_table_increase(th_table_t *table)
{
    th_table_t new_table;

    th_table_init(&new_table);

    // New capacity
    new_table.capacity = TABLE_NEXT_CAPACITY(table->capacity);

    // New entry array bytes size
    size_t size = sizeof(th_entry_t *) * new_table.capacity;

    new_table.entries = (th_entry_t **) malloc(size);
    memset(new_table.entries, 0, size);

    // Re-compute the new index
    for (int i = 0; i < table->capacity; i++) {
        th_entry_t *entry = table->entries[i];

        while (entry != NULL) {
            th_table_put_with_key(
                &new_table,
                &entry->key,
                entry->value
            );

            entry = entry->next;
        }
    }

    // Destroy the old table
    th_table_destroy(table);

    *table = new_table;
}

static bool th_is_key_equal(th_key_t *first, th_key_t *second)
{
    if (first->size != second->size) return false;

    return memcmp(first->data, second->data, first->size) == 0;
}

static th_entry_t *th_table_find_with_hash(th_table_t *table, th_key_t *key,
    uint32_t hash)
{
    if (table->entries == NULL) return NULL;

    int index = hash % table->capacity;
    th_entry_t *entry = table->entries[index];

    while (entry != NULL) {
        if (th_is_key_equal(key, &entry->key)) {
            return entry;
        }

        entry = entry->next;
    }

    return NULL;
}

static th_entry_t *th_table_find(th_table_t *table, th_key_t *key)
{
    // Avoid division by 0
    if (table->capacity == 0) return NULL;

    return th_table_find_with_hash(table, key, key->hash);
}

th_any_t th_table_get(th_table_t *table, th_any_t data, size_t key_data_size)
{
    th_key_t key = th_key_new(data, key_data_size, table->options.hash_func);
    th_entry_t *entry = th_table_find(table, &key);

    if (entry == NULL) return NULL;
    
    return entry->value;
}

void static th_table_put_with_key(th_table_t *table, th_key_t *key,
    th_any_t value)
{
    if (table->count >= table->capacity) {
        th_table_increase(table);
    }

    th_entry_t *entry = th_table_find_with_hash(table, key, key->hash);

    if (entry == NULL) {
        int index = key->hash % table->capacity;
        th_entry_add(&table->entries[index], key, value);

        table->count++;
    } else {
        entry->value = value;
    }
}

void th_table_put(th_table_t *table, th_any_t data, size_t key_data_size,
    th_any_t value)
{
    th_key_t key = th_key_new(data, key_data_size, table->options.hash_func);

    th_table_put_with_key(table, &key, value);
}

void th_table_destroy(th_table_t *table)
{
    th_entry_t *entry;
    th_entry_t *previous;

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
}
