#include "Projectile.h"

void Projectile::Update() 
{
	float MaxDist = Vector2(std::max(Camera::Size.x, Camera::Size.y)).Magnitude();
	if (Linked->Transform.Position.Magnitude() > MaxDist)
	{
		Linked->PrepareDelete();
	}
}

void Projectile::OnCollision(Object *hit)
{
	if (hit->Tag != Linked->Tag)
	{
		hit->PrepareDelete();
		Linked->PrepareDelete();
	}
}
