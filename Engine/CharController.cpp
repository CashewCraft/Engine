#include "CharController.h"

void CharController::InitHooks()
{
	KeyHooks::Register(Hook(true, SDLK_RIGHT), std::bind(&CharController::AddMoveRight, this));
	KeyHooks::Register(Hook(false, SDLK_RIGHT), std::bind(&CharController::AddMoveLeft, this));
	KeyHooks::Register(Hook(true, SDLK_LEFT), std::bind(&CharController::AddMoveLeft, this));
	KeyHooks::Register(Hook(false, SDLK_LEFT), std::bind(&CharController::AddMoveRight, this));
	std::cout << "Hooking complete!";
}

void CharController::AddMoveRight()
{
	GameObject->body.AddForce(Vector2(0.1f * Time::deltaTime(), 0));
}
void CharController::AddMoveLeft()
{
	GameObject->body.AddForce(Vector2(-0.1f * Time::deltaTime(), 0));
}