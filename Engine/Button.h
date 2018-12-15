#pragma once

#include "Script.h"
#include "TextGenerator.h"
#include "UIpane.h"
#include "Mouse.h"
#include "KeyHooks.h"
#include "MenuManager.h"
#include "StateManager.h"

class Button : public Script
{
	std::string Text;

	int index;

	static Sprite *b; //sprite for the button highlighting
	bool Selected;

	protected:

	virtual void OnClick() {};
	virtual void OffClick() {};

	public:

	Button(Object* a, std::string text, int ID) : Script(a) { Text = text; index = ID; Init(); };
	Button(Object* a, ScriptData In) : Button(a, In.AdditionalData[0], std::stoi(In.AdditionalData[1])) {};
	Button() : Script() {};

	void Init();

	virtual Script* Clone(Object* Target, ScriptData In);
};

class RelayButton : public Button
{
	std::string Next;

	public:

	RelayButton(Object* a, ScriptData In) : Button(a, In.AdditionalData[0], std::stoi(In.AdditionalData[1])) { Next = In.AdditionalData[2]; };
	RelayButton() : Button() {};

	void OnClick();

	virtual Script* Clone(Object* Target, ScriptData In);
};

class DifficultyButton : public Button
{
	std::string Next;
	int Diff = 1;

	public:

	DifficultyButton(Object* a, ScriptData In) : Button(a, In.AdditionalData[0], std::stoi(In.AdditionalData[1])) { Next = In.AdditionalData[2]; Diff = std::stoi(In.AdditionalData[3]); Debug::Flag("[" + In.AdditionalData[1] + "] - " + In.AdditionalData[3]); };
	DifficultyButton() : Button() {};

	void OnClick();

	virtual Script* Clone(Object* Target, ScriptData In);
};

