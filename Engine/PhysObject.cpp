#include "PhysObject.h"

PhysObject::PhysObject(SDL_Surface *sprite) : Object(sprite) 
{
	body = Vehicle(&Transform.Position, &Transform.Rotation);
}

void PhysObject::Update()
{
	body.Simulate();
}

Object* PhysObject::Clone(SDL_Surface *sprite, transform pos)
{
	PhysObject *temp = new PhysObject(sprite);
	temp->Transform = pos;
	return temp;
}