#include "stdafx.h"
#include "BoardImp.h"

int BoardImp::getPlayer(const Point& pos) const {
	/*PiecePositionImp *derivedPointer = dynamic_cast<PiecePositionImp*>(board[pos.getX() - 1][pos.getY() - 1].get());
	return derivedPointer->getOwner();*/
	return board[pos.getX() - 1][pos.getY() - 1].getOwner();
}

BoardImp::BoardImp() {
	for (int i = 0; i < NUMBER_OF_ROWS; i++)
		board.resize(NUMBER_OF_COLUMNS);
}


const vector<vector<PiecePositionImp>>& BoardImp::getBoard() const{
	return board;
}