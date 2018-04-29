#ifndef __PLAYERALGORITHMIMP_H_
#define __PLAYERALGORITHMIMP_H_

#include "PlayerAlgorithm.h"
#include "BoardImp.h"
#include "PointImp.h"
#include "PiecePositionImp.h"

using std::vector;

class PlayerAlgorithmImp : public PlayerAlgorithm {
public:
	virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
	virtual void notifyOnOpponentMove(const Move& move); // called only on opponent’s move
	virtual void notifyFightResult(const FightInfo& fightInfo); // called only if there was a fight
	virtual unique_ptr<Move> getMove();
	virtual unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested
	void performInitialFights(vector<unique_ptr<PiecePosition>>& player1Board, vector<unique_ptr<PiecePosition>>& player2Board);
};

#endif