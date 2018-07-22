#include "PhysObject.h"

PhysObject::PhysObject(SDL_Surface *sprite) : Object(sprite) { base = new Move(Vector2(), -1); index = base; }

void PhysObject::Nudge(bool dir)
{
	short icr = ((dir) ? 1 : -1);

	if (index->Next != NULL && index->Next->Timestamp <= Time::GetFrame())
	{
		index = index->Next;
		Velocity += index->Change;
	}
	else if (index->Last != NULL && index->Timestamp > Time::GetFrame())
	{
		Velocity -= index->Change;
		index = index->Last;
	}
	else if (index->Accumulative)
	{
		Velocity += (index->Change*icr);
	}

	Shift(Velocity*icr);
}

void PhysObject::AddMove(Move *ToAdd)
{
	std::cout << "Adding move of " << ToAdd->Change << "\n";

	if (index->Timestamp == Time::GetFrame())
	{
		index = index->Last;
	}
	delete index->Next;

	index->Next = ToAdd;
	ToAdd->Last = index;

	ToAdd->SetTime(Time::GetFrame());

	//index = index->Next; //Since the thing happened THIS frame, we need to change it NOW
	//Velocity += index->Change; //Add this frame

	std::cout << "We now have " << index->GetTotal() << " items\n";
}

void PhysObject::Update()
{
	if (Time::UpdateFlag) { Nudge(Time::UpdateDir); }
}

Object* PhysObject::Clone(SDL_Surface *sprite, transform pos)
{
	PhysObject *temp = new PhysObject(sprite);
	temp->Transform = pos;
	return temp;
}