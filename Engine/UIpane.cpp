#include "UIpane.h"

UIpane::UIpane(SDL_Texture *Card, Vector2 A, Vector2 Size, Vector2 Pos) : Object(Card)
{
	Offset = -Pos;
	RelativeSize = Size;
	Anchor = -A;
}

void UIpane::Update()
{
	Size = Parent->Size * RelativeSize;
	Transform.Position = Parent->Transform.Position + (Parent->Size*Anchor) + (Offset * Size);
}