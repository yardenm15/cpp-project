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

	//initialize number of pieces each player has
	for (int i = 0; i < NUM_OF_DIFFERENT_PIECES; ++i) {
		piecesToPlace_Player1[i] = numberOfPieaces[i];
		piecesToPlace_Player2[i] = numberOfPieaces[i];
	}
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
			printBoardToFile(outputFile);
			return;
		}
		
		// fill the board with the Initial Positions
		fillBoardWithInitialPositions(PLAYER_ONE, positionsVectorPlayer1);
		fillBoardWithInitialPositions(PLAYER_TWO, positionsVectorPlayer2);

		//implement getMove befor uncomment:
		//unique_ptr<Move> player1Move = (*participatingAlgs[0]).getMove();
		//unique_ptr<Move> player2Move = (*participatingAlgs[1]).getMove();

		//todo: keep filling MoveImp data members and methods to continue iwth check if there was a fight
	}

	

}

void Game::printBoardToFile(ofstream& outputFile) const {
	char chr = ' ';
	for (int i = 0; i < NUM_OF_ROWS; ++i) {
		for (int j = 0; j < NUM_OF_COLS; ++j) {
			//chr = gameBoard.getBoard().at(i).at(j).getPiece();
			outputFile << gameBoard.getBoard()[i][j].getPiece();
		}
		outputFile << endl;
	}
}

void Game::fillBoardWithInitialPositions(int playerNumber, vector<unique_ptr<PiecePosition>>& positionsVector) {
	
	size_t size = positionsVector.size();
	
	for (size_t lineNum = 0; lineNum < size; ++lineNum) {
		PointImp *derivedPointer = dynamic_cast<PointImp*>(positionsVector[(int)lineNum].get());
		placePiece(playerNumber, derivedPointer->getX(), derivedPointer->getY(), positionsVector[lineNum].get()->getPiece(), lineNum);
	}
}

//------------to do finish implementation-----------
void Game::placePiece(int playerNumber, int x, int y, char piece, int lineNumber) {

	//empty valid cell
	if (gameBoard.getBoard()[x][y].getOwner() == NO_PLAYER) {
		/*
		//player has pieces left
		if (getNumberOfPiecesLeftToPlace(playerNumber, p) > 0) {
			decreasePieceFromStock(playerNumber, p);//reduce 1 piece left for player
			increasePieceOnBoard(playerNumber, p);//increase 1 piece on board for player
			fromCell.setCell(p, playerNumber);
			return true;
		}
		//illegal - out of pieces
		else {
			cout << "Player " << playerNumber << " had no more " << p << " pieces at line " << lineNumber + 1 << ":" << endl \
				<< line << endl;
			currentStatus.setStatus(playerNumber, PossibleStatus::input_File_Error, fromRow, line);
			return false;
		}
	}
	//illegal - same place piece
	else if (fromCell.getPlayerOwning() == playerNumber) {
		cout << "Player " << playerNumber << " tried to place a " << p << " in line " << lineNumber + 1 << ":" << endl \
			<< line << endl \
			<< "where he already placed there a " << fromCell.getCellPiece() << " before." << endl;
		currentStatus.setStatus(playerNumber, PossibleStatus::input_File_Error, lineNumber + 1, line);
		return false;
	}
	//legal place - fight
	else {
		decreasePieceFromStock(playerNumber, p);//reduce 1 piece from stock
		increasePieceOnBoard(playerNumber, p);//increase 1 piece on board
		fight(fromRow, fromColumn, p, playerNumber);
		return true;
	}*/

	}
}



