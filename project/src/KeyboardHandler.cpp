#include "KeyboardHandler.hpp"

//processInput
void KeyboardHandler::processInput() {
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_A]) {
		rotation.y -= glm::radians(1.0f);
	}
	if (state[SDL_SCANCODE_D]) {
		rotation.y += glm::radians(1.0f);
	}
	if (state[SDL_SCANCODE_W]) {
		rotation.x -= glm::radians(1.0f);
	}
	if (state[SDL_SCANCODE_S]) {
		rotation.x += glm::radians(1.0f);
	}
}
