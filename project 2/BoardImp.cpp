#include "BoardImp.h"

	int BoardImp::getPlayer(const Point& pos) const {
		//PiecePositionImp& piecePositionRef = dynamic_cast<PiecePositionImp&>((board[pos.getX()][pos.getY()]).release());
		//return piecePositionRef.getOwner();
		return 1;
	}

	BoardImp::BoardImp() {
		board.resize(NUMBER_OF_ROWS);
		for (int i = 0; i < NUMBER_OF_ROWS; i++)
			board[i].resize(NUMBER_OF_COLUMNS);
		//for (int i = 0; i < NUMBER_OF_ROWS; i++) {
		//	for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
		//		board[i][j] = shared_ptr<PiecePosition>();
		//	}
		//}
	}

	//static vector<unique_ptr<PiecePosition>> generate() {
	//	vector<unique_ptr<PiecePosition>> result(NUMBER_OF_COLUMNS*NUMBER_OF_ROWS);
	//	return result;
	//}

	vector<vector<shared_ptr<PiecePosition>>>& BoardImp::getBoardReg() {
		return board;
	}
	//
	//
	//const vector<vector<PiecePositionImp>>& BoardImp::getBoard() const{
	//	return board;
	//}

	//void BoardImp::setCell(int x, int y, int owner, char piece, char jokerRep) {
	//	board[x-1][y-1].setPosition(x, y);
	//	board[x-1][y-1].setOwner(owner);
	//	board[x-1][y-1].setPiece(piece);
	//	board[x-1][y-1].setJokerRep(jokerRep);
	//
	//}