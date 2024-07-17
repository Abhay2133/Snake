#include "core.h"
#include "game_scene.h"

Game::Game() : Game(120, 30) {}
Game::Game(int width, int height) : 
screen(width, height, ' ')
{
	srand(time(0));
	scenes["game_scene"] = new GameScene(&screen, &keysQueue, &isRunning, true);
	activeScene = scenes["game_scene"];
}

Game::~Game()
{
	isRunning = false;
}

void Game::start()
{
	startKeyboardCapture(keysQueue, isRunning);
	while (isRunning) {
		activeScene->update();
	}
}