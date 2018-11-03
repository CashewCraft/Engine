#include "Projectile.h"

void Projectile::OnCollision(Object *hit)
{
	Debug::Log("Hit " + hit->Name);
	if (hit != im)
	{
		hit->PrepareDelete();
		Linked->PrepareDelete();
	}
}
