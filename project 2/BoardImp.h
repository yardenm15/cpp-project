#ifndef __BOARDIMP_H_
#define __BOARDIMP_H_

#include "Board.h"

#define NUMBER_OF_ROWS 10
#define NUMBER_OF_COLUMNS 10

class BoardImp : public Board {
	vector<unique_ptr<PiecePosition>> board;
public:
	virtual int getPlayer(const Point& pos) const { return board[pos.getX()*NUMBER_OF_ROWS + pos.getY()].get()->getPosition; };
};

#endif