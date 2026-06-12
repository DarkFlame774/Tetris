#include "GameScreen.h"

void GameScreen::initScreen() {
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			if (j == 0
			 || j == SCREEN_WIDTH-1
			 || i == 0
			 || i == SCREEN_HEIGHT -1
			){
				mScreen[i][j] = BORDER;
			}
			else mScreen[i][j] = NETHER;
		}
	}
}

void GameScreen::DrawScreen(Board* board) {
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			if (mScreen[i][j] == BORDER) {
				std::cout << "*";
			}
			else if (mScreen[i][j] == FILLED || CheckForPiece(board, i, j)) std::cout << "#";
			else if (mScreen[i][j] == FREE || mScreen[i][j] == NETHER) {
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}
}

void GameScreen::projectBoard(Board* board) {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			mScreen[BOARD_PADDING_UP + i][BOARD_PADDING_SIDE + j] = board->mBoard[i][j];
		}
	}
}

bool GameScreen::CheckForPiece(Board* board, int x, int y) {
	if (x - BOARD_PADDING_UP >= 0 && x - BOARD_PADDING_UP < BOARD_HEIGHT && y - BOARD_PADDING_SIDE >= 0 && y - BOARD_PADDING_SIDE < BOARD_WIDTH) {
		return board->piece->isPiecePosition(x-BOARD_PADDING_UP,y-BOARD_PADDING_SIDE);
	}
	return false;
}

void GameScreen::Flash() {
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			if (i >= BOARD_PADDING_UP && i < BOARD_PADDING_UP + BOARD_HEIGHT
				&& j >= BOARD_PADDING_SIDE && j < BOARD_PADDING_SIDE + BOARD_WIDTH) {
				mScreen[i][j] = NETHER;
			}
		}

	}
}

void GameScreen::Flashing(Board* board)
{
	Flash();
	std::cout << "\033[J\033[H";
	DrawScreen(board);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	projectBoard(board);
	std::cout << "\033[J\033[H";
	DrawScreen(board);
	Flash();
	std::cout << "\033[J\033[H";
	DrawScreen(board);
	std::this_thread::sleep_for(std::chrono::milliseconds(70));
	projectBoard(board);
	std::cout << "\033[J\033[H";
	DrawScreen(board);

}