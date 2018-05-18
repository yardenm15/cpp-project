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
		participatingAlgs.push_back(std::make_unique<FilePlayerAlgorithmImp>(player1InitFile, player1MoveFile, &currentStatus, PLAYER_ONE));
		participatingAlgs.push_back(std::make_unique<FilePlayerAlgorithmImp>(player2InitFile, player2MoveFile, &currentStatus, PLAYER_TWO));

		
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

	(*participatingAlgs[0]).getInitialPositions(1, positionsVectorPlayer1);
	(*participatingAlgs[0]).getInitialPositions(2, positionsVectorPlayer2);

	//verify valid format of lines in Positions files
	if (currentStatus.getStatus(PLAYER_ONE) != PossibleStatus::Valid || currentStatus.getStatus(PLAYER_TWO) != PossibleStatus::Valid) {
		currentStatus.printStatusToFile(outputFile);
		printBoardToFile(outputFile);
		return;
	}

	// fill the board with the Initial Positions
	fillBoardWithInitialPositions(positionsVectorPlayer1, positionsVectorPlayer2);

	//verify no positioning 2 pieces by the same player at the same cell, no using more pieces than a plyer have,
	if (currentStatus.getStatus(PLAYER_ONE) != PossibleStatus::Valid || currentStatus.getStatus(PLAYER_TWO) != PossibleStatus::Valid) {
		currentStatus.printStatusToFile(outputFile);
		printBoardToFile(outputFile);
		return;
	}

	int flagsLeft = getNumberOfPiecesLeftToPlace(PLAYER_ONE, 'F');

	if (flagsLeft > 0) {
		currentStatus.setStatus(PLAYER_ONE, PossibleStatus::input_File_Error);
		cout << "Player " << PLAYER_ONE << " has still " << flagsLeft << " flags to use. Placing all flags is mendatory." << endl;
	}

	flagsLeft = getNumberOfPiecesLeftToPlace(PLAYER_TWO, 'f');

	if (flagsLeft > 0) {
		currentStatus.setStatus(PLAYER_TWO, PossibleStatus::input_File_Error);
		cout << "Player " << PLAYER_TWO << " has still " << flagsLeft << " flags to use. Placing all flags is mendatory." << endl;
	}

	//verify all flags for both players are on the board
	if (currentStatus.getStatus(PLAYER_ONE) != PossibleStatus::Valid && currentStatus.getStatus(PLAYER_ONE) != PossibleStatus::Valid) {
		currentStatus.printStatusToFile(outputFile);
		printBoardToFile(outputFile);
		return;
	}

	if (checkWinningConditions(currentStatus)) {
		currentStatus.printStatusToFile(outputFile);
		printBoardToFile(outputFile);
		return;
	}

	// positioning phase is over, moving phase starts
	currentStatus.setIsPositioningPhase(false);
	
	
	
	FilePlayerAlgorithmImp * d1 = dynamic_cast<FilePlayerAlgorithmImp*>(participatingAlgs[0].get());
	FilePlayerAlgorithmImp * d2 = dynamic_cast<FilePlayerAlgorithmImp*>(participatingAlgs[1].get());

	int numOfMOvesPlayer1 = d1->getMovesVectorSize();
	int numOfMOvesPlayer2 = d2->getMovesVectorSize();


	while (!isGameOver()) {


		
		//implement getMove() and getJokerChange() befor uncomment:
		//unique_ptr<Move> player1Move = (*participatingAlgs[0]).getMove();
		//unique_ptr<Move> player1JokerChange = (*participatingAlgs[0]).getJokerChange();
		//unique_ptr<Move> player2Move = (*participatingAlgs[1]).getMove();
		//unique_ptr<Move> player2JokerChange = (*participatingAlgs[2]).getJokerChange();



		//to do at this point:
		//1.validate the ligality of the moves
		//2. move the pieces above on the board and act correspondingly(fight for example) 
		//3.add calls to notify methods(which does nothing in file vs file case)
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

int Game::flagsLeft(int playerNumber) const {
	if (playerNumber == PLAYER_ONE)
		return piecesOnBoard_Player1[FLAG];
	return piecesOnBoard_Player2[FLAG];
}

bool Game::doPlayerHasMovablePieces(int playerNumber) const {
	if (playerNumber == PLAYER_ONE) {
		if (piecesOnBoard_Player1[ROCK] != 0 || piecesOnBoard_Player1[PAPER] != 0 || piecesOnBoard_Player1[SCISSORS] != 0 || aremovingJokers(playerNumber))
			return true;
	}
	else if (piecesOnBoard_Player2[ROCK] != 0 || piecesOnBoard_Player2[PAPER] != 0 || piecesOnBoard_Player2[SCISSORS] != 0 || aremovingJokers(playerNumber))
		return true;
	return false;
}

bool Game::aremovingJokers(int playerNumber) const {
	if (playerNumber == PLAYER_ONE) {
		for (int i = 0; i < NUM_OF_JOKERS; ++i) {
			if (jokersOnBoard_Player1[i].getJokerRep() == 'R' || jokersOnBoard_Player1[i].getJokerRep() == 'P' || jokersOnBoard_Player1[i].getJokerRep() == 'S')
				return true;
		}
		return false;
	}
	for (int i = 0; i < NUM_OF_JOKERS; ++i) {
		if (jokersOnBoard_Player2[i].getJokerRep() == 'r' || jokersOnBoard_Player2[i].getJokerRep() == 'p' || jokersOnBoard_Player2[i].getJokerRep() == 's')
			return true;
	}
	return false;
}

bool Game::checkWinningConditions(Status& currentStatus) const {
	if (flagsLeft(PLAYER_ONE) == 0 && flagsLeft(PLAYER_TWO) == 0) {
		currentStatus.setStatus(PLAYER_ONE, PossibleStatus::All_Flags_Captured);
		currentStatus.setStatus(PLAYER_TWO, PossibleStatus::All_Flags_Captured);
		return true;
	}
	else if (doPlayerHasMovablePieces(PLAYER_ONE) == false && doPlayerHasMovablePieces(PLAYER_TWO) == false) {
		currentStatus.setStatus(PLAYER_ONE, PossibleStatus::Out_Of_Moving_Pieces);
		currentStatus.setStatus(PLAYER_TWO, PossibleStatus::Out_Of_Moving_Pieces);
		return true;
	}

	else if (doPlayerHasMovablePieces(PLAYER_ONE) == false) {
		currentStatus.setStatus(PLAYER_ONE, PossibleStatus::Out_Of_Moving_Pieces);
		return true;
	}
	else if (flagsLeft(PLAYER_ONE) == 0) {
		currentStatus.setStatus(PLAYER_ONE, PossibleStatus::All_Flags_Captured);
		return true;
	}
	else if (doPlayerHasMovablePieces(PLAYER_TWO) == false) {
		currentStatus.setStatus(PLAYER_TWO, PossibleStatus::Out_Of_Moving_Pieces);
		return true;
	}
	else if (flagsLeft(PLAYER_TWO) == 0) {
		currentStatus.setStatus(PLAYER_TWO, PossibleStatus::All_Flags_Captured);
		return true;
	}
	return false;
}

void Game::fillBoardWithInitialPositions(vector<unique_ptr<PiecePosition>>& positionsVectorPlayer1, vector<unique_ptr<PiecePosition>>& positionsVectorPlayer2){
	
	;
	size_t firstVectorSize = positionsVectorPlayer1.size();
	size_t secondtVectorSize = positionsVectorPlayer2.size();
	int numOfSamallestVector = 1 ? 2 : firstVectorSize < secondtVectorSize;
	size_t samallestVectorSize = firstVectorSize ? secondtVectorSize : firstVectorSize < secondtVectorSize;
	size_t longestVectorSize = firstVectorSize ? secondtVectorSize : firstVectorSize > secondtVectorSize;
	size_t lineNum = 0;
	PiecePositionImp *pieceOfPlayer1 = dynamic_cast<PiecePositionImp*>(positionsVectorPlayer1[(int)lineNum].get());
	PiecePositionImp *pieceOfPlayer2 = dynamic_cast<PiecePositionImp*>(positionsVectorPlayer2[(int)lineNum].get());
	
	//placing simultaneously
	for (; lineNum < samallestVectorSize; ++lineNum) {
		
		placePiece(PLAYER_ONE, *pieceOfPlayer1, positionsVectorPlayer1[lineNum].get()->getPiece(), lineNum);
		placePiece(PLAYER_TWO, *pieceOfPlayer2, positionsVectorPlayer2[lineNum].get()->getPiece(), lineNum);
	}
	//keep placing the leftovers of the longest vector
	if (firstVectorSize != secondtVectorSize) {
		for (size_t line = lineNum; line < longestVectorSize; ++line) {
			if(numOfSamallestVector ==1)
				placePiece(PLAYER_TWO, *pieceOfPlayer2, positionsVectorPlayer2[line].get()->getPiece(), line);
			else
				placePiece(PLAYER_ONE, *pieceOfPlayer1, positionsVectorPlayer1[line].get()->getPiece(), line);
		}

	}
}

//------------to do finish implementation( update the cell and fight case)-----------
bool Game::placePiece(int playerNumber, PiecePositionImp piecePosition, char piece, int lineNumber) {

	//empty valid cell
	if (gameBoard.getBoard()[piecePosition.getPosition().getX()-1][piecePosition.getPosition().getY()-1].getOwner() == NO_PLAYER) {
		if (getNumberOfPiecesLeftToPlace(playerNumber, piece) > 0) {
			decreasePieceFromStock(playerNumber, piece);//reduce 1 piece left for player
			increasePieceOnBoard(playerNumber, piece, piecePosition);//increase 1 piece on board for player
			
			//update the cell
			gameBoard.setCell(piecePosition.getPosition().getX(), piecePosition.getPosition().getY(), piecePosition.getOwner(), piecePosition.getPiece(), piecePosition.getJokerRep());
			return true;
		}
		else {
			cout << "Player " << playerNumber << " had no more " << piece << " pieces at line " << lineNumber + 1 << ":" << endl;
			currentStatus.setStatus(playerNumber, PossibleStatus::input_File_Error, piecePosition.getPosition().getX());
			return false;
		}


	}
	//illegal - same place piece
	else if (gameBoard.getBoard()[piecePosition.getPosition().getX()-1][piecePosition.getPosition().getY()-1].getOwner() == playerNumber) {
		cout << "Player " << playerNumber << " tried to place a " << piece << " in line " << lineNumber + 1 << ":" << endl \
			<< "where he already placed there a  piece before." << endl;
		currentStatus.setStatus(playerNumber, PossibleStatus::input_File_Error, lineNumber + 1);
		return false;
	}
	//legal place - fight
	else {
		decreasePieceFromStock(playerNumber, piece);//reduce 1 piece from stock
		increasePieceOnBoard(playerNumber, piece, piecePosition);//increase 1 piece on board
		fight(piecePosition, playerNumber);
		return true;
	}
		

}

void Game::fight(PiecePositionImp piecePosition, int attackingPlayerNumber) {
	
	int defendingPlayerNumber = 1 ? 2 : attackingPlayerNumber == 2;
	int x = piecePosition.getPosition().getX();
	int y = piecePosition.getPosition().getY();

	char attackingPiece = piecePosition.getPiece();
	char attackingPieceJokerRep = piecePosition.getJokerRep();
	//in case joker, actuallAttackingPieceRep holds the "real" representation 
	char actuallAttackingPieceRep = attackingPiece ? attackingPieceJokerRep : attackingPieceJokerRep == '#';
	char defendingPiece = gameBoard.getBoard()[x - 1][y - 1].getPiece();
	char defendingPieceJokerRep = gameBoard.getBoard()[x - 1][y - 1].getJokerRep();
	char actuallDefendingPieceRep = defendingPiece ? defendingPieceJokerRep : defendingPieceJokerRep == '#';
	int battleResult = getFightResult(pieceToNumRep(actuallAttackingPieceRep), pieceToNumRep(actuallDefendingPieceRep));

	//case player initiates fight wins
	if (battleResult == WIN) {
		decreasePieceFromBoard(defendingPlayerNumber, actuallDefendingPieceRep, gameBoard.getBoard()[x - 1][y - 1]);
		//uptade cell with the Attacking player's details
		gameBoard.setCell(x, y, piecePosition.getOwner(), piecePosition.getPiece(), piecePosition.getJokerRep());

	}

	//case player initiates fight loses
	else if (battleResult == LOSE) {
		//decrease the number of pieces Attacking player has on board
		decreasePieceFromBoard(attackingPlayerNumber, actuallAttackingPieceRep, piecePosition);
	}

	//case of tie
	else if (battleResult == TIE) {
		//remove pieces for both players and initialize cell to be empty
		gameBoard.setCell(x, y, NO_PLAYER, ' ', ' ');
		decreasePieceFromBoard(attackingPlayerNumber, attackingPiece, piecePosition);
		decreasePieceFromBoard(defendingPlayerNumber, defendingPiece, gameBoard.getBoard()[x - 1][y - 1]);
	}
}

void Game::decreasePieceFromBoard(int playerNumber, char piece, PiecePositionImp piecePosition) {
	if (playerNumber == PLAYER_ONE) {
		if (piece == 'J') {
			for (int i = 0; i < NUM_OF_JOKERS; ++i)
				if (jokersOnBoard_Player1[i].getPosition().getX() == piecePosition.getPosition().getX() && jokersOnBoard_Player1[i].getPosition().getY() == piecePosition.getPosition().getY()) {
					jokersOnBoard_Player1[i].setJokerRep('#');// same as deleted
				}
		}
		piecesOnBoard_Player1[pieceToNumRep(piece)] -= 1;
	}
	else {
		if (piece == 'j') {
			for (int i = 0; i < NUM_OF_JOKERS; ++i)
				if (jokersOnBoard_Player2[i].getPosition().getX() == piecePosition.getPosition().getX() && jokersOnBoard_Player2[i].getPosition().getY() == piecePosition.getPosition().getY()) {
					jokersOnBoard_Player2[i].setJokerRep('#');
				}
		}
		piecesOnBoard_Player2[pieceToNumRep(piece)] -= 1;
	}

}

int Game::getNumberOfPiecesLeftToPlace(int playerNumber, char Piece) {
	if (playerNumber == 1) 
		return piecesToPlace_Player1[pieceToNumRep(Piece)];
	return piecesToPlace_Player2[pieceToNumRep(Piece)];
			
}

int Game::getFightResult(int x, int y) const {
	return strengthTable[x][y];
}

int Game::pieceToNumRep(char Piece) {
	if (Piece == 'R' || Piece == 'r')
		return ROCK;
	else if (Piece == 'P' || Piece == 'p')
		return PAPER;
	else if (Piece == 'S' || Piece == 's')
		return SCISSORS;
	else if (Piece == 'B' || Piece == 'b')
		return BOMB;
	else if (Piece == 'F' || Piece == 'f')
		return FLAG;
	return JOKER;
}

void Game::decreasePieceFromStock(int playerNumber, char piece) {
	if (playerNumber == PLAYER_ONE) 
		piecesToPlace_Player1[pieceToNumRep(piece)] -= 1;
	else
		piecesToPlace_Player2[pieceToNumRep(piece)] -= 1;

}

void Game::increasePieceOnBoard(int playerNumber, char piece, PiecePositionImp piecePosition) {

	if (playerNumber == PLAYER_ONE) {
		if (piece == 'J') {
			jokersOnBoard_Player1.push_back(piecePosition);
		}
		piecesOnBoard_Player1[pieceToNumRep(piece)] += 1;
	}
	else {
		if (piece == 'j') {
			jokersOnBoard_Player2.push_back(piecePosition);
		}
		piecesOnBoard_Player2[pieceToNumRep(piece)] += 1;
	}
}



