#include "TextGenerator.h"

std::map<std::string, TTF_Font*> TextGenerator::Fonts = std::map<std::string, TTF_Font*>();

SDL_Texture* TextGenerator::GenText(std::string Font, int Size, SDL_Colour Colour, std::string Text)
{
	PrepareFont(Font, Size);

	Debug::Log("Created new text pane with font " + Font + " at size " + std::to_string(Size) + " saying \"" + Text+"\"");
	return SDL_CreateTextureFromSurface(ResourceManager::r, TTF_RenderText_Solid(Fonts[(Font + std::to_string(Size))], Text.c_str(), Colour));
}

void TextGenerator::PrepareFont(std::string Font, int Size)
{
	if (Fonts[(Font + std::to_string(Size))] == nullptr)
	{
		Debug::Log("Initialised font " + Font + " with size " + std::to_string(Size));
		Fonts[(Font + std::to_string(Size))] = TTF_OpenFont(("Fonts/" + Font + ".ttf").c_str(), Size);
	}
}
