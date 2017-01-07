#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite() {};


AnimatedSprite::AnimatedSprite(const std::string &filepath, SDL_Rect rect, int timeToUpdate) :
	Sprite(filepath, rect)
{
	this->currentAnimation = "null";
	this->currentAnimationFrame = 0;
	this->timeToUpdate = timeToUpdate;
	this->currentElapsedTime = 0;
	this->lastUpdateTime = SDL_GetTicks();
}

AnimatedSprite::~AnimatedSprite() {}

void AnimatedSprite::addAnimationFrame(std::string animationName, int x, int y, int w, int h)
{
	animationFrames[animationName].push_back({ x, y, w, h });
}

void AnimatedSprite::setAnimation(std::string animationName, int step)
{
	this->currentAnimation = animationName;
	this->currentAnimationFrame = step;
	setCurrentSpriteRect();
}

SDL_Rect AnimatedSprite::getAnimationFrame(std::string animationName, int frame)
{
	if (hasAnimation(animationName))
	{
		if (animationFrames[animationName].size() > frame)
		{
			return animationFrames[animationName][frame];
		}
	}
}

void AnimatedSprite::setTimeToUpdate(int newTimeToUpdate)
{
	this->timeToUpdate = newTimeToUpdate;
}

void AnimatedSprite::nextFrame()
{
	currentAnimationFrame++;
	int maxSteps = animationFrames[currentAnimation].size();
	if (currentAnimationFrame == maxSteps)
		currentAnimationFrame = 0;
	setCurrentSpriteRect();
}

void AnimatedSprite::playAnimation(std::string animationName)
{
	if (hasAnimation(animationName))
	{
		const int CURRENT_TIME = SDL_GetTicks();
		if (CURRENT_TIME - lastUpdateTime < timeToUpdate) return;
		else
		{
			lastUpdateTime = CURRENT_TIME;
		}
		if (animationName == currentAnimation)
		{
			nextFrame();
		}
		else
		{
			currentAnimation = animationName;
			currentAnimationFrame = 0;
		}
		setCurrentSpriteRect();
	}
	else
	{
		throw std::invalid_argument("No such animation");
	}
};

bool AnimatedSprite::hasAnimation(std::string animationName)
{
	return animationFrames.hasKey(animationName);
}


void AnimatedSprite::setCurrentSpriteRect()
{
	this->usedRect = animationFrames[currentAnimation][currentAnimationFrame];
}