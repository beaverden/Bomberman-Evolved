#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite() {};


AnimatedSprite::AnimatedSprite(const std::string &filepath, SDL_Rect rect) :
	Sprite(filepath, rect)
{
	this->currentAnimation = "null";
	this->currentAnimationFrame = 0;
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

void AnimatedSprite::nextStep()
{
	currentAnimationFrame++;
	int maxSteps = animationFrames[currentAnimation].size();
	if (currentAnimationFrame == maxSteps)
		currentAnimationFrame = 0;
}

void AnimatedSprite::playAnimation(std::string animationName)
{
	if (hasAnimation(animationName))
	{
		if (animationName == currentAnimation)
		{
			nextStep();
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