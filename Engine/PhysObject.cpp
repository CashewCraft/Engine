#include "PhysObject.h"

#include "Script.h"

PhysObject::PhysObject(SDL_Texture *sprite) : Object(sprite) 
{
	body = Vehicle(&Transform.Position);
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

Object* PhysObject::Clone(ObjectData *From)
{
	PhysObject *temp = new PhysObject(From->Sprite);
	temp->Name = From->id;
	temp->Transform.Position = From->Pos;
	temp->Transform.Rotation = From->Rotation;
	temp->Size = From->Size;
	return temp;
}