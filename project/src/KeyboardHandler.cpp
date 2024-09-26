#include "KeyboardHandler.hpp"

void KeyboardHandler::processInput() {
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_A]) {
        position.x -= movementSpeed;
    }
    if (state[SDL_SCANCODE_D]) {
        position.x += movementSpeed;
    }
    if (state[SDL_SCANCODE_W]) {
        position.z -= movementSpeed;
    }
    if (state[SDL_SCANCODE_S]) {
        position.z += movementSpeed;
    }
}

void KeyboardHandler::handleMouseMotion(int xrel, int yrel) {
    rotation.y += xrel * rotationSpeed;
    rotation.x -= yrel * rotationSpeed;
}