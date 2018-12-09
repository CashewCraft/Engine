#pragma once

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Hierachy.h"

class TextGenerator
{
	static std::map<std::string, TTF_Font*> Fonts;

	public:

	static SDL_Texture* GenText(std::string Font, int Size, SDL_Colour Colour, std::string Text);

	static void PrepareFont(std::string Font, int Size);
};

