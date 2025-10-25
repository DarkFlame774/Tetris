#pragma once
#define PIECE_HEIGHT 5
#define PIECE_WIDTH 5
#define PIECE_KIND 3
int mPieces[PIECE_HEIGHT][PIECE_HEIGHT][PIECE_HEIGHT] =
{
	{
		{0,0,0,0,0},
		{0,2,1,1,0},
		{0,1,0,0,0},
		{0,1,0,0,0},
		{0,0,0,0,0}
	},
	{
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,2,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0}
	},
	{
		{0,0,0,0,0},
		{0,0,0,0,0},
		{1,1,2,1,1},
		{0,0,0,0,0},
		{0,0,0,0,0}
	},
};