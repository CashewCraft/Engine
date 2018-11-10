#include "CharController.h"

void CharController::InitHooks()
{
	KeyHooks::Register(new Hook_Pass(&Thrust), SDLK_UP);
	KeyHooks::Register(new Hook_Pass(&Slow), SDLK_DOWN);

	KeyHooks::Register(new Hook_Pass(&Firing), SDLK_SPACE);

	GameObject->Anim.AddFrame("Moving", LoaderTool::ResourceDict["GoodSpaceShip_Thrust.bmp"]);
	GameObject->Anim.AddFrame("Slowing", LoaderTool::ResourceDict["GoodSpaceShip_Slow.bmp"]);

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
		GameObject->Anim.SetState("Moving");
		//Debug::Log(std::to_string(GameObject->body.Velocity.Magnitude()));
		GameObject->body.AddForce(GameObject->Transform.Rotation.Normalize() * 20);
	}
	else if (Slow)
	{
		GameObject->Anim.SetState((GameObject->body.Velocity.Magnitude() > 0)?"Slowing":"");
		GameObject->body.AddForce((GameObject->body.Velocity.Magnitude() > 2)?-GameObject->body.Velocity * 0.005: -GameObject->body.Velocity);
	}
	else
	{
		GameObject->Anim.SetState("");
	}
}

void CharController::Shoot()
{
	PhysObject *Bullet = new PhysObject(LoaderTool::ResourceDict["Bullet.bmp"]);
	Bullet->Name = "Bill";
	//Object::Workspace->AddChild(Bullet);
	Bullet->Transform.Position = GameObject->Transform.Position;
	Bullet->body.Velocity = GameObject->Transform.Rotation.Normalize()*320;

	Object::Instanciate(Bullet, Object::Workspace);

	new Projectile(Bullet, Linked);
}

void CharController::OnCollision(Object *hit)
{
	//Debug::Log("Hit " + (hit->Name));
	Debug::DrawLine(GameObject->Transform.Position, hit->Transform.Position);
}