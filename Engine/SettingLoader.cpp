#include "SettingLoader.h"

Vector2 SettingLoader::Resolution;
SDL_WindowFlags SettingLoader::FullscreenMode;
std::map<std::string, std::string> SettingLoader::Set;
std::map<std::string, std::string> SettingLoader::Con;

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

void SettingLoader::Init()
{
	std::ifstream From;
	From.open("Settings.txt");
	if (!From.is_open())
	{
		//#pragma warning(suppress : 4996)
		//printf("Failed to open file: %s\n", strerror(errno));
		return;
	}

	std::string Line;
	while (std::getline(From, Line))
	{
		std::vector<std::string> Value = Split(Line, '=');
		Set[Value[0]] = Value[1];
	}

	From.close();
	From.open("Controls.txt");
	if (!From.is_open())
	{
		//#pragma warning(suppress : 4996)
		//printf("Failed to open file: %s\n", strerror(errno));
		return;
	}

	while (std::getline(From, Line))
	{
		if (Line != "")
		{
			std::vector<std::string> Value = Split(Line, '=');
			Con[Value[0]] = Value[1];
		}
	}

	From.close();
}

std::string SettingLoader::GetValueOf(std::string Name, std::string Default)
{
	std::string Result = Set[Name];
	if (Result != "")
	{
		return Result;
	}
	Debug::Error("Could not find setting " + Name + " in file, appending");
	SetVal(true, Name, Default);
	return Default;
}

int SettingLoader::GetControlFor(std::string Name, int Default)
{
	std::string Result = Con[Name];
	if (Result != "")
	{
		return std::stoi(Result);
	}
	else
	{
		SetVal(false, Name, std::to_string(Default));
		return Default;
	}
}

void SettingLoader::SetVal(bool s, std::string out, std::string v)
{
	std::ofstream To;
	To.open((s) ? "Settings.txt" : "Controls.txt");
	if (!To.is_open())
	{
		//#pragma warning(suppress : 4996)
		//printf("Failed to open file: %s\n", strerror(errno));
		return;
	}
	for (std::pair<std::string, std::string> i : (s) ? Set : Con)
	{
		if (i.first == out)
		{
			To << out << "=" << v << "\n";
		}
		else
		{
			To << i.first << "=" << i.second << "\n";
		}
	}

	((s) ? Set : Con)[out] = v;

	To.close();
}