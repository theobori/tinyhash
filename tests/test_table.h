#ifndef __TINYHASH_TEST_TABLE_H__
#define __TINYHASH_TEST_TABLE_H__

#include "munit/munit.h"

MunitResult test_th_table_put_and_get(const MunitParameter params[], void* data);
MunitResult test_th_table_get_with_empty_table(const MunitParameter params[], void* data);
MunitResult test_th_table_put_with_full_table(const MunitParameter params[], void* data);
MunitResult test_th_table_put_overwrite(const MunitParameter params[], void* data);
MunitResult test_th_table_put_collision(const MunitParameter params[], void* data);
MunitResult test_th_table_put_struct_as_key(const MunitParameter params[], void* data);

#endif
