/*
* cell.h
*
*  Created on:
*  Author: Oleg S.
*/

#ifndef CELL_H_
#define CELL_H_

#include <iostream>
#define NO_PLAYER 0
#define PLAYER_ONE 1
#define PLAYER_TWO 2
#define ROCK 0
#define PAPER 1
#define SCISSORS 2
#define BOMB 3
#define FLAG 4
#define JOKER 5

using std::cout;
using std::endl;

enum class RPC {
	None = -1, Rock, Paper, Scissors, Bomb, Flag
};

class Piece {
	RPC rpc;
	bool isJoker;
public:
	explicit Piece() : rpc(RPC::None), isJoker(false) {}
	explicit Piece(RPC r) : rpc(r), isJoker(false) {}
	explicit Piece(RPC r, bool b) : rpc(r), isJoker(b) {}
	Piece(const Piece& p);
	void setrpc(const RPC r);
	RPC getrpc() const;
	void setJoker(const bool b);
	bool getisJoker() const;
	friend std::ostream& operator<<(std::ostream& o, const Piece& p);
};

class Cell {
	Piece piece;
	int playerOwn;
public:
	explicit Cell() : piece(Piece()), playerOwn(NO_PLAYER) {}
	Cell(const Cell&) = delete;
	Cell& operator=(const Cell&) = delete;
	void setCell(Piece newPiece, int playerNumber = NO_PLAYER);
	Piece getCellPiece() const;
	int getPlayerOwning() const;
};

#endif