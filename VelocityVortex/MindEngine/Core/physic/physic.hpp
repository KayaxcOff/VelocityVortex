//
// Created by muham on 30.10.2025.
//

#ifndef VELOCITYVORTEX_PHYSIC_HPP
#define VELOCITYVORTEX_PHYSIC_HPP

#include <Box2D/box2d.h>
#include <memory>

namespace mind {
    class VortexPhysic {
    public:
        VortexPhysic();
        ~VortexPhysic();

        void Init(float pixelsPerMeter, float gravityX = 0, float gravityY = 9.81f);
        void update(float deltaTime, int velocityIterations, int positionIterations) const;
        void calculateCollisions(b2Body* body, float width, float height, int offsetX, int offsetY) const;

        [[nodiscard]] b2Body* initializeBox(float posX, float posY, float width, float height, bool isDynamic) const;
        [[nodiscard]] float to_met(float pixels) const;
        [[nodiscard]] float to_pix(float meters) const;
    private:
        float ppm;
        std::unique_ptr<b2World> world;

        void Shutdown();
    };
}

#endif //VELOCITYVORTEX_PHYSIC_HPP