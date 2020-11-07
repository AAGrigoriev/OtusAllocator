cmake_minimum_required(VERSION 3.6)

project(allocator)

set(HEADER otusAllocator.hpp)

set_target_properties( allocator 
                       PROPERTIES
                       CXX_STANDARD 14
                       CXX_STANDARD_REQUIRED ON
)

