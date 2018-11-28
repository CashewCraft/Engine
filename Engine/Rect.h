#ifndef RECT_H
#define RECT_H

#include <SDL.h>
#include <algorithm>
#include "Vector2.h"
#include "Camera.h"

class Rect
{
	public:

	Vector2 Pos;
	Vector2 Len;
	Vector2 Rot;

	SDL_Rect SDLf;

	Rect(Vector2 pos, Vector2 rot, int lenX, int lenY);

	Rect();

	bool GetCollision(Rect Other);
};

#endif