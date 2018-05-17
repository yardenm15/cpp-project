#include "stdafx.h"
#include "JokerChangeImp.h"

JokerChangeImp::JokerChangeImp(PointImp point, char joker) {
	changePoint = point;
	jokerRep = joker;
}

const Point& JokerChangeImp::getJokerChangePosition() const {
	return changePoint;
};
char JokerChangeImp::getJokerNewRep() const {
	return jokerRep;
}; 