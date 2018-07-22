#pragma once

#include "Vector2.h"

class Line
{
	Vector2 A,B;

	public:
	Line(Vector2 a, Vector2 b);

	Vector2 f(float t);
};

