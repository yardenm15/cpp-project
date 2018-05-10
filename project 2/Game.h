#ifndef GAME_H_
#define GAME_H_

#include "AutoPlayerAlgorithmImp.h"
#include "FilePlayerAlgorithmImp.h"
#include "BoardImp.h"
#include "gameStatus.h"



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

using namespace std;

class Game {
	BoardImp board;
	Status currentStatus;
	string player1InitFile;
	string player2InitFile;
	string player1MoveFile;
	string player2MoveFile;
	vector<unique_ptr<PlayerAlgorithm>> participatingAlgs;
	vector<unique_ptr<PiecePosition>> positionsVectorPlayer1;
	vector<unique_ptr<PiecePosition>> positionsVectorPlayer2;
	int strengthTable[STRENGTH_TABLE_SIZE][STRENGTH_TABLE_SIZE];
	bool gameOver;
public:
	//explicit Game(string firstAlgoType, string secondAlgoType);
	explicit Game(string firstAlgoType, string secondAlgoType, string player1InitFile = " ", string player1MoveFile = " ", string player2InitFile = " ", string player2MoveFile = " ");
	void startGame();
	bool isGameOver();
  //	BoardImp getBoard() const { return board; };
	//bool isGameOver();
	//void performInitialPositionsFights(vector<unique_ptr<PiecePosition>> & player1InitialBoard, vector<unique_ptr<PiecePosition>> & player2InitialBoard);
};
#endif
