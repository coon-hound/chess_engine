#ifndef BOARD_H
#define BOARD_H

#include <cstdint>

// rethink turn naming 
#define WHITE_PIECE 1
#define BLACK_PIECE 0

// keeps track of all the positions of all the pieces on the board. 
class Board {
public:
    static Board& GetInstance();

	// returns 1 meaning legal, returning -1 illegal
	int Move(int startingIndice, int destinationIndice);

	int* GetSquare();

	Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
private:
	Board();
	~Board();

	int square[64];

	// white = true (1), black = false (0)
	bool playerTurn;

};

#endif