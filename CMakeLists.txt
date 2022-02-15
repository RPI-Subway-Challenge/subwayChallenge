cmake_minimum_required(VERSION 3.20)
project(subwayChallenge)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(subwayChallenge
        main.cpp
        station.cpp
        station.h
        time.cpp
        time.h
        trip.cpp
        trip.h)
