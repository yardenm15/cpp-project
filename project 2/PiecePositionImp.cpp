#include "PiecePositionImp.h"

PiecePositionImp::PiecePositionImp() {
	position = make_shared<PointImp>();
	owner = NO_PLAYER;
	piece = '*';
	jokerRep = '*';
}
const Point& PiecePositionImp::getPosition() const { 
	return *position.get(); 
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
	position = make_shared<PointImp>();
	PointImp& pointImp = dynamic_cast<PointImp&>(*position.get());
	pointImp.setX(x);
	pointImp.setY(y);
}







