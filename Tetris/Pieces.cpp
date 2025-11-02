#include "Pieces.h"

void Piece::SetPiecePositions(int kind) {
	SetPivot(kind);
	int count = 0;
	for (int i = 0; i < PIECE_HIGHT; i++) {
		for (int j = 0; j < PIECE_WIDTH; j++) {
			if (mPiece[kind][i][j] == 1 || mPiece[kind][i][j] == 2) {
				piecePositions[count][0] = i - mPiecePivot[kind][0];
				piecePositions[count][1] = j - mPiecePivot[kind][1];
				count++;
			}
		}
	}
	totalPos = count;
}

void Piece::SetPivot(int kind) {
	for (int i = 0; i < PIECE_SIZE; i++) {
		piecePositions[i][0] = mPiecePivot[kind][0];
		piecePositions[i][1] = mPiecePivot[kind][1];
	}
}

void Piece::CalculatePiecePositions(int kind, int x, int y) {
	SetPiecePositions(kind);
	for (int i = 0; i < PIECE_SIZE; i++) {
		piecePositions[i][0] += x;
		piecePositions[i][1] += y;
	}
}

bool Piece::isPiecePosition(int i, int j) {
	for (int k = 0; k < totalPos; k++) {
		if (piecePositions[k][0] == i && piecePositions[k][1] == j) return true;
	}
	return false;
}