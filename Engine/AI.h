#pragma once
#include "Script.h"
#include "PhysObject.h"
#include "Camera.h"
#include "Mouse.h"

#include <iostream>
#include <random>

class AI : public Script
{
	PhysObject *GameObject;
	Vector2 Target;

	void InitHooks();

	double GetAngle(Vector2 p1, Vector2 p2);

	Vector2 InsideCircle(double radius);

	public:

	AI(Object* a) : Script(a) { GameObject = (PhysObject*)Linked; Target = InsideCircle(10); };

	void Update();
};

