#ifndef _BOARDIMP_H_
#define _BOARDIMP_H_

#include "Board.h"
#include "Point.h"
#include "PiecePosition.h"
#include "PiecePositionImp.h"
#include <vector>
#include <memory> // for unique_ptr

#define NUMBER_OF_ROWS 10
#define NUMBER_OF_COLUMNS 10

using namespace std;


class BoardImp : public Board {
	vector<vector<PiecePositionImp>> board;
public:
	BoardImp();
	BoardImp(const BoardImp&) = delete;
	BoardImp& operator =(const BoardImp&) = delete;
	virtual int getPlayer(const Point& pos) const;
	const vector<vector<PiecePositionImp>>&  getBoard() const ;
	void setCell(int x, int y, int owner, char piece, char jokerRep);

				
};

#endif