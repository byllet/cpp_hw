cmake_minimum_required(VERSION 3.15)
project(task7)

set(CMAKE_CXX_STANDARD 20)
add_executable(${PROJECT_NAME} main.cpp SetImpl.hpp LightSetImpl.hpp)