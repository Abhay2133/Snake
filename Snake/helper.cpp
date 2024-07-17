#include <functional>
#include "helper.h"
#include<iostream>
#include <iostream>
#include <chrono>
#include <thread>
#include <consoleapi2.h>
#include <WinBase.h>
#include<queue>
#include<mutex>

using namespace std;

// Function to sleep for a specified duration in milliseconds
void _sleep_(int milliseconds) {
	if (milliseconds <= 0) {
		std::cerr << "Error: Invalid sleep duration. Please provide a positive value." << std::endl;
		return;
	}

	// Create a chrono::milliseconds object for accurate timing
	std::chrono::milliseconds duration(milliseconds);

	// Suspend the current thread for the specified duration
	std::this_thread::sleep_for(duration);
}

void clrscr() {
	printf("\x1b[2J");
}

void home() {
	printf("\x1B[H");
}

void drawScreen(Screen& screen, int _sleep = 33) {
	home();
	for (int y = 0; y < screen.height; y++) {
		string line(screen.pixels[y].begin(), screen.pixels[y].end()); // Use range-based for constructor
		cout << line << endl;
		//putchar('\n');
	}
	_sleep_(_sleep);
}

void drawScreen(Screen& screen)
{
	drawScreen(screen, 33);
}

void createRect(Screen& screen, int x, int y, int width, int height, char c) {
	Pixels pixels = screen.pixels;

	// setting corners
	setPixel(screen, x, y, c ? c : '+');
	setPixel(screen, x + width + 1, y, c ? c : '+');
	setPixel(screen, x, y + height + 1, c ? c : '+');
	setPixel(screen, x + width + 1, y + height + 1, c ? c : '+');

	// setting vertical border
	for (int i = x + 1; i <= x + width; i++) {
		setPixel(screen, i, y, c ? c : '-');
		setPixel(screen, i, y + height + 1, c ? c : '-');
	}

	// setting horizontal border
	for (int i = y + 1; i <= y + height; i++) {
		setPixel(screen, x, i, c ? c : '|');
		setPixel(screen, x + width + 1, i, c ? c : '|');
	}

}

bool inRange(int n, int a, int z) {
	if (n < a) return false;
	if (n > z) return false;
	return true;
}

bool inScreen(int x, int y, int width, int height) {
	return inRange(x, 0, width - 1) && inRange(y, 0, height - 1);
}

void setPixel(Screen& screen, int x, int y, int c) {
	if (inScreen(x, y, screen.width, screen.height)) screen.pixels[y][x] = c;
}


COORD getScreenSize() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) {
		std::cerr << "Error getting console screen buffer information" << std::endl;
		COORD c = { -1,-1 };
		return c;
	}

	return info.dwSize;
}

void _captureKeyboard(Queue<char>& keysQueue, bool& Continue) {
	HANDLE hIn;
	HANDLE hOut;
	INPUT_RECORD InRec;
	DWORD NumRead;

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	while (Continue) {
		ReadConsoleInput(hIn, &InRec, 1, &NumRead);
		if (InRec.EventType != KEY_EVENT) continue;
		if (!InRec.Event.KeyEvent.bKeyDown) continue;
		char keyChar = InRec.Event.KeyEvent.uChar.AsciiChar;
		// string message = "";
		// message += keyChar;
		// flog(message + "\n");
		keysQueue.push(keyChar);
	}
}

int randint(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void drawText(Screen& screen, string text, int x, int y)
{
	for (int i = 0; i < text.size(); i++)
	{
		setPixel(screen, x + i, y, text[i]);
	}
}

void flog(const std::string& message) {
	std::ofstream log_file("log.txt", std::ios_base::out | std::ios_base::app);
	if (log_file.is_open()) {
		log_file << message;
		log_file.close();
	}
	else {
		std::cerr << "Error opening log file!" << std::endl;
	}
}

void startKeyboardCapture(Queue<char>& keysQueue, bool& Continue) {
	std::thread* eventThread = new std::thread([&keysQueue, &Continue] {
		_captureKeyboard(keysQueue, Continue);
		});
	//eventThread->detach();
}

int clamp(int num, int min, int max) {
	if (num < min) return min;
	if (num > max) return max;
	return num;
}

void movePixel(Screen& screen, char c, Vec2D& pos, const function<void(void)>& posUpdater)
{
	movePixel(screen, ' ', c, pos, posUpdater);
}

void movePixel(Screen& screen, char bg, char c, Vec2D& pos, const function<void(void)>& posUpdater)
{
	setPixel(screen, pos.x, pos.y, bg);
	posUpdater();
	setPixel(screen, pos.x, pos.y, c);
}