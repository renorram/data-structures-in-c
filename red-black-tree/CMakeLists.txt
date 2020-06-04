cmake_minimum_required(VERSION 3.15)
project(red_black_tree C)

set(CMAKE_C_STANDARD 99)

add_executable(red_black_tree main.c tree.c tree.h)