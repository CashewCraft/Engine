#include "Vehicle.h"

Vehicle::Vehicle() {}

Vehicle::Vehicle(Vector2 *p, Vector2 *r, float m, float ms, float mf)
{
	Position = p;
	Rotation = r;
	Mass = m;
	MaxSpeed = ms;
	MaxForce = mf;
}

void Vehicle::AddForce(Vector2 f)
{
	Vector2 Steer = f.Truncate(MaxForce);
	Vector2 Acc = (Steer / Mass);
	Velocity = (Velocity + Acc).Truncate(MaxSpeed);
}

void Vehicle::Simulate()
{
	*Position += Velocity * Time::deltaTime();
}