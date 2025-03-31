#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_dyn.h"

// Function to copy strings
void* copy_string(const void* data)
{
    if (!data) return NULL;
    return strdup((const char*)data);
}

// Function to clear lines
void destroy_string(void* data)
{
    free(data);
}

int main(void)
{
    StackDyn* stack = NULL;
    const char* fruits[] = {"Apple", "Banana", "Cherry"};
    char* popped = NULL;
    
    printf("=== Dynamic Stack Example ===\n");
    
    // Initialize stack with copy/clear functions
    if (stack_dyn_init(&stack, copy_string, destroy_string) != STACK_OK)
    {
        fprintf(stderr, "Stack initialization failed!\n");
        return EXIT_FAILURE;
    }
    
    // Adding elements to the stack
    printf("Pushing fruits to stack:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("- %s\n", fruits[i]);
        if (stack_dyn_push(stack, fruits[i]) != STACK_OK)
        {
            fprintf(stderr, "Failed to push %s\n", fruits[i]);
            stack_dyn_destroy(stack);
            return EXIT_FAILURE;
        }
    }
    
    // Stack size check
    size_t size = 0;
    stack_dyn_size(stack, &size);
    printf("\nStack size: %zu\n", size);
    
    // Peek top element
    if (stack_dyn_peek(stack, (void**)&popped) == STACK_OK)
        printf("Top element (peek): %s\n", popped);
    
    // Pop all elements from the stack
    printf("\nPopping all elements:\n");
    while (stack_dyn_pop(stack, (void**)&popped) == STACK_OK)
    {
        printf("- %s\n", popped);
        free(popped); // freeing up memory
    }
    
    // Checking stack for emptyness
    bool is_empty = false;
    stack_dyn_is_empty(stack, &is_empty);
    printf("\nStack is empty: %s\n", is_empty ? "true" : "false");
    
    // Clearing and destroying the stack
    stack_dyn_destroy(stack);
    
    return 0;
}
