add_executable(SeaFlagTests
    test_main.c
)

target_link_libraries(SeaFlagTests PRIVATE SeaFlags)

target_include_directories(SeaFlagTests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include 
)

add_test(NAME RunSeaFlagTests COMMAND SeaFlagTests)
