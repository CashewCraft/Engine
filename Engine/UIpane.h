#pragma once
#include "Hierachy.h"
class UIpane : public Object
{
	bool Anchored = false;

	public:

	bool ModSize = false;

	Vector2 Offset = Vector2();
	Vector2 Relative = Vector2();
	Vector2 Anchor = Vector2();

	UIpane(SDL_Texture *Card, bool Modsize, Vector2 Pos, Vector2 Size);
	UIpane(SDL_Texture *Card, bool Modsize, Vector2 Pos, Vector2 Size, Vector2 Anchor);

	void Update();
};

