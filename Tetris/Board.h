#pragma once

#define BOARD_WIDTH 15 // Total width of Board
#define BOARD_HEIGHT 24
#define TSCREEN_WIDTH 130 //Total width of default windowed terminal
#define TSCREEN_HEIGHT 30 // Total height of default windowed terminal
#define SIDE_GAP (TSCREEN_WIDTH - BOARD_WIDTH) / 2
#define UPPER_GAP (TSCREEN_HEIGHT - BOARD_HEIGHT) / 2

class Board {
public:

	bool isFilled(int x, int y);
	bool isBorder(int x, int y);
	bool isFree(int x, int y);
	void DrawPiece(int x,int y);
	void Drawboard(int x, int y);
	void initBoard();

private:
	enum { BORDER, FREE, FILLED };
	int mBoard[BOARD_HEIGHT][BOARD_WIDTH];
	void SideGap();
	void UpperGap();
	void BoardInitial(int i,int x, int y);
	void DestroyPossibleLine();
};
