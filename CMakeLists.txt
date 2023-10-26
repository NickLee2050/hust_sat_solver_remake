cmake_minimum_required(VERSION 3.15)
set (CMAKE_EXPORT_COMPILE_COMMANDS True)

project(sat_solver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/build)

set(SRC_LIST main.cpp clause.cpp dpll_solver.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})