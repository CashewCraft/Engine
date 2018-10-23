#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2.h"
#include <SDL.h>

class transform
{
	public:
	Vector2 Position;
	Vector2 Rotation;

	static const double Rad2Deg;
	static const double Pi;

	double GetRotAngle();
};

#endif