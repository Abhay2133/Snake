#pragma once
#include "core.h"
#include <fstream>
#include<iostream>
class GameScene : public Scene
{
public:
	GameScene(Screen* screen, Queue<char>* keysQueue, bool* isRunning, bool isActive);
	void update () override;
	void init();

private:
	Snake snake;
	Fruit fruit;
	int score = 0;
	int _sleepMs = 100;
	int highScore = 0;
	std::ofstream highScoreFileHandle;

	// Inherited via Scene
	void handleInput() override;
	void updateEntities() override;
	void renderScreen() override;
	void handleCollisions();
	void saveHS();
	void loadHS();
	void gameover();
	void restart();
};

