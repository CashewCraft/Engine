#include "Transform.h"

double transform::GetRotAngle() 
{
	return std::atan2(Rotation.x, Rotation.y);
}