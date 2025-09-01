cmake_minimum_required(VERSION 3.10)
project(CarSystem)

# Use C++17
set(CMAKE_CXX_STANDARD 17)

# Include src folder
include_directories(src)

# Add source files
add_executable(main main.cpp src/Car.cpp)
