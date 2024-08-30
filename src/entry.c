#include "entry.h"

static th_entry_t *th_entry_new(th_key_t *key, th_any_t value)
{
    th_entry_t *entry = malloc(sizeof(th_entry_t));

    if (entry == NULL) return NULL;

    entry->key = *key;
    entry->value = value;
    entry->previous = NULL;
    entry->next = NULL;

    return entry;
}

static void th_entry_raw_add(th_entry_t **root, th_entry_t *entry)
{
    if (*root != NULL) {
        (*root)->previous = entry;
    }

    entry->next = *root;
    *root = entry;
}

bool th_entry_add(th_entry_t **root, th_key_t *key, th_any_t value)
{
    th_entry_t *entry = th_entry_new(key, value);

    if (entry == NULL) return false;
    
    th_entry_raw_add(root, entry);

    return true;
}
