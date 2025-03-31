/**
 * @file stack_errors.h
 * @brief Error codes for stack operations
 */

#ifndef STACK_ERRORS_H
#define STACK_ERRORS_H

#include <stdio.h>

// Error codes
typedef enum {
    STACK_OK = 0,           // Successful completion
    STACK_NULL_PTR,         // Pointer to NULL passed
    STACK_INVALID_TYPE,     // The stack type could not be determined
    STACK_INVALID_ARGS,     // Invalid arguments
    STACK_ALLOC_FAILED,     // Memory allocation error
    STACK_DATA_COPY_FAILED, // Data copy error (relevant for dynamic stack with deep copying)
    STACK_EMPTY,            // Stack is empty
    STACK_FULL,             // Stack is full
    STACK_NULL_OUT,         // The output variable pointer points to NULL.
    STACK_NULL_DATA,        /* The data pointer is NULL (relevant for a stack with a memory pool
                               and a dynamic stack with deep copying). */
    STACK_UNKNOWN_ERROR,    // Unknown error
} StackError;

// Global variable to store the last error
extern StackError stack_last_error;

extern char *str_errors[];

// Function to get tha last error
StackError stack_get_last_error(void);

// Macro to simplify error checking
#define STACK_CHECK_ERROR(func_call) \
    do { \
        stack_last_error = (func_call); \
        if (stack_last_error != STACK_OK) { \
            fprintf(stderr, "Error in " #func_call": %s\n", str_errors[stack_last_error]); \
            return stack_last_error; \
        } \
    } while (0)

#endif // STACK_ERRORS_H
