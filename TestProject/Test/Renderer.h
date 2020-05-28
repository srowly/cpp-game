#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "Texture.h"

#pragma once
class Renderer
{
public:
	Renderer();
	~Renderer();

	bool init(int width, int height);

	//Loads image at specified path
	void loadSpriteSheet(const char* path, int spriteDimensions);

	//Renders texture at given point
	 void renderTexture(int x, int y, Texture* texture, SDL_Rect* clip);

	 void renderSpriteFromSheet(int spriteNo, int xPos, int yPos);

	void drawFilledRect(int x, int y);
	void drawOutlinedRect(int x, int y);

	void drawLine(int x, int y);
	void drawDottedLine(int x, int y);

	void update();

	void clear();

private:

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Color* clearColor;

	Texture* spriteSheet;
	int spriteSheetDimensions;
};

