# Simple C hashmap

This is an implementation of the C hashmap that manages collisions using the ‘Separate chaining’ concept. The public API is deliberately simple and user-friendly.

## 📖 Build and run

For the build, you only need the following requirements:

- [CMake](https://cmake.org/download/) minimum 3.10

To build the library, you can run the following commands.
```sh
mkdir build
cd build
cmake ..
make
```

If you want to install the library, you can run the following command.
```sh
make install
```

The following CMake build arguments are available to enable or disable options.


| Name | Description | Default value |
| -- | -- | -- |
| `-DBUILD_TESTS` | Compile the test files | **`ON`**
| `-DBUILD_STATIC` | Link as a static library (instead of a shared library) | **`OFF`**

## 🤝 Contribute

If you want to help the project, you can follow the guidelines in [CONTRIBUTING.md](./CONTRIBUTING.md).

## 🧪 Tests

Make sure you run CMake with the `-DBUILD_TESTS=ON` flag.
The generated Makefile will contain a special `test` target, so you can run the tests with the following command:

```bash
make test
```

## 📎 Some examples

Here is a basic example of how you could use the hashmap.

```c
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <tinyhash/table.h>

typedef struct {
    char name[10];
    bool is_hydrated;
} Person;

uint32_t custom_hash_function(uint8_t *bytes, size_t size)
{
    return 123456;
}

int main(int argc, const char* argv[])
{
    th_table_t table;
    Person person = { "James", true };

    // Initialize the table
    th_table_init(&table);

    // Insert a new key value pair
    th_table_put(&table, "key_1", strlen("key_1"), &person);

    // Get the last inserted value
    Person *james;
    james = th_table_get(&table, "key_1", strlen("key_1"));
    if (james == NULL) {
        fprintf(stderr, "Unable to get value from key_1");
        return 1;
    }

    printf("name -> %s, is_hydrated -> %d\n", james->name, james->is_hydrated);

    // Feel free to change the hash function
    table.options.hash_func = custom_hash_function;

    // Free the allocated memory
    th_table_destroy(&table);

    return 0;
}

```
