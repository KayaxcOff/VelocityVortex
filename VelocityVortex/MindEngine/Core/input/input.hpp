//
// Created by muham on 30.10.2025.
//

#ifndef VELOCITYVORTEX_INPUT_HPP
#define VELOCITYVORTEX_INPUT_HPP

#include <SDL2/SDL.h>
#include <unordered_map>

namespace mind {
    class VortexInput {
    public:
        VortexInput();
        ~VortexInput();

        void handleEvent(const SDL_Event& e);
        void update();

        [[nodiscard]] bool isPressed(SDL_Scancode key) const;
    private:
        const Uint8* keyboardState;

        std::unordered_map<SDL_Scancode, bool> currentKeyStates;
        std::unordered_map<SDL_Scancode, bool> previousKeyStates;

        void Shutdown();
    };
}

#endif //VELOCITYVORTEX_INPUT_HPP