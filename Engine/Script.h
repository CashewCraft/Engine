#ifndef SCRIPT_H
#define SCRIPT_H

#include <vector>
#include <algorithm>
#include "Hierachy.h"
#include "ResourceManager.h"

class Script
{
	static std::map<int, Script*> PrototypeDict;

	protected:
	Object *Linked;

	Script(Object* attach);

	public:
	~Script();

	Script() {};

	virtual void Init() {};

	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void OnCollision(Object *hit) {};
	virtual void Release() {};


	//factory methods
	static void AddPrototype(int key, Script *ToClone);
	static Script* GetNew(int key, Object *Target);

	virtual Script* Clone(Object* Target);
};

#endif