# Stack Implementations in C

This project provides two efficient stack implementations in C:
1. **Dynamic Stack** (`stack_dyn`) - with dynamic memory allocation for elements
2. **Memory Pool Stack** (`stack_pool`) - with fixed-size memory blocks for fast access

## Key Features

- Fully documented code (Doxygen-style)
- Comprehensive error handling (11 error types)
- Unit tests for all components
- Usage examples for each implementation
- Cross-platform compatibility (C11 standard)
- Support for custom copy/destroy functions

## Project Structure
stack-project/
├── include/ # Header files
│ ├── stack_dyn.h # Dynamic stack interface
│ ├── stack_pool.h # Memory pool stack interface
│ └── stack_errors.h # Error handling system
├── src/ # Source code
│ ├── stack_dyn.c # Dynamic stack implementation
│ ├── stack_pool.c # Memory pool stack implementation
│ └── stack_errors.c # Error handling implementation
├── tests/ # Unit tests
├── examples/ # Usage examples
├── CMakeLists.txt # Main build file
└── README.md # This file


## Requirements

- C compiler with C11 support (GCC, Clang, MSVC)
- CMake ≥ 3.10
- For tests: CTest (bundled with CMake)

## Build and Installation

```bash
# Clone repository
git clone https://github.com/LittleRonk/stack.git
cd stack

# Build project
mkdir build && cd build
cmake ..
make
```

## Usage Examples

### Dynamic Stack

```c
#include "stack_dyn.h"

void* copy_int(const void* data) {
    int* copy = malloc(sizeof(int));
    *copy = *(const int*)data;
    return copy;
}

int main() {
    StackDyn* stack;
    stack_dyn_init(&stack, copy_int, free);
    
    int value = 42;
    stack_dyn_push(stack, &value);
    
    int* popped;
    stack_dyn_pop(stack, (void**)&popped);
    printf("Popped: %d\n", *popped);
    free(popped);
    
    stack_dyn_destroy(stack);
}
```

### Memory Pool Stack

```c
#include "stack_pool.h"

typedef struct {
    char name[20];
    double price;
} Product;

int main() {
    StackPool* stack;
    stack_pool_init(&stack, 100, sizeof(Product));
    
    Product apple = {"Apple", 1.99};
    stack_pool_push(stack, &apple);
    
    Product item;
    stack_pool_pop(stack, &item);
    printf("Got %s for $%.2f\n", item.name, item.price);
    
    stack_pool_destroy(stack);
}
```

## API Documentation

### Common Functions (all stack)

- **stack_get_last_error**: Get last error code
- **str_errors[]**: Array of error descriptions

### Dynamic Stack API

```c
StackError stack_dyn_init(StackDyn** stack, stack_copy_data copy, stack_destroy_data destroy);
StackError stack_dyn_push(StackDyn* stack, const void* data);
StackError stack_dyn_pop(StackDyn* stack, void** out_data);
StackError stack_dyn_peek(const StackDyn* stack, void** out_data);
StackError stack_dyn_is_empty(const StackDyn* stack, bool* out_empty);
StackError stack_dyn_size(const StackDyn* stack, size_t* out_size);
StackError stack_dyn_clear(StackDyn* stack);
StackError stack_dyn_destroy(StackDyn* stack);
```

# Memory Pool Stack API

```c
StackError stack_pool_init(StackPool** stack, size_t capacity, size_t block_size);
StackError stack_pool_push(StackPool* stack, const void* data);
StackError stack_pool_pop(StackPool* stack, void* out_data);
StackError stack_pool_peek(const StackPool* stack, void* out_data);
StackError stack_pool_is_empty(const StackPool* stack, bool* out_empty);
StackError stack_pool_size(const StackPool* stack, size_t* out_size);
StackError stack_pool_clear(StackPool* stack);
StackError stack_pool_destroy(StackPool* stack);
```
