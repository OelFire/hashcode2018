cmake_minimum_required(VERSION 3.8)

project(hashcode2018)

include_directories(include)

set(SOURCE_FILES
        sources/main.cpp
        sources/Map.cpp
        sources/Vehicle.cpp
        sources/Ride.cpp include/Vector2.hpp)

add_executable(hashcode2018 ${SOURCE_FILES})