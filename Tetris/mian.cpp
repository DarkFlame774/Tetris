#include <iostream>
#include "Board.h"
#include <chrono>
#include <thread>
#include "Windows.h"
#include "Pieces.h"

void hideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

Board *board;
Piece* piece;

bool isrunning = true;
int y;
int x;
int kind;
void initialPiece() {
	x = 1;
	y = rand() % (12 - 2 + 1) + 2;
	kind = rand() % 3;
	piece = new Piece();
	board->piece = piece;
	piece->CalculatePiecePositions(kind,x, y);
	
}

bool checkColl(Piece* piece,int x, int y) {
	piece->CalculatePiecePositions(kind,x, y);
	for (int i = 0; i < piece->totalPos; i++) {
		if (!board->isFree(piece->piecePositions[i][0], piece->piecePositions[i][1])) return true;
	}
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
	if (!checkColl(piece,newX, newY)) {x = newX; y = newY;}
}

void isGameOver() {
	if (board->checkForUpFill()) 
		isrunning = false;
}



void update() {
	x++;
	piece->CalculatePiecePositions(kind,x, y);
	if (checkColl(piece,x,y)) {
		x--;
		board->DrawPiece(kind,x, y);
		initialPiece();
	}
	isGameOver();

}
void render() {
	hideCursor();
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





