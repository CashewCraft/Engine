#include "KeyHooks.h"

std::map<int, std::vector<Hook*>> KeyHooks::Callbacks;

std::vector<SDL_Keycode> KeyHooks::Down;

void KeyHooks::Register(Hook *e, int key)
{
	Callbacks[key].emplace_back(e);
}

void KeyHooks::Execute(SDL_Event e)
{

	if (!(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) || e.key.repeat == 1)
	{
		return;
	}

	Down.emplace_back(e.key.keysym.sym);

	std::vector<Hook*> triggered = Callbacks[e.key.keysym.sym];

	for (int i = 0; i < triggered.size(); i++)
	{
		if (triggered[i]->Valid())
		{
			triggered[i]->Execute(e.type == SDL_KEYDOWN);
		}
		else
		{
			delete triggered[i];
			triggered.erase(triggered.begin()+i);
		}
	}
}