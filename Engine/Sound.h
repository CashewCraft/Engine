#pragma once

#include <SDL_mixer.h>
#include <string>

#include "ResourceManager.h"

class Sound
{
	Mix_Chunk *Track;
	int Channel;
	bool Playing = false;

	bool Fore;

	public:

	static bool ForeMuted;
	static bool BackMuted;
	static int ForeVolume;
	static int BackVolume;

	Sound(std::string Name, bool Fore);
	~Sound();

	void PlayOnce();
	void Play();
	void Stop();
};

