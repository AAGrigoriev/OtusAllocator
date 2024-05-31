cmake_minimum_required(VERSION 3.6)

project(allocator VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
