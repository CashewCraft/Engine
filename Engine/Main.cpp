#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <SDL.h>

#include "Hierachy.h"
#include "LoaderTool.h"
#include "SettingLoader.h"
#include "CharController.h"
#include "Time.h"
#include "Mouse.h"
#include "AI.h"

//Screen dimension constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	Debug::Init();

	//The window we'll be rendering to
	SDL_Window* Window = NULL;

	//The surface that will be pasted onto the window
	SDL_Surface* MainSurface = NULL;

	SDL_Renderer* Renderer = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Debug::Error("SDL could not initialize! SDL_Error: " + (std::string)SDL_GetError());
	}
	else
	{
		//Create window

		std::string Res = SettingLoader::GetValueOf("Resolution", "640x480");
		Vector2 ScreenSize = Vector2(std::stoi(Res.substr(0, Res.find('x'))), std::stoi(Res.substr(Res.find('x')+1, Res.length()-1)));

		Window = SDL_CreateWindow("Joshua Manders-Jones - Games Programming - 17642735 - <Game Name>", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenSize.x, ScreenSize.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (Window == NULL)
		{
			Debug::Error("Window could not be created! SDL_Error: " + (std::string)SDL_GetError());
		}
		else
		{
			std::string WindowMode = SettingLoader::GetValueOf("WindowMode", "Windowed");
			if (WindowMode == "Fullscreen")
			{
				SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);
			}
			else if (WindowMode == "Borderless")
			{
				SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			}

			Camera::Size = ScreenSize;

			//Get window surface
			MainSurface = SDL_GetWindowSurface(Window);

			//Create a renderer
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

			//Tell all the objects where to paste to
			Object::Main = Renderer;

			//Fill the surface white
			SDL_FillRect(MainSurface, NULL, SDL_MapRGB(MainSurface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(Window);

			//Wait two seconds
			SDL_Delay(2000);
		}
	}

	Mouse::Controller = SettingLoader::GetValueOf("Controller", "False") == "True";
	int ControlDeadzone = std::stoi(SettingLoader::GetValueOf("Deadzone", "8000"));
	Debug::Flag("There are currently " + std::to_string(SDL_NumJoysticks()) + " joystick(s) connected");
	if (Mouse::Controller && SDL_NumJoysticks() > 0)
	{
		Debug::Log("Initialising Gamepad controls");
		Mouse::Controller = true;
		Mouse::CInstance = SDL_JoystickOpen(0);
		if (Mouse::CInstance == nullptr)
		{
			Debug::Error("Failed to open joystick! SDL_Error: " + (std::string)SDL_GetError());
			Debug::Error("Settings are set to use controller, but no valid joysticks are connected! Defaulting to keyboard control.");
			Mouse::Controller = false;
			Mouse::SetPos();
		}
	}
	else if (Mouse::Controller)
	{
		Debug::Error("Settings are set to use controller, but no valid joysticks are connected! Defaulting to keyboard control.");
		Mouse::Controller = false;
		Mouse::SetPos();
	}
	else
	{
		Mouse::SetPos();
	}

	LoaderTool::init(); //Setup dictionaries for object creation

	Debug::Log("Successfully initalised, begining load process.");

	Object::Workspace = new Object(NULL);
	if (LoaderTool::LoadScene(Object::Workspace, "test.txt", Renderer) < 0)
	{
		std::cin.get();
		return -1;
	}

	bool running = true;
	SDL_Event e;

	new CharController(Object::Workspace->GetChildren()[0]->GetChildren()[0]);
	new AI(Object::Workspace->GetChildren()[0]->GetChildren()[1], (PhysObject*)(Object::Workspace->GetChildren()[0]->GetChildren()[0]));
	Object::Workspace->GetChildren()[0]->GetChildren()[0]->Name = "Player";
	Object::Workspace->GetChildren()[0]->GetChildren()[1]->Name = "Enemy";

	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

	SpacialHash::SetSize(15);

	while (running)
	{
		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
		//SDL_FillRect(MainSurface, NULL, SDL_MapRGB(MainSurface->format, 0xFF, 0xFF, 0xFF));

		//Camera::Position = (Workspace.GetChildren()[0]->GetChildren()[1])->Transform.Position - (Camera::Size/2);

		SDL_RenderClear(Renderer);

		SpacialHash::Update();

		SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);

		SDL_Rect r = SDL_Rect();
		r.w = Camera::Size.x;
		r.h = Camera::Size.y;
		SDL_RenderDrawRect(Renderer, &r);

		if (!Mouse::Controller)
		{
			Mouse::SetPos(); //Update the mouse position
		}

		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
				case (SDL_QUIT):
					running = false;
					break;
				case (SDL_WINDOWEVENT):
					if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
					{
						Debug::Log("Window resized");
						Camera::Size = Vector2(e.window.data1, e.window.data2);
					}
					break;
				case (SDL_JOYAXISMOTION):
					if (Mouse::Controller)
					{
						if (e.jaxis.axis < 2 && std::abs(e.jaxis.value) > ControlDeadzone)
						{
							((e.jaxis.axis == 0) ? (Mouse::Pos.x) : (Mouse::Pos.y)) = e.jaxis.value;
						}
					}
					break;
				default:
					KeyHooks::Execute(e); //Run any callback functions attached to this key
					break;
			}
		}

		//Update all of the physics for this tick, along with any fixedupdate functions
		Object::Workspace->OnPhysTick();

		//Render all the sprites after running any Regular update functions
		Object::Workspace->OnRendTick();

		//Full incorporate any objects that were added in the last run
		Object::ClearAddStack();

		SDL_RenderPresent(Renderer);
		//SDL_UpdateWindowSurface(Window);

		Time::Incr();
	}

	SDL_DestroyWindow(Window);
	SDL_Quit();
	
	Debug::Close();

	return 0;
}