#include "GameScreen.h"
#include <string>
int tetris_x = 1;
int tetris_y = 42;
std::string tetris_str = "!!TERMINAL TETRIS!!";

int left_text_pad = 5;

int name_x = 3;
std::string name_str = "Player_1";

int score_x = 4;
std::string score_str = "";

int line_x = 5;
std::string line_str = "";

int ruleBox_start_x = 10;
int ruleBox_start_y = 7;
int ruleBox_length = 8;
int ruleBox_width = 25;

int ruleBox_ruleText_x = ruleBox_start_x + 1;
int ruleBox_ruleText_y = ruleBox_start_y + 7;
std::string ruleBox_RuleText_str = "!!Controls!!";

int ruleBox_controlPad = ruleBox_start_y + 3;

int ruleBox_controlLeft_x = ruleBox_ruleText_x + 2;
std::string ruleBox_controlLeft_str = "A - Move Left";

int ruleBox_controlRight_x = ruleBox_ruleText_x + 3;
std::string ruleBox_controlRight_str = "D - Move Right";

int ruleBox_controlDown_x = ruleBox_ruleText_x + 4;
std::string ruleBox_controlDown_str = "S - Decend Faster";

int ruleBox_controlRotate_x = ruleBox_ruleText_x + 5;
std::string ruleBox_controlRotate_str = "Space - Rotate Piece";

void GameScreen::initScreen() {
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			if (j == 0
			 || j == SCREEN_WIDTH-1
			 || i == 0
			 || i == SCREEN_HEIGHT -1
			 || i == 2
			){
				mScreen[i][j] = BORDER;
			}
			 else if ((i == ruleBox_start_x  ||  i == ruleBox_start_x + ruleBox_length)
			        && (j >= ruleBox_start_y && j <= ruleBox_start_y + ruleBox_width)
					|| (j == ruleBox_start_y || j == ruleBox_start_y + ruleBox_width)
					&& (i >= ruleBox_start_x && i < ruleBox_start_x + ruleBox_length)) {
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
			else if (i == tetris_x && j == tetris_y){
				std::cout << tetris_str;
				j += tetris_str.size()-1;
			}
			else if (i == name_x && j == left_text_pad) {
				std::cout << name_str;
				j += name_str.size()-1;
			}
			else if (i == score_x && j == left_text_pad) {
				std::cout << score_str;
				j += score_str.size()-1;
			}
			else if (i == line_x && j == left_text_pad) {
				std::cout << line_str;
				j += line_str.size()-1;
			}
			// !!CONTROL!! text
			else if (i == ruleBox_ruleText_x && j == ruleBox_ruleText_y) {
				std::cout << ruleBox_RuleText_str;
				j += ruleBox_RuleText_str.size()-1;
			}
			//Control UI
			else if (i == ruleBox_controlLeft_x && j == ruleBox_controlPad) {
				std::cout << ruleBox_controlLeft_str;
				j += ruleBox_controlLeft_str.size()-1;
			}
			else if (i == ruleBox_controlRight_x && j == ruleBox_controlPad) {
				std::cout << ruleBox_controlRight_str;
				j += ruleBox_controlRight_str.size()-1;
			}
			else if (i == ruleBox_controlDown_x && j == ruleBox_controlPad) {
				std::cout << ruleBox_controlDown_str;
				j += ruleBox_controlDown_str.size()-1;
			}
			else if (i == ruleBox_controlRotate_x && j == ruleBox_controlPad) {
				std::cout << ruleBox_controlRotate_str;
				j += ruleBox_controlRotate_str.size()-1;
			}
			else if (mScreen[i][j] == FILLED || CheckForPiece(board, i, j)) std::cout << "#";
			else if (mScreen[i][j] == FREE) {
				std::cout << " ";
			}
			else {
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

void GameScreen::projectStats(int score, int lines) {
	if (score == 0) {
		score_str = "Score - 00";
	}
	else {
		score_str = "Score - " + std::to_string(score);
	}

	if (lines == 0) {
		line_str = "Lines Cleared - 00";
	}
	else {
		line_str = "Lines Cleared - " + std::to_string(lines);
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
	std::cout << "\033[J\033[H";
}