#pragma once
#include <iostream>
#include "Board.h"
#include <chrono>
#include <thread>
#define SCREEN_WIDTH 100 //Mostly deafult total width of default windowed terminal
#define SCREEN_HEIGHT 28 // Mostly deafult total height of default windowed terminal
#define BOARD_PADDING_UP 4
#define BOARD_PADDING_SIDE 40

class GameScreen {
	public:
		void initScreen();
		enum { NETHER, BORDER, FREE, FILLED };
		int mScreen[SCREEN_HEIGHT][SCREEN_WIDTH];
		void DrawScreen(Board* board);
		void projectBoard(Board* board);
		void projectStats(int score, int line);
		bool CheckForPiece(Board* board,int x, int y);
		void Flashing(Board* board);

	private:
		void Flash();
};
