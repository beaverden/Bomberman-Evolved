#pragma once
#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include "Map.h"
#include "SDL.h"

class KeyboardInput
{
public:
	KeyboardInput();
	~KeyboardInput();

	void newFrame();

	void keyUpEvent(const SDL_Event &event);
	void keyDownEvent(const SDL_Event &event);

	bool wasKeyPressed(SDL_Scancode key);
	bool wasKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);

	void processInputs();

	SDL_Event& getEvent();

	bool closePressed;
private:
	Map <SDL_Scancode, bool> heldKeys;
	Map <SDL_Scancode, bool> releasedKeys;
	Map <SDL_Scancode, bool> pressedKeys;
	SDL_Event event;
};

#endif /* KEYBOARD_INPUT_H */

