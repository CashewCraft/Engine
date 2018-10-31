#include "SpacialHash.h"

SpacialHash *SpacialHash::ins = nullptr;
std::map<Vector2, std::vector<Object*>> SpacialHash::HashTable = std::map<Vector2, std::vector<Object*>>();

SpacialHash::SpacialHash(int CellSize)
{
	Size = CellSize;

	if (SpacialHash::ins) 
	{
		delete SpacialHash::ins;
	}
	SpacialHash::ins = this;
}

Vector2 SpacialHash::GetHash(Vector2 Pos)
{
	return Vector2((int)(Pos.x/Size), (int)(Pos.y/Size));
}

void SpacialHash::Update() 
{
	SpacialHash::HashTable = std::map<Vector2, std::vector<Object*>>();
}

void SpacialHash::AddHash(Object *Obj)
{
	SpacialHash::HashTable[GetHash(Obj->Transform.Position)].push_back(Obj);
}

Object *SpacialHash::GetCollisions(Object *Obj) 
{
	//TODO: FIX DIS
}