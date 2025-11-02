//
// Created by muham on 30.10.2025.
//

#include "physic.hpp"

#include "../../Assert/assert.hpp"

using namespace mind;

VortexPhysic::VortexPhysic() : ppm(0.0f), world(nullptr) {}

VortexPhysic::~VortexPhysic() {
    Shutdown();
}

void VortexPhysic::Init(const float pixelsPerMeter, const float gravityX, const float gravityY) {
    ppm = pixelsPerMeter;
    b2Vec2 gravity(gravityX, gravityY);
    world = std::make_unique<b2World>(gravity);
}

void VortexPhysic::update(const float deltaTime, const int velocityIterations, const int positionIterations) const {
    VORTEX_ASSERT(world, "VortexPhysic::update: World is not initialized.");
    world->Step(deltaTime, velocityIterations, positionIterations);
}

void VortexPhysic::calculateCollisions(b2Body* body, const float width, const float height, const int offsetX, const int offsetY) const{
    b2Vec2 position = body->GetPosition();
    b2Vec2 velocity = body->GetLinearVelocity();

    const float halfX = width / 2.0f;
    const float halfY = height * 0.5f;

    const float screenWidth = static_cast<float>(offsetX) / ppm;
    const float screenHeight = static_cast<float>(offsetY) / ppm;

    bool isNeed = false;

    if (position.x - halfX < 0.0f) {
        position.x = halfX;
        velocity.x = 0.0f;
        isNeed = true;
    } else if (position.x + halfX > screenWidth) {
        position.x = screenWidth - halfX;
        velocity.x = 0.0f;
        isNeed = true;
    }

    if (position.y - halfY < 0.0f) {
        position.y = halfY;
        velocity.y = 0.0f;
        isNeed = true;
    } else if (position.y + halfY > screenHeight) {
        position.y = screenHeight - halfY;
        velocity.y = 0.0f;
        isNeed = true;
    }

    if (isNeed) {
        body->SetTransform(position, body->GetAngle());
        body->SetLinearVelocity(velocity);
    }
}

b2Body* VortexPhysic::initializeBox(const float posX, const float posY, const float width, const float height, const bool isDynamic) const {
    VORTEX_ASSERT(world, "VortexPhysic::initializeBox: World is not initialized.");

    b2BodyDef bodyDef;
    bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
    bodyDef.position.Set(posX, posY);

    if (isDynamic) {
        bodyDef.linearDamping = 0.0f;
        bodyDef.angularDamping = 0.0f;
        bodyDef.allowSleep = false;
        bodyDef.fixedRotation = false;
    }

    b2Body* body = world->CreateBody(&bodyDef);
    VORTEX_ASSERT(body, "VortexPhysic::initializeBox: Failed to create body.");

    b2PolygonShape boxShape;
    boxShape.SetAsBox(width / 2, height / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    return body;
}

void VortexPhysic::Shutdown() {
    if (world) {
        world.reset();
    }
}

float VortexPhysic::to_met(const float pixels) const {
    return pixels / ppm;
}

float VortexPhysic::to_pix(const float meters) const {
    return meters * ppm;
}