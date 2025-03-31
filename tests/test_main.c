#include <stdio.h>
#include "test.h"

extern void test_stack_dyn_init(void);

int main() {
    printf("Starting stack tests...\n\n");
    
    // Tests for dynamic stack
    test_stack_dyn_init();
    test_stack_dyn_push_pop();
    test_stack_dyn_clear_is_empty();
    
    // Tests for stack with memory pool
    test_stack_pool_init();
    test_stack_pool_push_pop();
    test_stack_pool_clear_is_empty();
    
    printf("All tests passed successfully!\n");
    return 0;
}
