#include "ResourceManager.h"

std::map<std::string, SDL_Texture*> ResourceManager::ResourceDict = std::map<std::string, SDL_Texture*>();
std::map<std::string, Mix_Chunk*> ResourceManager::SoundDict = std::map<std::string, Mix_Chunk*>();

SDL_Renderer *ResourceManager::r = nullptr;

SDL_Texture *ResourceManager::GetSprite(std::string Name)
{
	if (ResourceDict[Name] == nullptr)
	{
		ResourceDict[Name] = SDL_CreateTextureFromSurface(r, SDL_LoadBMP(("Sprites/" + Name + ".bmp").c_str()));
		Debug::Loading("Added sprite " + Name + " to resource directory");
	}
	return ResourceDict[Name];
}
