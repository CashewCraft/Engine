#include "CharController.h"

void CharController::Init()
{
	Debug::Log("Initalising Charcontroller");
	GameObject = (PhysObject*)Linked;

	KeyHooks::Register(new Hook(std::bind(&CharController::Set_Key, this, 1, true)), SDL_KEYDOWN, SettingLoader::GetControlFor("Thrust", SDLK_UP));
	KeyHooks::Register(new Hook(std::bind(&CharController::Set_Key, this, 1, false)), SDL_KEYUP, SettingLoader::GetControlFor("Thrust", SDLK_UP));

	KeyHooks::Register(new Hook(std::bind(&CharController::Set_Key, this, 0, true)), SDL_KEYDOWN, SettingLoader::GetControlFor("Shoot", SDLK_SPACE));
	KeyHooks::Register(new Hook(std::bind(&CharController::Set_Key, this, 0, false)), SDL_KEYUP, SettingLoader::GetControlFor("Shoot", SDLK_SPACE));

	KeyHooks::Register(new Hook(std::bind(&CharController::Set_Key, this, 2, true)), SDL_KEYDOWN, SettingLoader::GetControlFor("Brake", SDLK_DOWN));
	KeyHooks::Register(new Hook(std::bind(&CharController::Set_Key, this, 2, false)), SDL_KEYUP, SettingLoader::GetControlFor("Brake", SDLK_DOWN));

	GameObject->Anim.AddFrame("Moving", ResourceManager::GetSprite("GoodSpaceShip_Thrust"));
	GameObject->Anim.AddFrame("Slowing", ResourceManager::GetSprite("GoodSpaceShip_Slow"));

	ThrustNoise = new Sound("Thrust");

	GameObject->body.MaxSpeed = 500;
	GameObject->body.MaxForce = 0.4;
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
		ThrustNoise->Play();

		GameObject->Anim.SetState("Moving");
		//Debug::Log(std::to_string(GameObject->body.Velocity.Magnitude()));
		GameObject->body.AddForce(GameObject->Transform.Rotation.Normalize() * 20);
	}
	else if (Slow)
	{
		ThrustNoise->Stop();
		GameObject->Anim.SetState((GameObject->body.Velocity.Magnitude() > 0)?"Slowing":"");
		GameObject->body.AddForce((GameObject->body.Velocity.Magnitude() > 0.5)?-GameObject->body.Velocity * 0.005: -GameObject->body.Velocity);
	}
	else
	{
		ThrustNoise->Stop();
		GameObject->Anim.SetState("");
	}

	if (GameObject->Transform.Position.x < Camera::Position.x || GameObject->Transform.Position.x > (Camera::Position + Camera::Size).x)
	{
		GameObject->body.Velocity.x *= -1;

		GameObject->Transform.Position.x = (GameObject->Transform.Position.x < Camera::Position.x) ? Camera::Position.x : (Camera::Position + Camera::Size).x;
	}
	if (GameObject->Transform.Position.y < Camera::Position.y || GameObject->Transform.Position.y > (Camera::Position + Camera::Size).y)
	{
		GameObject->body.Velocity.y *= -1;

		GameObject->Transform.Position.y = (GameObject->Transform.Position.y < Camera::Position.y) ? Camera::Position.y : (Camera::Position + Camera::Size).y;
	}
}

void CharController::Release()
{
	delete ThrustNoise;
}

void CharController::Shoot()
{
	PhysObject *Bullet = new PhysObject(ResourceManager::ResourceDict["Bullet"]);
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