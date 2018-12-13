#pragma once

#include "Vector2.h"
#include "Camera.h"
#include "ResourceManager.h"

#include <iostream>
#include <fstream>
#include <ctime>

class Debug
{
	static std::map<std::string, std::ofstream*> File;

	static void Output(std::string MSG, std::string FileName);
	static void InitFile(std::string name);

	public:

	static void Init();
	static void Close();

	static void DrawLine(Vector2 a, Vector2 b);
	static void DrawSquare(Vector2 a, Vector2 b);

	static void Log(std::string out);
	static void Error(std::string out);
	static void Flag(std::string out);
	static void Loading(std::string out);
};

