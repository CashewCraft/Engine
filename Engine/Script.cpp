#include "Script.h"

Script::Script(Object* a)
{
	Linked = a;
	a->AttachedScripts.push_back(this);
}