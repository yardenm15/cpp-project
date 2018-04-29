#ifndef __POINTIMP_H_
#define __POINTIMP_H_

#include "Point.h"

#define NO_OWNER 0
#define PLAYER_1 1
#define PLAYER_2 2

class PointImp : public Point {
	int x, y;
public:
	virtual int getX() const override { return x; };
	virtual int getY() const override { return y; };
	void setX(int row) { x = row; };
	void setY(int column) { y = column; };
};

#endif