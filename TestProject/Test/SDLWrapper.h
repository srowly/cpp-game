//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

#pragma once
class SDLWrapper
{
public:
	bool isRunning = false;

	//Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	//Starts up SDL and creates window
	bool initSDL();

	//Loads media
	bool loadMedia(const char *);

	//Frees media and shuts down SDL
	void deinitSDL();

	//delays the app via SDL
	void delay(Uint32 duration);

	void EventLoop();

private:

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;

	//The image we will load and show on the screen
	SDL_Surface* gHelloWorld = NULL;

};

