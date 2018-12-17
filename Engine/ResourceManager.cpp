#include "ResourceManager.h"

std::map<std::string, SDL_Texture*> ResourceManager::ResourceDict = std::map<std::string, SDL_Texture*>();
std::map<std::string, Mix_Chunk*> ResourceManager::SoundDict = std::map<std::string, Mix_Chunk*>();

SDL_Renderer *ResourceManager::r = nullptr;

SDL_Texture *ResourceManager::GetSprite(std::string Name)
{
	if (ResourceDict[Name] == nullptr)
	{
		ResourceDict[Name] = SDL_CreateTextureFromSurface(r, SDL_LoadBMP(("Sprites/" + Name + ".bmp").c_str()));
		if (ResourceDict[Name] == NULL)
		{
			Debug::Error("Problem loading sprite " + Name + " to resource directory: "+ (std::string)SDL_GetError());
		}
		else
		{
			Debug::Loading("Added sprite " + Name + " to resource directory");
		}
	}
	return ResourceDict[Name];
}

Mix_Chunk *ResourceManager::GetSound(std::string Name)
{
	if (SoundDict[Name] == nullptr)
	{
		SoundDict[Name] = Mix_LoadWAV(("Sounds/" + Name + ".wav").c_str());
		Debug::Loading("Added sound " + Name + " to resource directory");
	}
	return SoundDict[Name];
}

void ResourceManager::FreeAll()
{
	for (std::pair<std::string, SDL_Texture*> i : ResourceDict)
	{
		SDL_DestroyTexture(i.second);
	}
	for (std::pair<std::string, Mix_Chunk*> i : SoundDict)
	{
		Mix_FreeChunk(i.second);
	}
}
