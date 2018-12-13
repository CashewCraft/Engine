#include "Debug.h"

std::map<std::string, std::ofstream*> Debug::File;

void Debug::Output(std::string m, std::string file)
{
	char Buffer[32];
	time_t CurrentTime = std::time(0);
	struct tm info;
	localtime_s(&info, &CurrentTime);
	size_t written = strftime(Buffer, 32, "%d/%m/%y %T", &info);

	if (File[file] != nullptr)
	{
		*File[file] << "[" << Buffer << "] " << m << "\r\n";
		File[file]->flush();
	}
	std::cout << "[" << Buffer << "] " << m << "\r\n";
}

void Debug::Init() 
{
	InitFile("Info");
	InitFile("Debug");
	InitFile("Error");
	InitFile("Load");
}

void Debug::InitFile(std::string name)
{
	File[name] = new std::ofstream();
	File[name]->open("Logs/"+name+".txt", 'w');
	if (File[name]->is_open())
	{
		Debug::Log("Output file "+name+".txt opened for logs");
	}
	else
	{
		Debug::Error("Failed to open output file "+name+": Output will be console only");
	}
}

void Debug::Close() 
{
	File["Debug"]->close();
	File["Info"]->close();
	File["Error"]->close();
	File["Load"]->close();
}

void Debug::DrawLine(Vector2 a, Vector2 b) 
{
	if (ResourceManager::r) 
	{
		SDL_RenderDrawLine(ResourceManager::r, a.x - Camera::Position.x, a.y - Camera::Position.y, b.x - Camera::Position.x, b.y - Camera::Position.y);
	}
}
void Debug::DrawSquare(Vector2 a, Vector2 b)
{
	if (ResourceManager::r)
	{
		SDL_RenderDrawLine(ResourceManager::r, a.x - Camera::Position.x, a.y - Camera::Position.y, b.x - Camera::Position.x, a.y - Camera::Position.y);
		SDL_RenderDrawLine(ResourceManager::r, a.x - Camera::Position.x, a.y - Camera::Position.y, a.x - Camera::Position.x, b.y - Camera::Position.y);
		SDL_RenderDrawLine(ResourceManager::r, b.x - Camera::Position.x, b.y - Camera::Position.y, b.x - Camera::Position.x, a.y - Camera::Position.y);
		SDL_RenderDrawLine(ResourceManager::r, b.x - Camera::Position.x, b.y - Camera::Position.y, a.x - Camera::Position.x, b.y - Camera::Position.y);
	}
}

void Debug::Log(std::string out)
{
	Output("INFO: " + out, "Info");
}
void Debug::Error(std::string out)
{
	Output("ERROR: " + out, "Error");
}
void Debug::Flag(std::string out)
{
	Output("DEBUG: " + out, "Debug");
}
void Debug::Loading(std::string out)
{
	Output("LOAD: " + out, "Load");
}