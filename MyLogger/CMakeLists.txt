cmake_minimum_required(VERSION 3.31)
project(MyLogger)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyLogger main.cpp
        Logger.h
        Writer.h
        ConsoleWriter.h)
