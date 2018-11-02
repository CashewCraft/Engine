#include "SpacialHash.h"

std::map<Vector2, std::vector<Object*>> SpacialHash::HashTable = std::map<Vector2, std::vector<Object*>>();

int SpacialHash::Size;

void SpacialHash::SetSize(int CellSize)
{
	Size = CellSize;
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
	//Debug::Log("Adding " + Obj->Name + " as hash: " + (std::string)GetHash(Obj->Transform.Position));
	SpacialHash::HashTable[GetHash(Obj->Transform.Position)].push_back(Obj);
}

std::vector<Object*> *SpacialHash::GetCollisions(Object *Obj) 
{
	return &SpacialHash::HashTable[SpacialHash::GetHash(Obj->Transform.Position)];
}