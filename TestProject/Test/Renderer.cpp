#include "Renderer.h"

Renderer::Renderer()
{
	renderer = NULL;
	spriteSheet = NULL;
	window = NULL;
	clearColor = NULL;
}

Renderer::~Renderer()
{
	clearColor = NULL;

	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}

	if (window != NULL)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}
	
	setSpriteSheet(NULL, 0);

	//de init png loading substem
	IMG_Quit();
}

bool Renderer::init(int width, int height)
{
	SDL_Color color = { 255, 255, 255, 255 };
	clearColor = &color;

	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		//Create renderer for window
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			}
		}
	}
	clear();
	return true;
}

void Renderer::update()
{
	SDL_RenderPresent(renderer);
}

void Renderer::clear()
{
	SDL_SetRenderDrawColor(renderer, clearColor->r, clearColor->g, clearColor->b, clearColor->a);
	SDL_RenderClear(renderer);
}

void Renderer::drawFilledRect(int x, int y) 
{
	//Render red filled quad
	SDL_Rect fillRect = { x / 4, y / 4, x / 2, y / 2 };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &fillRect);

	update();
}

void Renderer::drawOutlinedRect(int x, int y)
{
	//Render green outlined quad
	SDL_Rect outlineRect = { x / 6, y / 6, x * 2 / 3, y * 2 / 3 };
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(renderer, &outlineRect);
}

void Renderer::drawLine(int x, int y)
{
	//Draw blue horizontal line
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(renderer, 0, y / 2, x, y / 2);
}

void Renderer::drawDottedLine(int x, int y)
{
	//Draw vertical line of yellow dots
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
	for (int i = 0; i < y; i += 4)
	{
		SDL_RenderDrawPoint(renderer, x / 2, i);
	}
}

Texture* Renderer::loadTextureFromFile(const char* path)
{
    //The final texture
	Texture* texture = new Texture();

    SDL_Texture* sdlTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        //Create texture from surface pixels
		sdlTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if (sdlTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }
        else
        {
			texture->init(sdlTexture, loadedSurface->w, loadedSurface->h);
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    return texture;
}

void Renderer::setSpriteSheet(Texture* sheet, int dimension)
{
	if (spriteSheet != NULL)
	{
		delete spriteSheet;
	}

	spriteSheet = sheet;
	this->dimension = dimension;
}

void Renderer::renderSpriteFromSheet(int spriteNo, int xPos, int yPos)
{
	if (spriteSheet == NULL)
		return;

	int rows = spriteSheet->getHeight() / dimension;

	int y = spriteNo / rows;
	int x = spriteNo % rows;

	SDL_Rect clip = { x*dimension, y*dimension, dimension, dimension };

	renderTexture(xPos, yPos, spriteSheet, &clip);
}

void Renderer::renderTexture(int xPos, int yPos, Texture* texture, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { xPos, yPos, texture->getWidth(), texture->getHeight() };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

    //Set rendering space and render to screen
    SDL_RenderCopy(renderer, texture->getTexture(), clip, &renderQuad);

	update();
}