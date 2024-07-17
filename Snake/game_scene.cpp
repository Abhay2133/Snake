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
	//snake.setSize(10);
	loadHS();
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
		case 'w':
		case 'a':
		case 's':
		case 'd':
		case 'p':
			snake.handleInput(key);
			break;
		case 'r':
			if (snake.isDead) restart();
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
	string hsTxt = "HighScore : " + to_string(highScore);

	createRect(*screen, 0, 0, screen->width - 2, screen->height - 2);

	drawText(*screen, scoreTxt, screen->width - scoreTxt.size() - 5, 3);
	drawText(*screen, hsTxt, 3, 3);
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

	// HEAD and WALL collision
	auto pos = snakeHead->pos;
	if (pos.y == 0) 
	{
		snakeHead->pos.y = screen->height - 1;
	}
	else if (pos.y == screen->height - 1)
	{
		snakeHead->pos.y = 1;
	}
	else if (pos.x == 0)
	{
		snakeHead->pos.x = screen->width - 1;
	}
	else if (pos.x == screen->width - 1)
	{
		snakeHead->pos.x = 1;
	}

	// HEAD and Body collision
	for (int i = 1; i < snake.body.size(); i++) {
		Unit* part = snake.body[i];
		if (snakeHead->pos.x == part->pos.x && snakeHead->pos.y == part->pos.y)
		{
			gameover();
		}
	}
}

void GameScene::saveHS()
{
	std::ofstream log_file("highscore.txt", std::ios_base::out | std::ios_base::trunc);
	if (log_file.is_open()) {
		log_file << to_string(highScore);
		log_file.close();
	}
	else {
		std::cerr << "Error opening log file!" << std::endl;
	}
}

void GameScene::loadHS()
{
	std::ifstream myfile;
	myfile.open("highscore.txt");

	if (myfile.is_open()) {
		string highscoreString = "";
		myfile >> highscoreString;
		myfile.close();
		highScore = stoi(highscoreString);
	}
	else {
		std::cerr << "Error opening file!" << std::endl;
		return;
	}
}

void GameScene::gameover()
{
	snake.isDead = true;
	if (score > highScore)
	{
		highScore = score;
		saveHS();
		string hsTxt = "NEW HIGH SCORE : " + to_string(highScore);
		drawText(*screen, hsTxt, screen->width / 2 - hsTxt.length() / 2, 3);
	}
	string gameoverText = "- GAME OVER -";
	string restartText = "press <R> to restart";
	drawText(*screen, gameoverText, screen->width / 2 - gameoverText.length()/2, 5);
	drawText(*screen, restartText, screen->width / 2 - restartText.length()/2, 6);
}

void GameScene::restart()
{
	snake.setSize(4);
	snake.isDead = false;
	score = 0;
	clearScreen(*screen);
}
