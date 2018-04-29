#include "Point.h"
class PointImp : public Point {
	int x, y;
public:
	virtual int getX() const override { return x; };
	virtual int getY() const override { return y; };
};