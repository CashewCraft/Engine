#include "LoaderTool.h"

void LoaderTool::init()
{
	//Failsafe
	Object::AddPrototype("", new Object(NULL));

	//Add new Object types here
	Object::AddPrototype("PhysObject", new PhysObject(NULL));
}

std::map<std::string, SDL_Texture*> LoaderTool::ResourceDict = std::map<std::string, SDL_Texture*>();

int LoaderTool::LoadScene(Object *ToParent, const char *filename, SDL_Renderer *r)
{
	std::vector<std::string> Names;
	std::vector<int> NameCounts;
	int NullCount = 0;

	std::ifstream From;
	From.open(filename);
	if (!From.is_open())
	{
	    //#pragma warning(suppress : 4996)
		//printf("Failed to open file: %s\n", strerror(errno));
		return -1;
	}

	std::stack<Object*> Parent;

	Parent.push(ToParent);

	std::string Line;

	while (std::getline(From, Line))
	{
		//Lines are formatted like this: 
		// (ParentType)"ParentImgName"[X,Y]
		// {
		//   (ChildType)"Child1ImgName"[X,Y]
		//   "NULL"
		//   {
		//     "Child2ImgName"[X,Y]
		//   }
		// }

		//std::map<std::string, SDL_Surface*> SurfaceDict;

		std::string Type;
		std::string Name;
		double pos [2];
		std::string FromNumber;
		std::string FromNumber2;
		double Scale = 1;
		bool ReadingY = false;

		bool ReadingPos = false;
		bool ReadingName = false;
		bool ReadingType = false;
		bool ReadingScale = false;
		Object *CreatedScope;
		for (char i : Line)
		{
			if (ReadingType)
			{
				if (i == ')')
				{
					ReadingType = false;
				}
				else
				{
					Type += i;
				}
				continue;
			}
			if (ReadingName)
			{
				if (i == '"')
				{
					if (Name == "NULL")
					{
						CreatedScope = new Object(NULL);

						CreatedScope->Name = "NULL (" + std::to_string(NullCount) + ")";
						Debug::Log("Creating object NULL (" + std::to_string(NullCount) + ")");
						NullCount++;
						Parent.top()->AddChild(CreatedScope);
						Name = "";
					}
					ReadingName = false;
				}
				else
				{
					Name += i;
				}
				continue;
			}
			if (ReadingScale)
			{
				if (i == '>')
				{
					ReadingScale = false;
				}
				else
				{
					FromNumber2 += i;
				}
			}
			if (ReadingPos)
			{
				if (i == ']')
				{
					pos[1] = std::stod(FromNumber);
					transform temp;
					temp.Position = Vector2(pos[0], pos[1]);

					ptrdiff_t pos = std::find(Names.begin(), Names.end(), Name) - Names.begin();
					if (std::find(Names.begin(), Names.end(), Name) != Names.end())
					{
						CreatedScope = Object::GetNew(Type, ResourceDict[Name], temp);

						Debug::Log("Creating object " + Name + " (" + std::to_string(NameCounts[pos]) + ")");
						CreatedScope->Name = Name + " (" + std::to_string(NameCounts[pos]) + ")";
						NameCounts[pos]++;
					}
					else
					{
						ResourceDict[Name] = SDL_CreateTextureFromSurface(r, SDL_LoadBMP(Name.c_str()));
						Debug::Log("Added file " + Name + " to resource directory");
						CreatedScope = Object::GetNew(Type, ResourceDict[Name], temp);

						Names.push_back(Name);
						NameCounts.push_back(0);
						Debug::Log("Creating object " + Name + " (" + std::to_string(NameCounts[pos]) + ")");
						CreatedScope->Name = Name + " (" + std::to_string(NameCounts[pos]) + ")";
						NameCounts[pos]++;
					}

					CreatedScope->Scale = (FromNumber2 == "")?1:std::stod(FromNumber2);

					Parent.top()->AddChild(CreatedScope);

					Type = "";
					Name = "";
					FromNumber = "";
					FromNumber2 = "";
					ReadingPos = false;
					ReadingY = false;
				}
				else if (i == ',')
				{
					pos[0] = std::stod(FromNumber);
					FromNumber = "";
					ReadingY = true;
				}
				else
				{
					FromNumber += i;
				}
				continue;
			}
			switch (i)
			{
				case '(':
					ReadingType = true;
					break;
				case '"':
					ReadingName = true;
					break;
				case '[':
					ReadingPos = true;
					break;
				case '<':
					ReadingScale = true;
					break;
				case '{':
					Parent.emplace(CreatedScope);
					break;
				case '}':
					Parent.pop();
					break;
				default:
					break;
			}
			if (Parent.size() < (unsigned)1)
			{
				break; //Stop reading the file because we've emptied the last object from the stack so we're just going to run into problems
			}
		}
	}

	From.close();

	From.open("LoadAdditional.txt");
	if (!From.is_open())
	{
		//#pragma warning(suppress : 4996)
		//printf("Failed to open file: %s\n", strerror(errno));
		return -1;
	}

	while (std::getline(From, Line))
	{
		ResourceDict[Line] = SDL_CreateTextureFromSurface(r, SDL_LoadBMP(Line.c_str()));
		Debug::Log("Added additional file " + Line + " to resource directory");
	}

	From.close();

	return 0;
}
