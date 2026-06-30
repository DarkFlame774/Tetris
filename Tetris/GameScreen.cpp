#include "GameScreen.h"
#include <string>


int tetris_x = 1;
int tetris_y = 42;
std::string tetris_str = "!!TERMINAL TETRIS!!";

int left_text_pad = 7;
int ui_start_x = 3;

int name_x = ui_start_x + 1;
std::string name_str = "Player_1";
std::string playerName = name_str;

int score_x = ui_start_x + 3;
std::string score_str = "";

int line_x = ui_start_x + 4;
std::string line_str = "";

int ruleBox_start_x = 10;
int ruleBox_start_y = 7;
int ruleBox_length = 8;
int ruleBox_width = 26;

int ruleBox_ruleText_x = ruleBox_start_x + 1;
int ruleBox_ruleText_y = ruleBox_start_y + 7;
std::string ruleBox_RuleText_str = "!!Controls!!";

int ruleBox_controlPad = ruleBox_start_y + 3;

int ruleBox_controlLeft_x = ruleBox_ruleText_x + 2;
std::string ruleBox_controlLeft_str = "A / -> - Move Left";

int ruleBox_controlRight_x = ruleBox_ruleText_x + 3;
std::string ruleBox_controlRight_str = "D / -> - Move Right";

int ruleBox_controlDown_x = ruleBox_ruleText_x + 4;
std::string ruleBox_controlDown_str = "S / v  - Decend Faster";

int ruleBox_controlRotate_x = ruleBox_ruleText_x + 5;
std::string ruleBox_controlRotate_str = "Space  - Rotate Piece";

int pieceBox_start_x = PIECE_PADDING_UP - 2;
int pieceBox_start_y = PIECE_PADDING_SIDE - 3;
int pieceBox_length = 6;
int pieceBox_width = 9;

int nextPiece_start_x = pieceBox_start_x + pieceBox_length+1;
int nextPiece_start_y = pieceBox_start_y - 2;
std::string nextPiece_str = "!!Next Piece!!";

int leaderboard_start_x = 2;
int leaderboard_width = 22;
int leaderboard_start_y = SCREEN_WIDTH-leaderboard_width-1;
int leaderboard_length = 7;

int leaderboard_str_start_x = leaderboard_start_x + 2;
int leaderboard_str_start_y = leaderboard_start_y + 1;
int leaderboard_strs_size = 5;
std::string leaderboard_strs[5] = {" ",
								   " ",
								   " ",
								   "---------------------",
								   " "
								   };

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
			 else if ( (i == pieceBox_start_x || i == pieceBox_start_x + pieceBox_length)
			        && (j >= pieceBox_start_y && j <= pieceBox_start_y + pieceBox_width)
					|| (j == pieceBox_start_y || j == pieceBox_start_y + pieceBox_width)
					&& (i >= pieceBox_start_x && i < pieceBox_start_x + pieceBox_length)) {
				mScreen[i][j] = BORDER;
			}
			 else if ( (i == leaderboard_start_x || i == leaderboard_start_x + leaderboard_length)
			        && (j >= leaderboard_start_y && j <= leaderboard_start_y + leaderboard_width)
					|| (j == leaderboard_start_y || j == leaderboard_start_y + leaderboard_width)
					&& (i >= leaderboard_start_x && i < leaderboard_start_x + leaderboard_length)) {
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
				std::cout << playerName;
				j += playerName.size()-1;
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
			else if (i == nextPiece_start_x && j == nextPiece_start_y) {
				std::cout << nextPiece_str;
				j += nextPiece_str.size()-1;
			}
			else if ((i >= leaderboard_str_start_x && i <= leaderboard_str_start_x + leaderboard_strs_size-1) && j == leaderboard_str_start_y) {
				std::cout << leaderboard_strs[i-leaderboard_str_start_x];
				j += leaderboard_strs[i - leaderboard_str_start_x].size()-1;
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
		score_str = "Score     - 00";
	}
	else {
		score_str = "Score     - " + std::to_string(score);
	}

	if (lines == 0) {
		line_str = "Lines Clr - 00";
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

void GameScreen::projectNextPiece(Piece* piece, int kind, int rot) {
	for (int i = 0; i < PIECE_HIGHT; i++) {
		for (int j = 0; j < PIECE_WIDTH; j++) {
			mScreen[PIECE_PADDING_UP + i][PIECE_PADDING_SIDE + j] = piece->mPiece[kind][rot][i][j] + 2;
			if (i == piece->GetPiecePivotX(kind) && j == piece->GetPiecePivotY(kind)) 
				mScreen[PIECE_PADDING_UP + i][PIECE_PADDING_SIDE + j] -= 1;
		}
	}
}

void GameScreen::PopulateDashboard(APIManager& apiManager,json id) {
	json leaderboardData = apiManager.GetDashboard(id);
	auto top_players = leaderboardData["topPlayers"];
	int i = 0;
	for (const auto& player : top_players) {
		int rank = player["rank"];
		std::string name = player["name"];
		int score = player["bestScore"];
		leaderboard_strs[i] = " " + std::to_string(rank) + " " + name + " - " + std::to_string(score);
		i++;
	}
	auto me = leaderboardData["currentPlayer"];
	int rank = me["rank"];
	std::string name = me["name"];
	int score = me["bestScore"];
	leaderboard_strs[4] = " " + std::to_string(rank) + " " + name + " - " + std::to_string(score);
}