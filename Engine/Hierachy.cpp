#include "Hierachy.h"

#include "Script.h"

std::map<std::string, Object*> Object::PrototypeDict;

SDL_Renderer* Object::Main = nullptr;

void Object::AddPrototype(std::string key, Object *ToClone)
{
	PrototypeDict[key] = ToClone;
}
Object* Object::GetNew(std::string type, SDL_Texture *sprite, transform pos)
{
	if (PrototypeDict.find(type) == PrototypeDict.end())
	{
		return NULL;
	}
	else
	{
		return PrototypeDict[type]->Clone(sprite, pos);
	}
}

Object::Object(SDL_Texture *sprite)
{
	Sprite = sprite;
}

Object::~Object()
{
	for (Object* i : Children)
	{
		delete i;
	}
	for (Script* i : AttachedScripts)
	{
		delete i;
	}
}

std::vector<Object*> Object::GetChildren()
{
	return Children;
}

Object* Object::GetParent()
{
	return Parent;
}

void Object::SwitchParent(Object *p)
{
	//method to cleanly deparent from current parent and child this object to a new one
	Parent->ForgetChild(this);
	p->AddChild(this);
}

void Object::AddChild(Object *p)
{
	Children.push_back(p);
	p->Parent = this;
}

void Object::DelChild(Object *p)
{
	int count = 0;
	for (Object *i : Children)
	{
		if (i == p)
		{
			Children.erase(Children.begin() + count);
			delete p;
			break;
		}
		count++;
	}
}

void Object::DelSelf()
{
	Parent->DelChild(this);
}

Rect Object::GetRect()
{
	int w, h;
	SDL_QueryTexture(Sprite, NULL, NULL, &w, &h);
	return Rect(Transform.Position, w, h);//Sprite->w, Sprite->h);
}

void Object::OnPhysTick()
{
	for (Script *i : AttachedScripts)
	{
		i->FixedUpdate();
	}

	for (Object *i : Children)
	{
		i->OnPhysTick();
	}

	Update();
}

void Object::OnRendTick()
{
	for (Script *i : AttachedScripts)
	{
		for (Object *c : *SpacialHash::GetCollisions(this))
		{
			if (c != this)
			{
				i->OnCollision(c);
			}
		}
		i->Update();
	}

	Draw();

	for (Object *i : Children)
	{
		i->OnRendTick();
	}
}

void Object::Update() {}

void Object::Shift(Vector2 c, int m)
{
	Transform.Position += (c * m);
	for (Object *i : Children)
	{
		i->Shift(c,m);
	}
}

void Object::Draw()
{
	SDL_Rect PosRect = GetRect().SDLf;

	Debug::DrawLine(Transform.Position, Transform.Position + Transform.Rotation);

	SDL_RenderCopyEx(Object::Main, Sprite, NULL, &PosRect, Transform.GetRotAngle(), NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}

void Object::ForgetChild(Object *p)
{
	//Remove our reference to a given child without deleting it
	int count = 0;
	for (Object *i : Children)
	{
		if (i == p)
		{
			Children.erase(Children.begin() + count);
			break;
		}
		count++;
	}
}

//Factory method, children should ALL overwrite this if they want to be created properly at stage load
Object* Object::Clone(SDL_Texture *sprite, transform pos) { return new Object(NULL); }