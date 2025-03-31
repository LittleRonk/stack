/**
 * @file stack_pool.h
 *
 * @brief Implementation of a stack with a memory pool
 * and fixed-size blocks.
 */

#ifndef STACK_POOL_H
#define STACK_POOL_H

#include <stddef.h>
#include <stdbool.h>
#include <stack_errors.h>


// Represents the minimum memory addressing cell (1 byte)
typedef unsigned char byte;

//Definition of the stack structure with a memory pool
typedef struct {
    void *pool;         // Pointer to the beginning of the memory pool
    void *top;          // Stack top pointer
    size_t capacity;    // Maximum capacity
    size_t block_size;  // The size of one element in bytes
    size_t size;        // Number of stack elements
} StackPool;

/**
 * @brief Creates a stack with a memory pool.
 *
 * @param stack Pointer to a pointer of type StackPool
 * to bind to the new stack.
 * @param capacity Number of elements the stack can hold.
 * @param block_size The size of one element in bytes.
 * @return StackError:
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 *          -STACK_INVALID_ARGS: The capacity parameter or the block_size parameter is zero.
 *          -STACK_ALLOC_FAILED: Failed to allocate the required memory.
 */
StackError stack_pool_init(StackPool **stack, size_t capacity, size_t block_size);

/*
 * @brief Clears the stack.
 *
 * @param stack: Pointer to the stack.
 * @return StackError:
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 */
StackError stack_pool_clear(StackPool *stack);

/*
 * @brief Destroys the stack and frees all allocated memory.
 *
 * The caller is responsible for the danding pointer itself.
 *
 * @param stack Pointer to the stack.
 * @return StackError:
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 */
StackError stack_pool_destroy(StackPool *stack);

/*
 * @brief Pushes an element onto the stack.
 *
 * @param stack Pointer to the stack.
 * @param data Pointer to the data.
 * @return StackError:
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 *          -STACK_NULL_DATA: The data pointer is NULL.
 *          -STACK_FULL: The stack is full.
 */
StackError stack_pool_push(StackPool *stack, const void *data);

/*
 * @brief Pops an element from the stack.
 *
 * @param stack Pointer to the stack.
 * @param out_data Pointer to a variable into which
 * the extracted value will be written.
 * @return StackError: 
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 *          -STACK_NULL_OUT: The out_data pointer is NULL.
 *          -STACK_EMPTY: The stack is empty.
 */
StackError stack_pool_pop(StackPool *stack, void *out_data);

/*
 * @brief Retrieves the top element of the stack without removing it.
 *
 * @param stack Pointer to the stack
 * @param out_data Pointer to a variable into which
 * the retrieved value will be written.
 * @return StackError:
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 *          -STACK_NULL_OUT: The out_data pointer is NULL.
 *          -STACK_EMPTY: The stack is empty.
 */
StackError stack_pool_peek(const StackPool *stack, void *out_data);

/*
 * @brief Checks if the stack is empty.
 *
 * @param stack Pointer to the stack.
 * @param out_empty Pointer to a boolean variable to store
 * the return value.
 * @return StackError:
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 *          -STACK_NULL_OUT: The out_empty pointer is NULL.
 */
StackError stack_pool_is_empty(const StackPool *stack, bool *out_empty);

/*
 * @brief Gets the current size of the stack.
 *
 * @param stack Pointer to the stack
 * @param out_size Pointer to a variable in which the current stack
 * size will be saved.
 * @return StackError:
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 *          -STACK_NULL_OUT: The out_size pointer is NULL.
 */
StackError stack_pool_size(const StackPool *stack, size_t *out_size);

#endif // STACK_POOL_H

