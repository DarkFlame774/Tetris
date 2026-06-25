#pragma once
#include "Pieces.h"

#define BOARD_WIDTH 23 // Total width of Board
#define BOARD_HEIGHT 22 // Total Height of Board

class Board {
public:
	Piece* piece;
	bool isFilled(int x, int y);
	bool isBorder(int x, int y);
	bool isFree(int x, int y);
	void DrawPiece(int kind,int Rot, int x,int y);
	void initBoard();
	void DestroyPossibleLine();
	void ShiftExistingPieces();
	bool checkForUpFill();
	enum { NETHER, BORDER, FREE, FILLED };
	int mBoard[BOARD_HEIGHT][BOARD_WIDTH];
	bool destroy;

private:
	int destroyLine;
	int GetPossibleDestroyableLine();
};
