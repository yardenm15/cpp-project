#ifndef MOVEIMP_H_
#define MOVEIMP_H_

#include "Move.h"
#include "PointImp.h"
#include "JokerChangeImp.h"
#include <memory>

using std::unique_ptr;
using std::make_unique;

class MoveImp : public Move {
	unique_ptr<Point> srcPoint;
	unique_ptr<Point> destPoint;
public:
	explicit MoveImp();
	virtual const Point& getFrom() const;
	virtual const Point& getTo() const;
	void setFrom(PointImp p);
	void setTo(PointImp p);
	MoveImp(PointImp srcPoint, PointImp destPoint);
	MoveImp(const MoveImp & m);
};

#endif