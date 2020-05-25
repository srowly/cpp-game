#include <SDL.h>

#pragma once
class Texture
{
public:
    //Initializes variables
    Texture();

    //Deallocates memory
    ~Texture();

    void init(SDL_Texture* texture, int width, int height);

    //Deallocates texture
    void free();

    //Gets image dimensions
    int getWidth();
    int getHeight();

    SDL_Texture* getTexture();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

