#ifndef GAME_H_
#define GAME_H_

#include "AutoPlayerAlgorithmImp.h"
#include "FilePlayerAlgorithmImp.h"
#include "BoardImp.h"
#include "gameStatus.h"
#include "Point.h"



#define ROCK 0
#define PAPER 1
#define SCISSORS 2
#define BOMB 3
#define FLAG 4
#define JOKER 5
#define TIE 0
#define WIN 1
#define LOSE 2
#define STRENGTH_TABLE_SIZE 5
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

using namespace std;

const static int numberOfPieaces[] = { NUM_OF_ROCKS, NUM_OF_PAPERS, NUM_OF_SCISSORS, NUM_OF_BOMBS, NUM_OF_FLAGS, NUM_OF_JOKERS };

class Game {
	BoardImp gameBoard;
	Status currentStatus;
	string player1InitFile;
	string player2InitFile;
	string player1MoveFile;
	string player2MoveFile;
	string outFile;
	int piecesToPlace_Player1[NUM_OF_DIFFERENT_PIECES];
	int piecesToPlace_Player2[NUM_OF_DIFFERENT_PIECES];
	int piecesOnBoard_Player1[NUM_OF_DIFFERENT_PIECES];
	int piecesOnBoard_Player2[NUM_OF_DIFFERENT_PIECES];
	vector<unique_ptr<PlayerAlgorithm>> participatingAlgs;
	vector<unique_ptr<PiecePosition>> positionsVectorPlayer1;
	vector<unique_ptr<PiecePosition>> positionsVectorPlayer2;
	int strengthTable[STRENGTH_TABLE_SIZE][STRENGTH_TABLE_SIZE];
	bool gameOver;
public:
	//explicit Game(string firstAlgoType, string secondAlgoType);
	explicit Game(string firstAlgoType, string secondAlgoType, string outputFile, string player1InitFile = " ", string player1MoveFile = " ", string player2InitFile = " ", string player2MoveFile = " ");
	void startGame();
	bool isGameOver();
	void printBoardToFile(ofstream& outputFile) const;
	void fillBoardWithInitialPositions(int playerNumber, vector<unique_ptr<PiecePosition>>& positionsVectorPlayer);
	bool placePiece(int playerNumber, PiecePositionImp Piece, char piece, int lineNum);
	int getNumberOfPiecesLeftToPlace(int playerNumber, char Piece);
	int pieceToNumRep(char Piece);
	void decreasePieceFromStock(int playerNumber, char piece);
	void increasePieceOnBoard(int playerNumber, char piece);

	//bool isGameOver();
};
#endif
