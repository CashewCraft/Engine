#ifndef SCRIPT_H
#define SCRIPT_H

#include <vector>
#include "Hierachy.h"

class Script
{
	protected:
	virtual void Init() {};
	Object *Linked;

	Script(Object* attach);

	public:

	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void OnCollision(Object *hit) {};
};

#endif