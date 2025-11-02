cmake_minimum_required(VERSION 3.10)
project(VelocityVortex)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)

# Find Box2D
find_package(box2d REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Car.cpp
)

# Create executable
add_executable(VelocityVortex ${SOURCES})

# Include directories
target_include_directories(VelocityVortex PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(VelocityVortex ${SDL2_LIBRARIES} box2d)
