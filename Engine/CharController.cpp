#include "CharController.h"

void CharController::InitHooks()
{
	KeyHooks::Register(Hook(true, SDLK_RIGHT), std::bind(&CharController::AddMoveRight, this));
	KeyHooks::Register(Hook(false, SDLK_RIGHT), std::bind(&CharController::AddMoveLeft, this));
	KeyHooks::Register(Hook(true, SDLK_LEFT), std::bind(&CharController::AddMoveLeft, this));
	KeyHooks::Register(Hook(false, SDLK_LEFT), std::bind(&CharController::AddMoveRight, this));
	KeyHooks::Register(Hook(true, SDLK_UP), std::bind(&CharController::AddMoveUp, this));
	KeyHooks::Register(Hook(false, SDLK_UP), std::bind(&CharController::AddMoveDown, this));
	KeyHooks::Register(Hook(true, SDLK_DOWN), std::bind(&CharController::AddMoveDown, this));
	KeyHooks::Register(Hook(false, SDLK_DOWN), std::bind(&CharController::AddMoveUp, this));
	std::cout << "Hooking complete!";
}

void CharController::AddMoveRight()
{
	GameObject->body.AddForce(Vector2(1, 0));
}
void CharController::AddMoveLeft()
{
	GameObject->body.AddForce(Vector2(-1, 0));
}
void CharController::AddMoveUp()
{
	GameObject->body.AddForce(Vector2(0, 1));
}
void CharController::AddMoveDown()
{
	GameObject->body.AddForce(Vector2(0, -1));
}