cmake_minimum_required(VERSION 3.24)
project(YukonGameG6 C CXX)

set(CMAKE_C_STANDARD 11)

add_executable(YukonGameG6 main.c TestFunctionsMain.c)

add_subdirectory(/Users/mikkel/Desktop/Cprojekter/YukonGameG6/Googletest/googletest-main)

target_link_libraries(YukonGameG6 gtest_main)



