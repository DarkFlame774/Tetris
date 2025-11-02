#pragma once

#define PIECE_SIZE 9
#define PIECE_HIGHT 3
#define PIECE_WIDTH 3
#define PIECE_KIND 3

class Piece {
public:

	int totalPos = 0;

	int mPiece[PIECE_KIND][PIECE_HIGHT][PIECE_WIDTH] = 
	{
		{
			{0,1,0},
			{0,2,0},
			{0,1,0}
		},
		{
			{0,0,0},
			{1,2,0},
			{0,1,1}
		},
		{
			{0,1,0},
			{1,2,1},
			{0,0,0}
		}
	};

	int piecePositions[PIECE_SIZE][2];

	void CalculatePiecePositions(int kind, int x, int y);

	bool isPiecePosition(int i, int j);


private:
	int mPiecePivot[PIECE_KIND][2] =
	{
		{1,1},
		{1,1},
		{1,1}
	};
	void SetPiecePositions(int kind);
	void SetPivot(int kind);

};