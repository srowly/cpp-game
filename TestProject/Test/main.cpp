#include "SDLWrapper.h"

int main(int argc, char* args[])
{
	SDLWrapper sdl;

	if (!sdl.initSDL())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		while (sdl.isRunning)
		{
			sdl.MainLoop();
		}
	}

	sdl.deinitSDL();
	return 0;
}	