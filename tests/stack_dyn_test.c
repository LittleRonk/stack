#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stack_dyn.h>

// Helper functions for testing
void* copy_string(const void* data) {
    if (!data) return NULL;
    return strdup((const char*)data);
}

void destroy_string(void* data) {
    free(data);
}

void test_stack_dyn_init() {
    printf("Testing stack_dyn_init...\n");
    
    StackDyn* stack = NULL;
    
    // Normal initialization
    assert(stack_dyn_init(&stack, copy_string, destroy_string) == STACK_OK);
    assert(stack != NULL);
    assert(stack->size == 0);
    assert(stack->top == NULL);
    stack_dyn_destroy(stack);
    
    // Initialization without copy/destroy function
    assert(stack_dyn_init(&stack, NULL, NULL) == STACK_OK);
    stack_dyn_destroy(stack);
    
    // Invalid arguments
    assert(stack_dyn_init(NULL, NULL, NULL) == STACK_NULL_PTR);
    assert(stack_dyn_init(&stack, copy_string, NULL) == STACK_INVALID_ARGS);
    
    printf("stack_dyn_init tests passed!\n\n");
}

void test_stack_dyn_push_pop() {
    printf("Testing stack_dyn push/pop...\n");
    
    StackDyn* stack = NULL;
    assert(stack_dyn_init(&stack, copy_string, destroy_string) == STACK_OK);
    
    const char* test_str1 = "Hello";
    const char* test_str2 = "World";
    void* data = NULL;
    
    // Push first element
    assert(stack_dyn_push(stack, test_str1) == STACK_OK);
    assert(stack->size == 1);
    
    // Peek first element
    assert(stack_dyn_peek(stack, &data) == STACK_OK);
    assert(strcmp((char*)data, test_str1) == 0);
    
    // Push second element
    assert(stack_dyn_push(stack, test_str2) == STACK_OK);
    assert(stack->size == 2);
    
    // Pop second element
    assert(stack_dyn_pop(stack, &data) == STACK_OK);
    assert(stack->size == 1);
    assert(strcmp((char*)data, test_str2) == 0);
    destroy_string(data);
    
    // Pop first element
    assert(stack_dyn_pop(stack, &data) == STACK_OK);
    assert(stack->size == 0);
    assert(strcmp((char*)data, test_str1) == 0);
    destroy_string(data);
    
    // Attempt to pop from empty stack
    assert(stack_dyn_pop(stack, &data) == STACK_EMPTY);
    
    // Attempt to push NULL with copy funnction
    assert(stack_dyn_push(stack, NULL) == STACK_NULL_DATA);
    
    stack_dyn_destroy(stack);
    
    // Shallow copy testing (without copy function)
    assert(stack_dyn_init(&stack, NULL, NULL) == STACK_OK);
    int x = 42;
    assert(stack_dyn_push(stack, &x) == STACK_OK);
    assert(stack_dyn_pop(stack, &data) == STACK_OK);
    assert(*(int*)data == x);
    
    stack_dyn_destroy(stack);
    printf("stack_dyn push/pop tests passed!\n\n");
}

void test_stack_dyn_clear_is_empty() {
    printf("Testing stack_dyn clear/is_empty...\n");
    
    StackDyn* stack = NULL;
    assert(stack_dyn_init(&stack, copy_string, destroy_string) == STACK_OK);
    
    bool is_empty = false;
    
    // Checking for an empty stack
    assert(stack_dyn_is_empty(stack, &is_empty) == STACK_OK);
    assert(is_empty == true);
    
    // Push elements
    assert(stack_dyn_push(stack, "Test1") == STACK_OK);
    assert(stack_dyn_push(stack, "Test2") == STACK_OK);
    
    // Checking for a non-empty stack
    assert(stack_dyn_is_empty(stack, &is_empty) == STACK_OK);
    assert(is_empty == false);
    
    // Clearing the stack
    assert(stack_dyn_clear(stack) == STACK_OK);
    assert(stack->size == 0);
    assert(stack->top == NULL);
    
    // Check after cleaning
    assert(stack_dyn_is_empty(stack, &is_empty) == STACK_OK);
    assert(is_empty == true);
    
    stack_dyn_destroy(stack);
    printf("stack_dyn clear/is_empty tests passed!\n\n");
}
