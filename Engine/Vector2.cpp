#include "Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(double X, double Y)
{
	x = X;
	y = Y;
}

Vector2::Vector2(double XY)
{
	x = XY;
	y = XY;
}

Vector2 Vector2::Truncate(float To)
{
	if (Magnitude() > To)
	{
		return Normalize() * To;
	}
	else
	{
		return *this;
	}
}

Vector2 Vector2::Normalize()
{
	return (*this / Magnitude());
}

float Vector2::Magnitude()
{
	return std::sqrt((x*x) + (y*y));
}

Vector2 Vector2::Cross()
{
	return Vector2(y, -x);
}

Vector2 Vector2::Slerp(Vector2 b, double t)
{
	//TODO: make acutal sperical lerping
	return (*this * (1 - t)) + (b * t);
}

bool Vector2::operator==(const Vector2 &rhs) const
{
	return (x == rhs.x && y == rhs.y);
}
bool Vector2::operator!=(const Vector2 &rhs) const
{
	return !(x == rhs.x && y == rhs.y);
}
bool Vector2::operator<(const Vector2 &rhs) const
{
	return (x < rhs.x && y < rhs.y);
}
bool Vector2::operator>(const Vector2 &rhs) const
{
	return (x > rhs.x && y > rhs.y);
}

Vector2& Vector2::operator+=(const Vector2 &rhs)
{
	this->x = this->x + rhs.x;
	this->y = this->y + rhs.y;
	return *this;
}
Vector2& Vector2::operator-=(const Vector2 &rhs)
{
	this->x = this->x - rhs.x;
	this->y = this->y - rhs.y;
	return *this;
}
Vector2& Vector2::operator*=(const Vector2 &rhs)
{
	this->x = this->x * rhs.x;
	this->y = this->y * rhs.y;
	return *this;
}
Vector2& Vector2::operator/=(const Vector2 &rhs)
{
	this->x = this->x / rhs.x;
	this->y = this->y / rhs.y;
	return *this;
}
Vector2& Vector2::operator+=(const double &rhs)
{
	this->x = this->x + rhs;
	this->y = this->y + rhs;
	return *this;
}
Vector2& Vector2::operator-=(const double &rhs)
{
	this->x = this->x - rhs;
	this->y = this->y - rhs;
	return *this;
}
Vector2& Vector2::operator*=(const double &rhs)
{
	this->x = this->x  * rhs;
	this->y = this->y  * rhs;
	return *this;
}
Vector2& Vector2::operator/=(const double &rhs)
{
	this->x = this->x / rhs;
	this->y = this->y / rhs;
	return *this;
}

Vector2 Vector2::operator+(const Vector2 &rhs)
{
	Vector2 n;
	n.x = this->x + rhs.x;
	n.y = this->y + rhs.y;
	return n;
}
Vector2 Vector2::operator-(const Vector2 &rhs)
{
	Vector2 n;
	n.x = this->x - rhs.x;
	n.y = this->y - rhs.y;
	return n;
}
Vector2 Vector2::operator*(const Vector2 &rhs)
{
	Vector2 n;
	n.x = this->x * rhs.x;
	n.y = this->y * rhs.y;
	return n;
}
Vector2 Vector2::operator/(const Vector2 &rhs)
{
	Vector2 n;
	n.x = this->x / rhs.x;
	n.y = this->y / rhs.y;
	return n;
}
Vector2 Vector2::operator+(const double &rhs)
{
	Vector2 n;
	n.x = this->x + rhs;
	n.y = this->y + rhs;
	return n;
}
Vector2 Vector2::operator-(const double &rhs)
{
	Vector2 n;
	n.x = this->x - rhs;
	n.y = this->y - rhs;
	return n;
}
Vector2 Vector2::operator*(const double &rhs)
{
	Vector2 n;
	n.x = this->x * rhs;
	n.y = this->y * rhs;
	return n;
}
Vector2 Vector2::operator/(const double &rhs)
{
	Vector2 n;
	n.x = this->x / rhs;
	n.y = this->y / rhs;
	return n;
}

Vector2 Vector2::operator-()
{
	Vector2 n;
	n.x = -(this->x);
	n.y = -(this->y);
	return n;
}