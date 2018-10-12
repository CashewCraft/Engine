#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <SDL.h>
#include <chrono>

class Time
{
	static unsigned int Frame;
	static std::chrono::time_point<std::chrono::high_resolution_clock> t;
	static float dt;

	public:

	static void Incr();
	static unsigned int GetFrame();

	static float deltaTime();
};

#endif