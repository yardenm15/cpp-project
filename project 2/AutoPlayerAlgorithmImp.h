#ifndef AUTOPLAYERALGORITHMIMP_H_
#define AUTOPLAYERALGORITHMIMP_H_


#include "PlayerAlgorithm.h"
#include "Board.h"
#include "Point.h"
#include "PiecePosition.h"
#include "PiecePositionImp.h"
#include "gameStatus.h"
#include "Move.h"
#include "BoardImp.h"
#include "MoveImp.h"
#include <vector>
#include <memory> // for unique_ptr
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <random>
#include <set>

#define NO_PLAYER 0
#define PLAYER_ONE 1
#define PLAYER_TWO 2
#define NUM_OF_ROWS 10 
#define NUM_OF_COLS 10 
#define NUM_OF_ROCKS 2
#define NUM_OF_PAPERS 5
#define NUM_OF_SCISSORS 1
#define NUM_OF_BOMBS 2
#define NUM_OF_FLAGS 1
#define NUM_OF_JOKERS 2
#define NUM_OF_DIFFERENT_PIECES 6
#define TOTAL_NUM_OF_PIECES 13



using namespace std;

class AutoPlayerAlgorithmImp :  public PlayerAlgorithm {
	typedef pair<int, int> pairs;
	set<pairs> s;
	int myPlayerNumber;
	BoardImp myGameBoard;
	int numberOfToolsLeftForOpponent;
	vector<PointImp> myOccupiedPoints;
	vector<PointImp> opponentOccupiedPoints;
	PiecePositionImp randomPiece;
	PiecePositionImp auxPiece;
	unique_ptr<JokerChangeImp> jokerChange;
	bool acuredJokerChange;

	int numOfRocksDestroyedByMe;
	int numOfPapersDestroyedByMe;
	int numOfScissorsDestroyedByMe;
	int numOfBombsDestroyedByMe;
	int numOfFlagsDestroyedByMe;
	int numberOfJokersDestroyedByMe;

	int numberOfRocksOwning;
	int numberOfPapersOwning;
	int numberOfScissorsOwning;
	int numberOfBombsOwning;
	int numberOfJokersOwning;
	int numberOfFlagsOwning;



public:
	explicit AutoPlayerAlgorithmImp(int playerNum);
	void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
	void notifyOnOpponentMove(const Move& move);
	void notifyFightResult(const FightInfo& fightInfo); // called only if there was a fight
	unique_ptr<Move> getMove();
	unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested
	int getRandomPosition();
	char getRandomJokerRep(int player);
	int getRandomNumInRange(int size);
	void decreaseToolFromMyStock(char Piece);
	void increaseDestroyedPieces(char Piece);
	void removePointFromOccupiedPoints(PointImp point);
	void removePointFromOpponentOccupiedPoints(PointImp point);
	bool doIOccupiePoint(int X, int Y);
	bool doOpponentOccupiePoint(int X, int Y);
	bool hasMovingPieces();
	char getStrongJokerRep(int playerNumber, char toolThatOponnentAte);


};
#endif