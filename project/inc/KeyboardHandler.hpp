#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class KeyboardHandler {
public:
    KeyboardHandler() : rotation(0.0f) {}
    void processInput();

    glm::vec3 getRotation() const {
        return rotation;
    }

private:
    glm::vec3 rotation;
};