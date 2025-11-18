cmake_minimum_required(VERSION 4.0)
project(Individuellt_projektarbete)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        inc
)

add_executable(i_p
        main.cpp
        src/Cell.cpp)
