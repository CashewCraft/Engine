#include "TimeControl.h"

void TimeControl::InitHooks()
{
	KeyHooks::Register(Hook(false, SDLK_UP), std::bind(&TimeControl::SkipFrame, this));
	KeyHooks::Register(Hook(false, SDLK_DOWN), std::bind(&TimeControl::RevFrame, this));
}

void TimeControl::SkipFrame()
{
	std::cout << "Skip\n";
	Time::Incr(true);
}


void TimeControl::RevFrame()
{
	Time::Incr(false);
}
