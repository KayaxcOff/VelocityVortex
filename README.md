# VelocityVortex

A 2D car game engine built with SDL2 and Box2D physics.

## Description

VelocityVortex is a top-down 2D car racing game that demonstrates realistic car physics using the Box2D physics engine and renders graphics with SDL2.

## Features

- Realistic car physics with Box2D
- Top-down 2D rendering with SDL2
- Keyboard controls (WASD or Arrow keys)
- Smooth car movement with acceleration, braking, and steering
- Lateral friction simulation for realistic car handling

## Dependencies

- SDL2
- Box2D
- CMake (>= 3.10)
- C++17 compatible compiler

## Building

### Linux/macOS

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get install libsdl2-dev libbox2d-dev cmake

# Build the project
mkdir build
cd build
cmake ..
make
```

### Running

```bash
./VelocityVortex
```

## Controls

- **W/Up Arrow**: Accelerate
- **S/Down Arrow**: Brake/Reverse
- **A/Left Arrow**: Turn Left
- **D/Right Arrow**: Turn Right
- **ESC**: Quit game

## Project Structure

```
VelocityVortex/
├── include/
│   ├── Game.h      # Main game class
│   └── Car.h       # Car physics and rendering
├── src/
│   ├── main.cpp    # Entry point
│   ├── Game.cpp    # Game implementation
│   └── Car.cpp     # Car implementation
└── CMakeLists.txt  # Build configuration
```

## License

This project is open source and available under the MIT License.