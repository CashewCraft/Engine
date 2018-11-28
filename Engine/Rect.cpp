#include "Rect.h"

Rect::Rect(Vector2 pos, Vector2 rot, int lenX, int lenY)
{
	Rot = rot;
	Pos = pos;
	Len = Vector2(lenX, lenY);
	SDLf.x = (Pos.x-(lenX/2)) - Camera::Position.x;
	SDLf.y = (Pos.y-(lenY/2)) - Camera::Position.y;
	SDLf.w = lenX;
	SDLf.h = lenY;
}

Rect::Rect() {}

bool Rect::GetCollision(Rect Other)
{
	return (Pos-Other.Pos).Magnitude() < ((std::max(Other.Len.x, Other.Len.y) / 2) + (std::max(Len.x, Len.y) / 2));
}