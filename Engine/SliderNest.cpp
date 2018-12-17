#include "SliderNest.h"

SliderNest::SliderNest(Object *a, ScriptData o) : Script(a)
{
	Object *n = new UIpane(NULL, Vector2(), Vector2(0.06,2), Vector2());
	Linked->AddChild(n);
	new Slider(n, o);
}