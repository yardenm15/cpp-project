#ifndef FIGHTINFOIMP_H_
#define FIGHTINFOIMP_H_

#include "FightInfo.h"
#include "PiecePositionImp.h"
#include "memory"

#define TIE 0
#define PLAYER1_WON 1
#define PLAYER2_WON 2
#define NUM_OF_DIFFERENT_SHAPES 5
using std::unique_ptr;

class FightInfoImp : public FightInfo {
	int playerAttacking;
	PiecePositionImp player1Piece;
	PiecePositionImp player2Piece;
	PointImp position;
	int fightTable[NUM_OF_DIFFERENT_SHAPES][NUM_OF_DIFFERENT_SHAPES];
public:
	virtual const Point& getPosition() const { return position; };
	virtual char getOpponentPiece() const;
	virtual int getWinner() const;
	//PiecePositionImp getPlayer1PiecePosition() const { return player1Piece; };
	//PiecePositionImp getPlayer2PiecePosition() const { return player2Piece; };
	int getPlayerAttacking() const { return playerAttacking; };
};

#endif