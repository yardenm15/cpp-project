#ifndef AUTOPLAYERALGORITHMIMP_H_
#define AUTOPLAYERALGORITHMIMP_H_

#include "PlayerAlgorithmImp.h"

class AutoPlayerAlgorithmImp : public PlayerAlgorithm {
	PlayerStatus playerStatus;
	unique_ptr<Board> playerBoard;
	//int counter;
public:
	virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
	virtual void notifyOnOpponentMove(const Move& move);
	virtual void notifyFightResult(const FightInfo& fightInfo);
	virtual unique_ptr<Move> getMove();
	virtual unique_ptr<JokerChange> getJokerChange();
};
#endif