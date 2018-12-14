#ifndef KeyHooks_H
#define KeyHooks_H

#include <map>
#include <SDL.h>
#include <vector>
#include <iostream>
#include <functional>
#include <string>
#include <algorithm>

#include <stdint.h>

#include "Hook.h"
#include "Debug.h"

class KeyHooks
{
	static std::map<int,std::map<int, std::vector<Hook*>>> Callbacks;

	public:

	static void Register(Hook *e, int eventtype, int key);
	static void Execute(SDL_Event e);
};

#endif