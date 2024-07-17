#pragma once
#include <ctime>
#include <cstdlib>
#include<string>
#include<vector>
#include<stdlib.h>
#include<Windows.h>
#include<queue>
#include<mutex>
#include <functional>
#include<fstream>
#include<iostream>

using namespace std;
typedef vector<vector<char>> Pixels;


void _sleep_(int milliseconds);

void clrscr();
void home();

struct Screen {
	int height;
	int width;
	Pixels pixels;
	Screen() :Screen(0, 0, ' ') {};
	Screen(int w, int h) :Screen(w, h, ' ') {};
	Screen(int w, int h, char bg) : height{ h }, width{ w }, pixels(h, std::vector<char>(w, bg)) {};
};

void drawScreen(Screen& screen, int _sleep);
void drawScreen(Screen& screen);

void createRect(Screen& screen, int x, int y, int width, int height, char c = '\0');

bool inRange(int n, int a, int z);

bool inScreen(int x, int y, int width, int height);

void setPixel(Screen& screen, int x, int y, int c);

COORD getScreenSize();

struct Vec2D {
	int x;
	int y;
	Vec2D* set(int _x, int _y) { x = _x; y = _y; return (this); }
	Vec2D() :Vec2D(0, 0) {};
	Vec2D(int x, int y) : x{ x }, y{ y } {};
};

template<typename T>
class Queue {
public:
	// Add an element to the queue.
	void push(T item) {
		std::unique_lock<std::mutex> lock(mtx);
		q.push(item);
		cv.notify_one();
	}

	// Remove an element from the queue. If the queue is empty, wait until an element is available.
	T pop() {
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [this] { return !q.empty(); });
		T item = q.front();
		q.pop();
		return item;
	}

	// Get the number of elements in the queue.
	T front() {
		std::unique_lock<std::mutex> lock(mtx);
		return q.front();
	}


	// Get the number of elements in the queue.
	size_t size() {
		std::unique_lock<std::mutex> lock(mtx);
		return q.size();
	}

	// Check if the queue is empty.
	bool isEmpty() {
		std::unique_lock<std::mutex> lock(mtx);
		return q.empty();
	}

private:
	std::queue<T> q;
	std::mutex mtx;
	std::condition_variable cv;
};

void startKeyboardCapture(Queue<char>& keysQueue, bool& stop);

int clamp(int num, int min, int max);

void movePixel(Screen& screen, char c, Vec2D& pos, const std::function<void(void)>& posUpdater);
void movePixel(Screen& screen, char bg, char c, Vec2D& pos, const function<void(void)>& posUpdater);

void _captureKeyboard(Queue<char>& keysQueue, bool& Continue);


int randint(int min, int max);

void drawText(Screen& screen, string text, int x, int y);

void flog(const std::string& message);


