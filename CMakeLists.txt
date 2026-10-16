cmake_minimum_required(VERSION 4.1)
project(SDeA)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Common flags
add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(common)
add_subdirectory(ex_binary_search_trees)
