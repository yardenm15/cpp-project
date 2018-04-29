#ifndef __PIECEPOSITIONIMP_H_
#define __PIECEPOSITIONIMP_H_

#include "PiecePosition.h"
#include "PointImp.h"

class PiecePositionImp : public PiecePosition {
	PointImp position;
	int owner;
	char piece;
	char jokerRep;
public:
	virtual const Point& getPosition() const { return position; };
	virtual char getPiece() const { return piece; }; 
	virtual char getJokerRep() const { return jokerRep; };
	int getOwner() const { return owner; };
	void setPiece(char p) { piece = p; };
	void setJokerRep(char j) { jokerRep = j; };
	void setOwner(int o) { owner = o; };
};

#endif