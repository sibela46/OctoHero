#pragma once
#include "Game.h"
#include <tuple>

class GameObject {
public:
	GameObject(const char* texturesheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	std::tuple<int, int> GetPos();

private:
	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, dstRect;

};