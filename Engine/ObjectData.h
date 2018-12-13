#pragma once

#include <vector>
#include <sdl.h>
#include "Vector2.h"
#include "ResourceManager.h"

class LoaderTool;

class ObjectData
{
	public:

	static std::vector<std::string> Split(std::string To_Split, std::string Del);

	ObjectData(std::string Init);

	int id;

	int Type;
	SDL_Texture *Sprite;
	Vector2 Size;
	Vector2 Pos;
	Vector2 Rotation;

	std::vector<int> Children;
	std::vector<int> Scripts;
};
