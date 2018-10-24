#ifndef HIERACHY_H
#define HIERACHY_H

#include <vector>
#include <SDL.h>
#include <map>
#include <string>
#include <iostream>
#include "Transform.h"
#include "Rect.h"
#include "Debug.h"

class Script; //Forward declaration for Script because otherwise we get a circular dependancy

class Object
{
	static std::map<std::string, Object*> PrototypeDict;

	std::vector<Object*> Children;

	SDL_Texture *Sprite;

	public:

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

	void DelSelf();

	Rect GetRect();

	void OnTick();

	virtual void Update();

	void Shift(Vector2 Change, int Mult = 1);

	virtual void Draw();

	protected: 

	Object *Parent;

	void ForgetChild(Object *p);

	//Factory Method
	virtual Object* Clone(SDL_Texture *sprite, transform pos);
};

#endif