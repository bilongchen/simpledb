cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")

project(
    SimpleDB
    VERSION 2022.10
    DESCRIPTION "Building simpledb for learning purpose"
    LANGUAGES C CXX
)

set(SIMPLEDB_BUILD_SUPPORT_DIR, "${CMAKE_SOURCE_DIR}/build_support")
set(SIMPLEDB_CLANG_SEARCH_PATH "/usr/local/bin" "/usr/bin")

enable_testing()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-unused-parameter -Wno-attributes")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb -fno-omit-frame-pointer -fno-optimize-sibling-calls")

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SIMPLEDB_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)
set(SIMPLEDB_TEST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/test/include)
set(SIMPLEDB_THIRD_PARTY_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/third_party)

include_directories(${SIMPLEDB_SRC_INCLUDE_DIR} ${SIMPLEDB_TEST_INCLUDE_DIR} ${SIMPLEDB_THIRD_PARTY_INCLUDE_DIR})
include_directories(BEFORE src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(third_party)

string(CONCAT SIMPLEDB_FORMAT_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/src,"
        "${CMAKE_CURRENT_SOURCE_DIR}/test,")