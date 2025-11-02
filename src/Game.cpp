#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game() : window(nullptr), renderer(nullptr), running(false) {
    for (int i = 0; i < 4; i++) {
        keys[i] = false;
    }
}

Game::~Game() {
}

bool Game::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    window = SDL_CreateWindow("VelocityVortex - 2D Car Game",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize Box2D world
    b2Vec2 gravity(0.0f, 0.0f); // No gravity for top-down car game
    world = std::make_unique<b2World>(gravity);

    // Create car in the center of the screen
    car = std::make_unique<Car>(world.get(), SCREEN_WIDTH / (2.0f * PIXELS_PER_METER), 
                                 SCREEN_HEIGHT / (2.0f * PIXELS_PER_METER));

    running = true;
    return true;
}

void Game::run() {
    const float TIME_STEP = 1.0f / 60.0f;
    const int VELOCITY_ITERATIONS = 8;
    const int POSITION_ITERATIONS = 3;

    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // Cap delta time to prevent spiral of death
        if (deltaTime > 0.05f) {
            deltaTime = 0.05f;
        }

        handleEvents();
        
        // Step the Box2D world
        world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
        
        update(deltaTime);
        render();

        // Cap frame rate at 60 FPS
        SDL_Delay(16);
    }
}

void Game::cleanup() {
    car.reset();
    world.reset();

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_w:
                    keys[0] = true;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    keys[1] = true;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    keys[2] = true;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    keys[3] = true;
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_w:
                    keys[0] = false;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    keys[1] = false;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    keys[2] = false;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    keys[3] = false;
                    break;
            }
        }
    }
}

void Game::update(float deltaTime) {
    // Update car with current key states
    car->update(keys[0], keys[1], keys[2], keys[3]);
}

void Game::render() {
    // Clear screen with dark gray (asphalt color)
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // Draw simple track markings (dashed lines)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int y = 100; y < SCREEN_HEIGHT; y += 40) {
        SDL_Rect dashRect = { SCREEN_WIDTH / 2 - 2, y, 4, 20 };
        SDL_RenderFillRect(renderer, &dashRect);
    }

    // Render car
    car->render(renderer, PIXELS_PER_METER);

    // Present
    SDL_RenderPresent(renderer);
}
