add_executable(
    Flowbook.CLI
    main.cpp
)

target_link_libraries(
    Flowbook.CLI
    PRIVATE
        Flowbook.Core
)

target_compile_features(
    Flowbook.CLI
    PRIVATE
        cxx_std_20
)