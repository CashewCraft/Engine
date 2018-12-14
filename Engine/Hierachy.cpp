#include "Hierachy.h"

#include "Script.h"

std::stack<Object*> Object::ToAdd = std::stack<Object*>();
std::stack<Object*> Object::ToParents = std::stack<Object*>();

void Object::Instanciate(Object *TA, Object *Parent)
{
	ToAdd.push(TA);
	ToParents.push(Parent);
}
void Object::ClearAddStack()
{
	while (!ToAdd.empty())
	{
		if (ToParents.top() != NULL)
		{
			ToParents.top()->AddChild(ToAdd.top());
			//ToAdd.top()->Parent = ToParents.top();
		}
		else
		{
			delete ToAdd.top();
		}
		ToAdd.pop(); ToParents.pop();
	}
}

std::map<int, Object*> Object::PrototypeDict;

Object* Object::Workspace = nullptr;
Object* Object::UI = nullptr;

void Object::AddPrototype(int key, Object *ToClone)
{
	PrototypeDict[key] = ToClone;
}
Object* Object::GetNew(int type, ObjectData *From)
{
	if (PrototypeDict.find(type) == PrototypeDict.end())
	{
		return NULL;
	}
	else
	{
		return PrototypeDict[type]->Clone(From);
	}
}

Object::Object(SDL_Texture *sprite)
{
	Anim = Sprite(sprite);
	int w, h;
	SDL_QueryTexture(Anim.GetCurrSprite(), NULL, NULL, &w, &h);
	Size = Vector2(w, h);
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

void Object::PrepareDelete()
{
	DeleteFlag = true;
}

void Object::DelSelf()
{
	Parent->DelChild(this);
}

Rect Object::GetRect()
{
	return Rect(Transform.Position, Transform.Rotation, Size.x, Size.y);
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

	FixedUpdate();
}

void Object::OnRendTick()
{
	Update();

	for (Script *i : AttachedScripts)
	{
		i->Update();
	}

	Draw();

	for (Object *i : Children)
	{
		i->OnRendTick();
	}

	if (DeleteFlag)
	{
		DelSelf();
	}
}

void Object::FixedUpdate() {}
void Object::Update() {}

void Object::Draw()
{
	SDL_Rect PosRect = GetRect().SDLf;

	//Debug::DrawLine(Transform.Position, Transform.Position + Transform.Rotation);

	SDL_RenderCopyEx(ResourceManager::r, Anim.GetCurrSprite(), NULL, &PosRect, Transform.GetRotAngle(), NULL, SDL_RendererFlip::SDL_FLIP_NONE);
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
Object* Object::Clone(ObjectData *From) { return new Object(NULL); }