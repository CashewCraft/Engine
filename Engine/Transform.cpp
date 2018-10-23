#include "Transform.h"

const double transform::Pi = 3.14159265359;
const double transform::Rad2Deg = 180/Pi;

double transform::GetRotAngle() 
{
	Vector2 NewPos = Rotation.Normalize();
	return (std::atan2(Rotation.x, Rotation.y)*transform::Rad2Deg);
}