#pragma once

#include <map>
#include <functional>

#include "Script.h"
#include "Mouse.h"
#include "Sound.h"

typedef std::function<void(void)> callback_function;

class MenuManager : public Script
{
	static std::map<int, std::pair<Object*,std::pair<callback_function, callback_function>>> Buttons;
	static int Selected;
	static bool AnySelected;

	static Sound *ClickSound;

	static std::vector<MenuManager*> ins;

	public:

	MenuManager(Object *a) : Script(a) { Init(); ins.push_back(this); };
	MenuManager(Object* a, ScriptData In) : MenuManager(a) {};
	MenuManager() : Script() {};

	static void RegisterButton(int index, Object *b, callback_function On, callback_function Off) { Buttons[index] = std::make_pair(b, std::make_pair(On,Off)); };
	static void ClearAll();

	void Init();

	void Update();
	void CheckCursor();

	void Click();
	void UnClick();

	void DecrSelect();
	void IncrSelect();

	virtual Script* Clone(Object* Target, ScriptData In);
};

