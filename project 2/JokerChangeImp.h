#ifndef JOKERCHANGEIMP_H_
#define JOKERCHANGEIMP_H_
#include "JokerChange.h"
#include "PointImp.h"

class JokerChangeImp : public JokerChange {
	PointImp changePoint;
	char jokerRep;
public:
	JokerChangeImp();
	JokerChangeImp(PointImp changeP, char jokerR) : changePoint(changeP), jokerRep(jokerR) {};
	virtual const Point& getJokerChangePosition() const;
	virtual char getJokerNewRep() const;
};

#endif