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
	text = new UIpane(c, Vector2(), Vector2(0.1*Text.size(), 0.9), Vector2());
	Linked->AddChild(text);

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

ControlButton::ControlButton(Object* a, ScriptData In) : Button(a, In.AdditionalData[0], std::stoi(In.AdditionalData[1]))
{
	Default = std::stoi(In.AdditionalData[2]);
	SettingName = SDL_GetKeyName(SettingLoader::GetControlFor(In.AdditionalData[0], Default));

	UIpane *sel = new UIpane(Linked->Anim.GetCurrSprite(), Vector2(-0.5, 0), Vector2(0.2*SettingName.size(),1), Vector2(-0.5,0));
	SDL_Texture* c = TextGenerator::GenText("BADABOOM", 512, SDL_Colour{ 107, 3, 57 }, SettingName);

	subtext = new UIpane(c, Vector2(), Vector2(0.9, 0.9), Vector2());
	sel->AddChild(subtext);

	Linked->AddChild(sel);

	Linked->GetChildren()[0]->Anim.AddFrame("new", TextGenerator::GenText("BADABOOM", 512, SDL_Colour{ 107, 3, 57 }, "Press any key.."));

	Generate_Hook(std::bind(&ControlButton::KeyCallback, this), SDL_KEYDOWN, -1);
}

void ControlButton::SetNewValue(int k)
{
	Default = k;
	SettingName = SDL_GetKeyName(k);

	SDL_Texture* c = TextGenerator::GenText("BADABOOM", 512, SDL_Colour{ 107, 3, 57 }, SettingName);

	subtext->Anim.SetDefault(c);

	((UIpane*)subtext->GetParent())->RelativeSize = Vector2(0.2*SettingName.size(), 1);
}

void ControlButton::OnClick()
{
	Linked->GetChildren()[0]->Anim.SetState("new");
	StateManager::LockInput = true;
	AwaitingKey = true;
}

void ControlButton::KeyCallback()
{
	if (AwaitingKey)
	{
		SettingLoader::SetVal(false, Text, std::to_string(StateManager::KeyReturn));
		SetNewValue(StateManager::KeyReturn);
		StateManager::LockInput = false;
		AwaitingKey = false;
		Linked->GetChildren()[0]->Anim.SetState("");
	}
}

Script* ControlButton::Clone(Object* Target, ScriptData In)
{
	return new ControlButton(Target, In);
}

Slider::Slider(Object* a, ScriptData In) : Button(a, "", std::stoi(In.AdditionalData[0]))
{
	Fore = (In.AdditionalData[1] == "true");
	Linked->Anim = Sprite(ResourceManager::GetSprite("SliderKnob"));
	Linked->Anim.AddFrame("Selected", ResourceManager::GetSprite("SliderKnobSel"));
	Percent = ((Fore) ? Sound::ForeVolume : Sound::BackVolume) / 100.0;
	((UIpane*)Linked)->Anchor = Vector2(Percent - 0.5, 0);
}

void Slider::Update()
{
	if (Dragging)
	{
		Linked->Anim.SetState("Selected");
		Object *Parent = Linked->GetParent();
		Percent = ((Parent->Transform.Position - (Parent->Size / 2)).x < Mouse::Pos.x)?std::max(std::min((((Parent->Transform.Position - (Parent->Size / 2)) - Mouse::Pos).Magnitude()) / Parent->Size.x, 1.0), 0.0) : 0;
		((UIpane*)Linked)->Anchor.x = Percent - 0.5;
	}
}

Script* Slider::Clone(Object* Target, ScriptData In)
{
	return new Slider(Target, In);
}

Sprite *Mute::Active = nullptr;
Sprite *Mute::inActive = nullptr;

Mute::Mute(Object* a, ScriptData In) : Button(a, "", std::stoi(In.AdditionalData[0]))
{
	if (Active == nullptr)
	{
		Active = new Sprite(ResourceManager::GetSprite("MuteUnAct"));
		Active->AddFrame("Selected", ResourceManager::GetSprite("MuteAct"));
		inActive = new Sprite(ResourceManager::GetSprite("MuteUninAct"));
		inActive->AddFrame("Selected", ResourceManager::GetSprite("MuteinAct"));
	}

	Fore = (In.AdditionalData[1] == "true");

	Muted = ((Fore) ? Sound::ForeMuted : Sound::BackMuted);
	Linked->Anim = ((Fore) ? Sound::ForeMuted : Sound::BackMuted) ? *inActive : *Active;
}

void Mute::OnClick()
{
	Muted = !Muted;
	Linked->Anim = (!Muted) ? *Active : *inActive;
	((Fore) ? Sound::ForeMuted : Sound::BackMuted) = Muted;
}

Script* Mute::Clone(Object* Target, ScriptData In)
{
	return new Mute(Target, In);
}