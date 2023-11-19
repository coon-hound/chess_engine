#include "board/board.h"

Board& Board::GetInstance() {
	static Board instance;
	return instance;
}

int* Board::GetSquare() {
	return square;
}