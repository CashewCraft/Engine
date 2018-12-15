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
#include "ObjectData.h"

class Script; //Forward declaration for Script because otherwise we get a circular dependancy

class Object
{
	static std::map<int, Object*> PrototypeDict;

	std::vector<Object*> Children;

	bool DeleteFlag = false;

	static std::stack<Object*>ToAdd;
	static std::stack<Object*>ToParents;

	public:

	std::string Tag;

	Sprite Anim;

	static void Instanciate(Object *ToAdd, Object *Parent);

	static void ClearAddStack();

	static Object* Workspace;
	static Object* UI;

	std::vector<Script*> AttachedScripts;

	//factory methods
	static void AddPrototype(int key, Object *ToClone);
	static Object* GetNew(int key, ObjectData *From);

	std::string Name;

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

	virtual void Draw();

	Vector2 Size;

	protected:


	void DelSelf();

	Object *Parent;

	void ForgetChild(Object *p);

	//Factory Method
	virtual Object* Clone(ObjectData* From);
};

#endif