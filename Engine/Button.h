#pragma once

#include "Script.h"
#include "TextGenerator.h"
#include "UIpane.h"
#include "Mouse.h"
#include "KeyHooks.h"

class Button : public Script
{
	std::string NextMenu;
	std::string Text;

	static Sprite *b; //sprite for the button highlighting
	bool Selected;

	void SetLoad();

	public:

	//TODO: put this somewhere more appropriate
	static bool Reload;
	static std::string ToLoad;

	Button(Object* a, std::string nextmenu, std::string text) : Script(a) { NextMenu = nextmenu, Text = text;  Init(); };
	Button(Object* a, ScriptData In) : Button(a, In.AdditionalData[0], In.AdditionalData[1]) {};
	Button() : Script() {};

	void Init();

	void Update();

	virtual Script* Clone(Object* Target, ScriptData In);
};

