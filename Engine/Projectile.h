#pragma once
#include "Script.h"
class Projectile : public Script
{
	Object *im;

	public:
	
	Projectile(Object* a, Object* b) : Script(a) { im = b; };

	void OnCollision(Object *hit);
};

