//
// Created by muham on 30.10.2025.
//

#ifndef VELOCITYVORTEX_AUDIOS_HPP
#define VELOCITYVORTEX_AUDIOS_HPP

#include <SDL2/SDL_mixer.h>
#include <unordered_map>
#include <string>

namespace mind {
    class VortexAudio {
    public:
        VortexAudio();
        ~VortexAudio();

        void Init();
        void playMusic(const std::string& key, const std::string& path, int loops=0);
    private:
        std::unordered_map<std::string, Mix_Music*> musics;

        Mix_Music* loadMusic(const std::string& key, const std::string& path);
        void Shutdown();
    };
}

#endif //VELOCITYVORTEX_AUDIOS_HPP