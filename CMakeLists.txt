cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(subwayChallenge LANGUAGES CXX)

add_library(Boost INTERFACE)
target_include_directories(Boost INTERFACE "D:/source/boost_1_80_0")

add_executable(main main.cpp algos.cpp line.cpp station.cpp time.cpp trip.cpp)
target_link_libraries(main PRIVATE Boost)

if(MSVC)
  target_compile_options(main PRIVATE /W4 /WX)
else()
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic)
endif()
