#ifndef FILEPLAYERALGORITHMIMP_H_
#define FILEPLAYERALGORITHMIMP_H_



#include "PlayerAlgorithm.h"
#include "Board.h"
#include "Point.h"
#include "PiecePosition.h"
#include "PiecePositionImp.h"
#include "gameStatus.h"
#include "Move.h"
#include "MoveImp.h"
#include <vector>
#include <memory> // for unique_ptr
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>

#define PLAYER_ONE 1
#define PLAYER_TWO 2

using namespace std;

class FilePlayerAlgorithmImp : public PlayerAlgorithm {
	string positionsFile;
	string MovesFile;
	Status currentStatus;
	int playerNumber;
	vector<unique_ptr<Move>> movesVector; 
	vector<unique_ptr<JokerChange>> jokerChangeVector;
	int counter;
	
public:
	//FilePlayerAlgorithmImp();
	//FilePlayerAlgorithmImp(const FilePlayerAlgorithmImp&) = delete;
	//FilePlayerAlgorithmImp& operator =(const FilePlayerAlgorithmImp&) = delete;
	explicit FilePlayerAlgorithmImp(string positionsFile, string MovesFile, Status& currentStatus, int PlayerNumber);
	void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
	void notifyOnOpponentMove(const Move& move);
	void notifyFightResult(const FightInfo& fightInfo); // called only if there was a fight
	unique_ptr<Move> getMove();
	unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested
	
	void parseToPiecePosition(int lineNumber, string line, int player, Status& status, PiecePositionImp& Piece);
	PiecePositionImp getPieceFromVector(const vector<string>& tokens) const;
	void parseMovesFile(string MovesFile);
	vector<string> splitLineBySpaces(string line);
	int getMovesVectorSize();

};
#endif
