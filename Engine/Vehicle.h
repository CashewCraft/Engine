#pragma once

#include "Vector2.h"
#include "Time.h"

class Vehicle
{
	public:

	float Mass, MaxSpeed, MaxForce;
	Vector2 Velocity, *Position;

	Vehicle();
	Vehicle(Vector2 *Pos, float mass = 1, float maxSpeed = 100, float maxForce = 1);

	void AddForce(Vector2 Force);

	void Simulate();
};

