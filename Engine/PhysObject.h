#ifndef PHYSOBJECT_H
#define PHYSOBJECT_H

#include <vector>
#include <SDL.h>
#include <iostream>
#include "Hierachy.h"
#include "Move.h"
#include "Vector2.h"
#include "Time.h"
#include "MoveCap.h"

class PhysObject : public Object
{ 
	Move* base;
	Move* index;
	Vector2 Velocity = Vector2();

	public:

	PhysObject(SDL_Surface *sprite);

	void Nudge(bool dir = true);

	void AddMove(Move *ToAdd);

	virtual void Update();

	protected:

	virtual Object* Clone(SDL_Surface *sprite, transform pos);
};

#endif