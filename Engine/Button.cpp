#include "Button.h"

Sprite *Button::b = nullptr;
bool Button::Reload = false;
std::string Button::ToLoad;

void Button::Init()
{
	if (b == nullptr)
	{
		b = new Sprite(ResourceManager::ResourceDict["Button_unselect"]);
		b->AddFrame("Selected", ResourceManager::ResourceDict["Button_select"]);
	}

	SDL_Texture* c = TextGenerator::GenText("BADABOOM", 512, SDL_Colour{ 107, 3, 57 }, Text);

	Linked->Anim = *b;
	Linked->AddChild(new UIpane(c, Vector2(), Vector2(0.7, 0.9), Vector2()));

	MenuManager::RegisterButton(index, Linked, std::bind(&Button::SetLoad, this));

	//KeyHooks::Register(new Hook(std::bind(&Button::SetLoad, this)), SDL_MOUSEBUTTONDOWN, SDL_BUTTON_LEFT);
}

void Button::Update()
{
	/*Vector2 P = Mouse::Pos;
	Vector2 BR = Linked->Transform.Position + (Linked->Size / 2);
	Vector2 TL = Linked->Transform.Position - (Linked->Size / 2);

	Selected = (P.x < BR.x && P.x > TL.x && P.y < BR.y && P.y > TL.y);

	if (Selected)
	{
		Linked->Anim.SetState("Selected");
	}
	else
	{
		Linked->Anim.SetState("");
	}*/
}

void Button::SetLoad()
{
	Reload = true;
	ToLoad = NextMenu;
}

Script* Button::Clone(Object* Target, ScriptData In)
{
	return new Button(Target, In);
}