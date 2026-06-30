cmake_minimum_required(VERSION 3.20)

project(educational_bsod_experiment LANGUAGES CXX)

if(NOT WIN32)
    message(FATAL_ERROR "This experiment targets Windows and requires a Windows C++ toolchain.")
endif()

add_executable(educational_bsod_experiment
    src/main.cpp
)

target_compile_features(educational_bsod_experiment PRIVATE cxx_std_17)
target_include_directories(educational_bsod_experiment PRIVATE include)

if(MSVC)
    target_compile_options(educational_bsod_experiment PRIVATE /W4 /permissive-)
else()
    target_compile_options(educational_bsod_experiment PRIVATE -Wall -Wextra -Wpedantic)
endif()
