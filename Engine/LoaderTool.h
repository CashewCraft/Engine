#ifndef LOADERTOOL_H
#define LOADERTOOL_H

#include <fstream>
#include <stack>
#include <string>
#include <map>
#include <iostream>
#include "Hierachy.h"
#include "PhysObject.h"
#include "Transform.h"

class LoaderTool
{
	public:
	static void init();
	static int LoadScene(Object *ToParent, const char *filename, SDL_Renderer *r);
};

#endif