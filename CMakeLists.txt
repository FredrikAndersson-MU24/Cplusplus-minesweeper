cmake_minimum_required(VERSION 4.0)
project(Individuellt_projektarbete)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        inc
        utils/inc
)

add_executable(minesweeper
        main.cpp
        src/Cell.cpp
        src/GameBoard.cpp
        utils/src/InputHandlers.cpp)
