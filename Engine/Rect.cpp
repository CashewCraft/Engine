#include "Rect.h"

Rect::Rect(Vector2 pos, int lenX, int lenY)
{
	Pos = pos;
	Len = Vector2(lenX, lenY);
	SDLf.x = (Pos.x-(lenX/2)) - Camera::Position.x;
	SDLf.y = (Pos.y-(lenY/2)) - Camera::Position.y;
	SDLf.w = lenX;
	SDLf.h = lenY;
}

Rect::Rect() {}
