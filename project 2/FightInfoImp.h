#ifndef FIGHTINFOIMP_H_
#define FIGHTINFOIMP_H_

#include "FightInfo.h"
#include "PiecePositionImp.h"
#include "HelperFunctions.h"
#include <memory>

#define NO_OWNER 0
#define PLAYER_1 1
#define PLAYER_2 2

using std::unique_ptr;
using std::make_unique;
using std::move;

class FightInfoImp : public FightInfo {
	//int playerAttacking;
	unique_ptr<PiecePosition> player1Piece;
	unique_ptr<PiecePosition> player2Piece;
	shared_ptr<Point> position;
public:
	virtual const Point& getPosition() const;
	virtual char getPiece(int player) const;
	virtual int getWinner() const;
	FightInfoImp(PiecePosition& player1Pie, PiecePosition& player2Pie);
	char getJokerRep() const;
	//int getPlayerAttacking() const { return playerAttacking; };
};

#endif