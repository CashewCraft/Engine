#include "Debug.h"

std::ofstream Debug::File;

void Debug::Output(std::string m)
{
	char Buffer[32];
	time_t CurrentTime = std::time(0);
	struct tm info;
	localtime_s(&info, &CurrentTime);
	size_t written = strftime(Buffer, 32, "%d/%m/%y %T", &info);
	File << "[" << Buffer << "] " << m << "\r\n";
	std::cout << "[" << Buffer << "] " << m << "\r\n";
	File.flush();
}

void Debug::Init() 
{
	File.open("Output.txt", 'w');
	if (File.is_open())
	{
		Debug::Log("Output file opened for logs");
	}
	else
	{
		Debug::Error("Failed to open output file: Output will be console only");
	}
}

void Debug::Close() 
{
	File.close();
}

void Debug::DrawLine(Vector2 a, Vector2 b) 
{
	if (Object::Main) 
	{
		SDL_RenderDrawLine(Object::Main, a.x - Camera::Position.x, a.y - Camera::Position.y, b.x - Camera::Position.x, b.y - Camera::Position.y);
	}
}
void Debug::DrawSquare(Vector2 a, Vector2 b)
{
	if (Object::Main)
	{
		SDL_RenderDrawLine(Object::Main, a.x - Camera::Position.x, a.y - Camera::Position.y, b.x - Camera::Position.x, a.y - Camera::Position.y);
		SDL_RenderDrawLine(Object::Main, a.x - Camera::Position.x, a.y - Camera::Position.y, a.x - Camera::Position.x, b.y - Camera::Position.y);
		SDL_RenderDrawLine(Object::Main, b.x - Camera::Position.x, b.y - Camera::Position.y, b.x - Camera::Position.x, a.y - Camera::Position.y);
		SDL_RenderDrawLine(Object::Main, b.x - Camera::Position.x, b.y - Camera::Position.y, a.x - Camera::Position.x, b.y - Camera::Position.y);
	}
}

void Debug::Log(std::string out)
{
	Output("INFO: " + out);
}
void Debug::Error(std::string out)
{
	Output("ERROR: " + out);
}
void Debug::Flag(std::string out)
{
	Output("DEBUG: " + out);
}