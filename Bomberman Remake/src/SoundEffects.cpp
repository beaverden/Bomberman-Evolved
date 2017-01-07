#include "SoundEffects.h"
#include "globals.h"

Map <std::string, Mix_Chunk*> SoundEffects::effects;
Map <std::string, Vector<Mix_Chunk*>> SoundEffects::commonEffects;
Map <std::string, Mix_Music*> SoundEffects::music;

SoundEffects::SoundEffects() {}


SoundEffects::~SoundEffects() {}

void SoundEffects::init()
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		if (Globals::DEBUG) printf("Can't open audio: %s\n", SDL_GetError());
	}
	Mix_Volume(-1, MIX_MAX_VOLUME/8);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 10);

	Mix_Chunk* happy1 = loadChunk("resources/Sounds/Happy1.wav");
	Mix_VolumeChunk(happy1, MIX_MAX_VOLUME / 5);
	commonEffects["Happy"].push_back(happy1);
	Mix_Chunk* happy2 = loadChunk("resources/Sounds/Happy2.wav");
	Mix_VolumeChunk(happy2, MIX_MAX_VOLUME / 5);
	commonEffects["Happy"].push_back(happy2);
	Mix_Chunk* happy3 = loadChunk("resources/Sounds/Happy3.wav");
	Mix_VolumeChunk(happy3, MIX_MAX_VOLUME / 5);
	commonEffects["Happy"].push_back(happy3);


	commonEffects["Boom"].push_back(loadChunk("resources/Sounds/boom1.wav"));
	commonEffects["Boom"].push_back(loadChunk("resources/Sounds/boom2.wav"));

	commonEffects["EnemyHit"].push_back(loadChunk("resources/Sounds/Enemy_hit1.wav"));
	commonEffects["EnemyHit"].push_back(loadChunk("resources/Sounds/Enemy_hit2.wav"));

	commonEffects["GotHit"].push_back(loadChunk("resources/Sounds/Got_hit1.wav"));
	commonEffects["GotHit"].push_back(loadChunk("resources/Sounds/Got_hit2.wav"));

	commonEffects["Win"].push_back(loadChunk("resources/Sounds/I_won.wav"));
	commonEffects["TimeOver"].push_back(loadChunk("resources/Sounds/Time_over.wav"));
	commonEffects["Lost"].push_back(loadChunk("resources/Sounds/I_lost.wav"));
}

void SoundEffects::destroy()
{
	effects.clear();
	music.clear();
	commonEffects.clear();
}

Mix_Chunk* SoundEffects::loadChunk(std::string chunkPath)
{
	Mix_Chunk* chunk = effects[chunkPath];
	if (!chunk)
	{
		chunk = Mix_LoadWAV(chunkPath.c_str());
		if (!chunk)
		{
			if (Globals::DEBUG) printf("Error loading sound %s : %s\n", chunkPath, SDL_GetError());
		}
		else
		{
			effects[chunkPath] = chunk;
		}
	}
	return chunk;
}

Mix_Music* SoundEffects::loadMusic(std::string musicPath)
{
	Mix_Music* mus = music[musicPath];
	if (!mus)
	{
		mus = Mix_LoadMUS(musicPath.c_str());
		if (!mus)
		{
			if (Globals::DEBUG) printf("Error loading sound %s : %s\n", musicPath, SDL_GetError());
		}
		else
		{
			music[musicPath] = mus;
		}
	}
	return mus;
}

void SoundEffects::playEffect(std::string name)
{
	int effectsSize = commonEffects[name].size();
	int randomIndex = rand() % effectsSize;
	Mix_PlayChannel(-1, commonEffects[name][randomIndex], 0);
}

void SoundEffects::playMusic(std::string musicPath)
{
	Mix_PlayMusic(loadMusic(musicPath), -1);
}

void SoundEffects::turnVolumeOff()
{
	Mix_Volume(-1, 0);
	Mix_VolumeMusic(0);
}

void SoundEffects::turnVolumeOn()
{
	Mix_Volume(-1, MIX_MAX_VOLUME / 8);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 10);
}