#pragma once
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

private:
	Map <SDL_Scancode, bool> heldKeys;
	Map <SDL_Scancode, bool> releasedKeys;
	Map <SDL_Scancode, bool> pressedKeys;
};

