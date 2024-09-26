#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Controller {
public:
    Controller() 
        : rotation(0.0f), position(0.0f), lastMousePosition(0.0f), 
          movementSpeed(0.1f), rotationSpeed(0.001f) {}

    void processInput();
    void handleMouseMotion(int xrel, int yrel);

    glm::vec3 getRotation() const {
        return rotation;
    }

    glm::vec3 getPosition() const {
        return position;
    }

private:
    glm::vec3 rotation;
    glm::vec3 position;
    glm::vec2 lastMousePosition;
    float movementSpeed;
    float rotationSpeed;
};