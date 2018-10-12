#pragma once

#include "Vector2.h"

class Vehicle
{
	public:

	float Mass, MaxSpeed, MaxForce;
	Vector2 *Position, Velocity, *Rotation;

	Vehicle();
	Vehicle(Vector2 *position, Vector2 *rotation, float mass = 1, float maxSpeed = 1, float maxForce = 1);

	void AddForce(Vector2 Force);

	void Simulate();
};

