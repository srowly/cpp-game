#include "SDLWrapper.h"

SDLWrapper::SDLWrapper()
{
	renderer = NULL;
}

SDLWrapper::~SDLWrapper()
{
	renderer = NULL;
}

bool SDLWrapper::initSDL()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//set running flag
		isRunning = true;
		renderer = new Renderer;
		renderer->init(1600, 960);
		renderer->loadSpriteSheet("sprite_sheet_full.png", 32);
		renderer->renderSpriteFromSheet(curSprite, 800, 480);
	}

	return success;
}

void SDLWrapper::deinitSDL()
{
	delete renderer;
	//Quit SDL subsystems
	SDL_Quit();
}

void SDLWrapper::delay(Uint32 duration)
{
	SDL_Delay(duration);
}

void SDLWrapper::MainLoop()
{
	EventLoop();
}

void SDLWrapper::EventLoop()
{
	//Event handler
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		switch (e.type)
		{
		case SDL_QUIT:
		{
			printf("User Quit");
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				break;
			case SDLK_DOWN:
				break;
			case SDLK_LEFT:
				renderer->clear();
				renderer->renderSpriteFromSheet(curSprite--, 800, 480);
				break;
			case SDLK_RIGHT:
				renderer->clear();
				renderer->renderSpriteFromSheet(curSprite++, 800, 480);
				break;
			default:
				break;
			}
		}
		}
	}
}
