cmake_minimum_required(VERSION 3.24)
project(YukonGameG6 C)

set(CMAKE_C_STANDARD 11)

# Create a library target for the common source code
add_library(YukonGameG6_lib STATIC main.c)

# Create the main executable
add_executable(YukonGameG6 main.c)

# Link the main executable with the library
target_link_libraries(YukonGameG6 YukonGameG6_lib)

# Create the test executable
add_executable(test_main test_main.c)

# Link the test executable with the library
target_link_libraries(test_main YukonGameG6_lib)

# Add test case
add_test(NAME MyTest COMMAND test_main)
include_directories(include)
