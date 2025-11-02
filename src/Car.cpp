#include "Car.h"
#include <cmath>
#include <algorithm>

Car::Car(b2World* world, float x, float y) : world(world) {
    // Create car body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    bodyDef.linearDamping = 0.5f;
    bodyDef.angularDamping = 0.8f;
    
    body = world->CreateBody(&bodyDef);

    // Create car shape
    b2PolygonShape boxShape;
    boxShape.SetAsBox(CAR_WIDTH / 2.0f, CAR_HEIGHT / 2.0f);

    // Create fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.2f;

    body->CreateFixture(&fixtureDef);
}

Car::~Car() {
    if (world && body) {
        world->DestroyBody(body);
    }
}

void Car::update(bool accelerate, bool brake, bool turnLeft, bool turnRight) {
    updateFriction();
    updateDrive(accelerate, brake);
    updateTurn(turnLeft, turnRight);
}

void Car::render(SDL_Renderer* renderer, float pixelsPerMeter) {
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();

    // Convert Box2D coordinates to screen coordinates
    int screenX = static_cast<int>(position.x * pixelsPerMeter);
    int screenY = static_cast<int>(position.y * pixelsPerMeter);

    // Calculate car corners
    float halfWidth = CAR_WIDTH / 2.0f * pixelsPerMeter;
    float halfHeight = CAR_HEIGHT / 2.0f * pixelsPerMeter;

    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);

    SDL_Point points[5];
    
    // Calculate rotated corners
    float corners[4][2] = {
        {-halfWidth, -halfHeight},
        { halfWidth, -halfHeight},
        { halfWidth,  halfHeight},
        {-halfWidth,  halfHeight}
    };

    for (int i = 0; i < 4; i++) {
        float rotatedX = corners[i][0] * cosAngle - corners[i][1] * sinAngle;
        float rotatedY = corners[i][0] * sinAngle + corners[i][1] * cosAngle;
        
        points[i].x = screenX + static_cast<int>(rotatedX);
        points[i].y = screenY + static_cast<int>(rotatedY);
    }
    points[4] = points[0]; // Close the polygon

    // Draw car body (red)
    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
    for (int i = 0; i < 4; i++) {
        SDL_RenderDrawLine(renderer, points[i].x, points[i].y, 
                          points[i + 1].x, points[i + 1].y);
    }

    // Draw car direction indicator (white line at front)
    float frontX = halfHeight * cosAngle;
    float frontY = halfHeight * sinAngle;
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, screenX, screenY,
                      screenX + static_cast<int>(frontX),
                      screenY + static_cast<int>(frontY));
}

b2Vec2 Car::getPosition() const {
    return body->GetPosition();
}

float Car::getAngle() const {
    return body->GetAngle();
}

b2Vec2 Car::getLateralVelocity() const {
    b2Vec2 currentRightNormal = body->GetWorldVector(b2Vec2(1, 0));
    return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 Car::getForwardVelocity() const {
    b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
    return b2Dot(currentForwardNormal, body->GetLinearVelocity()) * currentForwardNormal;
}

void Car::updateFriction() {
    // Kill lateral velocity (drift reduction)
    b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    
    // Apply forward friction
    b2Vec2 forwardVelocity = getForwardVelocity();
    float forwardSpeed = forwardVelocity.Length();
    
    if (forwardSpeed > 0.1f) {
        b2Vec2 dragForce = -FRICTION * forwardVelocity;
        body->ApplyForce(dragForce, body->GetWorldCenter(), true);
    } else {
        // Stop the car completely if moving very slowly
        body->SetLinearVelocity(b2Vec2(0, 0));
    }
    
    // Apply angular friction
    body->ApplyAngularImpulse(0.1f * body->GetInertia() * -body->GetAngularVelocity(), true);
}

void Car::updateDrive(bool accelerate, bool brake) {
    float desiredSpeed = 0;
    
    if (accelerate) {
        desiredSpeed = MAX_FORWARD_SPEED;
    } else if (brake) {
        desiredSpeed = MAX_BACKWARD_SPEED;
    }

    // Get current forward velocity
    b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
    float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

    // Apply force
    float force = 0;
    if (desiredSpeed > currentSpeed) {
        force = ACCELERATION;
    } else if (desiredSpeed < currentSpeed) {
        force = -ACCELERATION;
    }

    if (force != 0) {
        b2Vec2 forceVector = force * currentForwardNormal;
        body->ApplyForce(forceVector, body->GetWorldCenter(), true);
    }
}

void Car::updateTurn(bool left, bool right) {
    float desiredTorque = 0;

    // Get current speed to scale turning
    b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
    float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);
    
    // Only allow turning when moving
    if (std::abs(currentSpeed) > 0.5f) {
        if (left) {
            desiredTorque = -TURN_SPEED * (currentSpeed / MAX_FORWARD_SPEED);
        } else if (right) {
            desiredTorque = TURN_SPEED * (currentSpeed / MAX_FORWARD_SPEED);
        }
    }

    body->ApplyTorque(desiredTorque * body->GetInertia(), true);
}
