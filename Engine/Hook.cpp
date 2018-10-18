#include "Hook.h"

Hook::Hook(bool KeyDown, int key, bool repeat)
{
	UD = KeyDown;
	K = key;
	R = repeat;
}