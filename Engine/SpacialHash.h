#pragma once

#include "Vector2.h"
#include "Hierachy.h"
#include <map>
#include <vector>

class Object; //Forward declaration to resolve circular dependancy

class SpacialHash
{
	static int Size;
	static std::map<std::pair<int, int>, std::vector<Object*>> HashTable;

	public:
	
	static void SetSize(int CellSize);

	static std::pair<int, int> GetHash(Vector2 Pos);

	static void Update();

	static void AddHash(Object *Obj);

	static std::vector<Object*> *GetCollisions(Object *Obj);
};

