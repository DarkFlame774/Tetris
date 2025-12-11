#include <iostream>
#include "Board.h"
#include "Windows.h"

Board::Board() {
	BoardSizeCal();
}

void Board::BoardSizeCal() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	TSCREEN_WIDTH = csbi.srWindow.Right - csbi.srWindow.Left;
	TSCREEN_HEIGHT = csbi.srWindow.Bottom - csbi.srWindow.Top;
}

//Initialize the Board cells with appropriate values;BORDER,FREE,FILLED
void Board::initBoard() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			mBoard[i][j] = FREE;
			mBoard[0][j] = BORDER;//upper
			mBoard[i][BOARD_WIDTH - 1] = BORDER; //right
			mBoard[i][0] = BORDER; //left
			mBoard[BOARD_HEIGHT - 1][j] = BORDER; //lower
		}
	}
}

//check satte of cell
bool Board::isFilled(int x, int y) {
	if (mBoard[x][y] == FILLED) return true;
	return false;
}
bool Board::isBorder(int x, int y) {
	if (mBoard[x][y] == BORDER) return true;
	return false;
}
bool Board::isFree(int x, int y) {
	if (mBoard[x][y] == FREE) return true;
	return false;
}

//make the cell filled with piece
void Board::DrawPiece(int kind,int Rot, int x, int y) {
	piece->CalculatePiecePositions(kind,Rot,x, y);
	for(int i = 0; i < piece->totalPos; i++) mBoard[piece->piecePositions[i][0]][piece->piecePositions[i][1]] = FILLED;

}


void Board::UpperGap() {
	for (int i = 0; i < UPPER_GAP; i++) {
		std::cout << std::endl;
	}
}

//responisible for drawing Board
void Board::SideGap()
{
	for (int j = 0; j < SIDE_GAP; j++) {
		std::cout << " ";
	}
}
void Board::SideGapWithScore(int i)
{
	for (int j = 0; j < SIDE_GAP; j++) {
		if (j == 3 && i == BOARD_HEIGHT/2) {
			if (score / 10 == 0) std::cout << "00" << score;
			else if (score / 10 > 0) std::cout << "0" << score;
			else std::cout << score;
			j += 3;
		}
		else 
			std::cout << " ";
	}
}
void Board::BoardInitial(int i,int x,int y) {
	for (int j = 0; j < BOARD_WIDTH; j++) {
		if (mBoard[i][j] == BORDER) {
			std::cout << "*";
		}
		else if (mBoard[i][j] == FILLED) {
			std::cout << "#";
		}
		else
			if (piece->isPiecePosition(i,j)) std::cout << "#";
			else std::cout << " ";
	}
}

//Draws the board
void Board::Drawboard(int x, int y)
{
	UpperGap();
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		SideGap();
		BoardInitial(i,x,y);
		SideGapWithScore(i);
		std::cout << std::endl;
	}
	UpperGap();
}


int Board::GetPossibleDestroyableLine() {
	for (int i = 1; i < BOARD_HEIGHT-1; i++) {
		bool destroy = false;
		for (int j = 1; j < BOARD_WIDTH-1; j++) {
			destroy = false;
			if (!isFilled(i, j)) break; 
			destroy = true;
		}
		if (destroy) return i;
	}

	return -1;
}

//Destroy the line 
void Board::DestroyPossibleLine() {
	destroyLine = GetPossibleDestroyableLine();
	if (destroyLine < 0) return;
	for (int j = 1; j < BOARD_WIDTH-1; j++) {
		mBoard[destroyLine][j] = FREE;
	}
	score++;
}

void Board::ShiftExistingPieces() {
	if (destroyLine < 0) return;
	for (int i = destroyLine; i > 0; i--) {
		for (int j = 1; j < BOARD_WIDTH-1; j++) {
			if (i == 1) {
				mBoard[i][j] = FREE;
				continue;
			}
			mBoard[i][j] = mBoard[i - 1][j];
		}
	}
}

bool Board::checkForUpFill() {
	for (int j = 1; j < BOARD_WIDTH - 1; j++) {
		if (mBoard[1][j] == FILLED) return true;
	}
	return false;
}





