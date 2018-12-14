#ifndef LOADERTOOL_H
#define LOADERTOOL_H

#include <SDL_mixer.h>
#include <fstream>
#include <stack>
#include <string>
#include <map>
#include <iostream>
#include "Hierachy.h"
#include "PhysObject.h"
#include "UIpane.h"
#include "Transform.h"

#include "ResourceManager.h"
#include "ObjectData.h"

#include "AI.h"
#include "CharController.h"
#include "Button.h"
#include "Scoreboard.h"
#include "MenuManager.h"

class LoaderTool
{
	public:

	static void init();

	static int LoadScene(Object *ObjParent, Object *UIParent, std::string filename);
};

#endif