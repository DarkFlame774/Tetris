#include <iostream>
#include "Board.h"
#include <chrono>
#include <thread>
#include "Windows.h"

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
int y = BOARD_WIDTH-3;
int x;
int kind;
int Rot = 1;
void initialPiece() {
	x = 1;
	y = rand() % (BOARD_WIDTH-3 - 2 + 1) + 2;
	kind = rand() % 7;
	Rot = 0;
	piece = new Piece();
	board->piece = piece;
	piece->CalculatePiecePositions(kind,Rot,x, y);
	
}

bool checkColl(Piece* piece,int Rot,int x, int y) {
	piece->CalculatePiecePositions(kind,Rot,x, y);
	for (int i = 0; i < piece->totalPos; i++) {
		if (!board->isFree(piece->piecePositions[i][0], piece->piecePositions[i][1])) return true;
	}
	return false;
}


void input() {
	int newX = x, newY = y, newRot = Rot;
	if (GetAsyncKeyState('W')) {
		newRot = (newRot + 1) % ROTATIONS;
	}
	if (GetAsyncKeyState('A') || (GetAsyncKeyState(VK_LEFT) & 0x8000)) {
		newY--;
	}
	if (GetAsyncKeyState('D')|| (GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
		newY++;
	}
	if (GetAsyncKeyState('S') || (GetAsyncKeyState(VK_DOWN) & 0x8000)) {
		newX++;
	}
	if (!checkColl(piece, newRot, newX, newY)) { x = newX; y = newY; Rot = newRot; }
}

void isGameOver() {
	if (board->checkForUpFill()) 
		isrunning = false;
}



void update() {
	x++;
	piece->CalculatePiecePositions(kind,Rot,x, y);
	if (checkColl(piece,Rot,x,y)) {
		x--;
		board->DrawPiece(kind,Rot,x, y);
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
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::cout << "Game Over!! Thanks for Playing.";
	std::cin.get();
}





