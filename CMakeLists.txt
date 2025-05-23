cmake_minimum_required(VERSION 3.10)
project(CarSystem)

# Use C++17
set(CMAKE_CXX_STANDARD 17)

# Include src folder for header files
include_directories(src)

# Create a static library from Car.cpp
add_library(car src/Car.cpp)

# Create main executable
add_executable(main main.cpp)
target_link_libraries(main car)

# Enable testing and build test executable
enable_testing()
add_executable(test_car test/CarTest.cpp)
target_link_libraries(test_car car)

# Register test (optional, used with `ctest`)
add_test(NAME CarTest COMMAND test_car)
