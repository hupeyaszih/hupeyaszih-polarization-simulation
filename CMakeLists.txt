cmake_minimum_required(VERSION 3.16)

project(hupeyaszih-polarization-simulation LANGUAGES C)

set(CMAKE_C\_STANDARD 11)
set(CMAKE_C\_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(hupeyaszih-polarization-simulation
    src/main.c
    src/logger.c
    src/config.c
    src/argument_parser.c
    src/hstring.c
)

target_link_libraries(hupeyaszih-polarization-simulation PRIVATE m)

target_include_directories(hupeyaszih-polarization-simulation
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
