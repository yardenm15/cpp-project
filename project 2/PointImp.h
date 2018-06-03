#ifndef POINTIMP_H_
#define POINTIMP_H_

#include "Point.h"

class PointImp : public Point {
	int x, y;
public:
	virtual int getX() const override;
	virtual int getY() const override;
	explicit PointImp() : x(-1), y(-1) {};
	void PointImp::setX(int row);
	void PointImp::setY(int col);
};

#endif