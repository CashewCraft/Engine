#ifndef SCRIPT_H
#define SCRIPT_H

#include <vector>
#include "Hierachy.h"

class Script
{
	protected:
	virtual void InitHooks() {};
	Object *Linked;

	Script(Object* attach);

	public:

	~Script();

	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void OnCollision(Object *hit) {};
};

#endif