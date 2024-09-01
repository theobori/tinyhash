#include <stdint.h>
#include <string.h>

#include "../src/open_addressing/table.h"
#include "../src/tinyhash.h"
#include "munit/munit.h"

typedef struct {
  uint32_t a;
  uint8_t b[22];
} TestStruct;

#define SET_GET_ITERATIONS 256 * 256

static th_method_t str_to_method(const char *str) {
  switch (*str) {
  case 'o':
    return TH_OPEN_ADRESSING;
  case 's':
    return TH_SEPARATE_CHAINING;
  }

  return TH_SEPARATE_CHAINING;
}

MunitResult test_th_put_and_get(const MunitParameter params[], void *data) {
  th_any_t value;
  const char *method_str = munit_parameters_get(params, "method");
  th_method_t method = str_to_method(method_str);
  th_t th = th_create(method);

  th_put(&th, "hello", strlen("hello"), (th_any_t)333);

  value = th_get(&th, "hello", strlen("hello"));

  munit_assert_uint64((uint64_t)value, ==, 333);

  th_free(&th);

  return MUNIT_OK;
}

MunitResult test_th_get_with_empty_table(const MunitParameter params[],
                                         void *data) {
  th_any_t value;
  const char *method_str = munit_parameters_get(params, "method");
  th_method_t method = str_to_method(method_str);
  th_t th = th_create(method);

  value = th_get(&th, "hello", strlen("hello"));
  munit_assert_null(value);

  th_free(&th);

  return MUNIT_OK;
}

MunitResult test_th_put_with_full_table(const MunitParameter params[],
                                        void *data) {
  int *value;

  const char *method_str = munit_parameters_get(params, "method");
  th_method_t method = str_to_method(method_str);
  th_t th = th_create(method);

  for (int i = 0; i < SET_GET_ITERATIONS; i++) {
    int *j = malloc(sizeof(i));
    *j = i;

    th_put(&th, j, sizeof(i), j);
  }

  for (int i = 0; i < SET_GET_ITERATIONS; i++) {
    value = (int *)th_get(&th, &i, sizeof(i));
    th_delete(&th, &i, sizeof(i));

    munit_assert_int(*value, ==, i);

    free(value);
  }

  th_put(&th, "b", strlen("b"), (th_any_t)1);
  th_put(&th, "c", strlen("c"), (th_any_t)1);
  th_put(&th, "d", strlen("d"), (th_any_t)1);
  th_put(&th, "e", strlen("e"), (th_any_t)1);
  th_put(&th, "f", strlen("f"), (th_any_t)1);
  th_put(&th, "g", strlen("g"), (th_any_t)1);
  th_put(&th, "h", strlen("h"), (th_any_t)1);
  th_put(&th, "hva", strlen("hva"), (th_any_t)1);
  th_put(&th, "hb", strlen("hb"), (th_any_t)1);

  th_put(&th, "azdaz", strlen("azdaz"), (th_any_t)10);
  value = th_get(&th, "azdaz", strlen("azdaz"));

  munit_assert_int((uint64_t)value, ==, 10);

  th_free(&th);

  return MUNIT_OK;
}

MunitResult test_th_put_overwrite(const MunitParameter params[], void *data) {
  th_any_t value;
  const char *method_str = munit_parameters_get(params, "method");
  th_method_t method = str_to_method(method_str);
  th_t th = th_create(method);

  th_put(&th, "a", strlen("a"), (th_any_t)1);
  th_put(&th, "b", strlen("b"), (th_any_t)1);
  th_put(&th, "a", strlen("a"), (th_any_t)2);

  value = th_get(&th, "a", strlen("a"));

  munit_assert_uint64((uint64_t)value, ==, 2);

  th_free(&th);

  return MUNIT_OK;
}

MunitResult test_th_put_collision(const MunitParameter params[], void *data) {
  th_any_t value;
  const char *method_str = munit_parameters_get(params, "method");
  th_method_t method = str_to_method(method_str);
  th_t th = th_create(method);

  th_put(&th, "b", strlen("b"), (th_any_t)123);
  th_put(&th, "ello", strlen("ello"), (th_any_t)456);

  value = th_get(&th, "b", strlen("b"));
  munit_assert_uint64((uint64_t)value, ==, 123);

  value = th_get(&th, "ello", strlen("ello"));
  munit_assert_uint64((uint64_t)value, ==, 456);

  th_free(&th);

  return MUNIT_OK;
}

MunitResult test_th_put_struct_as_key(const MunitParameter params[],
                                      void *data) {
  th_any_t value;
  TestStruct test_struct;

  memset(&test_struct, 0, sizeof(TestStruct));

  test_struct.b[3] = 222;

  const char *method_str = munit_parameters_get(params, "method");
  th_method_t method = str_to_method(method_str);
  th_t th = th_create(method);

  th_put(&th, &test_struct, sizeof(TestStruct), (th_any_t)123);

  value = th_get(&th, &test_struct, sizeof(TestStruct));
  munit_assert_uint64((uint64_t)value, ==, 123);

  munit_assert_uint8(test_struct.b[3], ==, 222);

  th_free(&th);

  return MUNIT_OK;
}

MunitResult test_th_delete(const MunitParameter params[], void *data) {
  th_any_t value;
  bool ok;

  const char *method_str = munit_parameters_get(params, "method");
  th_method_t method = str_to_method(method_str);
  th_t th = th_create(method);

  char *keys[] = {"a", "b", "bb", "bb", "bbb", "c", "ello"};

  size_t keys_length = sizeof(keys) / sizeof(keys[0]);

  // Insert key value pair
  for (int i = 0; i < keys_length; i++) {
    th_put(&th, keys[i], strlen(keys[i]), (th_any_t)(uint64_t)i + 1);
  }

  // Check everything exists
  for (int i = 0; i < keys_length; i++) {
    value = th_get(&th, keys[i], strlen(keys[i]));
    munit_assert_not_null(value);
  }

  ok = th_delete(&th, "a", strlen("a"));
  munit_assert_true(ok);

  ok = th_delete(&th, "a", strlen("a"));
  munit_assert_false(ok);
  ok = th_delete(&th, "ello", strlen("ello"));
  munit_assert_true(ok);
  ok = th_delete(&th, "bb", strlen("bb"));
  munit_assert_true(ok);
  ok = th_delete(&th, "b", strlen("b"));
  munit_assert_true(ok);
  ok = th_delete(&th, "bbb", strlen("bbb"));
  munit_assert_true(ok);

  value = th_get(&th, "a", strlen("a"));
  munit_assert_null(value);

  // Delete everything
  for (int i = 0; i < keys_length; i++) {
    th_delete(&th, keys[i], strlen(keys[i]));

    value = th_get(&th, keys[i], strlen(keys[i]));
    munit_assert_null(value);
  }

  th_free(&th);

  return MUNIT_OK;
}
