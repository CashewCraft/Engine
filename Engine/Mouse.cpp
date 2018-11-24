#include "Mouse.h"

Vector2 Mouse::Pos = Vector2();
bool Mouse::Controller = false;
SDL_Joystick *Mouse::CInstance = nullptr;

void Mouse::SetPos() 
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	Pos = Vector2(x, y) + Camera::Position;
}