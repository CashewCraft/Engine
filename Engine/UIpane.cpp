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

Object* UIpane::Clone(ObjectData *From)
{
	UIpane *temp = new UIpane(From->Sprite);
	temp->Anchor = From->Pos;
	temp->Offset = From->Rotation;
	temp->RelativeSize = From->Size;
	return temp;
}