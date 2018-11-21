#pragma once

#include "Vector2.h"
#include "Camera.h"
#include "Hierachy.h"

#include <iostream>
#include <fstream>
#include <ctime>

class Debug
{
	static std::ofstream File;

	static void Output(std::string MSG);

	public:

	static void Init();
	static void Close();

	static void DrawLine(Vector2 a, Vector2 b);
	static void DrawSquare(Vector2 a, Vector2 b);

	static void Log(std::string out);
	static void Error(std::string out);
	static void Flag(std::string out);
	static void Custom(std::string Flag, std::string out);
};

