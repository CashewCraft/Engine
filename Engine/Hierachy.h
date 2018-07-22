#ifndef HIERACHY_H
#define HIERACHY_H

#include <vector>
#include <SDL.h>
#include <map>
#include <string>
#include "Transform.h"
#include "Rect.h"

class Object
{
	static std::map<std::string, Object*> PrototypeDict;

	std::vector<Object*> Children;

	SDL_Surface *Sprite;

	std::string Name;

	public:

	//factory methods
	static void AddPrototype(std::string key, Object *ToClone);
	static Object* GetNew(std::string key, SDL_Surface *sprite, transform pos);

	static SDL_Surface *Main;
	transform Transform;

	Object(SDL_Surface *sprite);
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

	virtual void Draw(SDL_Surface *To);

	protected: 

	Object *Parent;

	void ForgetChild(Object *p);

	//Factory Method
	virtual Object* Clone(SDL_Surface *sprite, transform pos);
};

#endif