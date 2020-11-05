cmake_minimum_required(VERSION 3.6)

project(allocator)

add_executable(main otusAllocator.cpp otusAllocator.hpp)

set_target_properties(main 
PROPERTIES
CXX_STANDARD 17
CXX_STANDARD_REQUIRED ON
)