#include <iostream>
#include "Board.h"

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
void Board::DrawPiece(int x, int y) {
	mBoard[x][y] = FILLED;
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
void Board::BoardInitial(int i,int x,int y) {
	for (int j = 0; j < BOARD_WIDTH; j++) {
		if (mBoard[i][j] == BORDER) {
			std::cout << "*";
		}
		else if (mBoard[i][j] == FILLED) {
			std::cout << "#";
		}
		else
			if (j == y && i == x) std::cout << "#";
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
		SideGap();
		std::cout << std::endl;
	}
	UpperGap();
}

//Destroy the line 





