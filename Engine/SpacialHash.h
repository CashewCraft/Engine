#pragma once

#include "Vector2.h"
#include "Hierachy.h"
#include <map>
#include <vector>

class SpacialHash
{
	int Size;
	static std::map<Vector2, std::vector<Object*>> HashTable;

	public:

	static SpacialHash *ins;
	
	SpacialHash(int CellSize);

	Vector2 GetHash(Vector2 Pos);

	void Update();

	void AddHash(Object *Obj);

	Object *GetCollisions(Object *Obj);
};

