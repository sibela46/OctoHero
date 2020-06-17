#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

GameObject* player;
Map* map;
SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{
}


Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen)
{
	int flags = 0;
	if (fullScreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised..." << std::endl;
		windowWidth = width;
		windowHeight = height;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}

	map = new Map();
	player = new GameObject("assets/player.png", 0, 0);
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	auto pos = player->GetPos();
	int xPos = std::get<0>(pos);
	int yPos = std::get<1>(pos);
	int cellType = -1;
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				cellType = map->GetCellType(xPos, yPos, -1, 0);
				if (cellType == 0 && (xPos-32 >= 0)) {
					player->MoveLeft();
				}
				break;
			case SDLK_RIGHT:
				cellType = map->GetCellType(xPos, yPos, 1, 0);
				if (cellType == 0 && (xPos+32 <= windowWidth)) {
					player->MoveRight();
				}
				break;
			case SDLK_UP:
				cellType = map->GetCellType(xPos, yPos, 0, -1);
				if (cellType == 0 && (yPos-32 >= 0)) {
					player->MoveUp();
				}
				break;
			case SDLK_DOWN:
				cellType = map->GetCellType(xPos, yPos, 0, 1);
				if (cellType == 0 && (yPos+32 <= windowHeight)) {
					player->MoveDown();
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
	}
}

void Game::update()
{
	player->Update();
	auto pos = player->GetPos();
	int xPos = std::get<0>(pos);
	int yPos = std::get<1>(pos);
	std::cout << xPos << " " << yPos << std::endl;
	if (xPos == 0 && yPos == 576) {
		isRunning = false;
		std::cout << "You Win!!!" << std::endl;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	player->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

