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

	PhysObject *Player;

	Vector2 InsideCircle(double radius);

	AI(Object* a, PhysObject *p) : Script(a) { GameObject = (PhysObject*)Linked; Player = p; Target = InsideCircle(10); GameObject->body.MaxForce = 0.005; };

	void Update();

	Vector2 Wander();

	Vector2 Chase();
};

