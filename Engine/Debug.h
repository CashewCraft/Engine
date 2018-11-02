#pragma once

#include "Vector2.h"
#include "Camera.h"
#include "Hierachy.h"

#include <iostream>

class Debug
{
	public:

	static void DrawLine(Vector2 a, Vector2 b);
	static void Log(std::string out, char *end = (char*)"\n");
};

