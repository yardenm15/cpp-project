#ifndef JOKERCHANGEIMP_H_
#define JOKERCHANGEIMP_H_
#include "JokerChange.h"
#include "PointImp.h"

class JokerChangeImp : public JokerChange {
	PointImp changePoint;
	char jokerRep;
public:
	JokerChangeImp(PointImp changePoint, char jokerRep);
	virtual const Point& getJokerChangePosition() const;
	virtual char getJokerNewRep() const; // R, P, S or B (but NOT J and NOT F)
};

#endif