#pragma once

#include "Vector2.h"
#include "Camera.h"
#include "Hierachy.h"

#include <iostream>
#include <fstream>

class Debug
{
	static std::fstream File;

	public:

	static void Init();
	static void Close();

	static void DrawLine(Vector2 a, Vector2 b);
	static void Log(std::string out, char end = '\n');
};

