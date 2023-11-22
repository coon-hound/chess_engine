#include "board/board.h"
#include "utility/SDL2Wrapper.h"
#include <iostream>

Board::Board() {
	playerTurn = WHITE_PIECE;
}

Board::~Board() {
}

Board& Board::GetInstance() {
	static Board instance;
	return instance;
}

int Board::Move(int startingIndice, int destinationIndice) {
	// ericsson cuckbluck
	if (startingIndice == -1) {
		return -1;
	}
    SDL2Wrapper &wrapper = wrapper.GetInstance();

	int pieceValue = square[startingIndice];
	bool pieceColor;
	printf("starting indice = %d, destindice = %d\n", startingIndice, destinationIndice);

	// determine if its white or black	
	if (((pieceValue >> 3) & 1) == 0) {
		pieceColor = BLACK_PIECE;
	}
	else {
		pieceColor = WHITE_PIECE;
	}

	printf("piece color = %d\n", pieceColor);

	square[startingIndice] = 0;
	square[destinationIndice] = pieceValue;
	
	wrapper.PlaySound();

	return 'E';
}

int* Board::GetSquare() {
	return square;
}
