#include "Controller.hpp"

void Controller::processInput() {
    const Uint8* state = SDL_GetKeyboardState(NULL);

    glm::vec3 forward = getForwardVector();
    glm::vec3 right = getRightVector();

    if (state[SDL_SCANCODE_W]) {
        position += forward * movementSpeed; // Move forward
    }
    if (state[SDL_SCANCODE_S]) {
        position -= forward * movementSpeed; // Move backward
    }
    if (state[SDL_SCANCODE_A]) {
        position -= right * movementSpeed; // Move left
    }
    if (state[SDL_SCANCODE_D]) {
        position += right * movementSpeed; // Move right
    }
    if (state[SDL_SCANCODE_Q]) {
        position.y -= movementSpeed; // Move down
    }
    if (state[SDL_SCANCODE_E]) {
        position.y += movementSpeed; // Move up
    }

    if (state[SDL_SCANCODE_LEFT]) {
        rotation.y -= rotationSpeed;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        rotation.y += rotationSpeed;
    }
}

void Controller::handleMouseMotion(int xrel, int yrel) {
    // rotation.y += xrel * rotationSpeed;
    // rotation.x -= yrel * rotationSpeed;
}

glm::vec3 Controller::getForwardVector() const {
    glm::vec3 forward;
    forward.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    forward.y = sin(glm::radians(rotation.x));
    forward.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    return glm::normalize(forward);
}

glm::vec3 Controller::getRightVector() const {
    glm::vec3 forward = getForwardVector();
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    return glm::normalize(glm::cross(forward, up));
}