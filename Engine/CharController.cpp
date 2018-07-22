#include "CharController.h"

void CharController::InitHooks()
{
	KeyHooks::Register(Hook(true, SDLK_RIGHT), std::bind(&CharController::AddMoveLeft, this));
	KeyHooks::Register(Hook(false, SDLK_RIGHT), std::bind(&CharController::ReMoveLeft, this));
	std::cout << "Hooking complete!";
}

void CharController::AddMoveLeft()
{
	GameObject->AddMove(new Move(Vector2(2, 0)));
	Time::Ticking = true;
}
void CharController::ReMoveLeft()
{
	GameObject->AddMove(new Move(Vector2(-2, 0)));
	Time::Ticking = false;
}