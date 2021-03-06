#include "pch.h";

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <SDL.h>


//Screen dimension constants
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{

	//The window we'll be rendering to
	SDL_Window* Window = NULL;

	//The surface that will be pasted onto the window
	SDL_Surface* MainSurface = NULL;

	SDL_Renderer* renderer = NULL;

	const int SquareSize = 30;
	const int SquaresNoX = 30;
	const int SquaresNoY = 30;
	bool Squares[SquaresNoY][SquaresNoX];

	SDL_Rect *SquarePos[SquaresNoY][SquaresNoX];
	for (int y = 0; y < SquaresNoY; y++)
	{
		for (int x = 0; x < SquaresNoX; x++)
		{
			Squares[y][x] = false;

			SquarePos[y][x] = new SDL_Rect();
			SDL_Rect *r = SquarePos[y][x];
			r->x = x * SquareSize;
			r->y = y * SquareSize;
			r->w = SquareSize;
			r->h = SquareSize;;
		}
	}

	int SCREEN_WIDTH = SquaresNoX * SquareSize;
	int SCREEN_HEIGHT = SquaresNoY * SquareSize;

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

			//Fill the surface white
			SDL_FillRect(MainSurface, NULL, SDL_MapRGB(MainSurface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(Window);

			renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
			//Clear everything on the window -- paint over with a black colour

			SDL_RenderClear(renderer);
			//Tell SDL we have finished drawing, SDL will actually show our changes:
			SDL_RenderPresent(renderer);

			//Wait two seconds
			SDL_Delay(2000);
		}
	}

	bool running = true;
	SDL_Event e;

	Squares[0][1] = true;
	Squares[1][2] = true;
	Squares[2][0] = true;
	Squares[2][1] = true;
	Squares[2][2] = true;

	while (running)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
				break;
			}
		}

		printf("Frame");

		bool NewSquares[SquaresNoY][SquaresNoX];

		for (int y = 0; y < SquaresNoY; y++) 
		{
			for (int x = 0; x < SquaresNoX; x++)
			{
				bool *thi = &Squares[y][x];

				if (*thi)
				{
					SDL_RenderFillRect(renderer, SquarePos[y][x]);
				}
				else
				{
					SDL_RenderDrawRect(renderer, SquarePos[y][x]);
					//SDL_FillRect(MainSurface, &SquarePos[y%SquaresNoY][x%SquaresNoY], SDL_MapRGB(MainSurface->format, 0xFF, 0xFF, 0xFF));
				}

				int Alive = 0;
				printf("Checking %i,%i",x,y);
				for (int y1 = -1; y1 < 2; y1++) 
				{
					for (int x1 = -1; x1 < 2; x1++)
					{
						printf("Checking n %i,%i", x+x1, y+y1);
						if (x1 != 0 && y1 != 0 && Squares[(y + y1)][(x + x1)])
						{
							Alive++;
						}
					}
				}

				NewSquares[y][x] = (Alive == 2 || Alive == 3);
			}
		}

		for (int y = 0; y < SquaresNoY; y++)
		{
			for (int x = 0; x < SquaresNoX; x++)
			{
				Squares[y][x] = NewSquares[y][x];
			}
		}

		SDL_Delay(2000);

		SDL_RenderPresent(renderer);

		//SDL_UpdateWindowSurface(Window);
	}

	SDL_DestroyWindow(Window);
	SDL_Quit();

	return 0;
}