#include "PointImp.h"

int PointImp::getX() const { 
	return x; 
}

int PointImp::getY() const { 
	return y; 
}

void PointImp::setX(int row) {
	x = row;
}

void PointImp::setY(int col)  {
	y = col;
}