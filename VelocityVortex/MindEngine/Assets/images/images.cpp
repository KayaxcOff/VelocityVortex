//
// Created by muham on 30.10.2025.
//

#include "images.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>
#include <ranges>
#include "../../Assert/assert.hpp"

using namespace mind;

VortexImage::VortexImage(SDL_Renderer *renderer) : renderer(renderer) {}

VortexImage::~VortexImage() {
    Shutdown();
}

void VortexImage::Init() {
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF);

    if (constexpr int flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF; !(IMG_Init(flags) & flags)) {
        std::cout << "SDL_image could not initialize!" << std::endl;
        std::cerr << IMG_GetError() << std::endl;
    }
}

SDL_Texture* VortexImage::initializeTexture(const std::string& path) {
    VORTEX_ASSERT(renderer, "VortexImage::initializeTexture: Renderer is null!");

    SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());
    VORTEX_ASSERT(texture, "VortexImage::initializeTexture: Failed to load texture");

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    images[path] = texture;
    return texture;
}

void VortexImage::Shutdown() {
    for (const auto &val: images | std::views::values) {
        SDL_DestroyTexture(val);
    }
    images.clear();
    IMG_Quit();
}