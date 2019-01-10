#ifndef SCRIPT_H
#define SCRIPT_H

#include <vector>
#include <algorithm>
#include "Hierachy.h"
#include "ResourceManager.h"
#include "ObjectData.h"
#include "KeyHooks.h"

class Script
{
	static std::map<int, Script*> PrototypeDict;
	std::vector<Hook*> AttachedHooks;

	protected:

	Hook *Generate_Hook(callback_function f, int eventtype, int key);

	Script(Object* attach);

	~Script();

	public:
	Object *Linked;

	Script() {};

	virtual void Init() {};

	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void OnCollision(Object *hit) {};
	virtual void Release() { };

	virtual void Kill() { Release(); delete this; }

	//factory methods
	static void AddPrototype(int key, Script *ToClone);
	static Script* GetNew(int key, Object *Target, ScriptData In);

	virtual Script* Clone(Object* Target, ScriptData In);
};

#endif