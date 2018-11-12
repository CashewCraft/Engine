#ifndef HIERACHY_H
#define HIERACHY_H

#include <vector>
#include <SDL.h>
#include <map>
#include <string>
#include <iostream>
#include <stack>
#include "Transform.h"
#include "Rect.h"
#include "Debug.h"
#include "SpacialHash.h"
#include "Sprite.h"

class Script; //Forward declaration for Script because otherwise we get a circular dependancy

class Object
{
	static std::map<std::string, Object*> PrototypeDict;

	std::vector<Object*> Children;

	bool DeleteFlag = false;

	static std::stack<Object*>ToAdd;
	static std::stack<Object*>ToParents;

	public:

	Sprite Anim;

	static void Instanciate(Object *ToAdd, Object *Parent);

	static void ClearAddStack();

	static Object* Workspace;

	std::vector<Script*> AttachedScripts;

	//factory methods
	static void AddPrototype(std::string key, Object *ToClone);
	static Object* GetNew(std::string key, SDL_Texture *sprite, transform pos);

	std::string Name;

	static SDL_Renderer *Main;
	transform Transform;

	Object(SDL_Texture *sprite);
	~Object(); //Make sure children are deleted since we only use references

	std::vector<Object*> GetChildren();

	Object* GetParent();

	void SwitchParent(Object *p);

	void AddChild(Object *p);

	void DelChild(Object *p);

	void PrepareDelete();

	Rect GetRect();

	void OnPhysTick();
	void OnRendTick();

	virtual void FixedUpdate();
	virtual void Update();

	void Shift(Vector2 Change, int Mult = 1);

	virtual void Draw();

	Vector2 Size;

	protected:


	void DelSelf();

	Object *Parent;

	void ForgetChild(Object *p);

	//Factory Method
	virtual Object* Clone(SDL_Texture *sprite, transform pos);
};

#endif