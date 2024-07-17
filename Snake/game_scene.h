#pragma once
#include "core.h"

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

	// Inherited via Scene
	void handleInput() override;
	void updateEntities() override;
	void renderScreen() override;
	void handleCollisions();
};