#include "Scoreboard.h"

void Scoreboard::Init()
{
	KeyHooks::Register(new Hook_Once(true,std::bind(&Scoreboard::IncrRound, this)), SDLK_p);

	TextGenerator::PrepareFont("BADABOOM", 1024);

	Title = new UIpane(TextGenerator::GenText("BADABOOM", 1024, SDL_Colour{ 107, 3, 57 }, "Round"), Vector2(0, 0.5), Vector2(0.3, 0.2), Vector2(0.1, -0.5));
	Linked->AddChild(Title);

	for (int i = 0; i < 10; i++)
	{
		Numbers[i] = TextGenerator::GenText("BADABOOM", 1024, SDL_Colour{ 214, 3, 57 }, std::to_string(i));
	}

	Title->AddChild(new UIpane(Numbers[0], Vector2(-0.5, -0.5), Vector2(0.2, 1), Vector2(0.15, 0.15)));
}

void Scoreboard::IncrRound()
{
	for (Object *i : Title->GetChildren())
	{
		Title->DelChild(i);
	}

	Round++;
	std::string ToString = std::to_string(Round);

	for (int i = 0; i < ToString.length(); i++)
	{
		Title->AddChild(new UIpane(Numbers[ToString[i]-'0'], Vector2(-0.5, -0.5), Vector2(0.2, 1), Vector2(0.15 - i, 0.15)));
	}
}