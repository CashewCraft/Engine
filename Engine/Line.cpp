#include "Line.h"

Line::Line(Vector2 a, Vector2 b)
{
	A = a;
	B = b;
}

Vector2 Line::f(float i)
{
	return (A*(1-i)) + (B*i);
}
