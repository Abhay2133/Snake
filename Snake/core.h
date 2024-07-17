#pragma once
#include "helper.h"
#include "entities.h"
#include"EventEmitter.h"
#include<unordered_map>
#include<string>


class Scene : public EventEmitter
{
protected:
	Screen* screen;
	Queue<char>* keysQueue;
	bool* isRunning;
	bool isActive;

	virtual void handleInput()=0;
	virtual void updateEntities()=0;
	virtual void renderScreen()=0;

public:

	virtual void update() = 0;

	Scene(Screen* screen, Queue<char>* keysQueue, bool* isRunning, bool isActive)
		: screen(screen), keysQueue(keysQueue), isRunning(isRunning), isActive(isActive)
	{
	}
};

class Game
{
public:
	Game();
	Game(int width, int height);
	~Game();
	void start();

private:
	std::unordered_map <std::string, Scene*> scenes;
	Scene* activeScene = nullptr;
	Screen screen;
	Queue<char> keysQueue;
	bool isRunning=true;
};
