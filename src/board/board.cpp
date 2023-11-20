#include "board/board.h"

Board& Board::GetInstance() {
	static Board instance;
	return instance;
}

void Board::Move(int startingIndice, int destinationIndice) {
	int pieceValue = square[startingIndice];
	square[startingIndice] = 0;
	square[destinationIndice] = pieceValue;

}

int* Board::GetSquare() {
	return square;
}
