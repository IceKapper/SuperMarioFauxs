#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include"constants.h"
#include<iostream>

using namespace std;

//globals
SDL_Window* g_window = nullptr;

//Function prototypes
bool InitSDL();
void CLoseSDL();

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		SDL_Delay(5000);
	}

	CLoseSDL();

	return 0;
}

bool InitSDL() 
{
	//setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error " << SDL_GetError();
		return false;
	}
	else
	{
		//setup passed to create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//did the window get created>
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		return true;
	}
}

void CLoseSDL()
{
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	
}