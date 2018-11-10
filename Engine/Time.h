#ifndef TIME_H
#define TIME_H

#include "Debug.h"

#include <iostream>
#include <SDL.h>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::steady_clock::time_point TimePoint;

class Time
{
	static unsigned int Frame;
	static TimePoint t;
	static double dt;

	public:

	static void Incr();
	static unsigned int GetFrame();

	static double deltaTime();
};

#endif