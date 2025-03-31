#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stack_pool.h>

typedef struct {
    int id;
    char name[16];
} TestStruct;

void test_stack_pool_init() {
    printf("Testing stack_pool_init...\n");
    
    StackPool* stack = NULL;
    
    // Normal initialization
    assert(stack_pool_init(&stack, 10, sizeof(int)) == STACK_OK);
    assert(stack != NULL);
    assert(stack->size == 0);
    assert(stack->capacity == 10);
    assert(stack->block_size == sizeof(int));
    stack_pool_destroy(stack);
    
    // Invalid arguments
    assert(stack_pool_init(NULL, 10, sizeof(int)) == STACK_NULL_PTR);
    assert(stack_pool_init(&stack, 0, sizeof(int)) == STACK_INVALID_ARGS);
    assert(stack_pool_init(&stack, 10, 0) == STACK_INVALID_ARGS);
    
    printf("stack_pool_init tests passed!\n\n");
}

void test_stack_pool_push_pop() {
    printf("Testing stack_pool push/pop...\n");
    
    StackPool* stack = NULL;
    assert(stack_pool_init(&stack, 3, sizeof(TestStruct)) == STACK_OK);
    
    TestStruct item1 = {1, "Alice"};
    TestStruct item2 = {2, "Bob"};
    TestStruct item3 = {3, "Charlie"};
    TestStruct out_item;
    
    // Push first element
    assert(stack_pool_push(stack, &item1) == STACK_OK);
    assert(stack->size == 1);
    
    // Peek first element
    assert(stack_pool_peek(stack, &out_item) == STACK_OK);
    assert(out_item.id == item1.id);
    assert(strcmp(out_item.name, item1.name) == 0);
    
    // Push two more elements
    assert(stack_pool_push(stack, &item2) == STACK_OK);
    assert(stack_pool_push(stack, &item3) == STACK_OK);
    assert(stack->size == 3);
    
    // Attempting to push into a full stack
    assert(stack_pool_push(stack, &item1) == STACK_FULL);
    
    // Pop elements (should be retrieved in reverse order)
    assert(stack_pool_pop(stack, &out_item) == STACK_OK);
    assert(stack->size == 2);
    assert(out_item.id == item3.id);
    
    assert(stack_pool_pop(stack, &out_item) == STACK_OK);
    assert(stack->size == 1);
    assert(out_item.id == item2.id);
    
    assert(stack_pool_pop(stack, &out_item) == STACK_OK);
    assert(stack->size == 0);
    assert(out_item.id == item1.id);
    
    // Attempt to pop from empty stack
    assert(stack_pool_pop(stack, &out_item) == STACK_EMPTY);
    
    stack_pool_destroy(stack);
    printf("stack_pool push/pop tests passed!\n\n");
}

void test_stack_pool_clear_is_empty() {
    printf("Testing stack_pool clear/is_empty...\n");
    
    StackPool* stack = NULL;
    assert(stack_pool_init(&stack, 5, sizeof(int)) == STACK_OK);
    
    bool is_empty = false;
    int values[] = {1, 2, 3};
    
    // Checking for a empty stack
    assert(stack_pool_is_empty(stack, &is_empty) == STACK_OK);
    assert(is_empty == true);
    
    // Push elements
    for (int i = 0; i < 3; i++) {
        assert(stack_pool_push(stack, &values[i]) == STACK_OK);
    }
    
    // Checking for a non-empty stack
    assert(stack_pool_is_empty(stack, &is_empty) == STACK_OK);
    assert(is_empty == false);
    
    // Clearing the stack
    assert(stack_pool_clear(stack) == STACK_OK);
    assert(stack->size == 0);
    
    // Check after cleaning
    assert(stack_pool_is_empty(stack, &is_empty) == STACK_OK);
    assert(is_empty == true);
    
    stack_pool_destroy(stack);
    printf("stack_pool clear/is_empty tests passed!\n\n");
}
