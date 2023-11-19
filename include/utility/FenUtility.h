#ifndef FENUTILITY_H
#define FENUTILITY_H

#include <board/board.h>
#include <string>

class FenUtility {
public:
	FenUtility() = default;
	~FenUtility() = default;

	static std::string GetFen(Board board);
	static void LoadPositionFromFen(std::string fen);
private:


};

#endif