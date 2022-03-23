#pragma once

#include <SDL.h>
#include "Game.h"

class GameObject
{
public:
	GameObject(const char* texturePath, SDL_Renderer* ren, int x, int y);
	~GameObject();

	void update();
	void render();
	inline int getX()
	{
		return xpos;
	}
	inline int getY()
	{
		return ypos;
	}
	void handleInputMouseDown(int mouseX, int mouseY);
	void handleInputMouseUp(int p_mouseX, int p_mouseY);
	void collisionDetection();

private:
	int mouseX, mouseY;
	int xpos, ypos;
	float forceX, forceY;
	int mass = 5;
	float friction = 0.005;
	float angle = 0;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, dstRect;
	SDL_Renderer* renderer;
};

