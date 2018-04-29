#include "PlayerAlgorithmImp.h"
class PlayerAlgorithmImp {
	virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
	virtual void notifyOnOpponentMove(const Move& move); // called only on opponent’s move
	virtual void notifyFightResult(const FightInfo& fightInfo); // called only if there was a fight
	virtual unique_ptr<Move> getMove();
	virtual unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested
	void performInitialFights(vector<unique_ptr<PiecePosition>>& player1Board, vector<unique_ptr<PiecePosition>>& player2Board);
};

void PlayerAlgorithmImp::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) {

}

void PlayerAlgorithmImp::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) {

}

void PlayerAlgorithmImp::notifyOnOpponentMove(const Move& move) {

}

void PlayerAlgorithmImp::notifyFightResult(const FightInfo& fightInfo) {

}

unique_ptr<Move> PlayerAlgorithmImp::getMove() {

}

unique_ptr<JokerChange> PlayerAlgorithmImp::getJokerChange() {

}

void PlayerAlgorithmImp::performInitialFights(vector<unique_ptr<PiecePosition>>& player1Board, vector<unique_ptr<PiecePosition>>& player2Board) {

}
