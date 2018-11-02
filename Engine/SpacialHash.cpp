#include "SpacialHash.h"

std::map<std::pair<int, int>, std::vector<Object*>> SpacialHash::HashTable = std::map<std::pair<int, int>, std::vector<Object*>>();

int SpacialHash::Size;

void SpacialHash::SetSize(int CellSize)
{
	Size = CellSize;
}

std::pair<int, int> SpacialHash::GetHash(Vector2 Pos)
{
	return std::make_pair((int)(Pos.x/Size), (int)(Pos.y/Size));
}

void SpacialHash::Update() 
{
	SpacialHash::HashTable = std::map<std::pair<int, int>, std::vector<Object*>>();
}

void SpacialHash::AddHash(Object *Obj)
{
	SpacialHash::HashTable[GetHash(Obj->Transform.Position)].push_back(Obj);
}

std::vector<Object*> *SpacialHash::GetCollisions(Object *Obj) 
{
	return &SpacialHash::HashTable[SpacialHash::GetHash(Obj->Transform.Position)];
}