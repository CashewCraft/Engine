#include "LoaderTool.h"

void LoaderTool::init()
{
	//Failsafe
	Object::AddPrototype("", new Object(NULL));

	//Add new Object types here
	Object::AddPrototype("PhysObject", new PhysObject(NULL));
}

int LoaderTool::LoadScene(Object *ToParent, const char *filename, SDL_Renderer *r)
{
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

		std::map<std::string, SDL_Surface*> SurfaceDict;

		std::string Type;
		std::string Name;
		double pos [2];
		std::string FromNumber;
		bool ReadingY = false;

		bool ReadingPos = false;
		bool ReadingName = false;
		bool ReadingType = false;
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
			if (ReadingPos)
			{
				if (i == ']')
				{
					pos[1] = std::stod(FromNumber);
					transform temp;
					temp.Position = Vector2(pos[0], pos[1]);

					CreatedScope = Object::GetNew(Type, SDL_CreateTextureFromSurface(r, SDL_LoadBMP(Name.c_str())), temp);
					Parent.top()->AddChild(CreatedScope);
					Type = "";
					Name = "";
					FromNumber = "";
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
	return 0;
}
