#pragma once

#include <SDL.h>
#include <iostream>
#include <functional>

#include "Script.h"

typedef std::function<void(void)> callback_function;

class Hook
{
	protected:

	SDL_Keycode K;

	Hook() {};

	public:

	virtual void Execute(bool KeyDown) {};
	virtual bool Valid() { return false; };
};

class Hook_Once : public Hook
{
	bool UD;
	callback_function F;

	public:

	Hook_Once(bool Keydown, callback_function cb) { UD = Keydown; F = cb; };

	void Execute(bool KeyDown);
	bool Valid() { return F != NULL; };
};

class Hook_Pass : public Hook
{
	bool *ToFlip;

	public:

	Hook_Pass(bool *To) { ToFlip = To; };

	void Execute(bool KeyDown);
	bool Valid() { return ToFlip != NULL; };
};