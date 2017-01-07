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

	/*
	Plays a Mix_Chunk on all the channels
	All the chunks are stored by a specific alias, for example: "Happy", "TimeOver", etc
	Picks a random effects if there are more of them, for example: Happy1, Happy2, Happy3
	@param name alias of the effect
	*/
	static void playEffect(std::string name);

	/*
	Plays music on the single channel
	@param path to music file
	*/
	static void playMusic(std::string musicPath);

	static void turnVolumeOff();

	static void turnVolumeOn();

private:
	static Map <std::string, Mix_Chunk*> effects;
	static Map <std::string, Mix_Music*> music;
	static Map <std::string, Vector<Mix_Chunk*>> commonEffects;

	/*
	Loads the chunk if not loaded already. 
	If loaded returns the existing one
	*/
	static Mix_Chunk* loadChunk(std::string chunkPath);

	/*
	Loads the music file if not loaded already.
	If loaded returns the existing one
	*/
	static Mix_Music* loadMusic(std::string musicPath);
};

#endif /* SOUND_EFFECTS_H */

