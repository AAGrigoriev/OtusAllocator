cmake_minimum_required(VERSION 3.6)

project(Main)

add_executable(main main.cpp)

target_include_directories(main 
            PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR}/allocator
            ${CMAKE_CURRENT_SOURCE_DIR}/sList
)

set_target_properties(main 
            PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON
)