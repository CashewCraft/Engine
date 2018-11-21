#pragma once

#include "Vector2.h"
#include "Debug.h"

#include <fstream>
#include <string>
#include <vector>
#include <SDL.h>

class SettingLoader
{
	static std::vector<std::string> Split(std::string Original, char Split);

	public:

	static Vector2 Resolution;
	static SDL_WindowFlags FullscreenMode;

	static std::string GetValueOf(std::string Name, std::string Default);

	static std::string SearchFor(std::string Name, std::string FileName);

	static int GetControlFor(std::string Name, int Default);

	static void AppendTo(std::string FileName, std::string SettingName, std::string Value);
};

