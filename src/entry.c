#include "entry.h"
#include "hash.h"

#include <string.h>

static th_entry_t *th_entry_new(th_key_t *key, th_any_t value)
{
    th_entry_t *entry = malloc(sizeof(th_entry_t));

    entry->key = *key;
    entry->value = value;
    entry->next = NULL;

    return entry;
}

static void th_entry_raw_add(th_entry_t **root,
    th_entry_t *entry)
{
    entry->next = *root;
    *root = entry;
}

void th_entry_add(th_entry_t **root, th_key_t *key,
    th_any_t value)
{
    th_entry_t *entry = th_entry_new(key, value);
    
    th_entry_raw_add(root, entry);
}

th_key_t th_key_new(th_any_t data, size_t size,
    th_hash_func_t hash_func)
{
    return (th_key_t) {
        .hash = hash_func(data, size),
        .size = size,
        .data = data,
    };
}
