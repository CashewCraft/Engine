#include "MenuManager.h"

std::map<int, std::pair<Object*, std::pair<callback_function, callback_function>>> MenuManager::Buttons;
int MenuManager::Selected = 0;
bool MenuManager::AnySelected = false;

Sound *MenuManager::ClickSound = nullptr;

std::vector<MenuManager*> MenuManager::ins = std::vector<MenuManager*>();

void MenuManager::ClearAll()
{
	AnySelected = false;
	Selected = 0;
	Buttons.erase(Buttons.begin(), Buttons.end());
}

void MenuManager::Init()
{
	if (ClickSound == nullptr)
	{
		ClickSound = new Sound("Click", true);
	}

	Generate_Hook(std::bind(&MenuManager::IncrSelect, this), SDL_KEYDOWN, SDLK_UP);
	Generate_Hook(std::bind(&MenuManager::DecrSelect, this), SDL_KEYDOWN, SDLK_DOWN);

	Generate_Hook(std::bind(&MenuManager::CheckCursor, this), SDL_MOUSEMOTION, 0);

	Generate_Hook(std::bind(&MenuManager::Click, this), SDL_MOUSEBUTTONDOWN, SDL_BUTTON_LEFT);
	Generate_Hook(std::bind(&MenuManager::UnClick, this), SDL_MOUSEBUTTONUP, SDL_BUTTON_LEFT);

	Generate_Hook(std::bind(&MenuManager::Click, this), SDL_KEYDOWN, SDLK_RETURN);
	Generate_Hook(std::bind(&MenuManager::UnClick, this), SDL_KEYUP, SDLK_RETURN);
}

void MenuManager::Update()
{
	if (AnySelected)
	{
		Buttons[Selected].first->Anim.SetState("Selected");
	}
}

void MenuManager::CheckCursor()
{
	if (Mouse::Controller)
	{
		AnySelected = true;
		//Check the controller
	}
	else
	{
		Vector2 P = Mouse::Pos;
		AnySelected = false;

		for (std::pair<int, std::pair<Object*, std::pair<callback_function, callback_function>>> i : Buttons)
		{
			Vector2 BR = i.second.first->Transform.Position + (i.second.first->Size / 2);
			Vector2 TL = i.second.first->Transform.Position - (i.second.first->Size / 2);

			if ((P.x < BR.x && P.x > TL.x && P.y < BR.y && P.y > TL.y))
			{
				i.second.first->Anim.SetState("Selected");
				Selected = i.first;
				AnySelected = true;
			}
			else
			{
				i.second.first->Anim.SetState("");
			}
		}
	}
}

void MenuManager::Click()
{
	ClickSound->PlayOnce();
	if (AnySelected)
	{
		Buttons[Selected].second.first();
	}
}
void MenuManager::UnClick()
{
	if (AnySelected)
	{
		Buttons[Selected].second.second();
	}
}

void MenuManager::DecrSelect()
{
	AnySelected = true;
	Buttons[Selected].first->Anim.SetState("");
	if (Selected == Buttons.size()-1)
	{
		Selected = 0;
	}
	else
	{
		Selected++;
	}
}
void MenuManager::IncrSelect()
{
	AnySelected = true;
	Buttons[Selected].first->Anim.SetState("");
	if (Selected == 0)
	{
		Selected = Buttons.size() - 1;
	}
	else
	{
		Selected--;
	}
}

Script* MenuManager::Clone(Object* Target, ScriptData In)
{
	return new MenuManager(Target, In);
}