#include "UIpane.h"

UIpane::UIpane(SDL_Texture *Card, bool MSize, Vector2 Pos, Vector2 Size) : Object(Card) 
{
	Offset = Pos; 
	Relative = Size;
	Anchored = false;
	ModSize = MSize;
	if (!ModSize)
	{
		Size *= Relative;
	}
}
UIpane::UIpane(SDL_Texture *Card, bool MSize, Vector2 Pos, Vector2 Size, Vector2 A) : Object(Card)
{
	Offset = Pos;
	Relative = Size;
	Anchored = true;
	Anchor = A;
	ModSize = MSize;
	if (!ModSize)
	{
		Size *= Relative;
	}
}

void UIpane::Update()
{
	if (!Anchored)
	{
		Transform.Position = Parent->Transform.Position + (Parent->Size*Offset);
	}
	else
	{
		Transform.Position = Parent->Transform.Position + (Parent->Size*Anchor) + Offset;
	}
	if (ModSize) 
	{ 
		Size = Parent->Size * Relative; 
	}
}