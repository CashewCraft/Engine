#pragma once

#include <SDL_mixer.h>
#include <string>

#include "LoaderTool.h"

class Sound
{
	static int Volume;

	Mix_Chunk *Track;
	int Channel;
	bool Playing = false;

	public:
	Sound(std::string Name);
	~Sound();

	void PlayOnce();
	void Play();
	void Stop();
};

