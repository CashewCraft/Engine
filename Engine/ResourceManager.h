#pragma once

#include <map>
#include <SDL.h>
#include <SDL_mixer.h>

#include "Debug.h"

class ResourceManager
{
	public:

	static SDL_Renderer *r;

	static std::map<std::string, SDL_Texture*> ResourceDict;
	static std::map<std::string, Mix_Chunk*> SoundDict;

	static SDL_Texture* GetSprite(std::string Name);
};

