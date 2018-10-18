#include "Mouse.h"

Vector2 Mouse::Pos = Vector2();

void Mouse::SetPos() 
{
	SDL_GetMouseState((int*)(&Pos.x), (int*)(&Pos.y));
}
