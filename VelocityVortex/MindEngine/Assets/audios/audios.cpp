//
// Created by muham on 30.10.2025.
//

#include "audios.hpp"

#include <ranges>
#include <SDL2/SDL.h>
#include <stdexcept>

using namespace mind;

VortexAudio::VortexAudio() : musics(NULL) {}

VortexAudio::~VortexAudio() {
    Shutdown();
}

void VortexAudio::Init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void VortexAudio::playMusic(const std::string &key, const std::string &path, int loops) {
    if (Mix_Music* music = loadMusic(key, path); Mix_PlayMusic(music, loops) == -1) {
        throw std::runtime_error("Failed to play music: " + std::string(Mix_GetError()));
    }
}


Mix_Music* VortexAudio::loadMusic(const std::string &key, const std::string &path) {
    if (const auto it = musics.find(key); it != musics.end()) {
        return it->second;
    }
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (!music) {
        throw std::runtime_error("Failed to load music: " + path + " Error: " + Mix_GetError());
    }
    musics[key] = music;
    return music;
}

void VortexAudio::Shutdown() {
    for (const auto &val: musics | std::views::values) Mix_FreeMusic(val);

    musics.clear();

    Mix_CloseAudio();
}