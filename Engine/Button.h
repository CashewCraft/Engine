#pragma once

#include "Script.h"
#include "TextGenerator.h"
#include "UIpane.h"
#include "Mouse.h"
#include "KeyHooks.h"
#include "MenuManager.h"
#include "StateManager.h"
#include "SettingLoader.h"
#include "Sound.h"

#include <algorithm>

class Button : public Script
{
	UIpane *text;

	int index;

	//static Sprite *b; //sprite for the button highlighting
	bool Selected;

	protected:

	std::string Text;

	virtual void OnClick() {};
	virtual void OffClick() {};

	public:
	static Sprite *b; //sprite for the button highlighting

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

class ControlButton : public Button
{
	UIpane *subtext;
	std::string SettingName;

	int Default;

	bool AwaitingKey;

	public:

	ControlButton(Object* a, ScriptData In);
	ControlButton() : Button() {};

	void KeyCallback();
	void SetNewValue(int key);

	void OnClick();

	virtual Script* Clone(Object* Target, ScriptData In);
};

class Slider : public Button
{
	bool Dragging = false;
	double Percent = 0;

	bool Fore;

	public:

	Slider(Object* a, ScriptData In);
	Slider() : Button() {};

	void OnClick() { if (!((Fore) ? Sound::ForeMuted : Sound::BackMuted)) { Dragging = true; } };
	void OffClick() { Dragging = false; ((Fore) ? Sound::ForeVolume : Sound::BackVolume) = Percent * 100; };

	void Update();

	virtual Script* Clone(Object* Target, ScriptData In);
};

class Mute : public Button
{
	bool Muted = false;
	static Sprite *Active;
	static Sprite *inActive;

	bool Fore;

	public:

	Mute(Object* a, ScriptData In);
	Mute() : Button() {};

	void OnClick();

	virtual Script* Clone(Object* Target, ScriptData In);
};