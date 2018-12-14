#include "KeyHooks.h"

std::map<int,std::map<int, std::vector<Hook*>>> KeyHooks::Callbacks;

void KeyHooks::Register(Hook *e, int eventtype, int key)
{
	Callbacks[eventtype][key].emplace_back(e);
}

void KeyHooks::Execute(SDL_Event e)
{

	if (e.key.repeat == 1)
	{
		return;
	}

	int Key = 0;
	switch (e.type)
	{
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			Key = e.button.button;
			break;
		
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
			Key = e.jbutton.button;
			break;

		default:
			Key = e.key.keysym.sym;
			break;
	}

	std::vector<Hook*> triggered = Callbacks[e.type][Key];

	for (int i = 0; i < triggered.size(); i++)
	{
		if (triggered[i]->Valid())
		{
			triggered[i]->Execute();
		}
		else
		{
			delete triggered[i];
			triggered.erase(triggered.begin()+i);
		}
	}
}