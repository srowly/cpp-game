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
		//Load media
		if (!sdl.loadMedia("02_getting_an_image_on_the_screen/hello_world.bmp"))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//While application is running
			while (sdl.isRunning)
			{
				sdl.EventLoop();
			}
		}
	}

	sdl.deinitSDL();
	return 0;
}	