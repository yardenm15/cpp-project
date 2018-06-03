#ifndef FILEPLAYERALGORITHMIMP_H_
#define FILEPLAYERALGORITHMIMP_H_

#include "PlayerAlgorithmImp.h"
#include "PiecePositionImp.h"
#include "MoveImp.h"
#include "BoardImp.h"
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>

#define PLAYER_1 1
#define PLAYER_2 2

using std::ifstream;
using std::vector;
using std::make_unique;

class FilePlayerAlgorithmImp : public PlayerAlgorithm {
	unique_ptr<PlayerStatus> playerStatus;
	shared_ptr<Board> playerBoard;
	//int counter;

public:
	virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) {};
	virtual void notifyOnOpponentMove(const Move& move);
	virtual void notifyFightResult(const FightInfo& fightInfo);
	virtual unique_ptr<Move> getMove();
	virtual unique_ptr<JokerChange> getJokerChange();
	explicit FilePlayerAlgorithmImp() : playerBoard(make_shared<BoardImp>()), playerStatus(make_unique<PlayerStatus>()) {};
	void parseToPiecePosition(int lineNumber, string line, int player, PiecePositionImp& Piece);
	PiecePositionImp getPieceFromVector(const vector<string>& tokens) const;
	//PlayerStatus getPlayerStatus()const;
	//void parseMovesFile(string MovesFile);
	//vector<string> splitLineBySpaces(string line);
	//int getMovesVectorSize();

};
#endif
