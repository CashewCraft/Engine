#include "AI.h"

void AI::InitHooks() { GameObject->Transform.Rotation = Vector2(); }

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
	Debug::DrawLine(GameObject->Transform.Position, Target);

	GameObject->body.AddForce(((Target - GameObject->Transform.Position) * Speed) - GameObject->body.Velocity);
	GameObject->Transform.Rotation = GameObject->body.Velocity;

	if ((GameObject->Transform.Position - Target).Magnitude() < 30)
	{
		Target = InsideCircle(std::min(Camera::Size.x, Camera::Size.y));
	}
}