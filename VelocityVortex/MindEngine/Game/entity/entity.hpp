//
// Created by muham on 30.10.2025.
//

#ifndef VELOCITYVORTEX_ENTITY_HPP
#define VELOCITYVORTEX_ENTITY_HPP

#include <SDL2/SDL.h>
#include <Box2D/box2d.h>
#include "../../Assert/assert.hpp"

namespace mind {
    class Entity {
    public:
        Entity(b2Body* body, SDL_Texture* texture, const float width, const float height) : body(body), texture(texture), width(width), height(height), rotation(0) {}
        virtual ~Entity() {
            Entity::Shutdown();
        }

        virtual void render(SDL_Renderer* renderer, const float ppm, const int offsetX, const int offsetY) const {
            VORTEX_ASSERT(renderer, "Renderer is null in Entity::render()");
            VORTEX_ASSERT(body, "Body is null in Entity::render()");
            VORTEX_ASSERT(texture, "Texture is null in Entity::render()");

            const b2Vec2 pos = body->GetPosition();

            SDL_Rect dst;

            dst.x = static_cast<int>(pos.x*ppm - (width*ppm)/2);
            dst.y = static_cast<int>(static_cast<float>(offsetY) - (pos.y*ppm) - (height*ppm)/2);
            dst.w = static_cast<int>(width*ppm);
            dst.h = static_cast<int>(height*ppm);

            SDL_Point center;
            center.x = dst.w / 2;
            center.y = dst.h / 2;

            //SDL_RenderCopy(renderer, texture, nullptr, &dst);
            SDL_RenderCopyEx(renderer, texture, nullptr, &dst, rotation, &center, SDL_FLIP_NONE);
        }

        virtual void move(const float posX, const float posY) {
            VORTEX_ASSERT(body, "Body is null in Entity::move()");

            b2Vec2 pos = this->body->GetPosition();

            pos.x += posX;
            pos.y += posY;

            this->body->SetTransform(pos, this->body->GetAngle());
        }

        void setRotation(const float angle) {
            rotation = angle;
        }

        [[nodiscard]] virtual b2Body* getBody() const {return body;}
        [[nodiscard]] virtual float getWidth() const {return width;}
        [[nodiscard]] virtual float getHeight() const {return height;}
        [[nodiscard]] virtual SDL_Texture* getTexture() const {return texture;}
        [[nodiscard]] virtual float getRotation() const {return rotation;}
    private:
        b2Body* body;
        SDL_Texture* texture;
        float width, height;
        float rotation;

        virtual void Shutdown() {
            if (body) {
                b2World* world = body->GetWorld();
                world->DestroyBody(body);
                body = nullptr;
            }
        }
    };
}

#endif //VELOCITYVORTEX_ENTITY_HPP