cmake_minimum_required(VERSION 3.24)

project(
    Flowbook
    VERSION 1.0.0
    DESCRIPTION "C++20 limit order book and matching engine"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

add_subdirectory(Flowbook.Core)
add_subdirectory(Flowbook.CLI)

if (BUILD_TESTING)
    add_subdirectory(Flowbook.Tests)
endif()