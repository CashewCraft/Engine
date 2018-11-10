#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <map>
#include <string>

//#include "Debug.h"

class Sprite
{
	std::map<std::string, SDL_Texture*> Frames = std::map<std::string, SDL_Texture*>();
	std::string State = "";
	SDL_Texture *Default = NULL;

	public:
	Sprite() {}
	Sprite(SDL_Texture *Default);

	SDL_Texture *GetCurrSprite();
	void SetState(std::string State);
	void AddFrame(std::string Name, SDL_Texture *Resource);
};

#endif