cmake_minimum_required(VERSION 3.16)
project(SeaFlags LANGUAGES CXX C)

enable_testing()
add_subdirectory(tests)

add_library(SeaFlags STATIC
    src/seaflags.c
)

target_include_directories(SeaFlags
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
)

install(TARGETS SeaFlags
    ARCHIVE DESTINATION lib       
)

install(DIRECTORY include/
    DESTINATION include
)
