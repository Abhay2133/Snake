#include "core.h"
#include "game_scene.h"

constexpr auto _HEIGHT_ = 20;
constexpr auto _WIDTH_ = 80;

Game::Game() : Game(_WIDTH_, _HEIGHT_) {}
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