/*
* cell.cpp
*
*  Created on:
*  Author: Oleg S.
*/

//#include "stdafx.h"
#include "cell.h"

void Cell::setCell(Piece newPiece, int playerNumber) {
		currentPiece = newPiece;
		playerOwn = playerNumber;
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

Piece Cell::getCellPiece() {
	return currentPiece;
}

int Cell::getPlayerOwning() {
	return playerOwn;
}

Piece::Piece(const Piece &piece) {
	isJoker = piece.isJoker;
	rpc = piece.rpc;
}

Piece & Piece::operator=(const Piece & other) {
	isJoker = other.isJoker;
	rpc = other.rpc;
	return *this;
}

void Piece::setrpc(RPC r) {
	rpc = r;
}

RPC Piece::getrpc() const{
	return rpc;
}

void Piece::setJoker(bool bol) {
	Piece::isJoker = bol;
}

bool Piece::getisJoker() const {
	return isJoker;
}
