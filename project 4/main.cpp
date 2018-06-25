#include <string>
#include <utility>

#include "ex4_header.h"
#include "unit_test_util.h"

using std::string;
using std::get;

static bool test1() {
	GameBoard<12, 7, string, 4> board;
	int i = 0;
	for (int row = 0; row < 12; row++) {
		for (int col = 0; col < 7; col++) {
			board.setPiece(row, col, "Piece", i);
			i = (i + 1) % 4;
		}
	}
	int occurence[4] = { 0,0,0,0 };
	for (auto pieceInfo : board) {
		occurence[get<3>(pieceInfo)]++;
	}
	for (int i = 0;i < 4;i++) {
		if (occurence[i] != 21) {
			return false;
		}
	}
	return true;
}

//check iterator 'a' with uninitialized pieces on board
static bool test2() {
	GameBoard<12, 7, string, 4> board;
	int i = 0;
	for (int row = 0; row < 12; row++) {
		for (int col = 0; col < 7; col++) {
			if (col % 3 == 0)
				board.setPiece(row, col, "Piece", i);
			i = (i + 1) % 4;
		}
	}
	int occurence[4] = { 0,0,0,0 };
	for (auto pieceInfo : board) {
		occurence[get<3>(pieceInfo)]++;
	}
	for (int i = 0;i < 4;i++) {
		if (occurence[i] != 9) {
			return false;
		}
	}
	return true;
}

//check iterator 'b' with uninitialized pieces on board
static bool test3() {
	GameBoard<12, 7, string, 4> board;
	int i = 0;
	for (int row = 0; row < 12; row++) {
		for (int col = 0; col < 7; col++) {
			if (col % 3 == 0)
				board.setPiece(row, col, "Piece", i);
			i = (i + 1) % 4;
		}
	}
	int occurence[4] = { 0,0,0,0 };
	int playerNum = 0;
	for (auto pieceInfo : board.allPiecesOfPlayer(playerNum)) {
		occurence[get<3>(pieceInfo)]++;
	}

	if (occurence[i] != 9) {
		return false;
	}
	for (int i = 1;i < 4;i++) {
		if (occurence[i] != 0) {
			return false;
		}
	}
	return true;
}

//check iterator 'c' with uninitialized pieces on board
static bool test4() {
	GameBoard<12, 7, char, 4> board;
	int i = 0;
	for (int row = 0; row < 12; row++) {
		for (int col = 0; col < 7; col++) {
			if (col % 3 == 0) {
				if (row % 2 == 0)
					board.setPiece(row, col, 'J', i);
				else
					board.setPiece(row, col, 'R', i);
			}
			i = (i + 1) % 4;
		}
	}
	int occurence[4] = { 0,0,0,0 };
	char piece = 'J';
	for (auto pieceInfo : board.allOccureneceOfPiece(piece)) {
		occurence[get<3>(pieceInfo)]++;
	}

	for (int i = 0;i < 4;i++) {
		if (i % 2 == 0) {
			if (occurence[i] != 6) {
				return false;
			}
		}
		else {
			if (occurence[i] != 3) {
				return false;
			}
		}
	}
	return true;
}

//check iterator 'd' with uninitialized pieces on board
static bool test5() {
	GameBoard<12, 7, char, 4> board;
	int i = 0;
	for (int row = 0; row < 12; row++) {
		for (int col = 0; col < 7; col++) {
			if (col % 3 == 0)
				if (row % 2 == 0)
					board.setPiece(row, col, 'J', i);
				else
					board.setPiece(row, col, 'R', i);
			i = (i + 1) % 4;
		}
	}
	int occurence[4] = { 0,0,0,0 };
	char piece = 'J';
	int playerNum = 0;
	for (auto pieceInfo : board.allOccureneceOfPieceForPlayer(piece, playerNum)) {
		occurence[get<3>(pieceInfo)]++;
	}

	if (occurence[0] != 6) {
		return false;
	}
	for (int i = 1;i < 4;i++) {
		if (occurence[i] != 0) {
			return false;
		}
	}
	return true;
}

int main() {
	RUN_TEST(test1);
	RUN_TEST(test2);
	RUN_TEST(test3);
	RUN_TEST(test4);
	RUN_TEST(test5);
	return 0;
}
