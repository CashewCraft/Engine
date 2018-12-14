#include "LoaderTool.h"

void LoaderTool::init()
{
	//Add new Object types here
	Object::AddPrototype(0, new PhysObject(NULL));
	Object::AddPrototype(1, new UIpane(NULL));

	Script::AddPrototype(0, new CharController());
	Script::AddPrototype(1, new AI());
	Script::AddPrototype(2, new Scoreboard());
	Script::AddPrototype(3, new Button());

	std::ifstream From;
	From.open("LoadSound.txt");

	std::string Line;
	if (From.is_open())
	{
		while (std::getline(From, Line))
		{
			ResourceManager::SoundDict[Line] = Mix_LoadWAV(("Sounds/" + Line + ".wav").c_str());
			Debug::Loading("Added sound file " + Line + " to resource directory");
		}
	}

	From.close();
	From.open("LoadAdditional.txt");

	if (From.is_open())
	{
		while (std::getline(From, Line))
		{
			ResourceManager::ResourceDict[Line] = SDL_CreateTextureFromSurface(ResourceManager::r, SDL_LoadBMP(("Sprites/" + Line + ".bmp").c_str()));
			Debug::Loading("Added sprite " + Line + " to resource directory");
		}
	}

}

int LoaderTool::LoadScene(Object *ObjParent, Object *UIParent, std::string filename)
{
	Debug::Loading("Loading scene " + filename);

	std::vector<std::string> Names;
	std::vector<int> NameCounts;
	int NullCount = 0;

	std::ifstream From;
	From.open(filename + ".txt");
	if (!From.is_open())
	{
	    //#pragma warning(suppress : 4996)
		//printf("Failed to open file: %s\n", strerror(errno));
		Debug::Error("Could not open file " + (std::string)filename + "!\n");
		return -1;
	}

	std::string Line;
	std::getline(From, Line);

	std::vector<std::string> NormalObjects = ObjectData::Split(Line, ":");

	std::vector<ObjectData*> ConstructionList;
	std::map<int, Object*> Data;

	if (NormalObjects[0] != "")
	{

		for (int i = 0; i < NormalObjects.size(); i++)
		{
			ObjectData *Curr = new ObjectData(NormalObjects[i]);

			//Do something to construct a dependancy tree from children
			//ConstructonList acts so closest = less dependencies

			std::vector<int> RemainingChildren = Curr->Children;
			for (int j = 0; j < ConstructionList.size() + 1; i++)
			{
				//if we are at the end of the list (i.e. dependancies not initialised yet)
				if (j == ConstructionList.size() || RemainingChildren.size() == 0)
				{
					ConstructionList.emplace(ConstructionList.begin() + j, Curr);
					break;
				}

				//Get the position of the current ID in the list
				int Pos = std::find(RemainingChildren.begin(), RemainingChildren.end(), ConstructionList[j]->id) - RemainingChildren.begin();
				if (Pos != RemainingChildren.end() - RemainingChildren.begin())
				{
					//if the ID exists in the list, remove it
					RemainingChildren.erase(RemainingChildren.begin() + Pos);
				}
			}
		}

		for (int i = 0; i < ConstructionList.size(); i++)
		{
			Data[ConstructionList[i]->id] = Object::GetNew(ConstructionList[i]->Type, ConstructionList[i]);

			for (int j : ConstructionList[i]->Children)
			{
				Data[ConstructionList[i]->id]->AddChild(Data[j]);
			}
			for (int j = 0; j < ConstructionList[i]->Scripts.size(); j++)
			{
				Script::GetNew(ConstructionList[i]->Scripts[j], Data[ConstructionList[i]->id], ConstructionList[i]->ScriptAdditional[j]);
			}
		}
		for (int i = 0; i < ConstructionList.size(); i++)
		{
			if (Data[ConstructionList[i]->id]->GetParent() == nullptr)
			{
				ObjParent->AddChild(Data[ConstructionList[i]->id]);
			}
		}
	}

	std::getline(From, Line);

	NormalObjects = ObjectData::Split(Line, ":");

	if (NormalObjects[0] != "")
	{
		ConstructionList = std::vector<ObjectData*>();

		for (int i = 0; i < NormalObjects.size(); i++)
		{
			ObjectData *Curr = new ObjectData(NormalObjects[i]);

			//Do something to construct a dependancy tree from children
			//ConstructonList acts so closest = less dependencies

			std::vector<int> RemainingChildren = Curr->Children;
			for (int j = 0; j < ConstructionList.size() + 1; i++)
			{
				//if we are at the end of the list (i.e. dependancies not initialised yet)
				if (j == ConstructionList.size() || RemainingChildren.size() == 0)
				{
					ConstructionList.emplace(ConstructionList.begin() + j, Curr);
					break;
				}

				//Get the position of the current ID in the list
				int Pos = std::find(RemainingChildren.begin(), RemainingChildren.end(), ConstructionList[j]->id) - RemainingChildren.begin();
				if (Pos != RemainingChildren.end() - RemainingChildren.begin())
				{
					//if the ID exists in the list, remove it
					RemainingChildren.erase(RemainingChildren.begin() + Pos);
				}
			}
		}

		Data = std::map<int, Object*>();
		for (int i = 0; i < ConstructionList.size(); i++)
		{
			Data[ConstructionList[i]->id] = Object::GetNew(ConstructionList[i]->Type, ConstructionList[i]);

			for (int j : ConstructionList[i]->Children)
			{
				Data[ConstructionList[i]->id]->AddChild(Data[j]);
			}
			for (int j = 0; j < ConstructionList[i]->Scripts.size(); j++)
			{
				Script::GetNew(ConstructionList[i]->Scripts[j], Data[ConstructionList[i]->id], ConstructionList[i]->ScriptAdditional[j]);
			}

			if (Data[ConstructionList[i]->id]->GetParent() == nullptr)
			{
				UIParent->AddChild(Data[ConstructionList[i]->id]);
			}
		}
	}
	From.close();

	return 0;
}