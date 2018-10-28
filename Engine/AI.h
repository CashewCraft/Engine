#pragma once
#include "Script.h"
#include "PhysObject.h"
#include "Camera.h"
#include "Mouse.h"
#include "Debug.h"

#include <iostream>
#include <random>

class AI : public Script
{
	PhysObject *GameObject;
	Vector2 Target;

	double Speed = 2;

	virtual void InitHooks();

	double GetAngle(Vector2 p1, Vector2 p2);

	public:

	Vector2 InsideCircle(double radius);

	AI(Object* a) : Script(a) { GameObject = (PhysObject*)Linked; Target = InsideCircle(10); GameObject->body.MaxForce = 0.005; };

	void Update();
};

