#ifndef RECT_H
#define RECT_H

#include <SDL.h>
#include "Vector2.h"

class Rect
{
	public:

	Vector2 Pos;
	Vector2 Len;

	SDL_Rect SDLf;

	Rect(Vector2 pos, int lenX, int lenY);

	Rect();
};

#endif