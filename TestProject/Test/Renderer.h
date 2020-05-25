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
	Texture* loadTextureFromFile(const char* path);

	//Renders texture at given point
	 void renderTexture(int x, int y, Texture* texture);

	 void setRenderedTexture(Texture* texture);

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

	Texture* renderedTexture;
};
