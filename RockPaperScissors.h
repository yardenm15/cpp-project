/*
* RockPaperScissors.h
*
*  Created on:
*  Author: Oleg S.
*/

#ifndef ROCKPAPERSCISSORS_H_
#define ROCKPAPERSCISSORS_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <map>

#include "cell.h"
#include "gameStatus.h"

using namespace std;

#define NUM_OF_ROWS 10 
#define NUM_OF_COLS 10 
#define NUM_OF_TOTAL_PIECES 13
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
#define toDigit(c) (c-'0')

const static int numberOfPieaces[] = { NUM_OF_ROCKS, NUM_OF_PAPERS, NUM_OF_SCISSORS, NUM_OF_BOMBS, NUM_OF_FLAGS, NUM_OF_JOKERS };

class RockPaperScissors {

	Cell **board;
	int strengthTable[STRENGTH_TABLE_SIZE][STRENGTH_TABLE_SIZE];
	int piecesToPlace_Player1 [NUM_OF_DIFFERENT_PIECES];
	int piecesToPlace_Player2 [NUM_OF_DIFFERENT_PIECES];
	int piecesOnBoard_Player1[NUM_OF_DIFFERENT_PIECES];
	int piecesOnBoard_Player2[NUM_OF_DIFFERENT_PIECES];
	Piece jokersOnBoard_Player1[NUM_OF_JOKERS];
	Piece jokersOnBoard_Player2[NUM_OF_JOKERS];
	bool aremovingJokers(int playerNumber);
	void addJokerToJokerArray(int playerNumber, Piece p);
	void removeJokerFromJokerArray(int playerNumber, Piece p);
	void setPosition(int lineNumber, string& line, int playerNumber, status& currentStatus);
	void setMove(int lineNumber, string& line, int playerNumber, status& currentStatus);
	void fight(int x, int y, Piece p, int playerNumber, status& currentStatus);
	bool placePiece(int playerNumber, Piece p, Cell** board, int fromRow, int fromColumn, int toRow, int toColumn, string line, status& currentStatus);
	void decreasePieceFromStock(int playerNumber, Piece p);
	void increasePieceOnBoard(int playerNumber, Piece p);
	void decreasePieceFromBoard(int playerNumber, Piece p);
	int getNumberOfPiecesLeftToPlace(int playerNumber, Piece p);
	int getFightResult(int x, int y);
	bool checkWinningConditions(status& currentStatus);
	bool doPlayerHasMovablePieces(int playerNumber);
	int flagsLeft(int playerNumber);
	void printBoardToFile(ofstream& outputFile);
	int getPlayerOwningCell(int row, int col);
	Piece getPieceAt(int row, int col);
	void setPieceAt(int row, int col, int playerNumber, Piece p = Piece());
	bool isMoveFormatCorrect(vector<string> tokens);

public:
	explicit RockPaperScissors();
	~RockPaperScissors();
	void startGame(string& firstPlayerInitFile, string& secondPlayerInitFile, string& firstPlayerMoveFile, string& secondPlayerMoveFile, status& currentStatus);
};

#endif