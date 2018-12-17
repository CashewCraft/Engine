#pragma once

#include "Vector2.h"
#include "Debug.h"

#include <fstream>
#include <string>
#include <vector>
#include <SDL.h>
#include <map>

class SettingLoader
{
	static std::vector<std::string> Split(std::string Original, char Split);

	static std::map<std::string, std::string> Set;
	static std::map<std::string, std::string> Con;

	public:

	static Vector2 Resolution;
	static SDL_WindowFlags FullscreenMode;

	static void Init();

	static std::string GetValueOf(std::string Name, std::string Default);

	static int GetControlFor(std::string Name, int Default);

	static void SetVal(bool Setting, std::string SettingName, std::string Value);
};

