#ifndef KeyHooks_H
#define KeyHooks_H

#include <map>
#include <SDL.h>
#include <vector>
#include <iostream>
#include <functional>

#include "Script.h"
#include "Hook.h"

class KeyHooks
{
	static std::map<int, std::vector<Hook>> Callbacks;

	public:

	//TODO: work out what the hell is happening here to destroy the compiler
	
	static void Register(Hook e, int key);
	static void Execute(SDL_Event e);
};

#endif