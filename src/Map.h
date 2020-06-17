#pragma once
#include "Game.h"

class Map {
public:
	Map();
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();
	int GetCellType(int x, int y, int xMove, int yMove);

private:
	SDL_Rect srcRect, dstRect;

	SDL_Texture* water;
	SDL_Texture* grass;
	SDL_Texture* stone;

	int map[20][25];
};