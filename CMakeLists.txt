cmake_minimum_required(VERSION 3.10)

# Project name and version
project(TerminalFlappyBird VERSION 1.0)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source and header files
set(SOURCES
    src/main.cpp
    src/utils.cpp
    src/bird.cpp
    src/pipe.cpp
    src/game.cpp
    src/input.cpp
    src/color.cpp
)

set(HEADERS
    src/headers/bird.hpp
    src/headers/utils.hpp
    src/headers/pipe.hpp
    src/headers/game.hpp
    src/headers/input.hpp
    src/headers/color.hpp
)

# Exe
add_executable(Flappy-bird ${SOURCES} ${HEADERS})

target_include_directories(Flappy-bird PRIVATE src/headers)

# Optional: copy asset folder into build dir
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
