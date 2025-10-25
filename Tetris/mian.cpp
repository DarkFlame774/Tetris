#include <iostream>
#include "Board.h"
#include <chrono>
#include <thread>
#include "Windows.h"

Board *board;

bool isrunning = true;
int y = 5;
int x = 1;
void initialPiece() {
	x = 1;
	y = rand() % (13 + 1 - 1) + 1;
}

bool checkColl(int x, int y) {
	if (!board->isFree(x,y)) return true;
	return false;
}


void input() {
	int newX = x, newY = y;
	if (GetAsyncKeyState('A') || (GetAsyncKeyState(VK_LEFT) & 0x8000)) {
		newY--;
	}
	if (GetAsyncKeyState('D')|| (GetAsyncKeyState(VK_RIGHT) & 0x8000)) {

		newY++;
	}
	//if (GetAsyncKeyState('S')) {
	//	if (!checkColl(x+1,y)) x++;
	//}
	if (!checkColl(newX, newY)) {x = newX; y = newY;}
}

void isGameOver() {
	if (board->checkForUpFill()) isrunning = false;
}



void update() {
	x++;
	if (checkColl(x,y)) {
		x--;
		board->DrawPiece(x, y);
		initialPiece();
	}
	isGameOver();

}
void render() {
	board->DestroyPossibleLine();
	board->Drawboard(x,y);
	board->ShiftExistingPieces();
}

void start() {
	board = new Board();
	board->initBoard();
	initialPiece();
	board->Drawboard(x, y);
}

int main() {
	start();
	while (isrunning) {
		std::cout << "\033[J\033[H";
		input();
		update();
		render();
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
	std::cout << "Game Over!! Thanks for Playing.";
	std::cin.get();
}





