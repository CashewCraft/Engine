#include "Rect.h"

Rect::Rect(Vector2 pos, int lenX, int lenY)
{
	Pos = pos;
	Len = Vector2(lenX, lenY);
	SDLf.x = Pos.x;
	SDLf.y = Pos.y;
	SDLf.w = lenX;
	SDLf.h = lenY;
}

Rect::Rect() {}
