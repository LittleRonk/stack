cmake_minimum_required(VERSION 3.10)

project(stack LANGUAGES C)

# Library for error handing
add_library(stack_errors STATIC ${PROJECT_SOURCE_DIR}/src/stack_errors.c)
target_include_directories(stack_errors PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Library for dynamic stack
add_library(stack_dyn STATIC ${PROJECT_SOURCE_DIR}/src/stack_dyn.c)
target_include_directories(stack_dyn PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(stack_dyn PRIVATE stack_errors)

# Library for stack with mymory pool
add_library(stack_pool STATIC ${PROJECT_SOURCE_DIR}/src/stack_pool.c)
target_include_directories(stack_pool PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(stack_pool PRIVATE stack_errors)

add_library(stack INTERFACE)
target_link_libraries(stack INTERFACE stack_dyn stack_pool)

add_subdirectory(${PROJECT_SOURCE_DIR}/examples)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
