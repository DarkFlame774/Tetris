#pragma once

#define PIECE_SIZE 4
#define PIECE_HIGHT 4
#define PIECE_WIDTH 4
#define PIECE_KIND 7
#define ROTATIONS 4

class Piece {
public:

	int totalPos = 0;

	int mPiece[PIECE_KIND][ROTATIONS][PIECE_HIGHT][PIECE_WIDTH] = 
	{
		//  I Shaped
		{
			// Rot 1
			{
				{0,1,0},
				{0,2,0},
				{0,1,0}
			},
		    // Rot 2
			{
				{0,0,0},
				{1,2,1},
				{0,0,0}
			},
			// Rot 3
			{
				{0,1,0},
				{0,2,0},
				{0,1,0}
			},
			// Rot 4
			{
				{0,0,0},
				{1,2,1},
				{0,0,0}
			}
		},

		// Z shaped
		{
			// Rot 1
			{
				{0,0,0},
				{1,2,0},
				{0,1,1}
			},
			// Rot 2
			{
				{0,0,1},
				{0,2,1},
				{0,1,0}
			},
		    // Rot 3
			{
				{1,1,0},
				{0,2,1},
				{0,0,0}
			},
			// Rot 4	
			{
				{0,1,0},
				{1,2,0},
				{1,0,0}
			}
		},

		// S shaped
		{
			// Rot 1
			{
				{0,0,0},
				{0,2,1},
				{1,1,0}
			},
			// Rot 2
			{
				{1,0,0},
				{1,2,0},
				{0,1,0}
			},
			// Rot 3
			{
				{0,1,1},
				{1,2,0},
				{0,0,0}
			},
			// Rot 4
			{
				{0,1,0},
				{0,2,1},
				{0,0,1}
			}
		},
		// T shaped
		{
			// Rot 1
			{
				{0,0,0},
				{1,2,1},
				{0,1,0}
			},
			// Rot 2
			{
				{0,1,0},
				{0,2,1},
				{0,1,0}
			},
			// Rot 3
			{
				{0,1,0},
				{1,2,1},
				{0,0,0}
			},
			// Rot 4
			{
				{0,1,0},
				{1,2,0},
				{0,1,0}
			}
		},
		// L shaped
		{
			// Rot 1
			{
				{0,1,0},
				{0,2,0},
				{0,1,1}
			},
			// Rot 2
			{
				{0,0,1},
				{1,2,1},
				{0,0,0}
			},
			// Rot 3
			{
				{1,1,0},
				{0,2,0},
				{0,1,0}
			},
			// Rot 4
			{
				{0,0,0},
				{1,2,1},
				{1,0,0}
			}
		},
		// Inverted L shaped
		{
			// Rot 1
			{
				{0,1,0},
				{0,2,0},
				{1,1,0}
			},
			// Rot 2
			{
				{0,0,0},
				{1,2,1},
				{0,0,1}
			},
			// Rot 3
			{
				{0,1,1},
				{0,2,0},
				{0,1,0}
			},
			// Rot 4
			{
				{1,0,0},
				{1,2,1},
				{0,0,0}
			}
		},
		// Square shaped
		{
			// Rot 1
			{
				{0,0,0},
				{0,2,1},
				{0,1,1}
			},
			// Rot 2
			{
				{0,1,1},
				{0,2,1},
				{0,0,0}
			},
			// Rot 3
			{
				{1,1,0},
				{1,2,0},
				{0,0,0}
			},
			// Rot 4
			{
				{0,0,0},
				{1,2,0},
				{1,1,0}
			}
		},
	};

	int piecePositions[PIECE_SIZE][2];

	void CalculatePiecePositions(int kind,int Rot, int x, int y);

	bool isPiecePosition(int i, int j);


private:
	int mPiecePivot[PIECE_KIND][2] =
	{
		{1,1},
		{1,1},
		{1,1}
	};
	void SetPiecePositions(int kind,int Rot);
	void SetPivot(int kind);

};