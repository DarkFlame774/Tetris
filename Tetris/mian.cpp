#include <Windows.h>
#include "GameScreen.h"

int score = 0;
int linesDestroy = 0;

void static hideCursor() {
#ifdef WIN32
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
#else
	std::cout << "\033[?25l";

#endif
}

Board* board;
Piece* piece = new Piece();
GameScreen* screen;

bool isrunning = true;
int y = BOARD_WIDTH-3;
int x;
int kind = -1;
int nextKind;
int nextRot;
int Rot = -1;
void initialPiece() {
	x = 1;
	y = rand() % (BOARD_WIDTH - 3 - 2 + 1) + 2;
	if (kind = -1 && Rot == -1) {
		kind = rand() % 7;
		Rot = rand() % 4;
	}
	else {
		kind = nextKind;
		Rot = nextRot;
	}
	nextKind = rand() % 7;
	nextRot = rand() % 4;
	board->piece = piece;
	board->piece->CalculatePiecePositions(kind,Rot,x, y);
	
}

bool checkColl(Piece* piece,int Rot,int x, int y) {
	board->piece->CalculatePiecePositions(kind,Rot,x, y);
	for (int i = 0; i < board->piece->totalPos; i++) {
		if (!board->isFree(board->piece->piecePositions[i][0], board->piece->piecePositions[i][1])) return true;
	}
	return false;
}


void input() {
	int newX = x, newY = y, newRot = Rot;
	if (GetAsyncKeyState(VK_SPACE)) {
		newRot = (newRot + 1) % ROTATIONS;
	}
	if (GetAsyncKeyState('A') || (GetAsyncKeyState(VK_LEFT) & 0x8000)) {
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
			newY-=2;
	   }
		newY--;
	}
	if (GetAsyncKeyState('D')|| (GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
			newY += 2;
		}
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
	if (checkColl(piece,Rot,x,y)) {
		x--;
		board->DrawPiece(kind,Rot,x, y);
		initialPiece();
	}
	isGameOver();


}
void render() {
	hideCursor();
	bool flash = false;
	board->DestroyPossibleLine();
	if (board->destroy) {
		screen->projectBoard(board);
		screen->Flashing(board);
		flash = true;
		score += 10;
		linesDestroy++;
	}
	board->ShiftExistingPieces();
	screen->projectBoard(board);
	screen->projectStats(score,linesDestroy);
	screen->projectNextPiece(piece, nextKind, nextRot);
	screen->DrawScreen(board);

}

void start() {
	board = new Board();
	screen = new GameScreen();
	board->initBoard();
	initialPiece();
	screen->initScreen();
	screen->projectBoard(board);
	screen->projectStats(score, linesDestroy);
	screen->projectNextPiece(piece,nextKind, nextRot);
	screen->DrawScreen(board);
}

int Main() {
	SetConsoleOutputCP(CP_UTF8);
	start();
	while (isrunning) {
		std::cout << "\033[J\033[H";
		input();
		update();
		render();
		std::this_thread::sleep_for(std::chrono::milliseconds(120));
	}
	std::cout << "Game Over!! Thanks for Playing.";
	std::cin.get();
	return 0;
}





