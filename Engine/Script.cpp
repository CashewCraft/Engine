#include "Script.h"

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