#include "entry.h"

static th_sc_entry_t *th_sc_entry_new(th_key_t *key, th_any_t value) {
  th_sc_entry_t *entry = malloc(sizeof(th_sc_entry_t));

  if (entry == NULL)
    return NULL;

  entry->key = *key;
  entry->value = value;
  entry->previous = NULL;
  entry->next = NULL;

  return entry;
}

bool th_sc_entry_add(th_sc_entry_t **root, th_key_t *key, th_any_t value) {
  th_sc_entry_t *entry = th_sc_entry_new(key, value);

  if (entry == NULL)
    return false;

  if (*root != NULL)
    (*root)->previous = entry;

  entry->next = *root;
  *root = entry;

  return true;
}
