cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)
project(more_primitive_obj_loader VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} demo.c)
