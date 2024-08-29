#include <stdint.h>
#include <stdlib.h>

#define HASH_INITIAL_VALUE 2166136261u
#define HASH_MUL_VALUE 16777619

uint32_t th_hash(uint8_t *bytes, size_t size)
{
    if (bytes == NULL) return 0;
    
    uint32_t hash = HASH_INITIAL_VALUE;

    for (int i = 0; i < size; i++) {
        hash ^= bytes[i];
        hash *= HASH_MUL_VALUE;
    }

    return hash;
}
