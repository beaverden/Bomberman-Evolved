#include "KeyboardInput.h"



KeyboardInput::KeyboardInput()
{
}


KeyboardInput::~KeyboardInput()
{
}

void KeyboardInput::newFrame()
{
	pressedKeys.clear();
	releasedKeys.clear();
}

void KeyboardInput::keyUpEvent(const SDL_Event &event)
{
	releasedKeys[event.key.keysym.scancode] = true;
	heldKeys[event.key.keysym.scancode] = false;
}

void KeyboardInput::keyDownEvent(const SDL_Event &event)
{
	heldKeys[event.key.keysym.scancode] = true;
	pressedKeys[event.key.keysym.scancode] = true;
}

bool KeyboardInput::wasKeyPressed(SDL_Scancode key)
{
	return pressedKeys[key];
}


bool KeyboardInput::wasKeyReleased(SDL_Scancode key)
{
	return releasedKeys[key];
}

bool KeyboardInput::isKeyHeld(SDL_Scancode key)
{
	return heldKeys[key];
}
