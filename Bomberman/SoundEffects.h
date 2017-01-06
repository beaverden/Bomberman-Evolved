#pragma once
#ifndef SOUND_EFFECTS_H
#define SOUND_EFFECTS_H

#include "Map.h"
#include "Vector.h"
#include "SDL_mixer.h"
class SoundEffects
{
public:
	SoundEffects();
	~SoundEffects();

	static void init();

	static void destroy();

	static void playEffect(std::string name);

	static void playMusic(std::string musicPath);

private:
	static Map <std::string, Mix_Chunk*> effects;
	static Map <std::string, Mix_Music*> music;
	static Map <std::string, Vector<Mix_Chunk*>> commonEffects;

	static Mix_Chunk* loadChunk(std::string chunkPath);
	
	static Mix_Music* loadMusic(std::string musicPath);
};

#endif /* SOUND_EFFECTS_H */

