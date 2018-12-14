#pragma once

#include "Script.h"
#include "TextGenerator.h"
#include "UIpane.h"
#include "Mouse.h"
#include "KeyHooks.h"
#include "MenuManager.h"

class Button : public Script
{
	std::string NextMenu;
	std::string Text;

	int index;

	static Sprite *b; //sprite for the button highlighting
	bool Selected;

	void SetLoad();

	public:

	//TODO: put this somewhere more appropriate
	static bool Reload;
	static std::string ToLoad;

	Button(Object* a, std::string nextmenu, std::string text, int ID) : Script(a) { NextMenu = nextmenu, Text = text; index = ID; Init(); };
	Button(Object* a, ScriptData In) : Button(a, In.AdditionalData[0], In.AdditionalData[1], std::stoi(In.AdditionalData[2])) {};
	Button() : Script() {};

	void Init();

	void Update();

	virtual Script* Clone(Object* Target, ScriptData In);
};

