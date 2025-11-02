#ifndef CAR_H
#define CAR_H

#include <box2d/box2d.h>
#include <SDL2/SDL.h>

class Car {
public:
    Car(b2World* world, float x, float y);
    ~Car();

    void update(bool accelerate, bool brake, bool turnLeft, bool turnRight);
    void render(SDL_Renderer* renderer, float pixelsPerMeter);

    b2Vec2 getPosition() const;
    float getAngle() const;

private:
    b2Body* body;
    b2World* world;

    const float CAR_WIDTH = 2.0f;  // meters
    const float CAR_HEIGHT = 4.0f; // meters
    const float MAX_FORWARD_SPEED = 30.0f;
    const float MAX_BACKWARD_SPEED = -10.0f;
    const float ACCELERATION = 15.0f;
    const float TURN_SPEED = 2.0f;
    const float FRICTION = 0.3f;

    b2Vec2 getLateralVelocity() const;
    b2Vec2 getForwardVelocity() const;
    void updateFriction();
    void updateDrive(bool accelerate, bool brake);
    void updateTurn(bool left, bool right);
};

#endif // CAR_H
