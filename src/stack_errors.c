#include <stack_errors.h>

char *str_errors[] = {
    "STACK_OK",
    "STACK_NULL_PTR",
    "STACK_INVALID_TYPE",
    "STACK_INVALID_ARGS",
    "STACK_ALLOC_FAILED",
    "STACK_DATA_COPY_FAILED",
    "STACK_EMPTY",
    "STACK_FULL",
    "STACK_NULL_OUT",
    "STACK_NULL_DATA",
    "STACK_UNKNOWN_ERROR",
};

// Global variable to store the last error
StackError stack_last_error = STACK_OK;

// Function to get last error
StackError stack_get_last_error(void)
{
    return stack_last_error;
}
