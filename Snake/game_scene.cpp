#include "game_scene.h"
#include"helper.h"


GameScene::GameScene(Screen* screen, Queue<char>* keysQueue, bool* isRunning, bool isActive) :
	Scene(screen, keysQueue, isRunning, isActive),
	snake(5, 5, '#', 'O'),
	fruit()
{	
	init();
}

void GameScene::update()
{
	handleInput();
	handleCollisions();
	updateEntities();
	renderScreen();
}

void GameScene::init()
{
	createRect(*screen, 0, 0, screen->width - 2, screen->height - 2);
	fruit.pos.set(randint(1, screen->width - 3), randint(1, screen->height - 3));
}

void GameScene::handleInput()
{
	if (keysQueue->size() > 1) {
		int a = 1;
	}
	while (!keysQueue->isEmpty()) {
		char key = keysQueue->pop();
		// std::cout << key;
		switch (key) {

			// Handling Movement
		case 'w':
		case 'a':
		case 's':
		case 'd':
			snake.handleInput(key);
			break;
		}
	}
}


void GameScene::updateEntities()
{
	snake.update(*screen);
	fruit.update(*screen);
}

void GameScene::renderScreen()
{
	string scoreTxt = "Score : " + to_string(score);
	drawText(*screen, scoreTxt, screen->width - scoreTxt.size() - 5, 3);
	drawScreen(*screen, _sleepMs);
}

void GameScene::handleCollisions()
{
	Unit* snakeHead = snake.body.front();

	// HEAD AND FRUIT collison
	if (fruit.pos.x == snakeHead->pos.x && fruit.pos.y == snakeHead->pos.y)
	{
		fruit.respawn(*screen);
		snake.setSize(snake.body.size() + 1);
		score += 1;
	}
}
