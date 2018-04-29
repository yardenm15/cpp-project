#ifndef __MOVEIMP_H_
#define __MOVEIMP_H_

#include "Move.h"
#include "PointImp.h"

class MoveImp : public Move {
	PointImp from;
	PointImp to;
public:
	virtual const Point& getFrom() const { return from; };
	virtual const Point& getTo() const { return to; };
};

#endif