/*
* cell.cpp
*
*  Created on:
*  Author: Oleg S.
*/

#include "cell.h"

void Cell::setCell(Piece newPiece, int playerNumber) {
	piece = newPiece;
	playerOwn = playerNumber;
}

Piece Cell::getCellPiece() const {
	return piece;
}

std::ostream& operator<<(std::ostream& o, const Piece& p) {
	if (p.getisJoker())
		cout << "Joker";
	else {
		switch (p.getrpc()) {
			case RPC::Rock:
				cout << "Rock";
				break;
			case RPC::Paper:
				cout << "Paper";
				break;
			case RPC::Scissors:
				cout << "Scissors";
				break;
			case RPC::Bomb:
				cout << "Bomb";
				break;
			case RPC::Flag:
				cout << "Flag";
				break;
		}
	}
	return o;
}

int Cell::getPlayerOwning() const {
	return playerOwn;
}

Piece::Piece(const Piece& p) {
	rpc = p.getrpc();
	isJoker = p.getisJoker();
}

void Piece::setrpc(const RPC r) {
	rpc = r;
}

RPC Piece::getrpc() const {
	return rpc;
}

void Piece::setJoker(const bool bol) {
	Piece::isJoker = bol;
}

bool Piece::getisJoker() const {
	return isJoker;
}
