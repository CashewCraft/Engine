#ifndef VECTOR2_H
#define VECTOR2_H

#include <string>
#include <ostream>

class Vector2
{
	public:

	double x;
	double y;

	Vector2();
	Vector2(double X, double Y);
	Vector2(double XY);

	Vector2 Truncate(float To = 1);

	Vector2 Normalize();

	float Magnitude();

	Vector2 Cross();
	double Dot(Vector2 Other);

	Vector2 Slerp(Vector2 b, double t);

	operator std::string() const
	{
		return "("+std::to_string(x)+","+std::to_string(y)+")";
	}

	bool operator==(const Vector2 &rhs) const;
	bool operator!=(const Vector2 &rhs) const;
	bool operator<(const Vector2 &rhs) const;
	bool operator>(const Vector2 &rhs) const;

	Vector2& operator+=(const Vector2 &rhs);
	Vector2& operator-=(const Vector2 &rhs);
	Vector2& operator*=(const Vector2 &rhs);
	Vector2& operator/=(const Vector2 &rhs);

	Vector2& operator+=(const double &rhs);
	Vector2& operator-=(const double &rhs);
	Vector2& operator*=(const double &rhs);
	Vector2& operator/=(const double &rhs);

	Vector2 operator+(const Vector2 &rhs);
	Vector2 operator-(const Vector2 &rhs);
	Vector2 operator*(const Vector2 &rhs);
	Vector2 operator/(const Vector2 &rhs);

	Vector2 operator+(const double &rhs);
	Vector2 operator-(const double &rhs);
	Vector2 operator*(const double &rhs);
	Vector2 operator/(const double &rhs);

	Vector2 operator-();
};

inline std::ostream& operator<<(std::ostream& os, const Vector2 TS)
{
	os << "(" << TS.x << "," << TS.y << ")";
	return os;
}

#endif

