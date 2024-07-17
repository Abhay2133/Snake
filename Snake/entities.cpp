#include"helper.h"
#include "entities.h"

using namespace std;
void Unit::move()
{
	pos.x += speed.x * dir.x;
	pos.y += speed.x * dir.y;
}

void Unit::moveBy(DIR _dir, int step)
{
	switch (_dir) {
	case DIR::north:
		pos.y -= step; dir.x = 0; dir.y = -1; 
		//flog("north \n");
		break;
	case DIR::south:
		pos.y += step; dir.x = 0; dir.y = 1; 
		//flog("south \n");
		break;
	case DIR::east:
		pos.x += step; dir.y = 0; dir.x = 1; 
		//flog("east \n");
		break;
	case DIR::west:
		pos.x -= step; dir.y = 0; dir.x = -1; 
		//flog("west \n");
		break;
	}
}

void Unit::moveTo(Unit* unit, bool copyDir)
{
	//dir.x = _pos.x - pos.x;
	pos.x = unit->pos.x;
	pos.y = unit->pos.y;
	if (copyDir)
	{
		dir.x = unit->dir.x;
		dir.y = unit->dir.y;
	}
}

Snake::Snake() :Snake(10, 10, '#') {}
Snake::Snake(int px, int py) : Snake(px, py, '#') {}
Snake::Snake(int px, int py, char sbody) : Snake(px, py, sbody, 'O') {}
Snake::Snake(int px, int py, char sbody, char head) : 
	body(1, new Unit(px, py, 1, 0, head, 1, 1)) ,
	bodySprite{sbody},
	headSprite{head}
{
	setSize(4);
}	

Snake::~Snake() {}

void Snake::onEat()
{
	setSize(body.size() + 1);
}

void Snake::move()
{
	if (body.size() < 1) throw ERROR("Snake body size is less than 1");
	for (auto part : body)
	{
		part->move();
	}
}

Vec2D Snake::getNewPos(Unit* tail) {
	return { tail->pos.x - tail->dir.x, tail->pos.y - tail->dir.y };
}

Unit* Snake::createNewPart(Unit* tail, char c, Vec2D& speed)
{
	Vec2D pos = getNewPos(tail);
	return new Unit(pos.x, pos.y, tail->pos.x - pos.x, tail->pos.y - pos.y, c, speed.x, speed.y);
}

void Snake::handleInput(char input)
{
	switch (input)
	{
	case 'w':
		moves.push(DIR::north);
		break;
	case 'a':
		moves.push(DIR::west);
		break;
	case 's':
		moves.push(DIR::south);
		break;
	case 'd':
		moves.push(DIR::east);
		break;
	}
}

void Snake::setSize(int size)
{
	if (body.size() < 1 || size < 1 || size == body.size()) return;
	if (size > body.size())
	{
		for (int i = body.size(); i < size; i++)
		{
			Unit* newPart = createNewPart(body.back(), bodySprite, speed);
			body.push_back(newPart);
		}
	}
	else {
		for (int i = body.size(); i > size; i--)
		{
			body.pop_back();
			body.back()->removed = true;
		}
	}
}

void Snake::update(Screen& screen)
{
	// updating body positions
	setPixel(screen, body.back()->pos.x, body.back()->pos.y, ' ');
	for (int i = body.size() - 1; i > 0; i--)
	{
		body.at(i)->moveTo(body.at(i - 1), true);
	}

	// updating head position
	auto head = body.front();
	setPixel(screen, head->pos.x, head->pos.y, bodySprite);
	if (moves.isEmpty())
	{
		head->move();
		setPixel(screen, head->pos.x, head->pos.y, head->c);
		return;
	}
	if (moves.size() > 1)	
	{
		int a = 0;
	}
	auto _dir = moves.pop();//front(); moves.pop();
	head->moveBy(_dir, 1);
	setPixel(screen, head->pos.x, head->pos.y, head->c);
}

Fruit::Fruit():Fruit('F'){}
Fruit::Fruit(char _sprite) : sprite{_sprite}
{
	
}

void Fruit::update(Screen& screen)
{
	if (isEaten) return respawn(screen);
	setPixel(screen, pos.x, pos.y, sprite);
}

void Fruit::respawn(Screen& screen)
{
	Vec2D _pos = getRespawnPos(screen);
	pos.set(_pos.x, _pos.y);
	setPixel(screen, pos.x, pos.y, sprite);
}

Vec2D Fruit::getRespawnPos(Screen& screen)
{
	int x = randint(1, screen.width - 3);
	int y = randint(1, screen.height - 3);
	while (screen.pixels[y][x] != ' ') {
		x = randint(1, screen.width - 3);
		y = randint(1, screen.height - 3);
	}
	return Vec2D(x,y);
}


