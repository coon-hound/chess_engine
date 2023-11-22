#ifndef MOVE_H
#define MOVE_H

#include <vector>

class Move{
public: 
	Move() = default;
	~Move() = default;

	std::vector<int> GetPossibleMoves();

	int GetStartingIndice();
	int GetDestinationIndice();

private:
	int startingIndice;
	int destinationIndice;


};

#endif
