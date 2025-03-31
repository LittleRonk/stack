#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stack_dyn.h>

StackError stack_dyn_init(StackDyn **stack, stack_copy_data copy, stack_destroy_data destroy)
{
    if (!stack)
    {
        stack_last_error = STACK_NULL_PTR;
        return STACK_NULL_PTR;
    }

    if ((!copy && destroy) || (copy && !destroy))
    {
        stack_last_error = STACK_INVALID_ARGS;
        return STACK_INVALID_ARGS;
    }

    StackDyn *new_stack = calloc(1, sizeof(StackDyn));
    if (!new_stack)
    {
        stack_last_error = STACK_ALLOC_FAILED;
        return STACK_ALLOC_FAILED;
    }

    new_stack->top = NULL;
    new_stack->size = 0;
    new_stack->copy = copy;
    new_stack->destroy = destroy;
    *stack = new_stack;

    stack_last_error = STACK_OK;
    return STACK_OK;
}

StackError stack_dyn_push(StackDyn *stack, const void *data)
{
    if (!stack)
    {
        stack_last_error = STACK_NULL_PTR;
        return STACK_NULL_PTR;
    }

    if (stack->copy && !data)
    {
        stack_last_error = STACK_NULL_DATA;
        return STACK_NULL_DATA;
    }

    StNode *new_node = calloc(1, sizeof(StNode));
    if (!new_node)
    {
        stack_last_error = STACK_ALLOC_FAILED;
        return STACK_ALLOC_FAILED;
    }

    if (stack->copy)
    {
        new_node->data = stack->copy(data);
        if (!new_node->data)
        {
            free(new_node);
            stack_last_error = STACK_DATA_COPY_FAILED;
            return STACK_DATA_COPY_FAILED;
        }
    }
    else
        new_node->data = (void *) data;

    new_node->next = stack->top;
    stack->top = new_node;
    ++stack->size;

    stack_last_error = STACK_OK;
    return STACK_OK;
}

StackError stack_dyn_pop(StackDyn *stack, void **out_data)
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

    StNode *node = stack->top;
    stack->top = node->next;

    *out_data = (void *) node->data;
    free(node);
    --stack->size;

    stack_last_error = STACK_OK;
    return STACK_OK;
}

StackError stack_dyn_peek(const StackDyn *stack, void **out_data)
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

    *out_data = (void *) stack->top->data;

    stack_last_error = STACK_OK;
    return STACK_OK;
}

StackError stack_dyn_is_empty(const StackDyn *stack, bool *out_empty)
{
    if (!stack)
    {
        stack_last_error = STACK_NULL_PTR;
        return STACK_NULL_PTR;
    }

    if(!out_empty)
    {
        stack_last_error = STACK_NULL_OUT;
        return STACK_NULL_OUT;
    }

    *out_empty = stack->size == 0;
    stack_last_error = STACK_OK;
    return STACK_OK;
}

StackError stack_dyn_size(const StackDyn *stack, size_t *out_size)
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

StackError stack_dyn_clear(StackDyn *stack)
{
    if (!stack)
    {
        stack_last_error = STACK_NULL_PTR;
        return STACK_NULL_PTR;
    }

    StNode *node = stack->top;
    StNode *temp = NULL;

    while (node)
    {
        temp = node;
        node = node->next;

        if (stack->destroy)
            stack->destroy(temp->data);
        free(temp);
    }

    stack->top = NULL;
    stack->size = 0;

    stack_last_error = STACK_OK;
    return STACK_OK;
}

StackError stack_dyn_destroy(StackDyn *stack)
{
    if (!stack)
    {
        stack_last_error = STACK_NULL_PTR;
        return STACK_NULL_PTR;
    }

    stack_dyn_clear(stack);
    free(stack);

    stack_last_error = STACK_OK;
    return STACK_OK;
}
