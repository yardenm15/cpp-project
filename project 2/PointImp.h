#ifndef POINTIMP_H_
#define POINTIMP_H_

#include "Point.h"

#define NO_OWNER 0
#define PLAYER_1 1
#define PLAYER_2 2

class PointImp : public Point {
	int x, y;
public:
	virtual int getX() const override;
	virtual int getY() const override;
	void setX(int row);
	void setY(int column);
};

#endif