#include "PhysObject.h"

PhysObject::PhysObject(SDL_Texture *sprite) : Object(sprite) 
{
	body = Vehicle(&Transform.Position, &Transform.Rotation, 100);
}

void PhysObject::Update()
{
	body.Simulate();
}

Object* PhysObject::Clone(SDL_Texture *sprite, transform pos)
{
	PhysObject *temp = new PhysObject(sprite);
	temp->Transform = pos;
	return temp;
}