#pragma once
#include "Script.h"
#include "PhysObject.h"
#include "Camera.h"
#include "Mouse.h"
#include "Debug.h"

#include "Scoreboard.h"

#include <iostream>
#include <random>

class AI : public Script
{
	PhysObject *GameObject;
	Vector2 Target;

	double Speed = 2;

	virtual void Init();

	double GetAngle(Vector2 p1, Vector2 p2);

	public:

	PhysObject *Player;

	Vector2 InsideCircle(double radius);

	AI(Object* a) : Script(a) { GameObject = (PhysObject*)Linked; Target = InsideCircle(10); Init(); };
	AI(Object* a, ScriptData i) : AI(a) {};
	AI() : Script() {};

	virtual void Release();

	void Update();

	Vector2 Wander();

	Vector2 Chase();

	virtual Script* Clone(Object* Target, ScriptData In) { return new AI(Target, In); };
};

