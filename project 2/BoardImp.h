#ifndef _BOARDIMP_H_
#define _BOARDIMP_H_

#include "Board.h"
#include "Point.h"
#include "PiecePositionImp.h"
#include <vector>
#include <memory>

#define NUMBER_OF_ROWS 10
#define NUMBER_OF_COLUMNS 10

using namespace std;

class BoardImp : public Board {
	vector<vector<shared_ptr<PiecePosition>>> board;
public:
	virtual int getPlayer(const Point& pos) const;
	explicit BoardImp();
	vector<shared_ptr<PiecePosition>>& operator[](size_t i);
	void setCell(int x, int y, int owner, char piece, char jokerRep);
	//const vector<vector<PiecePositionImp>>&  getBoard() const ;
	//void setCell(int x, int y, int owner, char piece, char jokerRep);

				
};

#endif