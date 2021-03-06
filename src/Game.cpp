#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

GameObject* player;
GameObject* octopus;
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
	player = new GameObject("assets/player.png", 0, 480);
	octopus = new GameObject("assets/octopus.png", 768, 96);
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
				if (cellType == 0 && (xPos-16 >= 0)) {
					player->MoveLeft();
				}
				break;
			case SDLK_RIGHT:
				cellType = map->GetCellType(xPos, yPos, 1, 0);
				if (cellType == 0 && (xPos+16 <= windowWidth)) {
					player->MoveRight();
				}
				break;
			case SDLK_UP:
				cellType = map->GetCellType(xPos, yPos, 0, -1);
				if (cellType == 0 && (yPos-16 >= 0)) {
					player->MoveUp();
				}
				break;
			case SDLK_DOWN:
				cellType = map->GetCellType(xPos, yPos, 0, 1);
				if (cellType == 0 && (yPos+16 <= windowHeight)) {
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
	octopus->Update();
	auto pos = player->GetPos();
	int xPos = std::get<0>(pos);
	int yPos = std::get<1>(pos);
	if (xPos == 768 && yPos == 96) {
		isRunning = false;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	player->Render();
	octopus->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

