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

std::string SettingLoader::GetValueOf(std::string Name, std::string Default)
{
	std::string Result = SearchFor(Name, "Settings.txt");
	if (Result != "")
	{
		return Result;
	}
	Debug::Error("Could not find setting " + Name + " in file, appending");
	AppendTo("Settings.txt", "Name", Default);
	return Default;
}

std::string SettingLoader::SearchFor(std::string Name, std::string FileName)
{
	std::ifstream From;
	From.open(FileName);
	if (!From.is_open())
	{
		//#pragma warning(suppress : 4996)
		//printf("Failed to open file: %s\n", strerror(errno));
		return "";
	}

	std::string Line;
	while (std::getline(From, Line))
	{
		std::vector<std::string> Value = Split(Line, '=');
		if (Value[0] == Name)
		{
			From.close();
			return Value[1];
		}
	}

	From.close();

	return "";
}

int SettingLoader::GetControlFor(std::string Name, int Default)
{
	std::string Result = SearchFor(Name, "Controls.txt");
	if (Result != "")
	{
		return std::stoi(Result);
	}
	else
	{
		AppendTo("Controls.txt", Name, std::to_string(Default));
		return Default;
	}
}

void SettingLoader::AppendTo(std::string n, std::string out, std::string v)
{
	std::ofstream To;
	To.open(n, std::fstream::app);
	if (!To.is_open())
	{
		//#pragma warning(suppress : 4996)
		//printf("Failed to open file: %s\n", strerror(errno));
		return;
	}

	To << "\n" << out << "=" << v;

	To.close();
}