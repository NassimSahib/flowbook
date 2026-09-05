include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

add_executable(
    Flowbook.Tests
    OrderbookTests.cpp
)

target_link_libraries(
    Flowbook.Tests
    PRIVATE
        Flowbook.Core
        GTest::gtest_main
)

target_compile_features(
    Flowbook.Tests
    PRIVATE
        cxx_std_20
)

include(GoogleTest)

gtest_discover_tests(
    Flowbook.Tests
)