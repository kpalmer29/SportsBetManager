cmake_minimum_required(VERSION 3.15)
project(SportsBetManager)

set(CMAKE_CXX_STANDAR_17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES
        BetNode.h SportsBet.cpp SportsBet.h Date.cpp Date.h SportsBetManager.cpp SportsBetManager.h)

add_executable(SportsBetManager ${SOURCE_FILES})