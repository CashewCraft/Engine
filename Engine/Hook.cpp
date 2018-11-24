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
	Debug::Log(std::to_string(KeyDown));
	*ToFlip = KeyDown;
}