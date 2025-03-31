/**
 * @file stack_dyn.h
 * @brief Implementation of a stack with dynamic memory
 * allocation for elements.
 *
 * User-defined functions are used to copy and free element data.
 */

#ifndef STACK_DYN_H
#define STACK_DYN_H

#include <stddef.h>
#include <stdbool.h>
#include <stack_errors.h>

/**
 * @typedef copy
 * @brief Function pointer type for copying stack elements.
 *
 * @param data Pointer to the data to copy.
 * @return Pointer to the copied data.
 */
typedef void *(*stack_copy_data)(const void *data);

/**
 * @typedef destroy
 * @brief Function pointer type for freeing stack elements.
 *
 * @param data Pointer to the data to free.
 */
typedef void (*stack_destroy_data)(void *data);

// The structure represents a stack node.
typedef struct stack_node {
    void *data;
    struct stack_node *next;
} StNode;

// The structure represents a stack.
typedef struct stack_dyn {
    StNode *top;
    size_t size;
    stack_copy_data copy;
    stack_destroy_data destroy;
} StackDyn;

/**
 * @brief Creates a new stack.
 *
 * If the copy and destroy functions are not passed,
 * then shallow copying (working with pointers) will be used.
 *
 * @param stack Pointer to a pointer of type StackDyn to which
 * to attach the new stack.
 * @param copy Function to copy of data stack elements.
 * @param destroy Function to free data of a stack elements.
 * @return StackError:
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 *          -STACK_INVALID_ARGS: One function (copy or destroy) is passed.
 *          -STACK_ALLOC_FAILED: Memory allocation error.
 */
StackError stack_dyn_init(StackDyn **stack, stack_copy_data copy, stack_destroy_data destroy);

/**
 * @brief Destroys the stack and frees all allocated memory.
 *
 * The caller is responsible for the dangling pointer.
 *
 * @param stack Pointer to the stack.
 * @return StackError:
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 */
StackError stack_dyn_destroy(StackDyn *stack);

/**
 * @brief Removes all stack elements and clears the allocated memory.
 *
 * @param stack Pointer to the stack.
 * @return StackError:
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 */
StackError stack_dyn_clear(StackDyn *stack);

/**
 * @brief Pushes an element onto the stack.
 *
 * @param stack Pointer to the stack.
 * @param data Pointer to the data to push,
 * may be NULL only when working with pointers (shallow copyng),
 * otherwise an add error will occur.
 * @return StackError:
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 *          -STACK_NULL_DATA: The data pointer is NULL.
 *          -STACK_ALLOC_FAILED: Memory allocation error.
 *          -STACK_DATA_COPY_FAILED: Error copying data.
 */
StackError stack_dyn_push(StackDyn *stack, const void *data);

/**
 * @brief Pops an element from the stack.
 *
 * @param stack Pointer to the stack.
 * @param out_data Pointer to a variable into which
 * the retrieved value will be written.
 * @return StackError:
 *          -STACK_OK: The opearation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 *          -STACK_NULL_OUT: The out_data pointer is NULL.
 *          -STACK_EMPTY: The stack is empty.
 */
StackError stack_dyn_pop(StackDyn *stack, void **out_data);

/**
 * @brief Retrieves the top element of the stack without removing it.
 *
 * @param stack Pointer to the stack.
 * @param out_data Pointer to a variable into which
 * the retrieved value will be written.
 * @return StackError:
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stack pointer is NULL.
 *          -STACK_NULL_OUT: The out_data pointer is NULL.
 *          -STACK_EMPTY: The stack is empty.
 */
StackError stack_dyn_peek(const StackDyn *stack, void **out_data);

/**
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
StackError stack_dyn_is_empty(const StackDyn *stack, bool *out_empty);

/**
 * @brief Gets the current size of the stack.
 *
 * @param stack Pointer to the stack.
 * @param out_size Pointer to a variable in which the current stack size
 * will be saved.
 * @return StackError:
 *          -STACK_OK: The operation was successful.
 *          -STACK_NULL_PTR: The stackpointer is NULL.
 *          -STACK_NULL_OUT: The out_size pointer is NULL.
 */
StackError stack_dyn_size(const StackDyn *stack, size_t *out_size);

#endif // STACK_DYN_H
