add_library(
    Flowbook.Core
    STATIC
)

target_sources(
    Flowbook.Core
    PRIVATE
        Orderbook.cpp
)

target_include_directories(
    Flowbook.Core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(
    Flowbook.Core
    PUBLIC
        cxx_std_20
)

find_package(Threads REQUIRED)

target_link_libraries(
    Flowbook.Core
    PUBLIC
        Threads::Threads
)

if(MSVC)
    target_compile_options(
        Flowbook.Core
        PRIVATE
            /W4
    )
else()
    target_compile_options(
        Flowbook.Core
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
endif()