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

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			Key = e.key.keysym.sym;
			break;
	}

	//Hooks with -1 are just looking for any press of a given type
	for (Hook *i : Callbacks[e.type][-1])
	{
		if (i->Valid())
		{
			StateManager::KeyReturn = Key;
			i->Execute();
		}
		else
		{
			Debug::Flag("Removing hook for event type [" + std::to_string(e.type) + "] with key [-1]");
			Callbacks[e.type][-1].erase(std::remove(Callbacks[e.type][-1].begin(), Callbacks[e.type][-1].end(), i), Callbacks[e.type][-1].end());
		}
	}

	if (!StateManager::LockInput)
	{
		for (Hook *i : Callbacks[e.type][Key])
		{
			if (i->Valid())
			{
				i->Execute();
			}
			else
			{
				Debug::Flag("Removing hook for event type [" + std::to_string(e.type) + "] with key [" + std::to_string(Key) + "]");
				delete i;
				Callbacks[e.type][Key].erase(std::remove(Callbacks[e.type][Key].begin(), Callbacks[e.type][Key].end(), i), Callbacks[e.type][Key].end());
			}
		}
	}
}