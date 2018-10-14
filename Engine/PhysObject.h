#ifndef PHYSOBJECT_H
#define PHYSOBJECT_H

#include <vector>
#include <SDL.h>
#include <iostream>
#include "Hierachy.h"
#include "Move.h"
#include "Vehicle.h"
#include "Vector2.h"

class PhysObject : public Object
{ 
	public:

	Vehicle body;

	PhysObject(SDL_Surface *sprite);

	virtual void Update();

	protected:

	virtual Object* Clone(SDL_Surface *sprite, transform pos);
};

#endif