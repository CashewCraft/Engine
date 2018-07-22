#include "KeyHooks.h"

typedef std::function<void(void)> callback_fuction;

std::unordered_map<Hook, std::vector<callback_fuction>> KeyHooks::Callbacks;

void KeyHooks::Register(Hook e, callback_fuction c)
{
	Callbacks[e].emplace_back(c);
}

void KeyHooks::Execute(SDL_Event e)
{
	Hook wrapped = Hook((e.type == SDL_KEYDOWN), e.key.keysym.sym, e.key.repeat > 0);

	short index = 0;
	for (callback_fuction i : Callbacks[wrapped])
	{
		if (i) //Make sure the target is callable
		{
			i();
		}
		else
		{
			Callbacks[wrapped].erase(Callbacks[wrapped].begin() + index); //remove dead functions from the list
		}
		index++;
	}
}