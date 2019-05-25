cmake_minimum_required(VERSION 3.0)
project ("send")

add_compile_options(-std=c++11)

file(GLOB SOURCES
    ../../src/include/*.hpp
    ../../src/*.cpp
    main.cpp
)

set(EXECUTABLE_OUTPUT_PATH "bin")

add_executable( send ${SOURCES} )
