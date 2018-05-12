#ifndef FILEPLAYERALGORITHMIMP_H_
#define FILEPLAYERALGORITHMIMP_H_



#include "PlayerAlgorithm.h"
#include "Board.h"
#include "Point.h"
#include "PiecePosition.h"
#include "PiecePositionImp.h"
#include "gameStatus.h"
#include <vector>
#include <memory> // for unique_ptr
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>

using namespace std;

class FilePlayerAlgorithmImp : public PlayerAlgorithm {
	string positionsFile;
	string MovesFile;
	Status currentStatus;
	
public:
	//FilePlayerAlgorithmImp();
	//FilePlayerAlgorithmImp(const FilePlayerAlgorithmImp&) = delete;
	//FilePlayerAlgorithmImp& operator =(const FilePlayerAlgorithmImp&) = delete;
	explicit FilePlayerAlgorithmImp(string positionsFile, string MovesFile, Status& currentStatus);
	void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
	void notifyOnOpponentMove(const Move& move);
	void notifyFightResult(const FightInfo& fightInfo); // called only if there was a fight
	unique_ptr<Move> getMove();
	unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested
	void parseToPiecePosition(int lineNumber, string line, int player, Status& status, PiecePositionImp& Piece);
	PiecePositionImp getPieceFromVector(const vector<string>& tokens) const;

};
#endif
