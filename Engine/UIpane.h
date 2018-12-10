#pragma once
#include "Hierachy.h"
class UIpane : public Object
{	public:

	Vector2 Offset = Vector2();
	Vector2 RelativeSize = Vector2();
	Vector2 Anchor = Vector2();

	UIpane(SDL_Texture *Card, Vector2 Anchor, Vector2 Size, Vector2 Offset);

	void Update();
};

