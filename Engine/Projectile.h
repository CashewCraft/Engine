#pragma once

#include <algorithm>
#include "Script.h"
class Projectile : public Script
{
	Object *im;

	public:
	
	Projectile(Object* a, Object* b) : Script(a) { im = b; };

	void Update();

	void OnCollision(Object *hit);
};

