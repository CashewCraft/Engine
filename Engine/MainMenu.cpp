#include "MainMenu.h"

Sprite *Menu::Button = nullptr;

void Menu::Init()
{
	TextGenerator::PrepareFont("BADABOOM", 512);

	double SizePer = 0.6 / Options.size();
	for (int i = 0; i < Options.size(); i++)
	{
		SDL_Texture* c = TextGenerator::GenText("BADABOOM", 512, SDL_Colour{ 107, 3, 57 }, Options[i]);

		UIpane *n = new UIpane(NULL, Vector2(0, 0.3), Vector2(SizePer*2.1, SizePer), Vector2(0, -1.1*i));
		n->Anim = *Button;
		n->AddChild(new UIpane(c, Vector2(), Vector2(0.7,0.9), Vector2()));
		Linked->AddChild(n);
	}
}

void Menu::Update()
{
	for (Object *i : Linked->GetChildren())
	{
		Vector2 P = Mouse::Pos;
		Vector2 BR = (i->Transform.Position + (i->Size / 2));
		Vector2 TL = (i->Transform.Position - (i->Size / 2));
		if (P.x < BR.x && P.x > TL.x && P.y < BR.y && P.y > TL.y)
		{
			i->Anim.SetState("Selected");
		}
		else
		{
			i->Anim.SetState("");
		}
	}
}
