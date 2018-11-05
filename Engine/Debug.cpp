#include "Debug.h"

void Debug::Init() 
{
	File.open("Output", 'w');
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

void Debug::Log(std::string out, char end)
{
	File << out << end;
	std::cout << out << end;
}