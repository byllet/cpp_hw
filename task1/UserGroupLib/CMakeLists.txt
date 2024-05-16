cmake_minimum_required(VERSION 3.15)
project(UserGroupLib)

set(SOURCES
    src/Group.cpp
    src/User.cpp
    src/Manager.cpp
    )

set(HEADERS 
        include/Group.hpp
        include/User.hpp
        include/Manager.hpp
    )

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
