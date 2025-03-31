#include <stdio.h>
#include <stdlib.h>
#include "stack_pool.h"

// Structure for demonstrating working with composite types
typedef struct {
    int id;
    char name[20];
    double price;
} Product;

int main()
{
    StackPool* stack = NULL;
    Product products[] = {
        {1, "Laptop", 999.99},
        {2, "Phone", 699.99},
        {3, "Tablet", 399.99}
    };
    Product popped;
    
    printf("=== Memory Pool Stack Example ===\n");
    
    // Initializing a stack with a poool of 5 elements of size Product
    if (stack_pool_init(&stack, 5, sizeof(Product)))
    {
        fprintf(stderr, "Stack initialization failed!\n");
        return EXIT_FAILURE;
    }
    
    // Push elements to a stack
    printf("Pushing products to stack:\n");
    for (int i = 0; i < 3; i++) {
        printf("- %s (ID: %d, $%.2f)\n", 
               products[i].name, products[i].id, products[i].price);
        if (stack_pool_push(stack, &products[i])) {
            fprintf(stderr, "Failed to push product\n");
            stack_pool_destroy(stack);
            return EXIT_FAILURE;
        }
    }
    
    // Checking stack size
    size_t size = 0;
    stack_pool_size(stack, &size);
    printf("\nStack size: %zu (capacity: %zu)\n", size, stack->capacity);
    
    // Peek top element
    if (stack_pool_peek(stack, &popped) == STACK_OK) {
        printf("Top element (peek): %s\n", popped.name);
    }
    
    // Pop all elements from the stack
    printf("\nPopping all elements:\n");
    while (stack_pool_pop(stack, &popped) == STACK_OK) {
        printf("- %s (ID: %d, $%.2f)\n", 
               popped.name, popped.id, popped.price);
    }
    
    // Attempting to pop from an empty stack
    StackError err = stack_pool_pop(stack, &popped);
    printf("\nTrying to pop from empty stack: %s\n", 
           err == STACK_EMPTY ? "EMPTY (correct)" : "WRONG RESULT");
    
    // Clearing and destroying the stack
    stack_pool_destroy(stack);
    
    return EXIT_SUCCESS;
}
