#ifndef PLAYERALGORITHMIMP_H_
#define PLAYERALGORITHMIMP_H_

#include "PlayerAlgorithm.h"
#include "PlayerStatus.h"

class PlayerAlgorithmImp : public PlayerAlgorithm {
	//PlayerStatus playerStatus; //not relevant for auto player
	//unique_ptr<Board> playerBoard; //not relevant for file player
	//int counter;
public:
	virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) = 0;
	virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) = 0;
	virtual void notifyOnOpponentMove(const Move& move) = 0;
	virtual void notifyFightResult(const FightInfo& fightInfo) = 0;
	virtual unique_ptr<Move> getMove() = 0;
	virtual unique_ptr<JokerChange> getJokerChange() = 0;
};
#endif