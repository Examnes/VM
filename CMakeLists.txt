cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(FIXEDH VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11 -Wno-unused-parameter -g -Wno-unused-variable")

set(SRC ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/src/processor.cpp
        ${PROJECT_SOURCE_DIR}/src/memory.cpp
        ${PROJECT_SOURCE_DIR}/inc/cmd.gch
        ${PROJECT_SOURCE_DIR}/src/loader.cpp
    )

add_executable(${CMAKE_PROJECT_NAME} ${SRC})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

