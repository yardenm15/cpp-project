/*
* cell.h
*
*  Created on:
*  Author: Oleg S.
*/

#ifndef CELL_H_
#define CELL_H_

#include <iostream>
#define FIRST_PLAYER 1
#define SECOND_PLAYER 2

using namespace std;

enum class Piece { None, Rock, Paper, Scissors, Bomb, Joker_Rock,
	Joker_Paper, Joker_Scissors, Joker_Bomb, Flag };

class cell {
	
	Piece Player1;
	Piece Player2;

public:
	explicit cell() : Player1(Piece::None), Player2(Piece::None) {}
	cell(const cell&) = delete;
	cell& operator=(const cell&) = delete;
	void updateCell(Piece newPiece, int playerNumber);
	Piece getPlayer1Piece();
	Piece getPlayer2Piece();
};

#endif