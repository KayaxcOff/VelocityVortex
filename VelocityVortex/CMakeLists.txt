cmake_minimum_required(VERSION 4.0)
project(VelocityVortex)

set(CMAKE_CXX_STANDARD 20)

set(SDL_DIR "C:\\software\\Cpp\\libraries\\SDL2-2.32.6")
include_directories("${SDL_DIR}\\include")
link_directories("${SDL_DIR}\\lib\\x64")

set(BOX2D_DIR "C:\\software\\Cpp\\libraries\\Box2D\\box2d-2.4.1")
include_directories("${BOX2D_DIR}\\include")
link_directories("${BOX2D_DIR}\\build\\bin\\Debug")

set(NLOHMANN_DIR "C:\\software\\Cpp\\libraries\\json-3.12.0\\json-3.12.0")
include_directories("${NLOHMANN_DIR}\\include")

add_definitions(-DSDL_MAIN_HANDLED)

add_executable(VelocityVortex main.cpp
        MindEngine/Game/game/game.hpp
        MindEngine/Game/game/game.cpp
        MindEngine/Core/physic/physic.cpp
        MindEngine/Core/physic/physic.hpp
        MindEngine/Game/entity/entity.hpp
        MindEngine/Assets/images/images.hpp
        MindEngine/Assets/images/images.cpp
        MindEngine/Assets/audios/audios.hpp
        MindEngine/Assets/audios/audios.cpp
        MindEngine/Core/input/input.hpp
        MindEngine/Core/input/input.cpp
        MindEngine/Game/map/map.hpp
        MindEngine/Game/map/map.cpp
        MindEngine/Game/entity/structs.hpp
)

target_link_libraries(VelocityVortex
        "${SDL_DIR}\\lib\\x64\\SDL2.lib"
        "${SDL_DIR}\\lib\\x64\\SDL2_image.lib"
        "${SDL_DIR}\\lib\\x64\\SDL2_ttf.lib"
        "${SDL_DIR}\\lib\\x64\\SDL2_mixer.lib"
        "${BOX2D_DIR}\\build\\bin\\Debug\\box2d.lib"
)