//
// Created by muham on 30.10.2025.
//

#ifndef VELOCITYVORTEX_IMAGES_HPP
#define VELOCITYVORTEX_IMAGES_HPP

#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>

namespace mind {
    class VortexImage {
    public:
        explicit VortexImage(SDL_Renderer* renderer);
        ~VortexImage();

        void Init();
        SDL_Texture* initializeTexture(const std::string& path);
    private:
        SDL_Renderer* renderer;

        std::unordered_map<std::string, SDL_Texture*> images;

        void Shutdown();
    };
}

#endif //VELOCITYVORTEX_IMAGES_HPP