#include "Map.h"
#include "TextureManager.h"

int lvl1[20][25] = {
	{0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1},
	{0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1},
	{1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1},
	{1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1},
	{1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1},
	{1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

Map::Map() {
	water = TextureManager::LoadTexture("assets/water.png");
	grass = TextureManager::LoadTexture("assets/grass.png");
	stone = TextureManager::LoadTexture("assets/stone.png");

	LoadMap(lvl1);

	srcRect.x = srcRect.y = 0;
	srcRect.w = dstRect.w = 32;
	srcRect.h = dstRect.h = 32;
	dstRect.x = dstRect.y = 0;
}

void Map::LoadMap(int arr[20][25]) {
	for (int row = 0; row < 20; row++) {
		for (int col = 0; col < 25; col++) {
			map[row][col] = arr[row][col];
		}
	}
}

void Map::DrawMap() {
	int type = 0;

	for (int row = 0; row < 20; row++) {
		for (int col = 0; col < 25; col++) {
			type = map[row][col];
			dstRect.x = col * 32;
			dstRect.y = row * 32;
			switch (type) {
			case 0:
				TextureManager::Draw(stone, srcRect, dstRect);
				break;
			case 1:
				TextureManager::Draw(grass, srcRect, dstRect);
				break;
			case 2:
				TextureManager::Draw(water, srcRect, dstRect);
			default:
				break;
			}
		}
	}
}

int Map::GetCellType(int x, int y, int xMove, int yMove) {
	int futureRow = y / 32 + yMove;
	int futureCol = x / 32 + xMove;
	return map[futureRow+1][futureCol+1] + map[futureRow+1][futureCol] + map[futureRow][futureCol+1];
}