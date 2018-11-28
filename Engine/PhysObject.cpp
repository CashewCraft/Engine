#include "PhysObject.h"

#include "Script.h"

PhysObject::PhysObject(SDL_Texture *sprite) : Object(sprite) 
{
	body = Vehicle(&Transform.Position, &Transform.Rotation);
	CollDist = Size.Magnitude();
}

void PhysObject::FixedUpdate()
{
	body.Simulate();

	SpacialHash::AddHash(this);
}
void PhysObject::Update()
{
	Rect MyRect = GetRect();
	for (Script *i : AttachedScripts)
	{
		for (Object *c : *SpacialHash::GetCollisions(this))
		{
			if (c != this && MyRect.GetCollision(c->GetRect()))
			{
				i->OnCollision(c);
			}
		}
	}
}

Object* PhysObject::Clone(SDL_Texture *sprite, transform pos)
{
	PhysObject *temp = new PhysObject(sprite);
	temp->Transform = pos;
	return temp;
}