#ifndef MOVEIMP_H_
#define MOVEIMP_H_

#include "Move.h"
#include "PointImp.h"
#include "JokerChangeImp.h"

class MoveImp : public Move {
	PointImp srcPoint;
	PointImp destPoint;

public:
	MoveImp(PointImp srcPoint, PointImp destPoint);
	virtual const Point& getFrom() const;
	virtual const Point& getTo() const;
};

#endif