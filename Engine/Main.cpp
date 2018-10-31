#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <SDL.h>

#include "Hierachy.h"
#include "LoaderTool.h"
#include "CharController.h"
#include "Time.h"
#include "Mouse.h"
#include "AI.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{

	//The window we'll be rendering to
	SDL_Window* Window = NULL;

	//The surface that will be pasted onto the window
	SDL_Surface* MainSurface = NULL;

	SDL_Renderer* Renderer = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (Window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			Camera::Size = Vector2(SCREEN_WIDTH, SCREEN_HEIGHT);

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

	Mouse::SetPos();

	LoaderTool::init(); //Setup dictionaries for object creation

	printf("Successfully initalised, begining load process.\n");

	Object Workspace = Object(NULL);
	if (LoaderTool::LoadScene(&Workspace, "test.txt", Renderer) < 0)
	{
		std::cin.get();
		return -1;
	}

	bool running = true;
	SDL_Event e;

	CharController a = CharController(Workspace.GetChildren()[0]->GetChildren()[0]->GetChildren()[0]);
	AI b = AI(Workspace.GetChildren()[0]->GetChildren()[1]);
	Workspace.GetChildren()[0]->GetChildren()[0]->GetChildren()[0]->Name = "Player";
	b.Player = (PhysObject*)(Workspace.GetChildren()[0]->GetChildren()[0]->GetChildren()[0]);

	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

	printf("Result is %f", (std::atan2(1, 1)) / transform::Pi);

	while (running)
	{
		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
		//SDL_FillRect(MainSurface, NULL, SDL_MapRGB(MainSurface->format, 0xFF, 0xFF, 0xFF));

		//Camera::Position = (Workspace.GetChildren()[0]->GetChildren()[1])->Transform.Position - (Camera::Size/2);

		SDL_RenderClear(Renderer);

		SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);

		Mouse::SetPos(); //Update the mouse position
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
				break;
			}
			else if (e.type == SDL_WINDOWEVENT)
			{
				if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					Camera::Size = Vector2(e.window.data1, e.window.data2);
				}
			}
			KeyHooks::Execute(e); //Run any callback functions attached to this key
		}

		Workspace.OnTick();

		SDL_RenderPresent(Renderer);
		//SDL_UpdateWindowSurface(Window);

		Time::Incr();
	}

	SDL_DestroyWindow(Window);
	SDL_Quit();

	return 0;
}