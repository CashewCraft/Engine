#pragma once

#include "Vector2.h"

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

	template <typename Expected> static Expected GetValueOf(std::string Name)
	{
		std::ifstream From;
		From.open("Settings.txt");
		if (!From.is_open())
		{
			//#pragma warning(suppress : 4996)
			//printf("Failed to open file: %s\n", strerror(errno));
			return NULL;
		}

		int counter = 0;

		std::string Line;
		while (std::getline(From, Line))
		{
			std::vector<std::string> Value = Split(Line, '=');
			if (Value[0] == Name)
			{
				From.close();
				return (Expected)Value[1];
			}
		}

		From.close();
		return NULL;
	}
};

