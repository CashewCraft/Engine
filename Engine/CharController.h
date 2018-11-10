#pragma once

#include <SDL.h>

#include "Script.h"
#include "KeyHooks.h"
#include "Hook.h"
#include "PhysObject.h"
#include "Time.h"
#include "Mouse.h"
#include "Camera.h"
#include "LoaderTool.h"
#include "Projectile.h"

//#include "SpacialHash"
#include <iostream>
#include <algorithm>
#include <functional>

class CharController : public Script
{
	virtual void InitHooks();
	PhysObject *GameObject;

	bool Firing = false;
	bool Thrust = false;
	bool Slow = false;

	double FireRate = 0.1;
	double Limiter = 0;

	public:

	CharController(Object* a) : Script(a) { GameObject = (PhysObject*)Linked; InitHooks(); };

	void Update();

	void Shoot();

	void OnCollision(Object *hit);
};

