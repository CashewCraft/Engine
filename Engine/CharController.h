#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include "Script.h"
#include "KeyHooks.h"
#include "Hook.h"
#include "PhysObject.h"
#include "Time.h"
#include "Mouse.h"
#include "Camera.h"
#include "LoaderTool.h"
#include "Projectile.h"
#include "SettingLoader.h"
#include "Sound.h"

#include <iostream>
#include <algorithm>
#include <functional>

#include "PhysObject.h"
#include "Sound.h"

class CharController : public Script
{
	PhysObject *GameObject;

	Sound *ThrustNoise;

	bool Firing = false;
	bool Thrust = false;
	bool Slow = false;

	double FireRate = 0.1;
	double Limiter = 0;

	protected:

	void Init();

	public:

	CharController(Object* a) : Script(a) { Init(); };
	CharController() : Script() {};

	void Release();

	void Update();

	void Shoot();

	void OnCollision(Object *hit);

	virtual Script* Clone(Object* Target);
};

