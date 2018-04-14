/*
* RockPaperScissors.h
*
*  Created on:
*  Author: Oleg S.
*/

#ifndef ROCKPAPERSCISSORS_H_
#define ROCKPAPERSCISSORS_H_

#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>

#include "cell.h"
#include "gameStatus.h"
#include "helperFunctions.h"

#define NUM_OF_ROCKS 2
#define NUM_OF_PAPERS 5
#define NUM_OF_SCISSORS 1
#define NUM_OF_BOMBS 2
#define NUM_OF_FLAGS 1
#define NUM_OF_JOKERS 2
#define TIE 0
#define WIN 1
#define LOSE 2
#define STRENGTH_TABLE_SIZE 5
#define NUM_OF_DIFFERENT_PIECES 6
#define PIECES_ARRAY (1,2)

using std::istringstream;
using std::istream_iterator;
using std::ifstream;

const static int numberOfPieaces[] = { NUM_OF_ROCKS, NUM_OF_PAPERS, NUM_OF_SCISSORS, NUM_OF_BOMBS, NUM_OF_FLAGS, NUM_OF_JOKERS };

class RockPaperScissors {

	Cell **board;
	int strengthTable[STRENGTH_TABLE_SIZE][STRENGTH_TABLE_SIZE];
	int piecesToPlace_Player1[NUM_OF_DIFFERENT_PIECES];
	int piecesToPlace_Player2[NUM_OF_DIFFERENT_PIECES];
	int piecesOnBoard_Player1[NUM_OF_DIFFERENT_PIECES];
	int piecesOnBoard_Player2[NUM_OF_DIFFERENT_PIECES];
	Piece jokersOnBoard_Player1[NUM_OF_JOKERS];
	Piece jokersOnBoard_Player2[NUM_OF_JOKERS];
	bool aremovingJokers(int playerNumber) const;
	void addJokerToJokerArray(int playerNumber, const Piece& p);
	void removeJokerFromJokerArray(int playerNumber, const Piece& p);
	void setPosition(int lineNumber, const string& line, int playerNumber, Status& currentStatus);
	void setMove(int lineNumber, const string& line, int playerNumber, Status& currentStatus);
	void fight(int x, int y, const Piece& p, int playerNumber);
	bool placePiece(int playerNumber, const Piece& p, int fromRow, int fromColumn, int toRow, int toColumn, int lineNumber, const string& line, Status& currentStatus);
	void decreasePieceFromStock(int playerNumber, const Piece& p);
	void increasePieceOnBoard(int playerNumber, const Piece& p);
	void decreasePieceFromBoard(int playerNumber, const Piece& p);
	int getNumberOfPiecesLeftToPlace(int playerNumber, const Piece& p) const;
	int getFightResult(int x, int y) const;
	bool checkWinningConditions(Status& currentStatus) const;
	bool doPlayerHasMovablePieces(int playerNumber) const;
	int flagsLeft(int playerNumber) const;
	void printBoardToFile(ofstream& outputFile) const;
	int getPlayerOwningCell(int row, int col) const;
	Piece getPieceAt(int row, int col) const;
	void setPieceAt(int row, int col, int playerNumber, const Piece& p = Piece());
	Piece getPieceFromVector(const vector<string>& tokens) const;
	void printBoard();

public:
	explicit RockPaperScissors();
	~RockPaperScissors();
	void startGame(const string& firstPlayerInitFile, const string& secondPlayerInitFile, const string& firstPlayerMoveFile, const string& secondPlayerMoveFile, Status& currentStatus);
};

#endif