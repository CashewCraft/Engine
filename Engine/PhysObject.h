#ifndef PHYSOBJECT_H
#define PHYSOBJECT_H

#include <vector>
#include <SDL.h>
#include <float.h>
#include <iostream>
#include "Hierachy.h"
#include "Vehicle.h"
#include "Vector2.h"
#include "SpacialHash.h"

class PhysObject : public Object
{ 
	public:

	Vehicle body;

	double CollDist;

	PhysObject(SDL_Texture *sprite);

	virtual void FixedUpdate();
	virtual void Update();

	protected:

	virtual Object* Clone(ObjectData *From);
};

#endif