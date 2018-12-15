#pragma once

#include <algorithm>
#include "Script.h"
class Projectile : public Script
{
	public:
	
	Projectile(Object* a) : Script(a) {};

	void Update();

	void OnCollision(Object *hit);
};

