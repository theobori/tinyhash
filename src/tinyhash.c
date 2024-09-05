#include "tinyhash.h"

#include "./open_addressing/table.h"
#include "./separate_chaining/table.h"

/**
 * @brief Static array containing functions that accomplish hashmap operation
 * associated with an implementation method.
 *
 */
static th_funcs_t th_funcs[] = {
    [TH_SEPARATE_CHAINING] =
        {
            .create = th_sc_table_create,
            .get = th_sc_table_get,
            .put = th_sc_table_put,
            ._delete = th_sc_table_delete,
            ._free = th_sc_table_free,
            .begin_iterator = th_sc_iterator_begin,
            .len = th_sc_table_len,
        },

    [TH_OPEN_ADRESSING] =
        {
            .create = th_oa_table_create,
            .get = th_oa_table_get,
            .put = th_oa_table_put,
            ._delete = th_oa_table_delete,
            ._free = th_oa_table_free,
            .begin_iterator = th_oa_iterator_begin,
            .len = th_oa_table_len,
        },
};

static size_t th_funcs_length = sizeof(th_funcs) / sizeof(th_funcs[0]);

th_t th_create_default() { return th_create(TH_SEPARATE_CHAINING); }

th_t th_create(th_method_t method) {
  if (method < 0 || method >= th_funcs_length) {
    return th_create_default();
  }

  th_funcs_t funcs = th_funcs[method];

  return (th_t){
      .method = method,
      .funcs = funcs,
      .table = funcs.create(),
  };
}

th_any_t th_get(th_t *th, th_any_t data, size_t data_size) {
  return th->funcs.get(th->table, data, data_size);
}

bool th_put(th_t *th, th_any_t data, size_t data_size, th_any_t value) {
  return th->funcs.put(th->table, data, data_size, value);
}

bool th_delete(th_t *th, th_any_t data, size_t data_size) {
  return th->funcs._delete(th->table, data, data_size);
}

void th_clear(th_t *th) { th->funcs._free(th->table); }

void th_free(th_t *th) {
  th->funcs._free(th->table);

  free(th->table);
}

th_iterator_t *th_begin_iterator(th_t *th) {
  return th->funcs.begin_iterator(th->table, true);
}

th_iterator_t *th_empty_iterator(th_t *th) {
  return th->funcs.begin_iterator(th->table, false);
}

int th_len(th_t *th) { return th->funcs.len(th->table); }
