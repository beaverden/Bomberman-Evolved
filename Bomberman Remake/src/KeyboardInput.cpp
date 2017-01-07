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
	this->closePressed = false;
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

void KeyboardInput::processInputs()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			this->closePressed = true;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.repeat == 0)
			{
				keyDownEvent(event);
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			keyUpEvent(event);
		}
		else if (event.type == SDL_QUIT)
		{
			return;
		}
	}
}

SDL_Event& KeyboardInput::getEvent()
{
	return this->event;
}