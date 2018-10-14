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

Vector2 Vector2::Truncate(float To)
{
	return Normalize() * To;
}

Vector2 Vector2::Normalize()
{
	return (*this / Magnitude());
}

float Vector2::Magnitude()
{
	return std::sqrt((x*x) + (y*y));
}

bool Vector2::operator==(const Vector2 &rhs)
{
	return (x == rhs.x && y == rhs.y);
}
bool Vector2::operator!=(const Vector2 &rhs)
{
	return !(x == rhs.x && y == rhs.y);
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
Vector2& Vector2::operator+=(const int &rhs)
{
	this->x = this->x + rhs;
	this->y = this->y + rhs;
	return *this;
}
Vector2& Vector2::operator-=(const int &rhs)
{
	this->x = this->x - rhs;
	this->y = this->y - rhs;
	return *this;
}
Vector2& Vector2::operator*=(const int &rhs)
{
	this->x = this->x  * rhs;
	this->y = this->y  * rhs;
	return *this;
}
Vector2& Vector2::operator/=(const int &rhs)
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
Vector2 Vector2::operator+(const int &rhs)
{
	Vector2 n;
	n.x = this->x + rhs;
	n.y = this->y + rhs;
	return n;
}
Vector2 Vector2::operator-(const int &rhs)
{
	Vector2 n;
	n.x = this->x - rhs;
	n.y = this->y - rhs;
	return n;
}
Vector2 Vector2::operator*(const int &rhs)
{
	Vector2 n;
	n.x = this->x * rhs;
	n.y = this->y * rhs;
	return n;
}
Vector2 Vector2::operator/(const int &rhs)
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