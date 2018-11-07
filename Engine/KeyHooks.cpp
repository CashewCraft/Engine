#include "KeyHooks.h"

std::map<int, std::vector<Hook>> KeyHooks::Callbacks;

std::vector<SDL_Keycode> KeyHooks::Down;

void KeyHooks::Register(Hook e, int key)
{
	Callbacks[key].emplace_back(e);
}

void KeyHooks::Execute(SDL_Event e)
{

	if (!(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP))
	{
		return;
	}

	Down.emplace_back(e.key.keysym.sym);

	std::vector<Hook> triggered = Callbacks[e.key.keysym.sym];

	for (int i = 0; i < triggered.size(); i++)
	{
		if (triggered[i].F)
		{
			if ((e.key.repeat == 0 || triggered[i].R) && ((e.type == SDL_KEYDOWN) == triggered[i].UD))
			{
				triggered[i].F();
			}
		}
		else
		{
			triggered.erase(triggered.begin()+i);
		}
	}
}