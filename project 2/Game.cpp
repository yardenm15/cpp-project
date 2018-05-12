#include "stdafx.h"
#include "Game.h"
#include "MoveImp.h"


Game::Game(string firstAlgoType, string secondAlgoType, string outputFile, string player1InitFile, string player1MoveFile, string player2InitFile, string player2MoveFile) {

	//freedom to choose the input files names
	player1InitFile = player1InitFile;
	player2InitFile = player2InitFile;
	player1MoveFile = player1MoveFile;
	player2MoveFile = player2MoveFile;
	outFile = outputFile;

	gameOver = false;

	if (firstAlgoType.compare("file") && secondAlgoType.compare("file")) {
		participatingAlgs.push_back(std::make_unique<FilePlayerAlgorithmImp>(player1InitFile, player1MoveFile, currentStatus));
		participatingAlgs.push_back(std::make_unique<FilePlayerAlgorithmImp>(player2InitFile, player2MoveFile, currentStatus));

		
	}
	//-------to do: add the other options(file-vs-auto, auto-vs-auto,auto-vs-file)--------

	//fill strength Table: 
	//for example: row-0 col-2 means: i am rock and i win fighting Scissors
	//VICTORY means i eat Flag, DEFEAT means i am flag that got eaten

	//rock:
	strengthTable[ROCK][ROCK] = TIE;
	strengthTable[ROCK][PAPER] = LOSE;
	strengthTable[ROCK][SCISSORS] = WIN;
	strengthTable[ROCK][BOMB] = TIE;
	strengthTable[ROCK][FLAG] = WIN;

	//Paper:
	strengthTable[PAPER][ROCK] = WIN;
	strengthTable[PAPER][PAPER] = TIE;
	strengthTable[PAPER][SCISSORS] = LOSE;
	strengthTable[PAPER][BOMB] = TIE;
	strengthTable[PAPER][FLAG] = WIN;

	//Scissors:
	strengthTable[SCISSORS][ROCK] = LOSE;
	strengthTable[SCISSORS][PAPER] = WIN;
	strengthTable[SCISSORS][SCISSORS] = TIE;
	strengthTable[SCISSORS][BOMB] = TIE;
	strengthTable[SCISSORS][FLAG] = WIN;

	//Bomb:
	strengthTable[BOMB][ROCK] = TIE;
	strengthTable[BOMB][PAPER] = TIE;
	strengthTable[BOMB][SCISSORS] = TIE;
	strengthTable[BOMB][BOMB] = TIE;
	strengthTable[BOMB][FLAG] = TIE;

	//Flag:
	strengthTable[FLAG][ROCK] = LOSE;
	strengthTable[FLAG][PAPER] = LOSE;
	strengthTable[FLAG][SCISSORS] = LOSE;
	strengthTable[FLAG][BOMB] = TIE;
	strengthTable[FLAG][FLAG] = TIE;
}

bool Game::isGameOver() {
	return gameOver;
}

void Game::startGame() {

	ofstream outputFile;
	outputFile.open(outFile);

	while (!isGameOver()) {

		//to do :think about smart way to read moves lines from movesfile and return them one by one with getMove() method

		(*participatingAlgs[0]).getInitialPositions(1, positionsVectorPlayer1);
		(*participatingAlgs[0]).getInitialPositions(2, positionsVectorPlayer2);
		
		//verify valid format of lines in Positions files
		if (currentStatus.getStatus(PLAYER_ONE) != PossibleStatus::Valid || currentStatus.getStatus(PLAYER_TWO) != PossibleStatus::Valid) {
			currentStatus.printStatusToFile(outputFile);

			//-------to do: implement printBoardToFile
			//printBoardToFile(outputFile);
			return;
		}
		
		// fill the board with the Initial Positions

		//implement getMove befor uncomment:
		//unique_ptr<Move> player1Move = (*participatingAlgs[0]).getMove();
		//unique_ptr<Move> player2Move = (*participatingAlgs[1]).getMove();

		//todo: keep filling MoveImp data members and methods to continue iwth check if there was a fight
	}

	

}


