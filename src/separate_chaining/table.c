#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"

static bool th_sc_table_put_with_key(th_sc_table_t *table, th_key_t *key,
    th_any_t value);

void th_sc_table_init(th_sc_table_t *table)
{
    table->capacity = 0;
    table->count = 0;
    table->entries = NULL;
}

static th_sc_table_t *_th_sc_table_create()
{
    th_sc_table_t *table = malloc(sizeof(th_sc_table_t));

    if (table == NULL) return NULL;

    th_sc_table_init(table);

    return table;
}

th_generic_table_t th_sc_table_create()
{
    return (th_generic_table_t) _th_sc_table_create();
}

static bool th_sc_table_increase(th_sc_table_t *table)
{
    th_sc_table_t new_table;

    th_sc_table_init(&new_table);

    // New capacity
    new_table.capacity = TH_SC_TABLE_NEXT_CAPACITY(table->capacity);

    // New entry array bytes size
    size_t size = sizeof(th_sc_entry_t *) * new_table.capacity;

    new_table.entries = (th_sc_entry_t **) malloc(size);
    if (new_table.entries == NULL) return false;

    memset(new_table.entries, 0, size);

    // Re-compute the new index
    for (int i = 0; i < table->capacity; i++) {
        bool success;
        th_sc_entry_t *entry = table->entries[i];

        while (entry != NULL) {
            success = th_sc_table_put_with_key(
                &new_table,
                &entry->key,
                entry->value
            );

            if (success == false) return false;

            entry = entry->next;
        }
    }

    // Destroy the old table
    th_sc_table_free((th_generic_table_t) table);

    *table = new_table;

    return true;
}

static th_sc_entry_t *th_sc_table_find(th_sc_table_t *table, th_key_t *key)
{
    // Avoid division by 0
    if (table->capacity == 0) return NULL;
    
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
    size_t data_size)
{
    th_sc_table_t *table = (th_sc_table_t *) generic_table;
    th_key_t key = th_key_create(data, data_size);

    th_sc_entry_t *entry = th_sc_table_find(table, &key);
    if (entry == NULL) return NULL;
    
    return entry->value;
}

static bool th_sc_table_put_with_key(th_sc_table_t *table, th_key_t *key,
    th_any_t value)
{
    if (table->count >= table->capacity) {
        if (th_sc_table_increase(table) == false) return false;
    }

    th_sc_entry_t *entry = th_sc_table_find(table, key);

    if (entry == NULL) {
        int index = key->hash % table->capacity;
        th_sc_entry_t **bucket = &table->entries[index];

        if (*bucket == NULL) table->count++;
        if (th_sc_entry_add(bucket, key, value) == false) return false;
    } else {
        entry->value = value;
    }

    return true;
}

bool th_sc_table_put(th_generic_table_t generic_table, th_any_t data,
    size_t data_size, th_any_t value)
{
    th_sc_table_t *table = (th_sc_table_t *) generic_table;
    th_key_t key = th_key_create(data, data_size);

    return th_sc_table_put_with_key(table, &key, value);
}

bool th_sc_table_delete(th_generic_table_t generic_table, th_any_t data,
    size_t data_size)
{
    th_sc_table_t *table = (th_sc_table_t *) generic_table;
    th_key_t key = th_key_create(data, data_size);

    th_sc_entry_t *entry = th_sc_table_find(table, &key);
    if (entry == NULL) return false;

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

void th_sc_table_free(th_generic_table_t generic_table)
{
    th_sc_table_t *table = (th_sc_table_t *) generic_table;
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
}
