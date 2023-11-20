#ifndef BOARD_H
#define BOARD_H

#include <cstdint>

// keeps track of all the positions of all the pieces on the board. 
class Board {
public:
    static Board& GetInstance();

	void Move(int startingIndice, int destinationIndice);

	int* GetSquare();

	Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
private:
	Board() = default;  // Private constructor
	~Board() = default;  // Private destructor

	int square[64];

};

#endif