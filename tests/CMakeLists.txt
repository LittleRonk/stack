add_executable(stack_tests
    test_main.c
    stack_dyn_test.c
    stack_pool_test.c)

target_link_libraries(stack_tests PRIVATE stack)

enable_testing()

add_test(NAME stack_tests
    COMMAND stack_tests)
