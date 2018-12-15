#include "Button.h"

Sprite *Button::b = nullptr;

void Button::Init()
{
	if (b == nullptr)
	{
		b = new Sprite(ResourceManager::ResourceDict["Button_unselect"]);
		b->AddFrame("Selected", ResourceManager::ResourceDict["Button_select"]);
	}

	SDL_Texture* c = TextGenerator::GenText("BADABOOM", 512, SDL_Colour{ 107, 3, 57 }, Text);

	Linked->Anim = *b;
	Linked->AddChild(new UIpane(c, Vector2(), Vector2(0.1*Text.size(), 0.9), Vector2()));

	MenuManager::RegisterButton(index, Linked, std::bind(&Button::OnClick, this), std::bind(&Button::OffClick, this));

	//KeyHooks::Register(new Hook(std::bind(&Button::SetLoad, this)), SDL_MOUSEBUTTONDOWN, SDL_BUTTON_LEFT);
}

Script* Button::Clone(Object* Target, ScriptData In)
{
	return new Button(Target, In);
}

void RelayButton::OnClick()
{
	StateManager::NewScene = true;
	StateManager::SceneName = Next;
}

Script* RelayButton::Clone(Object* Target, ScriptData In)
{
	return new RelayButton(Target, In);
}

void DifficultyButton::OnClick()
{
	StateManager::Difficulty = Diff;

	Debug::Flag("Setting difficulty to " + std::to_string(Diff));

	StateManager::NewScene = true;
	StateManager::SceneName = Next;
}

Script* DifficultyButton::Clone(Object* Target, ScriptData In)
{
	return new DifficultyButton(Target, In);
}