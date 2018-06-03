#include "Move.h"
#include "MoveImp.h"

 const Point& MoveImp::getFrom() const { 
	 return *srcPoint; 
 };

 const Point& MoveImp::getTo() const { 
	 return *destPoint; 
 };

 MoveImp::MoveImp() {
	 srcPoint = make_unique<PointImp>();
	 destPoint = make_unique<PointImp>();
 }

 void MoveImp::setFrom(PointImp p) {
	 *srcPoint = p;
 }

 void MoveImp::setTo(PointImp p) {
	 *destPoint = p;
 }