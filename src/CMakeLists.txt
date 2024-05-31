cmake_minimum_required(VERSION 3.6)

project(Main VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})

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


install(TARGETS main RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
