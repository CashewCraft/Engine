#pragma once

#include <SDL.h>
#include <functional>

#include "Script.h"
#include "UIPane.h"
#include "TextGenerator.h"
#include "KeyHooks.h"
#include "Time.h"

class Scoreboard : public Script
{
	UIpane *Title;
	UIpane *Tim;

	unsigned int Round = 0;

	static SDL_Texture *Numbers[10];

	double Timer = 60;

	protected:

	void Init();

	public:

	Scoreboard(Object* a) : Script(a) { Init(); };

	void IncrRound();
	static void SetNumbers(Object* parent, unsigned int Number, Vector2 Anchor, Vector2 Size, Vector2 Offset);

	void Update();
};

