#pragma once

#include "Camera.h"
#include "Vector2.h"
#include <SDL.h>

class Mouse
{
	public:
		static Vector2 Pos;
		static bool Controller;
		static SDL_Joystick *CInstance;

		static void SetPos();
};

