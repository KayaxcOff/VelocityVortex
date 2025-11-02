//
// Created by muham on 31.10.2025.
//

#include "map.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "../../Assert/assert.hpp"

using namespace mind;
using json = nlohmann::json;

VortexMap::VortexMap(VortexImage* image, VortexPhysic* physic)
    : texture(nullptr), physic(physic), image(image), mapWidth(0), mapHeight(0), tileSize(32) {}

VortexMap::~VortexMap() {
    Shutdown();
}

void VortexMap::initializeMap(const std::string& mapPath, const std::string& imgPath, const int offsetX, const int offsetY) {

    std::ifstream file(mapPath);
    if (!file.is_open()) {
        std::cerr << "Map file not found: " << mapPath << std::endl;
        return;
    }

    json vortexMap;
    try {
        file >> vortexMap;
    } catch (const json::parse_error& e) {
        std::cerr << "Failed to parse map file: " << e.what() << std::endl;
        return;
    }

    mapWidth = vortexMap["width"];
    mapHeight = vortexMap["height"];

    const float tileW = static_cast<float>(offsetX) / static_cast<float>(mapWidth);
    const float tileH = static_cast<float>(offsetY) / static_cast<float>(mapHeight);
    tileSize = static_cast<int>(std::min(tileW, tileH));

    tiles.resize(mapHeight, std::vector(mapWidth, 0));

    for (int y=0; y<vortexMap["tiles"].size(); ++y) {
        for (int x=0; x<vortexMap["tiles"][y].size(); ++x) {
            tiles[y][x] = vortexMap["tiles"][y][x];
        }
    }

    texture = image->initializeTexture(imgPath);
    VORTEX_ASSERT(texture, "VortexMap::initializeMap: Failed to load wall texture");

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            if (tiles[y][x] == 1) {
                const float pixelCenterX = (static_cast<float>(x) + 0.5f) * static_cast<float>(tileSize);
                const float pixelCenterY = (static_cast<float>(y) + 0.5f) * static_cast<float>(tileSize);

                const float box2dCenterX = physic->to_met(pixelCenterX);
                const float box2dCenterY = physic->to_met(static_cast<float>(offsetY) - pixelCenterY);

                const float box2dWidth = physic->to_met(static_cast<float>(tileSize));
                const float box2dHeight = physic->to_met(static_cast<float>(tileSize));

                b2Body* wall = physic->initializeBox(
                    box2dCenterX,
                    box2dCenterY,
                    box2dWidth,
                    box2dHeight,
                    false
                );

                VORTEX_ASSERT(wall, "VortexMap::initializeMap: Failed to initialize box");
                bodies.push_back(wall);

                std::cout << "Wall at grid (" << x << ", " << y << ") "
                          << "SDL: (" << pixelCenterX << ", " << pixelCenterY << ") "
                          << "Box2D: (" << box2dCenterX << ", " << box2dCenterY << ")\n";
            }
        }
    }

    std::cout << "Map initialized: " << mapWidth << "x" << mapHeight
              << " (tile size: " << tileSize << "px)\n";
}

void VortexMap::render(SDL_Renderer* renderer) const {
    VORTEX_ASSERT(texture, "VortexMap::render: Failed to render wall texture");

    SDL_Rect dst;

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            if (tiles[y][x] == 1) {
                dst.x = x * tileSize;
                dst.y = y * tileSize;
                dst.w = tileSize;
                dst.h = tileSize;

                SDL_RenderCopy(renderer, texture, nullptr, &dst);

                #ifdef DEBUG_RENDER
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
                SDL_RenderDrawRect(renderer, &dst);
                #endif
            }
        }
    }
}

void VortexMap::Shutdown() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    for (const auto& item : bodies) {
        if (item && item->GetWorld()) {
            item->GetWorld()->DestroyBody(item);
        }
    }
    bodies.clear();
}

int VortexMap::getWidth() const {
    return mapWidth;
}

int VortexMap::getHeight() const {
    return mapHeight;
}