#include "stdafx.h"
#include "BoardImp.h"

int BoardImp::getPlayer(const Point& pos) const {
	PiecePositionImp *derivedPointer = dynamic_cast<PiecePositionImp*>(board[pos.getX() - 1][pos.getY() - 1].get());
	return derivedPointer->getOwner();
}

