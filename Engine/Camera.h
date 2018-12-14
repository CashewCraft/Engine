#pragma once
#include "transform.h"
#include "Vector2.h"

class Camera
{
	public:

	//0 = windowed, 1 = windowed, 2 = fullscreen
	static int WindowMode;

	static Vector2 Position;
	static Vector2 Size;
};

