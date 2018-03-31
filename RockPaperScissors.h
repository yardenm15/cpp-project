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

#include "cell.h"


using namespace std;

#define NUM_OF_ROWS 5 //should be 10
#define NUM_OF_COLS 5 //should be 10
#define NUM_OF_TOTAL_PIECES 13
#define NUM_OF_ROCKS 2
#define NUM_OF_PAPERS 5
#define NUM_OF_SCISSORS 1
#define NUM_OF_BOMBS 2
#define NUM_OF_JOKERS 2
#define NUM_OF_FLAGS 1
#define FIRST_PLAYER 1
#define SECOND_PLAYER 2
#define TIE 0
#define WIN 1
#define LOSE 2
#define VICTORY 3
#define DEFEAT 4

class RockPaperScissors {

	cell **board;
	int **strengthTable;
	int piecesLeft_Player1;
	int piecesLeft_Player2;
	int numOfFlagsPositioned_Player1;
	int numOfFlagsPositioned_Player2;
	int winner;
	void setFirstPlayerPosition(string& line);
	void setSecondPlayerPosition(string& line);
	void makeFight(int x, int y, Piece secondPlayerPiece);
	int getFightResult(int x, int y);
	int getIndexInStrengthTable(Piece piece);

public:
	explicit RockPaperScissors();
	~RockPaperScissors();
	void startGame(string& firstPlayerFile, string& secondPlayerFile);
	void printBoard();
	void movePieces(string firstPlayerFile, string secondPlayerFile);



};


#endif