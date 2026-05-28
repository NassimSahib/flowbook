cmake_minimum_required(VERSION 3.20)

project(flowbook LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# fmt installed with Homebrew
find_package(fmt REQUIRED)

# Core library
add_library(order_book_lib
    src/order.cpp
    src/price_level.cpp
    src/order_book.cpp
    src/trade.cpp
)

target_include_directories(order_book_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(order_book_lib
    PUBLIC
        fmt::fmt
)

# Warnings
target_compile_options(order_book_lib
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# Demo executable
add_executable(order_book_app
    app/main.cpp
)

target_link_libraries(order_book_app
    PRIVATE
        order_book_lib
)

# GoogleTest
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(order_book_tests
    tests/order_book_tests.cpp
)

target_link_libraries(order_book_tests
    PRIVATE
        order_book_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(order_book_tests)