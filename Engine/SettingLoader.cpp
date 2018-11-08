#include "SettingLoader.h"

Vector2 SettingLoader::Resolution;
SDL_WindowFlags SettingLoader::FullscreenMode;

std::vector<std::string> SettingLoader::Split(std::string o, char s)
{
	std::vector<std::string> r = std::vector<std::string>();
	std::string temp;
	for (char i : o)
	{
		if (i == s)
		{
			r.push_back(temp);
			temp = "";
		}
		else
		{
			temp += i;
		}
	}
	r.push_back(temp);
	return r;
}