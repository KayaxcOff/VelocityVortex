# VelocityVortex - Technical Documentation

## Architecture Overview

VelocityVortex is a 2D car racing game built using a simple game engine architecture.

### Components

#### 1. Game Engine (Game.h/Game.cpp)
The main game engine that manages:
- SDL2 initialization and window management
- Game loop with fixed timestep physics
- Event handling (keyboard input)
- Rendering pipeline
- Box2D physics world

**Key Methods:**
- `init()`: Initializes SDL2, creates window/renderer, sets up Box2D world
- `run()`: Main game loop with fixed timestep
- `handleEvents()`: Processes keyboard input
- `update()`: Updates game state
- `render()`: Renders the current frame

#### 2. Car Physics (Car.h/Car.cpp)
Implements realistic car physics using Box2D:
- Dynamic rigid body with proper mass and inertia
- Lateral friction to prevent unrealistic sliding
- Forward friction for natural deceleration
- Speed-dependent steering
- Acceleration and braking forces

**Physics Model:**
- Top-down 2D physics (no gravity)
- Lateral velocity cancellation for realistic car handling
- Forward/backward movement with max speed limits
- Angular velocity for turning (only when moving)

**Key Methods:**
- `update()`: Main physics update called each frame
- `updateFriction()`: Applies lateral and forward friction
- `updateDrive()`: Handles acceleration and braking
- `updateTurn()`: Handles steering based on current speed
- `render()`: Draws the car as a rotated rectangle

### Physics Constants

```cpp
CAR_WIDTH = 2.0f meters
CAR_HEIGHT = 4.0f meters
MAX_FORWARD_SPEED = 30.0f m/s
MAX_BACKWARD_SPEED = -10.0f m/s
ACCELERATION = 15.0f m/s²
TURN_SPEED = 2.0 rad/s
FRICTION = 0.3
```

### Game Loop

The game uses a fixed timestep game loop:

```
1. Handle input events
2. Step Box2D physics (1/60 second fixed step)
3. Update game state
4. Render current frame
5. Cap frame rate to 60 FPS
```

### Coordinate System

- **Box2D**: Uses meters as units, origin at center
- **SDL2**: Uses pixels, origin at top-left
- **Conversion**: PIXELS_PER_METER = 20.0

### Controls

| Key | Action |
|-----|--------|
| W / Up Arrow | Accelerate Forward |
| S / Down Arrow | Brake / Reverse |
| A / Left Arrow | Turn Left |
| D / Right Arrow | Turn Right |
| ESC | Quit Game |

## Building and Running

### Dependencies
- SDL2 2.0+
- Box2D 2.4+
- CMake 3.10+
- C++17 compiler

### Build Instructions

```bash
./build.sh
```

Or manually:
```bash
mkdir build
cd build
cmake ..
make
./VelocityVortex
```

## Extending the Game

### Adding More Cars
Create multiple `Car` instances in `Game::init()` and update/render them in the game loop.

### Adding Obstacles
Create static Box2D bodies in the world:
```cpp
b2BodyDef wallDef;
wallDef.position.Set(x, y);
b2Body* wall = world->CreateBody(&wallDef);
// Add fixture...
```

### Adding Collision Detection
Implement a `b2ContactListener` and attach it to the world:
```cpp
world->SetContactListener(myListener);
```

### Adding Sound Effects
Integrate SDL_mixer:
```cpp
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
Mix_Chunk* sound = Mix_LoadWAV("sound.wav");
Mix_PlayChannel(-1, sound, 0);
```

## Performance Considerations

- Box2D runs at fixed 60Hz timestep for deterministic physics
- Rendering is capped at 60 FPS
- Physics iterations: 8 velocity, 3 position (good balance)
- Linear/angular damping prevents perpetual motion

## License

MIT License
