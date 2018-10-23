#include "Hook.h"

Hook::Hook(bool KeyDown, callback_function cb, bool repeat)
{
	UD = KeyDown;
	R = repeat;
	F = cb;
}