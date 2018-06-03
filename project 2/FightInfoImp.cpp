#include "FightInfoImp.h"

FightInfoImp::FightInfoImp(PiecePosition& player1Pie, PiecePosition& player2Pie) : player1Piece(make_unique<PiecePositionImp>(dynamic_cast<PiecePositionImp&>(player1Pie))), player2Piece(make_unique<PiecePositionImp>(dynamic_cast<PiecePositionImp&>(player2Pie))) {
	position = make_shared<PointImp>();
	PointImp& positionRef = dynamic_cast<PointImp&>(*position.get());
	positionRef.setX(player1Piece->getPosition().getX());
	positionRef.setY(player1Piece->getPosition().getY());
}

const Point& FightInfoImp::getPosition() const {
	return *position.get(); 
}

char FightInfoImp::getPiece(int player) const{
	if (player == PLAYER_1)
		return player1Piece->getPiece() == 'J' ? player1Piece->getJokerRep() : player1Piece->getPiece();
	return player2Piece->getPiece() == 'J' ? player2Piece->getJokerRep() : player2Piece->getPiece();
}

char FightInfoImp::getJokerRep() const {
	if (getWinner() == PLAYER_1)
		return player1Piece->getJokerRep();
	return player2Piece->getJokerRep();
}

int FightInfoImp::getWinner() const {
	switch (getPiece(PLAYER_1)) {
		case('R'):
			switch (getPiece(PLAYER_2)) {
				case('R'):
					return TIE;
				case('P'):
					return LOSE;
				case('S'):
					return WIN;
				case('B'):
					return TIE;
				case('F'):
					return WIN;
			}
		case('P'):
			switch (getPiece(PLAYER_2)) {
				case('R'):
					return WIN;
				case('P'):
					return TIE;
				case('S'):
					return LOSE;
				case('B'):
					return TIE;
				case('F'):
					return WIN;
			}
		case('S'):
			switch (getPiece(PLAYER_2)) {
				case('R'):
					return LOSE;
				case('P'):
					return WIN;
				case('S'):
					return TIE;
				case('B'):
					return TIE;
				case('F'):
					return WIN;
			}
		case('B'):
			switch (getPiece(PLAYER_2)) {
				case('R'):
					return TIE;
				case('P'):
					return TIE;
				case('S'):
					return TIE;
				case('B'):
					return TIE;
				case('F'):
					return TIE;
			}
		case('F'):
			switch (getPiece(PLAYER_2)) {
				case('R'):
					return LOSE;
				case('P'):
					return LOSE;
				case('S'):
					return LOSE;
				case('B'):
					return TIE;
				case('F'):
					return TIE;
			}
	}
	return -1; // should never get here
}
