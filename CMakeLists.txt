cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)
project(obj_demo VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_executable(${PROJECT_NAME} demo.c)
