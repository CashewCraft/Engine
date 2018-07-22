#pragma once
#include "Move.h"
class MoveCap :
	public Move
{
	public:

	bool IsCap = false;

	MoveCap(Vector2 a, unsigned int b) : Move(a, b) { IsCap = true; }
};

