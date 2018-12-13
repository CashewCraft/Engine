#pragma once

#include "Script.h"
#include "TextGenerator.h"
#include "UIpane.h"
#include "Mouse.h"

#include <vector>

class Menu : public Script
{
	std::vector<std::string> Options;
	int SelectedIndex = 0;

	public:

	static Sprite *Button;

	Menu(Object *a, std::vector<std::string> O) : Script(a) { Options = O;  Init(); };

	void Init();
	void Update();
};

