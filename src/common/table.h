#ifndef __TINYHASH_COMMON_TABLE_H__
#define __TINYHASH_COMMON_TABLE_H__

#define TH_TABLE_NEXT_CAPACITY(capacity) \
    (capacity) == 0 ? 8 : (capacity) * 2

#endif
