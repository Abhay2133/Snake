#include<iostream>
#include "helper.h"
#include "game.h"

Game::Game() : Game(120, 30, ' ') {}
Game::Game(int width, int height, char _bg) : bg{ _bg }, isRunning(true), screen(width, height, _bg), player(4, 4, 0,0,'@',1,1) {}

Game::~Game()
{
	isRunning = false;
}

void Game::start()
{
	startKeyboardCapture(keysQueue, isRunning);

	createRect(screen, 0, 0, screen.width - 2, screen.height - 2);

	while (isRunning) {
		handleInput();
		updateEntities();
		renderScreen();
	}
}

void Game::handleInput()
{
	while (!keysQueue.isEmpty()) {
		char key = keysQueue.pop();
		std::cout << key;
		switch (key) {

			// Handling Movement
		case 'w': player.dir.y = player.dir.y == 0 ? -1 : player.dir.y; player.dir.x = 0; _sleepMs=100; break;
		case 'a': player.dir.x = player.dir.x == 0 ? -1 : player.dir.x; player.dir.y = 0; _sleepMs=33; break;
		case 's': player.dir.y = player.dir.y == 0 ? 1 : player.dir.y;  player.dir.x = 0; _sleepMs=100; break;
		case 'd': player.dir.x = player.dir.x == 0 ? 1 : player.dir.x;  player.dir.y = 0; _sleepMs=33; break;
		}
	}
}

void Game::renderScreen()
{
	drawScreen(screen, _sleepMs);

}

void Game::updateEntities()
{
	setPixel(screen, player.pos.x, player.pos.y, ' ');
	player.pos.x = clamp(player.pos.x + player.dir.x * player.speed.x, 1, screen.width - 2);
	player.pos.y = clamp(player.pos.y + player.dir.y * player.speed.x, 1, screen.height - 2);
	setPixel(screen, player.pos.x, player.pos.y, player.c);
}


