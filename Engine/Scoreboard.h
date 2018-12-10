#pragma once

#include <SDL.h>
#include <functional>

#include "Script.h"
#include "UIPane.h"
#include "TextGenerator.h"
#include "KeyHooks.h"

class Scoreboard : public Script
{
	UIpane *Title;

	int Round = 0;

	SDL_Texture *Numbers[10];

	protected:

	void Init();

	public:

	Scoreboard(Object* a) : Script(a) { Init(); };


	void IncrRound();
};

