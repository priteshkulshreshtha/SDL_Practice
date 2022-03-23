#pragma once

#include <SDL.h>
#include <SDL_image.h>


class Game
{
public:
	Game()
		:window(NULL), renderer(NULL)
	{};

	bool isRunning = true;

	void init(const char* p_title, int xpos, int ypos, int p_h, int p_w);
	void cleanUp();
	void handleEvent();
	void render();
	void update();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

