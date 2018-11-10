#include "AI.h"

void AI::Init() 
{ 
	GameObject->body.MaxSpeed = 500;
	GameObject->body.MaxForce = 0.4;
}

Vector2 AI::InsideCircle(double Radius)
{
	double x = (Radius * 2) * ((double)rand() / (double)RAND_MAX) - Radius;
	double y = (Radius * 2) * ((double)rand() / (double)RAND_MAX) - Radius;

	return Vector2(x, y);
}

double AI::GetAngle(Vector2 To, Vector2 From)
{
	return std::atan2(To.y - From.y, To.x - From.x);
}

void AI::Update()
{
	GameObject->body.AddForce(Wander());//Chase());
	GameObject->Transform.Rotation = GameObject->body.Velocity;
}

Vector2 AI::Wander() 
{
	Debug::DrawLine(GameObject->Transform.Position, Target);

	if ((GameObject->Transform.Position - Target).Magnitude() < 30)
	{
		Target = InsideCircle(std::min(Camera::Size.x, Camera::Size.y));
	}

	return (((Target - GameObject->Transform.Position) * Speed) - GameObject->body.Velocity);
}

Vector2 AI::Chase()
{
	Target = Player->Transform.Position + (Player->body.Velocity*2000);
	//Debug::DrawLine(GameObject->Transform.Position, Target);
	return (((Target - GameObject->Transform.Position) * Speed) - GameObject->body.Velocity);
}