//
// Created by muham on 30.10.2025.
//

#ifndef VELOCITYVORTEX_GAME_HPP
#define VELOCITYVORTEX_GAME_HPP

#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "../entity/entity.hpp"
#include "../map/map.hpp"
#include "../../Core/physic/physic.hpp"
#include "../../Core/input/input.hpp"
#include "../../Assets/images/images.hpp"
#include "../../Assets/audios/audios.hpp"

namespace mind {
    class VortexGame {
    public:
        explicit VortexGame(int offsetX=800, int offsetY=600);
        ~VortexGame();

        void Init();
        void run();

        [[nodiscard]] bool isRunning() const;
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

        int SCREEN_WIDTH, SCREEN_HEIGHT;
        bool inited;
        float ppm;

        constexpr static int TARGET_FPS = 60;
        constexpr static int FRAME_DELAY = 1000 / TARGET_FPS;

        std::unique_ptr<VortexPhysic> vortex_physic_;
        std::unique_ptr<VortexInput> vortex_input_;
        std::unique_ptr<Entity> entity_;
        std::unique_ptr<VortexImage> vortex_image_;
        std::unique_ptr<VortexAudio> vortex_audio_;
        std::unique_ptr<VortexMap> vortex_map_;

        std::vector<std::unique_ptr<Entity>> entities;

        void render() const;
        void update(float deltaTime) const;
        void Shutdown();
    };
}

#endif //VELOCITYVORTEX_GAME_HPP