#include <iostream>

#include "Game.h"
#include "TextureLoader.h"
#include "GameObject.h"


GameObject* ball;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

void Game::init(const char* p_title, int xpos, int ypos, int p_h, int p_w)
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		printf("Init has failed. %s \n", SDL_GetError());
		isRunning = false;
	}
	else
	{	
		printf("Init completed. \n");
		window = SDL_CreateWindow(p_title, xpos, ypos, p_w, p_h, SDL_WINDOW_SHOWN);
		if (!window)
		{
			printf("Window creation failed :%s \n", SDL_GetError());
			isRunning = false;
		}
		printf("Window Created \n");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
			printf("Renderer Created. \n");
		} 
		isRunning = true;
	}

	ball = new GameObject("./resources/gfx/ball.png", renderer, 100, 100);

}

void Game::cleanUp()
{
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_Quit();

	delete(ball);
	
	printf("Cleanup Completed \n");
}

void Game::handleEvent()
{
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
	{
		std::cout << "Button Down" << "\n";
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		ball->handleInputMouseDown(mouseX, mouseY);
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		std::cout << "Button Up" << "\n";
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		ball->handleInputMouseUp(mouseX, mouseY);
		break;
	}
	default:
		break;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	ball->render();
	SDL_RenderPresent(renderer);
}

void Game::update()
{
	ball->update();
}

