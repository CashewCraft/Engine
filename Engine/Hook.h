#pragma once

#include <SDL.h>
#include <iostream>
#include <functional>

#include "Script.h"

typedef std::function<void(void)> callback_function;

class Hook
{
	public:

	bool UD;
	bool R;
	callback_function F;

	Hook(bool Keydown, callback_function cb, bool Repeat = false);
};