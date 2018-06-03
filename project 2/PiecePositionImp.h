#ifndef PIECEPOSITIONIMP_H_
#define PIECEPOSITIONIMP_H_

#include "PiecePosition.h"
#include "PointImp.h"
#include <memory>

using std::make_shared;
using std::shared_ptr;

#define NO_PLAYER 0

class PiecePositionImp : public PiecePosition {
	shared_ptr<Point> position;
	int owner;
	char piece;
	char jokerRep;
public:
	virtual const Point& getPosition() const;
	virtual char getPiece() const;
	virtual char getJokerRep() const;
	PiecePositionImp();
	int getOwner() const;
	void setPiece(char p);
	void setJokerRep(char j);
	void setOwner(int o);
	void setPosition(int x, int y);
};

#endif