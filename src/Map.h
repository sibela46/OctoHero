#pragma once
#include "Game.h"

class Map {
public:
	Map();
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();

private:
	SDL_Rect srcRect, dstRect;

	SDL_Texture* sea;
	SDL_Texture* grass;

	int map[20][25];
};