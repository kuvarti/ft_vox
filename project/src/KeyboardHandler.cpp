#include "KeyboardHandler.hpp"

void KeyboardHandler::processInput() {
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_A]) {
        position.x -= 0.1f;
    }
    if (state[SDL_SCANCODE_D]) {
        position.x += 0.1f;
    }
    if (state[SDL_SCANCODE_W]) {
        position.z -= 0.1f;
    }
    if (state[SDL_SCANCODE_S]) {
        position.z += 0.1f;
    }
}

void KeyboardHandler::handleMouseMotion(int xrel, int yrel) {
    rotation.y += xrel * 0.1f;
    rotation.x -= yrel * 0.1f;
}