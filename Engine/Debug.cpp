#include "Debug.h"

std::ofstream Debug::File;

void Debug::Init() 
{
	File.open("Output.txt", 'w');
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

void Debug::Log(std::string out, bool NoEL)
{
	File << out << ((NoEL) ? "" : "\r\n");
	std::cout << out << ((NoEL) ? "\0" : "\r\n");
}