#ifndef KeyHooks_H
#define KeyHooks_H

#include <unordered_map> //because we're relying on SDL_events for the key, there's no way to order them
#include <SDL.h>
#include <vector>
#include <functional>
#include <iostream>

#include "Script.h"
#include "Hook.h"

typedef std::function<void(void)> callback_fuction;

class KeyHooks
{
	static std::unordered_map<Hook, std::vector<callback_fuction>> Callbacks;

	public:
	
	static void Register(Hook e, callback_fuction cb);
	static void Execute(SDL_Event e);
};

#endif