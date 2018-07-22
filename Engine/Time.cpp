#include "time.h"

unsigned int Time::Frame = 0;
unsigned int Time::FrameLimit = 128;

bool Time::Ticking = false;

bool Time::UpdateFlag = false;
bool Time::UpdateDir = true;
bool Time::LastDir = true;

void Time::Incr(bool dir)
{
	LastDir = UpdateDir;
	UpdateDir = dir;

	if ((dir && Frame == FrameLimit) || (!dir && Frame == 0))
	{
		return;
	}

	UpdateFlag = true;

	Frame += (dir) ? 1 : -1;
}

unsigned int Time::GetFrame()
{
	return Frame;
}