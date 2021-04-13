cmake_minimum_required(VERSION 3.10)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES
    inc/*.h
    inc/*.hpp
    src/*.cpp
)

add_executable(yourProj ${SOURCES})
# set the project name
project(ChandraTests)

# add the executable
add_executable(ChandraTests ${SOURCES})
