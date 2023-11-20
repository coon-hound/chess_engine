#include "utility/FenUtility.h"
#include "board/piece.h"
#include <map>
#include <sstream>
#include <vector>
#include <iostream>

std::vector<std::string> static split(const std::string& s) {
    std::vector<std::string> tokens;
    std::istringstream iss(s);
    std::string temp;

    while (std::getline(iss, temp, ' ')) {
        tokens.push_back(temp);
    }

    return tokens;
}

std::string FenUtility::GetFen(Board board) {
	int* square = board.GetSquare();
	std::string ret;

	int	nEmptySquares = 0;
	for (int i = 0; i < 64; i++) {
		char fenChar;
		if (square[i] == Piece::None) {
			nEmptySquares += 1;
		}
	}

	return ret;
}

void FenUtility::LoadPositionFromFen(std::string fen) {
	Board &board = board.GetInstance();
	int* square = board.GetSquare();

	std::map<char, int> charToPiece {{'p', Piece::Pawn}, {'n', Piece::Knight}, {'b', Piece::Bishop}, {'r', Piece::Rook}, {'q', Piece::Queen}, {'k', Piece::King}};

	auto splitFen = split(fen);

	std::cout << splitFen[0] << "\n";

	int file = 0;
	int rank = 0;

	for (char c : splitFen[0]) {
		if (c == '/') {
			file = 0;	
			rank++;
			continue;
		}
		if (isdigit(c)) {
			file += c - '0';
			printf("file = %d, c = %d\n", file, c - '0');
			continue;
		}

		if (isupper(c)) {
			square[rank * 8 + file] = charToPiece[tolower(c)] | Piece::White;
		}
		else if (islower(c)) {
			square[rank * 8 + file] = charToPiece[c] | Piece::Black;
		} 

		file ++;
	}
	
	for(int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%d ", square[i * 8 + j]);
		}
		printf("\n");
	}
}