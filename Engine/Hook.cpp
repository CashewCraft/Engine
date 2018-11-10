#include "Hook.h"

void Hook_Once::Execute(bool KeyDown)
{
	if (KeyDown == UD)
	{
		F();
	}
}

void Hook_Pass::Execute(bool KeyDown)
{
	*ToFlip = KeyDown;
}