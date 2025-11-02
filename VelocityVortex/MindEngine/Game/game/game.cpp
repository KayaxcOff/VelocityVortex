//
// Created by muham on 30.10.2025.
//

#include "game.hpp"

#include <iostream>
#include "../entity/structs.hpp"
#include "../../Assert/assert.hpp"

using namespace mind;

VortexGame::VortexGame(const int offsetX, const int offsetY) : window(nullptr), renderer(nullptr), SCREEN_WIDTH(offsetX), SCREEN_HEIGHT(offsetY), inited(false), ppm(100.f) {}

VortexGame::~VortexGame() {
    Shutdown();
}

void VortexGame::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL has failed to initialize" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        inited = false;
        return;
    }

    window = SDL_CreateWindow("Velocity Vortex", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    VORTEX_ASSERT(window, "VortexGame::Init: Window creation failed");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    VORTEX_ASSERT(renderer, "VortexGame::Init: Renderer creation failed");

    vortex_physic_ = std::make_unique<VortexPhysic>();
    vortex_physic_->Init(ppm, 0, 0);
    VORTEX_ASSERT(vortex_physic_, "VortexGame::Init: Physic engine initialization failed");

    vortex_input_ = std::make_unique<VortexInput>();
    VORTEX_ASSERT(vortex_input_, "VortexGame::Init: Input manager initialization failed");

    vortex_image_ = std::make_unique<VortexImage>(renderer);
    vortex_image_->Init();
    VORTEX_ASSERT(vortex_image_, "VortexGame::Init: Image manager initialization failed");

    vortex_audio_ = std::make_unique<VortexAudio>();
    vortex_audio_->Init();
    VORTEX_ASSERT(vortex_audio_, "VortexGame::Init: Audio manager initialization failed");
    vortex_audio_->playMusic("back-ground",R"(C:\software\Cpp\projects\VelocityVortex\Assets\musics\vortex-game-music.mp3)");

    vortex_map_ = std::make_unique<VortexMap>(vortex_image_.get(), vortex_physic_.get());
    VORTEX_ASSERT(vortex_map_, "VortexGame::Init: Map manager initialization failed");

    vortex_map_->initializeMap(R"(C:\software\Cpp\projects\VelocityVortex\Assets\map\vortex-map.json)",R"(C:\software\Cpp\projects\VelocityVortex\Assets\images\rock.png)", SCREEN_WIDTH, SCREEN_HEIGHT);

    const int tileSize = std::min(SCREEN_WIDTH / vortex_map_->getWidth(), SCREEN_HEIGHT / vortex_map_->getHeight());

    vecs::vortex_d car{};
    car._pos.velX = static_cast<float>(SCREEN_WIDTH) / 2;
    car._pos.velY = static_cast<float>(SCREEN_HEIGHT) - static_cast<float>(tileSize) * 2;
    car._size.velX = vortex_physic_->to_met(64.f);
    car._size.velY = vortex_physic_->to_met(96.f);
    car.body = vortex_physic_->initializeBox(vortex_physic_->to_met(car._pos.velX), vortex_physic_->to_met(car._pos.velY), car._size.velX, car._size.velY, true);
    car.texture = vortex_image_->initializeTexture(R"(C:\software\Cpp\projects\VelocityVortex\Assets\images\test\chibi.png)");

    entity_ = std::make_unique<Entity>(car.body, car.texture, car._size.velX, car._size.velY);
    VORTEX_ASSERT(entity_, "VortexGame::Init: Entity creation failed");
    entities.emplace_back(std::move(entity_));

    inited = true;
}

void VortexGame::run() {
    Uint64 lastTime = SDL_GetPerformanceCounter();
    const Uint64 freq = SDL_GetPerformanceFrequency();

    while (inited) {
        const Uint64 currentTime = SDL_GetPerformanceCounter();
        const float deltaTime = static_cast<float>(currentTime - lastTime) / static_cast<float>(freq);
        lastTime = currentTime;

        const Uint32 currentTick = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                inited = false;
            }
            vortex_input_->handleEvent(event);
        }

        vortex_input_->update();
        update(deltaTime);
        render();

        SDL_RenderPresent(renderer);

        if (const Uint32 elapsed = SDL_GetTicks() - currentTick; elapsed < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - elapsed);
        }
    }
}

bool VortexGame::isRunning() const {
    return inited;
}

void VortexGame::render() const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    vortex_map_->render(renderer);

    for (const auto& item : entities) {
        item->render(renderer, ppm, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
}

void VortexGame::update(const float deltaTime) const {
    if (!entities.empty()) {
        vecs::vortex_t<Entity> car{};
        car.ptr = entities[0].get();
        car.speed = 5.f;

        if (vortex_input_->isPressed(SDL_SCANCODE_W)) car._pos.velY = car.speed;
        if (vortex_input_->isPressed(SDL_SCANCODE_S)) car._pos.velY = -car.speed;
        if (vortex_input_->isPressed(SDL_SCANCODE_A)) car._pos.velX = -car.speed;
        if (vortex_input_->isPressed(SDL_SCANCODE_D)) car._pos.velX = car.speed;

        car._pos.velX *= deltaTime;
        car._pos.velY *= deltaTime;

        car.ptr->move(car._pos.velX, car._pos.velY);

        if (car._pos.velX != 0.f || car._pos.velY != 0.f) {
            const auto angle = static_cast<float>(std::atan2(car._pos.velY, car._pos.velX) * 180.f / M_PI);
            car.ptr->setRotation(angle);

            const b2Vec2 pos = car.ptr->getBody()->GetPosition();
            car.ptr->getBody()->SetTransform(pos, static_cast<float>(car.ptr->getRotation() * M_PI / 180.f));
        }

        vortex_physic_->calculateCollisions(car.ptr->getBody(), car.ptr->getWidth(), car.ptr->getHeight(), SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    vortex_physic_->update(deltaTime, 8, 3);
}

void VortexGame::Shutdown() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
    inited = false;
}