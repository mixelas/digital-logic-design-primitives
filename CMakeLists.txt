cmake_minimum_required(VERSION 3.16)
project(digital_logic_primitives LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dldp src/main.cpp)
target_include_directories(dldp PRIVATE src)

add_executable(tests tests/test_all.cpp)
target_include_directories(tests PRIVATE src)