//
// Created by muham on 31.10.2025.
//

#ifndef VELOCITYVORTEX_STRUCTS_HPP
#define VELOCITYVORTEX_STRUCTS_HPP

#include <SDL2/SDL.h>
#include <Box2D/box2d.h>

namespace mind::vecs {
    struct Velocity {
        float velX, velY;
    };

    struct vortex_d {
        Velocity _pos;
        b2Body* body;
        SDL_Texture* texture;
        Velocity _size;
    };

    template<typename T>
    struct vortex_t {
        T* ptr;
        float speed{};
        Velocity _pos{};
    };
}


#endif //VELOCITYVORTEX_STRUCTS_HPP