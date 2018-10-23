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

	//TODO: fix keyhooks not registering if repeats
	//ALSO TODO: maybe change the hooks so they can work as a binary tree?
	KeyHooks::Register(Hook(false, SDLK_UP, true), std::bind(&CharController::AddMoveUp, this));
	KeyHooks::Register(Hook(true, SDLK_DOWN, true), std::bind(&CharController::AddMoveDown, this));

	std::cout << "Hooking complete!\n";
}

void CharController::Update() 
{
	GameObject->Transform.Rotation = Mouse::Pos - GameObject->Transform.Position;
}

void CharController::AddMoveRight()
{
	//GameObject->body.AddForce(Vector2(1, 0));
}
void CharController::AddMoveLeft()
{
	//GameObject->body.AddForce(Vector2(-1, 0));
}
void CharController::AddMoveUp()
{
	GameObject->body.AddForce(GameObject->Transform.Rotation.Normalize()*2);
}
void CharController::AddMoveDown()
{
	GameObject->body.AddForce(-GameObject->body.Velocity);
}