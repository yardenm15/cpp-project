#ifndef GAME_H_
#define GAME_H_

#include "AutoPlayerAlgorithmImp.h"
#include "FilePlayerAlgorithmImp.h"
#include "BoardImp.h"
#include "GameStatus.h"
#include "Point.h"
#include "HelperFunctions.h"
#include "FightInfoImp.h"

#include <map>

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

using std::iterator;
using std::map;
using std::tuple;

const static int numberOfPieaces[] = { NUM_OF_ROCKS, NUM_OF_PAPERS, NUM_OF_SCISSORS, NUM_OF_BOMBS, NUM_OF_FLAGS, NUM_OF_JOKERS };

class Game {
	BoardImp gameBoard;
	GameStatus gameStatus;
	//unique_ptr<Move> move;
	int piecesToPlace_Player1[NUM_OF_DIFFERENT_PIECES];
	int piecesToPlace_Player2[NUM_OF_DIFFERENT_PIECES];
	int piecesOnBoard_Player1[NUM_OF_DIFFERENT_PIECES];
	int piecesOnBoard_Player2[NUM_OF_DIFFERENT_PIECES];
	//vector <unique_ptr<PiecePosition>> jokersOnBoard_Player1;
	//vector <unique_ptr<PiecePosition>> jokersOnBoard_Player2;
	unique_ptr<PlayerAlgorithm> player1Algo;
	unique_ptr<PlayerAlgorithm> player2Algo;
	//int strengthTable[STRENGTH_TABLE_SIZE][STRENGTH_TABLE_SIZE];
public:
	explicit Game(string& firstAlgoType, string& secondAlgoType);
	void startGame();
	void verifyInitialPositionsVector(vector<unique_ptr<PiecePosition>> &vector);
	//bool isGameOver();
	//void printBoardToFile(ofstream& outputFile) const;
	void fillBoardWithInitialPositions(vector<unique_ptr<PiecePosition>>& positionsVectorPlayer1, vector<unique_ptr<PiecePosition>>& positionsVectorPlayer2, vector<unique_ptr<FightInfo>>& fightsVector);
	bool placePiece(PiecePositionImp Piece);
	unique_ptr<FightInfo> makeMove(unique_ptr<Move> move);
	void verifyLegalMove(const PointImp& fromPoint, const PointImp& toPoint);
	//int getNumberOfPiecesLeftToPlace(int playerNumber, char Piece);
	//int pieceToNumRep(char Piece);
	//void decreasePieceFromStock(int playerNumber, char piece);
	//void increasePieceOnBoard(int playerNumber, char piece, PiecePositionImp piecePosition);
	//void fight(PiecePositionImp piecePosition, int attackingPlayerNumber);
	//int getFightResult(int x, int y) const;
	//void decreasePieceFromBoard(int playerNumber, char piece, PiecePositionImp piecePosition);
	//bool checkWinningConditions() const;
	//int flagsLeft(int playerNumber) const;
	//bool doPlayerHasMovablePieces(int playerNumber) const;
	//bool aremovingJokers(int playerNumber) const;
	bool isGameOver();
};
#endif
