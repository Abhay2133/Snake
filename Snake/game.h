#pragma once
#include "helper.h"
#include "entities.h"

class Game {
public:
	Game();
	Game(int width, int height, char bg);
	~Game();
	void start();

private:
	char bg;
	Queue<char> keysQueue;
	bool isRunning;
	Screen screen;
	Player player;
	int _sleepMs=33;

private:
	void handleInput();
	void renderScreen();
	void updateEntities();
};