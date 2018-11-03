#include "CharController.h"

void CharController::InitHooks()
{
	//KeyHooks::Register(Hook(true, SDLK_RIGHT), std::bind(&CharController::AddMoveRight, this));
	//KeyHooks::Register(Hook(false, SDLK_RIGHT), std::bind(&CharController::AddMoveLeft, this));
	//KeyHooks::Register(Hook(true, SDLK_LEFT), std::bind(&CharController::AddMoveLeft, this));
	//KeyHooks::Register(Hook(false, SDLK_LEFT), std::bind(&CharController::AddMoveRight, this));
	//KeyHooks::Register(Hook(true, SDLK_UP), std::bind(&CharController::AddMoveUp, this));
	//KeyHooks::Register(Hook(false, SDLK_UP), std::bind(&CharController::AddMoveDown, this));
	//KeyHooks::Register(Hook(true, SDLK_DOWN), std::bind(&CharController::AddMoveDown, this));
	//KeyHooks::Register(Hook(false, SDLK_DOWN), std::bind(&CharController::AddMoveUp, this));

	KeyHooks::Register(Hook(true, std::bind(&CharController::AddMoveLeft, this)), SDLK_LEFT);
	KeyHooks::Register(Hook(true, std::bind(&CharController::AddMoveRight, this)), SDLK_RIGHT);

	KeyHooks::Register(Hook(true, std::bind(&CharController::AddMoveUp, this), true), SDLK_UP);
	KeyHooks::Register(Hook(true, std::bind(&CharController::AddMoveDown, this), true), SDLK_DOWN);

	KeyHooks::Register(Hook(true, std::bind(&CharController::Shoot, this), false), SDLK_SPACE);

	std::cout << "Hooking complete!\n";
}

void CharController::Update() 
{
	GameObject->body.MaxSpeed = 0.05;

	//printf("%f\n", (Mouse::Pos - GameObject->Transform.Position).Magnitude());
	GameObject->Transform.Rotation = Mouse::Pos - GameObject->Transform.Position;

	Camera::Position = (GameObject->Transform.Position.Truncate(std::min(Camera::Size.x, Camera::Size.y) / 2)) - (Camera::Size / 2);
}

void CharController::AddMoveRight()
{
	//Camera::Position += Vector2(1 * Time::deltaTime(), 0);
}
void CharController::AddMoveLeft()
{
	//Camera::Position -= Vector2(1 * Time::deltaTime(), 0);
}
void CharController::AddMoveUp()
{
	GameObject->body.AddForce(GameObject->Transform.Rotation.Normalize()*4);
}
void CharController::AddMoveDown()
{
	GameObject->body.AddForce(-GameObject->body.Velocity*40);
}

void CharController::Shoot()
{
	PhysObject *Bullet = new PhysObject(LoaderTool::ResourceDict["Bullet.bmp"]);
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