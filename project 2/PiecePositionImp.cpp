#include "PiecePosition.h"
class PiecePositionImp : public PiecePosition {

public:
	virtual const Point& getPosition() const override {
		//switch (p.getrpc()) {
		//	case RPC::Rock:
		//		chr = 'R';
		//		break;
		//	case RPC::Paper:
		//		chr = 'P';
		//		break;
		//	case RPC::Scissors:
		//		chr = 'S';
		//		break;
		//	case RPC::Bomb:
		//		chr = 'B';
		//		break;
		//	case RPC::Flag:
		//		chr = 'F';
		//		break;
		//	default:
		//		break;
		//}
	};
	virtual char getPiece() const override {
	}; 
	virtual char getJokerRep() const override {
	}; 
};

