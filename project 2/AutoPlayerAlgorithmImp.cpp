#include "AutoPlayerAlgorithmImp.h"

void AutoPlayerAlgorithmImp::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) {};
void AutoPlayerAlgorithmImp::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) {};
void AutoPlayerAlgorithmImp::notifyOnOpponentMove(const Move& move){};
void AutoPlayerAlgorithmImp::notifyFightResult(const FightInfo& fightInfo){};
unique_ptr<Move> AutoPlayerAlgorithmImp::getMove() { unique_ptr<Move> m; return m; };
unique_ptr<JokerChange> AutoPlayerAlgorithmImp::getJokerChange() { unique_ptr<JokerChange> p; return p; };