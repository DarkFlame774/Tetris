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

//void DrawPieces() {
//	if(board->isFree(x, y)) board->DrawPiece(x,y);
//}


void input() {
	if (GetAsyncKeyState('A')) {
		if (!checkColl(x,y-1)) y--;
	}
	if (GetAsyncKeyState('D')) {

		if (!checkColl(x,y+1)) y++;
	}
	if (GetAsyncKeyState('S')) {
		if (!checkColl(x+1,y)) x++;
	}
}



void update() {
	x++;
	if (checkColl(x+1,y)) {
		board->DrawPiece(x, y);
		initialPiece();
	}
}
void render() {
	board->Drawboard(x,y);
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
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
}





