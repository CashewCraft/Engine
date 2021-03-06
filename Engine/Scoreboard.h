#pragma once

#include <SDL.h>
#include <functional>

#include "Script.h"
#include "UIPane.h"
#include "TextGenerator.h"
#include "KeyHooks.h"
#include "Time.h"
#include "Button.h"
#include "StateManager.h"

class Scoreboard : public Script
{
	UIpane *Title;
	UIpane *Tim;

	static SDL_Texture *Numbers[10];

	double Timer = 60;

	protected:

	void Init();

	public:

	static Scoreboard *ins;

	Scoreboard(Object* a) : Script(a) { Init(); };
	Scoreboard(Object* a, ScriptData In) : Scoreboard(a) {};
	Scoreboard() : Script() {};

	virtual void Release();

	void IncrScore(int amount);
	static void SetNumbers(Object* parent, unsigned int Number, Vector2 Anchor, Vector2 Size, Vector2 Offset);

	void Update();

	virtual Script* Clone(Object* Target, ScriptData In) { return new Scoreboard(Target, In); };
};

