/*
* cell.cpp 
*
*  Created on: 
*  Author: Oleg S.
*/

#include "stdafx.h"
#include "cell.h"


void cell::updateCell(Piece newPiece, int playerNumber) {
	if (playerNumber == FIRST_PLAYER)
		Player1 = newPiece;
	else
		Player2 = newPiece;
}


Piece cell::getPlayer1Piece() {
	return Player1;
}

Piece cell::getPlayer2Piece() {
	return Player2;
}


