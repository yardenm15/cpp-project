#include "stdafx.h"
#include "Move.h"
#include "MoveImp.h"

MoveImp::MoveImp(PointImp src, PointImp dest) {
	srcPoint = src;
	destPoint = dest;
}

 const Point& MoveImp::getFrom() const { 
	 return srcPoint; 
 };

 const Point& MoveImp::getTo() const { 
	 return destPoint; 
 };
