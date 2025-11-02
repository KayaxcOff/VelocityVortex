//
// Created by muham on 31.10.2025.
//

#ifndef VELOCITYVORTEX_MAP_HPP
#define VELOCITYVORTEX_MAP_HPP

#include <SDL2/SDL.h>
#include <Box2D/box2d.h>
#include <string>
#include <vector>
#include "../../Assets/images/images.hpp"
#include "../../Core/physic/physic.hpp"

namespace mind {
    struct MapTile {
        int x;
        int y;
        int value;
    };

    class VortexMap {
    public:
        explicit VortexMap(VortexImage* image, VortexPhysic* physic);
        ~VortexMap();

        void initializeMap(const std::string& mapPath, const std::string& imgPath, int offsetX, int offsetY);
        void render(SDL_Renderer* renderer) const;

        [[nodiscard]] int getWidth() const;
        [[nodiscard]] int getHeight() const;
    private:
        SDL_Texture* texture;

        VortexPhysic* physic;
        VortexImage* image;

        std::vector<std::vector<int>> tiles;
        std::vector<b2Body*> bodies;

        int mapWidth;
        int mapHeight;
        int tileSize;

        void Shutdown();
    };
}

#endif //VELOCITYVORTEX_MAP_HPP