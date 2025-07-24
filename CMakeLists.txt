cmake_minimum_required(VERSION 3.22.1)

project(cache-algorithms)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_compile_options(-Wall -Wextra -g -Werror)

add_subdirectory(../data-structures data-structures EXCLUDE_FROM_ALL)
add_subdirectory(source)

target_link_libraries(lru-cache PUBLIC doubly-linked-list hash-table)
target_include_directories(lru-cache PUBLIC data-structures/include include)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
     enable_testing()
     add_subdirectory(test)
     target_link_libraries(lru-cache-test PUBLIC lru-cache)
endif()
