cmake_minimum_required(VERSION 3.6)

project(googltest)

find_package(GTest REQUIRED)

add_executable(gtest_allocator
    main_test.cpp  
)

target_link_libraries(gtest_allocator PRIVATE ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

target_include_directories(gtest_allocator PRIVATE ${GTEST_INCLUDE_DIRS})

set_target_properties(gtest_allocator PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    gtest_allocator
    PRIVATE
    ${GTEST_INCLUDE_DIRS}
    ${TEST_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_test(gtest_allocator gtest_allocator) # ??? 