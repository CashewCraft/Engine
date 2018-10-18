#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2.h"

class transform
{
	public:
	Vector2 Position;
	Vector2 Rotation;

	double GetRotAngle();
};

#endif