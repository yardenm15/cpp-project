#include "stdafx.h"
#include "FightInfoImp.h"

char FightInfoImp::getOpponentPiece() const {
	if (playerAttacking == PLAYER_1)
		return player2Piece.getPiece() == 'J' ? player2Piece.getJokerRep() : player2Piece.getPiece();
	return player1Piece.getPiece() == 'J' ? player1Piece.getJokerRep() : player1Piece.getPiece();
}

//todo: complete this function using fightTable member
int FightInfoImp::getWinner() const {
	return 0;
}
