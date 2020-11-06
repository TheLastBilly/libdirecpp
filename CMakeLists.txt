cmake_minimum_required(VERSION 3.0)

include(settings.cmake)

project(libdirecpp VERSION ${LIBDIRECPP_VERSION})

macro(build_example)
get_filename_component(EXAMPLE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(
    GLOB SRCS

    "*.cpp"
    "*.hpp"
)

add_executable( ${EXAMPLE_NAME} ${SRCS} $<TARGET_OBJECTS:${PROJECT_NAME}>)
endmacro()

include_directories("src/")

file(
    GLOB SRCS
    
    "src/*.cpp"
    "src/*.hpp"
)

add_library(
    ${PROJECT_NAME}

    ${SRCS}
)

add_subdirectory(examples)