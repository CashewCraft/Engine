#include "Hierachy.h"

std::map<std::string, Object*> Object::PrototypeDict;

SDL_Surface* Object::Main = nullptr;

void Object::AddPrototype(std::string key, Object *ToClone)
{
	PrototypeDict[key] = ToClone;
}
Object* Object::GetNew(std::string type, SDL_Surface *sprite, transform pos)
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

Object::Object(SDL_Surface *sprite)
{
	Sprite = sprite;
}

Object::~Object()
{
	for (Object* i : Children)
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
	return Rect(Transform.Position, 1, 1);//Sprite->w, Sprite->h);
}

void Object::OnTick()
{
	Update();
	Draw(Main);
	for (Object *i : Children)
	{
		i->OnTick();
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

void Object::Draw(SDL_Surface *To)
{
	SDL_Rect PosRect = GetRect().SDLf;
	SDL_BlitSurface(Sprite, NULL, To, &PosRect);
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
Object* Object::Clone(SDL_Surface *sprite, transform pos) { return new Object(NULL); }