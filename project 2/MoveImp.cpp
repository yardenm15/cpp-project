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

 MoveImp::MoveImp(PointImp src, PointImp dest) {
	 srcPoint = make_unique<PointImp>(src);
	 destPoint = make_unique<PointImp>(dest);
 }

 MoveImp::MoveImp(const MoveImp & m) {
	 PointImp src;
	 PointImp dst;
	 src.setX(m.getFrom().getX());
	 src.setY(m.getFrom().getY());
	 dst.setX(m.getTo().getX());
	 dst.setY(m.getTo().getY());

	 srcPoint = make_unique<PointImp>(src);
	 destPoint = make_unique<PointImp>(dst);
 }