#pragma once

#include "Script.h"
#include "Time.h"
#include "Hook.h"
#include "KeyHooks.h"

#include <iostream>

class TimeControl : public Script
{
	virtual void InitHooks();

	public:
	TimeControl() : Script(NULL) { InitHooks(); };

	void SkipFrame();
	void RevFrame();
};

