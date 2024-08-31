#include "tinyhash.h"
#include "./separate_chaining/table.h"

static th_funcs_t th_funcs[] = {
    [TH_SEPARATE_CHAINING] = {
        .create = th_sc_table_create,
        .get = th_sc_table_get,
        .put = th_sc_table_put,
        ._delete = th_sc_table_delete,
        ._free = th_sc_table_free,
    },

    [TH_OPEN_ADRESSING] = {
        .create = NULL,
        .get = NULL,
        .put = NULL,
        ._delete = NULL,
        ._free = NULL,
    },
};

th_t th_create(th_kind_t kind)
{
    th_funcs_t funcs = th_funcs[kind];

    return (th_t) {
        .kind = kind,
        .funcs = funcs,
        .table = funcs.create(),
    };
}

th_t th_create_default()
{
    return th_create(TH_SEPARATE_CHAINING);
}

th_any_t th_get(th_t *th, th_any_t data, size_t data_size)
{
    return th->funcs.get(th->table, data, data_size);
}

bool th_put(th_t *th, th_any_t data, size_t data_size, th_any_t value)
{
    return th->funcs.put(th->table, data, data_size, value);
}

bool th_delete(th_t *th, th_any_t data, size_t data_size)
{
    return th->funcs._delete(th->table, data, data_size);
}

void th_free(th_t *th)
{
    th->funcs._free(th->table);

    free(th->table);
}
