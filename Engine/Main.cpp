#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <SDL.h>

#include "Hierachy.h"
#include "LoaderTool.h"
#include "SettingLoader.h"
#include "Time.h"
#include "Mouse.h"
#include "TextGenerator.h"

#include "StateManager.h"

//Screen dimension constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{

	Debug::Init();

	//Use this in case we need to resize the window
	bool JustResized = false;
	double ScreenAspect = 0;

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
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			Debug::Error("Could not intialise audio! SDL_Error: " + (std::string)SDL_GetError());
			return -1;
		}
		if (TTF_Init() < 0)
		{
			Debug::Error("Could not intialise Text! SDL_Error: " + (std::string)SDL_GetError());
			return -1;
		}

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
			SDL_DisplayMode dm;
			SDL_GetDesktopDisplayMode(0, &dm);

			ScreenAspect = ScreenSize.x / ScreenSize.y;

			std::string WindowMode = SettingLoader::GetValueOf("WindowMode", "Windowed");
			if (WindowMode == "Fullscreen")
			{
				Camera::WindowMode = 2;
				SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);
				SDL_SetWindowSize(Window, dm.w, dm.h);
			}
			else if (WindowMode == "Borderless")
			{
				Camera::WindowMode = 1;
				SDL_SetWindowSize(Window, dm.w, dm.h);
				SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			}

			Camera::Size = ScreenSize;

			//Get window surface
			MainSurface = SDL_GetWindowSurface(Window);

			//Create a renderer
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

			//Tell all the objects where to paste to
			ResourceManager::r = Renderer;

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
	Object::UI = new Object(NULL);
	if (LoaderTool::LoadScene(Object::Workspace, Object::UI, "MM") < 0)
	{
		std::cin.get();
		return -1;
	}

	bool running = true;
	SDL_Event e;

	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

	SpacialHash::SetSize(15);

	while (running)
	{
		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

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
						if (JustResized)
						{
							JustResized = false;
						}
						else
						{
							double Aspect = (double)e.window.data1 / (double)e.window.data2;

							if (Aspect != ScreenAspect && Camera::WindowMode == 0 && !(SDL_WINDOW_MAXIMIZED & SDL_GetWindowFlags(Window)))
							{
								Debug::Flag("Window does not match aspect, scaling");
								if (e.window.data1 != Camera::Size.x && e.window.data2 == Camera::Size.y)
								{
									//scale Y
									Camera::Size = Vector2(e.window.data1, (1.0 / ScreenAspect) * e.window.data1);
								}
								else if (e.window.data1 == Camera::Size.x && e.window.data2 != Camera::Size.y)
								{
									//scale X
									Camera::Size = Vector2(ScreenAspect * e.window.data2, e.window.data2);
								}
								else
								{
									if (std::abs(e.window.data1-Camera::Size.x) > std::abs(e.window.data2-Camera::Size.y))
									{
										//if X was changed more
										Camera::Size = Vector2(e.window.data1, (1.0 / ScreenAspect) * e.window.data1);
									}
									else
									{
										Camera::Size = Vector2(ScreenAspect * e.window.data2, e.window.data2);
									}
								}

								SDL_SetWindowSize(Window, Camera::Size.x, Camera::Size.y);
							}
							else
							{
								Camera::Size = Vector2(e.window.data1, e.window.data2);
								SDL_SetWindowSize(Window, Camera::Size.x, Camera::Size.y);
							}

							Debug::Flag("Resized window to " + (std::string)Camera::Size);
							JustResized = true; //Resizing the window via command will trigger a second event
						}
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

		//Set the Position and size of the UI base
		Object::UI->Size = Camera::Size;
		Object::UI->Transform.Position = Camera::Position + (Camera::Size/2);

		//Update all of the physics for this tick, along with any fixedupdate functions
		Object::Workspace->OnPhysTick();

		//Render all the sprites after running any Regular update functions
		Object::Workspace->OnRendTick();
		Object::UI->OnRendTick();

		//Full incorporate any objects that were added in the last run
		Object::ClearAddStack();

		SDL_RenderPresent(Renderer);
		//SDL_UpdateWindowSurface(Window);

		Time::Incr();

		if (StateManager::NewScene)
		{
			MenuManager::ClearAll();
			for (Object *i : Object::Workspace->GetChildren())
			{
				Object::Workspace->DelChild(i);
			}
			for (Object *i : Object::UI->GetChildren())
			{
				Object::UI->DelChild(i);
			}

			if (LoaderTool::LoadScene(Object::Workspace, Object::UI, StateManager::SceneName.c_str()) < 0)
			{
				std::cin.get();
				return -1;
			}
			StateManager::NewScene = false;
		}
	}

	ResourceManager::FreeAll();

	SDL_DestroyRenderer(ResourceManager::r);
	SDL_DestroyWindow(Window);
	SDL_Quit();
	
	Debug::Close();

	return 0;
}