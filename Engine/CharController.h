#pragma once

#include <SDL.h>

#include "Script.h"
#include "KeyHooks.h"
#include "Hook.h"
#include "PhysObject.h"
#include "Move.h"
#include <iostream>
#include <functional>

class CharController : public Script
{
	virtual void InitHooks();
	PhysObject *GameObject;

	public:

	CharController(Object* a) : Script(a) { GameObject = (PhysObject *)Linked; InitHooks(); };

	void AddMoveLeft();
	void ReMoveLeft();
};

