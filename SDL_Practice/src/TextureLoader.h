#pragma once

#include <SDL.h>
#include <SDL_image.h>

class TextureLoader
{
public:
	static SDL_Texture* loadTexture(const char* path, SDL_Renderer* ren);
	
};

