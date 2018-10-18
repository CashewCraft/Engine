#include "time.h"

unsigned int Time::Frame = 0;
TimePoint Time::t = Clock::now();
double Time::dt = 0;

void Time::Incr()
{
	//std::cout << std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t).count() * 0.000001 << "\n";
	dt = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t).count() * 0.01;
	t = Clock::now();

	Frame++;
}

unsigned int Time::GetFrame()
{
	return Frame;
}

double Time::deltaTime() { return dt; }