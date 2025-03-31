#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stack_pool.h>

StackError stack_pool_init(StackPool **stack, size_t capacity, size_t block_size)
{
    if (!stack)
    {
        stack_last_error = STACK_NULL_PTR;
        return STACK_NULL_PTR;
    }

    if ((capacity == 0) || (block_size == 0))
    {
        stack_last_error = STACK_INVALID_ARGS;
        return STACK_INVALID_ARGS;
    }

    StackPool *new_stack = calloc(1, sizeof(StackPool));
    if (!new_stack)
    {
        stack_last_error = STACK_ALLOC_FAILED;
        return STACK_ALLOC_FAILED;
    }

    byte (*pool)[block_size] = calloc(capacity, block_size);
    if (!pool)
        goto pool_allocation_error;

    new_stack->pool = pool;
    new_stack->top = pool;
    new_stack->capacity = capacity;
    new_stack->block_size = block_size;
    new_stack->size = 0;
    *stack = new_stack;

    stack_last_error = STACK_OK;
    return STACK_OK;


    pool_allocation_error:
        free(new_stack);

    stack_last_error = STACK_ALLOC_FAILED;
    return STACK_ALLOC_FAILED;
}

StackError stack_pool_clear(StackPool *stack)
{
    if (!stack)
    {
        stack_last_error = STACK_NULL_PTR;
        return STACK_NULL_PTR;
    }

    stack->top = stack->pool;
    stack->size = 0;

    stack_last_error = STACK_OK;
    return STACK_OK;
}

StackError stack_pool_destroy(StackPool *stack)
{
    if (!stack)
    {
        stack_last_error = STACK_NULL_PTR;
        return STACK_NULL_PTR;
    }
    
    free(stack->pool);
    free(stack);

    stack_last_error = STACK_OK;
    return STACK_OK;
}

StackError stack_pool_push(StackPool *stack, const void *data)
{
    if (!stack)
    {
        stack_last_error = STACK_NULL_PTR;
        return STACK_NULL_PTR;
    }

    if (!data)
    {
        stack_last_error = STACK_NULL_DATA;
        return STACK_NULL_DATA;
    }

    if (stack->size == stack->capacity)
    {
        stack_last_error = STACK_FULL;
        return STACK_FULL;
    }

    if (stack->size)
        stack->top = stack->top + stack->block_size;

    byte *block = stack->top;
    byte *data_byte = (void *) data;
    for (int i = 0; i < stack->block_size; ++i)
        *(block + i) = *(data_byte +i);

    ++stack->size;

    stack_last_error = STACK_OK;
    return STACK_OK;
}

StackError stack_pool_pop(StackPool *stack, void *out_data)
{
    if (!stack)
    {
        stack_last_error = STACK_NULL_PTR;
        return STACK_NULL_PTR;
    }

    if (!out_data)
    {
        stack_last_error = STACK_NULL_OUT;
        return STACK_NULL_OUT;
    }

    if (stack->size == 0)
    {
        stack_last_error = STACK_EMPTY;
        return STACK_EMPTY;
    }

    byte *block = (byte *) stack->top;
    byte *output = (byte *) out_data;
    for (int i = 0; i < stack->block_size; ++i)
        *(output + i) = *(block + i);

    if (stack->size > 1)
        stack->top = stack->top - stack->block_size;

    --stack->size;

    stack_last_error = STACK_OK;
    return STACK_OK;
}

StackError stack_pool_peek(const StackPool *stack, void *out_data)
{
    if (!stack)
    {
        stack_last_error = STACK_NULL_PTR;
        return STACK_NULL_PTR;
    }

    if (!out_data)
    {
        stack_last_error = STACK_NULL_OUT;
        return STACK_NULL_OUT;
    }

    if (stack->size == 0)
    {
        stack_last_error = STACK_EMPTY;
        return STACK_EMPTY;
    }

    byte *block = (byte *) stack->top;
    byte *output = (byte *) out_data;
    for (int i = 0; i < stack->block_size; ++i)
        *(output + i) = *(block + i);

    stack_last_error = STACK_OK;
    return STACK_OK;
}

StackError stack_pool_is_empty(const StackPool *stack, bool *out_empty)
{
    if (!stack)
    {
        stack_last_error = STACK_NULL_PTR;
        return STACK_NULL_PTR;
    }

    if (!out_empty)
    {
        stack_last_error = STACK_NULL_OUT;
        return STACK_NULL_OUT;
    }

    *out_empty = stack->size == 0;

    stack_last_error = STACK_OK;
    return STACK_OK;
}

StackError stack_pool_size(const StackPool *stack, size_t *out_size)
{
    if (!stack)
    {
        stack_last_error = STACK_NULL_PTR;
        return STACK_NULL_PTR;
    }

    if (!out_size)
    {
        stack_last_error = STACK_NULL_OUT;
        return STACK_NULL_OUT;
    }

    *out_size = stack->size;

    stack_last_error = STACK_OK;
    return STACK_OK;
}
