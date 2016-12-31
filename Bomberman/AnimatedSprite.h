#pragma once
#ifndef  ANIMATED_SPRITE_H
#define  ANIMATED_SPRITE_H

#include "Sprite.h"
#include "SDL.h"
#include "Vector.h"
#include "Map.h"
#include "Pair.h"
#include <stdexcept>

class AnimatedSprite :
	public Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(const std::string &filepath, SDL_Rect rect);
	~AnimatedSprite();

	/**
		Adds a frame to an animation, which is a part of it's texture
		@param animation name, ex: walk_left, idle_up, defaut
		@param x position of the top left corner
		@param y position of the top left corner
		@param w width of the animation image
		@param h height of the animation image
	*/
	void addAnimationFrame(std::string animationName, int x, int y, int w, int h);

	/**
		Sets the new current animation and the current frame
		@param animationName of the new animation (it must exist in the map)
		@param frame of the animation, by default is set to 0
	*/
	void setAnimation(std::string animationName, int frame = 0);



	/**
		Moves the current animation to the next frame
		If there are no more frames - resets the current frame to 0
	*/
	void nextFrame();

	/*
		Sets the new animation or advances to the next frame
		@param animationName to be played
	*/
	void playAnimation(std::string animationName);

	/**
		Checks whether the map contains any frame of the give animation
		@param animationName to be checked if exists
	*/
	bool hasAnimation(std::string animationName);

private:
	Map <std::string, Vector <SDL_Rect>> animationFrames;
	std::string currentAnimation;
	int currentAnimationFrame;

	void setCurrentSpriteRect();
};

#endif /* ANIMATED_SPRITE_H */

