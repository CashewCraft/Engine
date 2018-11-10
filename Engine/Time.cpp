#include "time.h"

unsigned int Time::Frame = 0;
TimePoint Time::t = Clock::now();
double Time::dt = 0;

void Time::Incr()
{
	//std::cout << std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t).count() * 0.000001 << "\n";
	//Debug::Log("Took " + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t).count() * 1e-6));
	dt = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t).count() * 1e-6;
	t = Clock::now();

	Frame++;
}

unsigned int Time::GetFrame()
{
	return Frame;
}

double Time::deltaTime() { return dt; }