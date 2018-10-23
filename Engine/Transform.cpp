#include "Transform.h"

const double transform::Pi = 3.14159265359;
const double transform::Rad2Deg = 180/Pi;

double transform::GetRotAngle() 
{
	return std::atan2(Rotation.y, Rotation.x) * transform::Rad2Deg;
}