#include "TextureLoader.h"

SDL_Texture* TextureLoader::loadTexture(const char* path, SDL_Renderer* ren)
{
    SDL_Surface* tempSurface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);
    
    return texture;
}
