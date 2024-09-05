#include <stdlib.h>

#include "iterator.h"

static void th_iterator_init(th_iterator_t *it,
                             th_generic_table_t generic_table,
                             th_iterator_next_func_t next) {
  it->index = 0;
  it->key = NULL;
  it->current = NULL;
  it->value = NULL;
  it->generic_table = generic_table;
  it->next = next;
}

th_iterator_t *th_iterator_create(th_generic_table_t generic_table,
                                  th_iterator_next_func_t next) {
  th_iterator_t *it = malloc(sizeof(th_iterator_t));

  if (it == NULL) {
    return NULL;
  }

  th_iterator_init(it, generic_table, next);

  return it;
}

void th_iterator_free(th_iterator_t *it) {
  th_iterator_init(it, NULL, NULL);

  free(it);
}

bool th_iterator_next(th_iterator_t **ptr) {
  th_iterator_t *it = *ptr;

  if (it->next == NULL) {
    return false;
  }

  bool ret = it->next(ptr);

  if (ret == false) {
    th_iterator_free(it);
  }

  return ret;
}
