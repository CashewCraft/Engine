#ifndef TIME_H
#define TIME_H

#include <iostream>

class Time
{
	static unsigned int Frame;
	static unsigned int FrameLimit;

	public:

	static bool UpdateFlag;
	static bool UpdateDir;
	static bool LastDir;

	static bool Ticking;

	static void Incr(bool dir);
	static unsigned int GetFrame();
};

#endif