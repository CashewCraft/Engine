#include "Mouse.h"

Vector2 Mouse::Pos = Vector2();

void Mouse::SetPos() 
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	Pos = Vector2(x, y) + Camera::Position;
}
