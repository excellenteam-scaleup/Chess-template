cmake_minimum_required(VERSION 3.15)
project(Chess)

# ── Language standard ────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Compiler warnings ────────────────────────────────────────────────────────
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ── IDE / tooling support ────────────────────────────────────────────────────
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ── Sources ──────────────────────────────────────────────────────────────────
# Automatically picks up Chess.cpp, main.cpp, and any files the student adds.
file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(include)

add_executable(Chess ${SOURCES})
