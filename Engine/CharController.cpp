#include "CharController.h"

void CharController::InitHooks()
{
	KeyHooks::Register(new Hook_Pass(&Thrust), SDLK_UP);
	KeyHooks::Register(new Hook_Pass(&Slow), SDLK_DOWN);

	KeyHooks::Register(new Hook_Pass(&Firing), SDLK_SPACE);

	std::cout << "Hooking complete!\n";
}

void CharController::Update() 
{
	
	GameObject->Transform.Rotation = Mouse::Pos - GameObject->Transform.Position;

	Camera::Position = (GameObject->Transform.Position.Truncate(std::min(Camera::Size.x, Camera::Size.y) / 2)) - (Camera::Size / 2);

	if (Limiter > 0)
	{
		Limiter -= Time::deltaTime();
	}
	if (Firing && Limiter <= 0)
	{
		Shoot();
		Limiter = FireRate;
	}

	if (Thrust)
	{
		Debug::Log(std::to_string(GameObject->body.Velocity.Magnitude()));
		GameObject->body.AddForce(GameObject->Transform.Rotation.Normalize() * 20);
	}
	else if (Slow)
	{
		GameObject->body.AddForce(-GameObject->body.Velocity * 2);
	}
}

void CharController::Shoot()
{
	PhysObject *Bullet = new PhysObject(LoaderTool::ResourceDict["Bullet.bmp"]);
	Bullet->Name = "Bill";
	Object::Workspace->AddChild(Bullet);
	Bullet->Transform.Position = GameObject->Transform.Position;
	Bullet->body.Velocity = GameObject->Transform.Rotation.Normalize()*0.1;

	new Projectile(Bullet, Linked);
}

void CharController::OnCollision(Object *hit)
{
	//Debug::Log("Hit " + (hit->Name));
	Debug::DrawLine(GameObject->Transform.Position, hit->Transform.Position);
}