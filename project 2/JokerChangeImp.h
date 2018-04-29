#ifndef __JOKERCHANGEIMP_H_
#define __JOKERCHANGEIMP_H_
#include "JokerChange.h"

class JokerChangeImp : public JokerChange {
	int x, y;
public:
	virtual const Point& getJokerChangePosition() const {};
	virtual char getJokerNewRep() const {}; // R, P, S or B (but NOT J and NOT F)
};

#endif