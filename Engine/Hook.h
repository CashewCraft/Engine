#pragma once

#include <SDL.h>
#include <iostream>
#include <functional>

#include "Script.h"

typedef std::function<void(void)> callback_function;

class Hook
{
	callback_function F;

	public:

	Hook(callback_function cb) { F = cb; };

	void Execute() { F(); };
	bool Valid() { return F != NULL; };
};