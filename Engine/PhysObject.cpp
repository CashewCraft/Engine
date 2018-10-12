#include "PhysObject.h"

PhysObject::PhysObject(SDL_Surface *sprite) : Object(sprite) {}

void PhysObject::Nudge(bool dir)
{
	short icr = ((dir) ? 1 : -1);

	Shift(Velocity*icr);
}

void PhysObject::AddMove(Vector2 Move)
{
	Velocity += Move;
}

void PhysObject::Update()
{
	Nudge(true);
}

Object* PhysObject::Clone(SDL_Surface *sprite, transform pos)
{
	PhysObject *temp = new PhysObject(sprite);
	temp->Transform = pos;
	return temp;
}