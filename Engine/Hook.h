#pragma once

#include <SDL.h>
#include <iostream>
#include <functional>

typedef std::function<void(void)> callback_function;

class Hook
{
	callback_function F;

	public:

	bool Zombie = false; //flag to let the hooking system know if this hook isn't being used anymore

	Hook(callback_function cb) { F = cb; };

	void Execute() { F(); };
	bool Valid() { return !Zombie; };
};