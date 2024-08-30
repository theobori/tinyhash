#include <string.h>

#include "key.h"
#include "hash.h"

th_key_t th_key_new(th_any_t data, size_t size)
{
    return (th_key_t) {
        .hash = th_hash(data, size),
        .size = size,
        .data = data,
    };
}

bool th_key_is_equal(th_key_t *first, th_key_t *second)
{
    if (first->size != second->size) return false;

    return memcmp(first->data, second->data, first->size) == 0;
}
