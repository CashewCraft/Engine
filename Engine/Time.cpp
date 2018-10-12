#include "time.h"

unsigned int Time::Frame = 0;
std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();

void Time::Incr()
{
	std::chrono::high_resolution_clock::time_point t2;
	dt = std::chrono::duration_cast<std::chrono::duration<float>>(t2 - t).count();
	t = t2;
	Frame++;
}

unsigned int Time::GetFrame()
{
	return Frame;
}

float Time::deltaTime() { return dt; }