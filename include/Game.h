#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <memory>
#include "Car.h"

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();
    void cleanup();

private:
    void handleEvents();
    void update(float deltaTime);
    void render();

    SDL_Window* window;
    SDL_Renderer* renderer;
    
    std::unique_ptr<b2World> world;
    std::unique_ptr<Car> car;
    
    bool running;
    bool keys[4]; // 0=up, 1=down, 2=left, 3=right
    
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const float PIXELS_PER_METER = 20.0f;
};

#endif // GAME_H
