#include "ObjectData.h"

ObjectData::ObjectData(std::string in)
{
	std::vector<std::string> args = Split(in, ";");

	id = std::stoi(args[0]);
	Type = std::stoi(args[1]);
	Sprite = (args[2] == "")?NULL:ResourceManager::GetSprite(args[2]);
	Size.x = std::stod(args[3]);
	Size.y = std::stod(args[4]);
	Pos.x = std::stod(args[5]);
	Pos.y = std::stod(args[6]);
	Rotation.x = std::stod(args[7]);
	Rotation.y = std::stod(args[8]);

	std::vector<std::string> Chil = Split(args[9], ",");
	for (std::string i : Chil)
	{
		if (i != "") { Children.push_back(std::stoi(i)); }
	}

	std::vector<std::string> Scri = Split(args[10], ",");
	for (std::string i : Scri)
	{
		if (i != "") { Scripts.push_back(std::stoi(i)); }
	}

	std::vector<std::string> ScriAdd = Split(args[11], ",");
	for (std::string i : ScriAdd)
	{
		ScriptAdditional.push_back(ScriptData(Split(i,"|")));
	}
}

std::vector<std::string> ObjectData::Split(std::string To_Split, std::string Del)
{
	//variable to store the position in the string that the delimiter occours
	int Pos;

	//list to store the results
	std::vector<std::string> Result;

	//while the delimiter exists in the string
	while ((Pos = To_Split.find(Del)) != std::string::npos)
	{
		//create a new string containing everything before the delimiter
		std::string Sub = To_Split.substr(0, Pos);

		//add it to the results
		Result.push_back(Sub);

		//Remove the stuff that was just added plus the delimiter
		To_Split.erase(0, Pos + Del.length());
	}

	Result.push_back(To_Split);

	//return the results
	return Result;
}