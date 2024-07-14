#pragma once
#include "helper.h"

struct Player {
	Vector pos;
	Vector dir;
	char c;
	Vector speed;
	Player() :Player(0, 0, 0, 0, '@', 2, 1) {};
	Player(int px, int py) : Player(px, py, 0, 0, '@', 2,1) {};
	Player(int px, int py, int dirX, int dirY, char _c, int sx, int sy) : pos{ px,py },
		dir{ dirX,dirY },
		speed {sx,sy},
		c{ _c } {};
};
