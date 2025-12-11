#pragma once
#include "Pieces.h"

#define BOARD_WIDTH 23 // Total width of Board
#define BOARD_HEIGHT 27
#define TSCREEN_WIDTH 130 //Total width of default windowed terminal
#define TSCREEN_HEIGHT 30 // Total height of default windowed terminal
#define SIDE_GAP (TSCREEN_WIDTH - BOARD_WIDTH) / 2
#define UPPER_GAP (TSCREEN_HEIGHT - BOARD_HEIGHT) / 2

class Board {
public:

	Piece* piece;
	int score = 0;
	bool isFilled(int x, int y);
	bool isBorder(int x, int y);
	bool isFree(int x, int y);
	void DrawPiece(int kind,int Rot, int x,int y);
	void Drawboard(int x, int y);
	void initBoard();
	void DestroyPossibleLine();
	void SideGapWithScore(int i);
	void ShiftExistingPieces();
	bool checkForUpFill();

private:
	enum { BORDER, FREE, FILLED };
	int mBoard[BOARD_HEIGHT][BOARD_WIDTH];
	void SideGap();
	void UpperGap();
	void BoardInitial(int i,int x, int y);
	int destroyLine;
	int GetPossibleDestroyableLine();

};
