#include "Script.h"

std::map<int, Script*> Script::PrototypeDict;

Hook *Script::Generate_Hook(callback_function f, int eventtype, int key)
{
	Debug::Flag("Hooking for event type [" + std::to_string(eventtype) + "] with key [" + std::to_string(key) + "]");
	Hook *h = new Hook(f);
	KeyHooks::Register(h, eventtype, key);
	AttachedHooks.push_back(h);
	return h;
}

Script::Script(Object* a)
{
	Linked = a;
	a->AttachedScripts.push_back(this);
}

Script::~Script()
{
	Release();
	for (Hook *i : AttachedHooks) { i->Zombie = true; i->ClearCallback(); }
	Linked->AttachedScripts.erase(std::remove(Linked->AttachedScripts.begin(), Linked->AttachedScripts.end(), this), Linked->AttachedScripts.end());
}

void Script::AddPrototype(int key,  Script *ToClone)
{
	PrototypeDict[key] = ToClone;
}
Script* Script::GetNew(int type, Object *From, ScriptData In)
{
	if (PrototypeDict.find(type) == PrototypeDict.end())
	{
		return NULL;
	}
	else
	{
		return PrototypeDict[type]->Clone(From, In);
	}
}

Script* Script::Clone(Object *From, ScriptData In) { return new Script(NULL); }