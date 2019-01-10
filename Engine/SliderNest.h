#pragma once

#include "Script.h"
#include "Button.h"
#include "UIpane.h"

class SliderNest : public Script
{
	public:
	SliderNest(Object* a, ScriptData s);
	SliderNest() : Script() {};

	Script* Clone(Object* Target, ScriptData In)
	{
		return new SliderNest(Target, In);
	}
};

