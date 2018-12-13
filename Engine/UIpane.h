#pragma once
#include "Hierachy.h"

#ifndef SCRIPT_H
class Script;
#endif

class UIpane : public Object
{	public:

	Vector2 Offset = Vector2();
	Vector2 RelativeSize = Vector2();
	Vector2 Anchor = Vector2();

	UIpane(SDL_Texture *Card) : UIpane(Card, Vector2(), Vector2(), Vector2()) {};
	UIpane(SDL_Texture *Card, Vector2 Anchor, Vector2 Size, Vector2 Offset);

	void Update();

	protected:

	virtual Object* Clone(ObjectData* From);
};

