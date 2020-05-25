#include "Texture.h"

Texture::Texture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

Texture::~Texture()
{
    //Deallocate
    free();
}

void Texture::init(SDL_Texture* texture, int width, int height)
{
    this->mTexture = texture;
    mWidth = width;
    mHeight = height;
}

void Texture::free()
{
    //Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

SDL_Texture* Texture::getTexture()
{
    return mTexture;
}

int Texture::getWidth()
{
    return mWidth;
}

int Texture::getHeight()
{
    return mHeight;
}