#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"
#include "entry.h"

static bool th_table_put_with_key(th_table_t *table, th_key_t *key,
    th_any_t value);

void th_table_init(th_table_t *table)
{
    table->capacity = 0;
    table->count = 0;
    table->entries = NULL;
}

static bool th_table_increase(th_table_t *table)
{
    th_table_t new_table;

    th_table_init(&new_table);

    // New capacity
    new_table.capacity = TH_TABLE_NEXT_CAPACITY(table->capacity);

    // New entry array bytes size
    size_t size = sizeof(th_entry_t *) * new_table.capacity;

    new_table.entries = (th_entry_t **) malloc(size);

    if (new_table.entries == NULL) return false;

    memset(new_table.entries, 0, size);

    // Re-compute the new index
    for (int i = 0; i < table->capacity; i++) {
        bool success;
        th_entry_t *entry = table->entries[i];

        while (entry != NULL) {
            success = th_table_put_with_key(
                &new_table,
                &entry->key,
                entry->value
            );

            if (success == false) return false;

            entry = entry->next;
        }
    }

    // Destroy the old table
    th_table_free(table);

    *table = new_table;

    return true;
}

static th_entry_t *th_table_find(th_table_t *table, th_key_t *key)
{
    // Avoid division by 0
    if (table->capacity == 0) return NULL;
    
    int index = key->hash % table->capacity;
    th_entry_t *entry = table->entries[index];

    while (entry != NULL) {
        if (th_key_is_equal(key, &entry->key)) {
            return entry;
        }

        entry = entry->next;
    }

    return NULL;
}

th_any_t th_table_get(th_table_t *table, th_any_t data, size_t key_data_size)
{
    th_key_t key = th_key_new(data, key_data_size);
    th_entry_t *entry = th_table_find(table, &key);

    if (entry == NULL) return NULL;
    
    return entry->value;
}

static bool th_table_put_with_key(th_table_t *table, th_key_t *key,
    th_any_t value)
{
    if (table->count >= table->capacity) {
        bool success = th_table_increase(table);
        if (success == false) return false;
    }

    th_entry_t *entry = th_table_find(table, key);

    if (entry == NULL) {
        int index = key->hash % table->capacity;
        th_entry_t **bucket = &table->entries[index];

        if (*bucket == NULL) table->count++;

        bool success = th_entry_add(bucket, key, value);
        if (success == false) return false;
    } else {
        entry->value = value;
    }

    return true;
}

bool th_table_put(th_table_t *table, th_any_t data, size_t key_data_size,
    th_any_t value)
{
    th_key_t key = th_key_new(data, key_data_size);

    return th_table_put_with_key(table, &key, value);
}

bool th_table_delete(th_table_t *table, th_any_t data, size_t key_data_size)
{
    th_key_t key = th_key_new(data, key_data_size);
    th_entry_t *entry = th_table_find(table, &key);

    if (entry == NULL) return false;

    int index = entry->key.hash % table->capacity;
    th_entry_t **bucket = &table->entries[index];
    
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

void th_table_free(th_table_t *table)
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
