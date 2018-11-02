#include "PhysObject.h"

PhysObject::PhysObject(SDL_Texture *sprite) : Object(sprite) 
{
	body = Vehicle(&Transform.Position, &Transform.Rotation, 100, 2);
}

void PhysObject::Update()
{
	body.Simulate();
	SpacialHash::AddHash(this);
}

Object* PhysObject::Clone(SDL_Texture *sprite, transform pos)
{
	PhysObject *temp = new PhysObject(sprite);
	temp->Transform = pos;
	return temp;
}