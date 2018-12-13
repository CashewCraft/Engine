#include "Script.h"

std::map<int, Script*> Script::PrototypeDict;

Script::Script(Object* a)
{
	Linked = a;
	a->AttachedScripts.push_back(this);
}

Script::~Script()
{
	Release();
	Linked->AttachedScripts.erase(std::remove(Linked->AttachedScripts.begin(), Linked->AttachedScripts.end(), this), Linked->AttachedScripts.end());
}

void Script::AddPrototype(int key,  Script *ToClone)
{
	PrototypeDict[key] = ToClone;
}
Script* Script::GetNew(int type, Object *From)
{
	if (PrototypeDict.find(type) == PrototypeDict.end())
	{
		return NULL;
	}
	else
	{
		return PrototypeDict[type]->Clone(From);
	}
}

Script* Script::Clone(Object *From) { return new Script(NULL); }