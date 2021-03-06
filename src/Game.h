#pragma once
#include "SDL.h"
#undef main
#include "SDL_image.h"
#include <stdio.h>
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer *renderer;

private:
	bool isRunning;
	SDL_Window *window;
	int windowWidth = 0;
	int windowHeight = 0;
};

