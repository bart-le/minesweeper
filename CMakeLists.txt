cmake_minimum_required(VERSION 3.17)
project(minesweeper)

set(CMAKE_CXX_STANDARD 20)

add_executable(minesweeper src/main.cpp src/Game.cpp src/Game.h src/Board.cpp src/Board.h)