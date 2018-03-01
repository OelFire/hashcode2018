cmake_minimum_required(VERSION 3.9)

project(hashcode2018)

include_directories(include)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        sources/main.cpp
        sources/Map.cpp
        sources/Vehicle.cpp
        sources/Ride.cpp include/Vector2.hpp)

add_executable(hashcode2018 ${SOURCE_FILES})