#pragma once
#include "Pieces.h"

#define BOARD_WIDTH 23 // Total width of Board
#define BOARD_HEIGHT 25 // Total Height of Board
#define SIDE_GAP (TSCREEN_WIDTH - BOARD_WIDTH) / 2
#define UPPER_GAP (TSCREEN_HEIGHT - BOARD_HEIGHT) / 2

class Board {
public:
    Board();
	Piece* piece;
	int score = 0;
	int TSCREEN_WIDTH = 130; //Mostly deafult total width of default windowed terminal
	int TSCREEN_HEIGHT = 30; // Mostly deafult total height of default windowed terminal
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
    void BoardSizeCal();
	enum { BORDER, FREE, FILLED };
	int mBoard[BOARD_HEIGHT][BOARD_WIDTH];
	void SideGap();
	void UpperGap();
	void BoardInitial(int i,int x, int y);
	int destroyLine;
	int GetPossibleDestroyableLine();

};
