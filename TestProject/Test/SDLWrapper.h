#include <SDL.h>
#include <stdio.h>

#include "Renderer.h"
#include "Level.h"

#pragma once
class SDLWrapper
{
public:

	SDLWrapper();
	~SDLWrapper();

	bool isRunning = false;

	//Starts up SDL and creates window
	bool initSDL();

	//Frees media and shuts down SDL
	void deinitSDL();

	//delays the app via SDL
	void delay(Uint32 duration);

	void MainLoop();
	void EventLoop();

private:
	Renderer* renderer;
	Level* level;
	int curSprite = 0;
};

