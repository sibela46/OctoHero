#include "GameObject.h"
#include "TextureManager.h"
#include <vector>

GameObject::GameObject(const char* texturesheet, int x, int y) {
	objTexture = TextureManager::LoadTexture(texturesheet);
	
	xpos = x;
	ypos = y;
}

void GameObject::Update() {

	srcRect.w = 32;
	srcRect.h = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	dstRect.x = xpos;
	dstRect.y = ypos;
	dstRect.w = srcRect.w * 2;
	dstRect.h = srcRect.h * 2;
}

void GameObject::MoveUp() {
	ypos -= srcRect.h;
}

void GameObject::MoveDown() {
	ypos += srcRect.h;
}

void GameObject::MoveLeft() {
	xpos -= srcRect.w;
}

void GameObject::MoveRight() {
	xpos += srcRect.w;
}

std::tuple<int, int> GameObject::GetPos() {
	return std::make_tuple(xpos, ypos);
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &dstRect);
}