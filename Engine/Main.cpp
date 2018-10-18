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
	Workspace.GetChildren()[0]->GetChildren()[0]->GetChildren()[0]->Name = "Player";

	//WHAT YOU WERE LAST DOING:

	//Need to fix issue where moves aren't being properly reversed when going back in time
	//they seem to have some wierd issues related to switching between them?

	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

	while (running)
	{
		//SDL_FillRect(MainSurface, NULL, SDL_MapRGB(MainSurface->format, 0xFF, 0xFF, 0xFF));

		SDL_RenderClear(Renderer);

		Mouse::SetPos(); //Update the mouse position
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
				break;
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