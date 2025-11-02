//
// Created by muham on 30.10.2025.
//

#include "input.hpp"

using namespace mind;

VortexInput::VortexInput() : keyboardState(nullptr) {}

VortexInput::~VortexInput() {
    Shutdown();
}

void VortexInput::handleEvent(const SDL_Event &e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.repeat == 0) {
            currentKeyStates[e.key.keysym.scancode] = true;
        }
    } else if (e.type == SDL_KEYUP) {
        currentKeyStates[e.key.keysym.scancode] = false;
    }
}

void VortexInput::update() {
    if (keyboardState) {
        for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
            currentKeyStates[static_cast<SDL_Scancode>(i)] = keyboardState[i] != 0;
        }
    }

    previousKeyStates = currentKeyStates;
}

bool VortexInput::isPressed(const SDL_Scancode key) const {
    if (keyboardState) {
        return keyboardState[static_cast<int>(key)] != 0;
    }
    return currentKeyStates.contains(key) ? currentKeyStates.at(key) : false;
}

void VortexInput::Shutdown() {
    keyboardState = nullptr;

    currentKeyStates.clear();
    previousKeyStates.clear();
}