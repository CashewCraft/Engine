#include "Scoreboard.h"

SDL_Texture *Scoreboard::Numbers[10] {};

void Scoreboard::Init()
{
	KeyHooks::Register(new Hook(std::bind(&Scoreboard::IncrRound, this)), SDL_KEYDOWN, SDLK_p);

	Title = new UIpane(TextGenerator::GenText("BADABOOM", 1024, SDL_Colour{ 107, 3, 57 }, "Round"), Vector2(0, 0.5), Vector2(0.3, 0.2), Vector2(0.1, -0.5));
	Linked->AddChild(Title);

	Tim = new UIpane(TextGenerator::GenText("BADABOOM", 1024, SDL_Colour{ 107, 3, 57 }, "Time!"), Vector2(0.5, 0.5), Vector2(0.15, 0.1), Vector2(-0.5, -0.5));
	Linked->AddChild(Tim);

	for (int i = 0; i < 10; i++)
	{
		Numbers[i] = TextGenerator::GenText("BADABOOM", 1024, SDL_Colour{ 214, 3, 57 }, std::to_string(i));
	}

	Title->AddChild(new UIpane(Numbers[0], Vector2(-0.5, -0.5), Vector2(0.2, 1), Vector2(0.15, 0.15)));
}

void Scoreboard::IncrRound()
{
	Round++;
	SetNumbers(Title, Round, Vector2(-0.5, -0.5), Vector2(0.2, 1), Vector2(0.15, 0.15));
}

void Scoreboard::SetNumbers(Object *par, unsigned int num, Vector2 Anchor, Vector2 Size, Vector2 Offset)
{
	for (Object *i : par->GetChildren())
	{
		par->DelChild(i);
	}

	std::string ToString = std::to_string(num);

	for (int i = 0; i < ToString.length(); i++)
	{
		par->AddChild(new UIpane(Numbers[ToString[i] - '0'], Anchor, Size, Vector2(Offset.x - i, Offset.y)));
	}
}

void Scoreboard::Update()
{
	Timer -= Time::deltaTime();
	SetNumbers(Tim, Timer, Vector2(0.5, -0.5), Vector2(0.2, 1), Vector2(-0.55, -0.025));

	if (Timer <= 0)
	{
		Button::Reload = true;
		Button::ToLoad = "MM";
	}
}