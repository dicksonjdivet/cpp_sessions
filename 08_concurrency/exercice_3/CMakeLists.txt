cmake_minimum_required(VERSION 3.10)

project(cpp-session)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)

add_executable(classes_8_exercice_3 src/main.cpp)
target_link_libraries(classes_8_exercice_3 Threads::Threads)
