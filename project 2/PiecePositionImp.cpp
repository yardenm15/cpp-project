#include "stdafx.h"
#include "PiecePositionImp.h"

PiecePositionImp::PiecePositionImp() {
	owner = NO_PLAYER;
}
const Point& PiecePositionImp::getPosition() const { 
	return position; 
};

char PiecePositionImp::getPiece() const { 
	return piece; 
};

char PiecePositionImp::getJokerRep() const { 
	return jokerRep; 
};

int PiecePositionImp::getOwner() const { 
	return owner; 
};

void PiecePositionImp::setPiece(char p) {
	piece = p; 
};

void PiecePositionImp::setJokerRep(char j)  {
	jokerRep = j; 
};

void PiecePositionImp::setOwner(int o)  {
	owner = o; 
};

void PiecePositionImp::setPosition(int x, int y) {
	position.setX(x);
	position.setY(y);
}

PiecePositionImp:: PiecePositionImp(PiecePositionImp &p) {
	owner = p.getOwner();
	piece = p.getPiece();
	jokerRep = p.getJokerRep();
	position.setX(p.getPosition().getX());
	position.setY(p.getPosition().getY());
}






