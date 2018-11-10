#include "Sprite.h"

Sprite::Sprite(SDL_Texture *D)
{
	Default = D;
}

SDL_Texture *Sprite::GetCurrSprite()
{
	return (Frames[State] == NULL) ? Default : Frames[State];
}

void Sprite::SetState(std::string S)
{
	State = S;
}

void Sprite::AddFrame(std::string Name, SDL_Texture *Resource)
{
	if (Frames[Name])
	{
		//Debug::Log("Overwriting frame for state " + Name);
	}
	Frames[Name] = Resource;
}
