#pragma once

#include "helper.h"
#include "events.h"

enum class DIR {
	north = 1, south = 2, east = 4, west = 8
};

class Entity {
public:
	virtual void handleInput(char input) = 0;
	virtual void update(Screen& screen) = 0;
};

class Unit {
public:
	Vec2D pos;
	Vec2D dir;
	char c;
	Vec2D speed;
	bool removed = false;

	Unit() :Unit(0, 0, 0, 0, '@', 2, 1) {};
	Unit(int px, int py) : Unit(px, py, 0, 0, '@', 2, 1) {};
	Unit(int px, int py, int dirX, int dirY, char _c, int sx, int sy) : pos{ px,py },
		dir{ dirX,dirY },
		speed{ sx,sy },
		c{ _c } {};
	//	Unit(Unit* other);

	void move();
	void moveBy(DIR dir, int step);
	void moveTo(Unit* unit, bool copyDir = false);
};

class Snake : public Entity {
private:
	Queue<DIR> moves;
public:
	vector<Unit*> body;

	Snake();
	Snake(int px, int py);
	Snake(int px, int py, char sbody);
	Snake(int px, int py, char sbody, char head);
	~Snake();

	Vec2D speed = { 1,1 };
	char bodySprite;
	char headSprite;

	static Vec2D getNewPos(Unit* tail);
	static Unit* createNewPart(Unit* tail, char c, Vec2D& speed);

	void onEat();
	void move();
	void handleInput(char input);
	void setSize(int size);
	void update(Screen& screen);
};

class Fruit {
public:
	Vec2D pos;
	bool isEaten = false;
	char sprite;

	Fruit();
	Fruit(char _sprite);

	void update(Screen& screen);
	void respawn(Screen& screen);
	static Vec2D getRespawnPos(Screen& screen);
};