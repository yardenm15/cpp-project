#include "Game.h"
#include "MoveImp.h"

int main(int argc, char* argv[]) {
	if (!verifyCommandLineArguments(argc, argv))
		return EXIT_FAILURE;
	string firstAlgoType = argv[1];
	firstAlgoType = firstAlgoType.substr(0, 4);
	string secondAlgoType = argv[1];
	secondAlgoType = secondAlgoType.substr(8, 12);
	Game game(firstAlgoType, secondAlgoType);
	game.startGame();
	return EXIT_SUCCESS;
}

Game::Game(string& firstAlgoType, string& secondAlgoType) {

	bool isPlayer1File = true;
	bool isPlayer2File = true;

	//initialize players algorithms
	if (firstAlgoType == "file")
		player1Algo = make_unique<FilePlayerAlgorithmImp>();
	else { //auto
		player1Algo = make_unique<AutoPlayerAlgorithmImp>(PLAYER_1);
		isPlayer1File = false;
	}

	if (secondAlgoType == "file")
		player2Algo = make_unique<FilePlayerAlgorithmImp>();
	else { //auto
		player2Algo = make_unique<AutoPlayerAlgorithmImp>(PLAYER_2);
		isPlayer2File = false;
	}

	//initialize number of pieces each player has
	for (int i = 0; i < NUM_OF_DIFFERENT_PIECES; ++i) {
		piecesToPlace_Player1[i] = numberOfPieaces[i];
		piecesToPlace_Player2[i] = numberOfPieaces[i];
	}

}

//TODO: write the function
bool Game::isGameOver() {
	return !((gameStatus.getGameStatus(PLAYER_1) == PossibleStatus::Valid) && (gameStatus.getGameStatus(PLAYER_2) == PossibleStatus::Valid));
}

//TODO: write the function
void Game::verifyInitialPositionsVector(vector<unique_ptr<PiecePosition>> &vector) {
	cout << typeid(player1Algo.get()).name();
}

//TODO: write the function
void Game::verifyLegalMove(const PointImp& fromPoint, const PointImp& toPoint) {

}

unique_ptr<FightInfo> Game::makeMove(unique_ptr<Move> move) {
	const PointImp fromPoint = dynamic_cast<const PointImp&>(move->getFrom());
	const PointImp toPoint = dynamic_cast<const PointImp&>(move->getTo());
	verifyLegalMove(fromPoint, toPoint);
	//move is legal at this point
	PiecePositionImp& fromPiece = dynamic_cast<PiecePositionImp&>(*gameBoard.getBoardReg()[fromPoint.getX()][fromPoint.getY()]);
	PiecePositionImp& toPiece = dynamic_cast<PiecePositionImp&>(*gameBoard.getBoardReg()[toPoint.getX()][toPoint.getY()]);
	//TODO: continue from here
	if (toPiece.getOwner() != NO_PLAYER)
		return nullptr;
	return nullptr;
}

void Game::startGame() {

	vector<unique_ptr<PiecePosition>> positionsVectorPlayer1;
	vector<unique_ptr<PiecePosition>> positionsVectorPlayer2;

	//get initial positions from both players
	player1Algo->getInitialPositions(PLAYER_1, positionsVectorPlayer1);
	player2Algo->getInitialPositions(PLAYER_2, positionsVectorPlayer2);

	//verify game is valid so far TODO:handle errors properly
	if (isGameOver() == true)
		return;

	//verify valid positions 
	verifyInitialPositionsVector(positionsVectorPlayer1);
	verifyInitialPositionsVector(positionsVectorPlayer2);

	//verify game is valid so far TODO:write gameover properly
	if (isGameOver() == true)
		return;

	//by here 2 positions vectors are valid.

	//fill the board with the initial positions
	vector<unique_ptr<FightInfo>> fightsVector;
	fillBoardWithInitialPositions(positionsVectorPlayer1, positionsVectorPlayer2, fightsVector);

	//notify players of board and fights
	player1Algo->notifyOnInitialBoard(gameBoard, fightsVector);
	player2Algo->notifyOnInitialBoard(gameBoard, fightsVector);

	////verify no positioning 2 pieces by the same player at the same cell, no using more pieces than a plyer have,
	//if (gamestatus.getgamestatus(player_one) != possiblestatus::valid || gamestatus.getgamestatus(player_two) != possiblestatus::valid) {
	//	gamestatus.printgamestatustofile(outputfile);
	//	printboardtofile(outputfile);
	//	return;
	//}

	//open output file
	ofstream outputFile("rps.output");

	unique_ptr<Move> move = player1Algo->getMove();
	unique_ptr<JokerChange> jokerChange = player1Algo->getJokerChange();
	//player1Algo->notifyFightResult();

	//int flagsLeft = getNumberOfPiecesLeftToPlace(PLAYER_ONE, 'F');

	//if (flagsLeft > 0) {
	//	gameStatus.setGameStatus(PLAYER_ONE, PossibleStatus::input_File_Error);
	//	cout << "Player " << PLAYER_ONE << " has still " << flagsLeft << " flags to use. Placing all flags is mendatory." << endl;
	//}

	//flagsLeft = getNumberOfPiecesLeftToPlace(PLAYER_TWO, 'f');

	//if (flagsLeft > 0) {
	//	gameStatus.setGameStatus(PLAYER_TWO, PossibleStatus::input_File_Error);
	//	cout << "Player " << PLAYER_TWO << " has still " << flagsLeft << " flags to use. Placing all flags is mendatory." << endl;
	//}

	////verify all flags for both players are on the board
	//if (gameStatus.getGameStatus(PLAYER_ONE) != PossibleStatus::Valid && gameStatus.getGameStatus(PLAYER_ONE) != PossibleStatus::Valid) {
	//	gameStatus.printGameStatusToFile(outputFile);
	//	printBoardToFile(outputFile);
	//	return;
	//}

	//if (checkWinningConditions()) {
	//	gameStatus.printGameStatusToFile(outputFile);
	//	printBoardToFile(outputFile);
	//	return;
	//}

	//// positioning phase is over, moving phase starts
	//gameStatus.setIsPositioningPhase(false);



	//FilePlayerAlgorithmImp * d1 = dynamic_cast<FilePlayerAlgorithmImp*>(player1Alg);
	//FilePlayerAlgorithmImp * d2 = dynamic_cast<FilePlayerAlgorithmImp*>(player2Alg);

	//int numOfMOvesPlayer1 = d1->getMovesVectorSize();
	//int numOfMOvesPlayer2 = d2->getMovesVectorSize();


	//while (!isGameOver()) {



		//implement getMove() and getJokerChange() befor uncomment:
		//unique_ptr<Move> player1Move = (*participatingAlgs[0]).getMove();
		//unique_ptr<Move> player1JokerChange = (*participatingAlgs[0]).getJokerChange();
		//unique_ptr<Move> player2Move = (*participatingAlgs[1]).getMove();
		//unique_ptr<Move> player2JokerChange = (*participatingAlgs[2]).getJokerChange();



		//to do at this point:
		//1.validate the ligality of the moves
		//2. move the pieces above on the board and act correspondingly(fight for example) 
		//3.add calls to notify methods(which does nothing in file vs file case)
	//}



}

//void Game::printBoardToFile(ofstream& outputFile) const {
//	char chr = ' ';
//	for (int i = 0; i < NUM_OF_ROWS; ++i) {
//		for (int j = 0; j < NUM_OF_COLS; ++j) {
//			//chr = gameBoard.getBoard().at(i).at(j).getPiece();
//			outputFile << gameBoard.getBoard()[i][j].getPiece();
//		}
//		outputFile << endl;
//	}
//}

//int Game::flagsLeft(int playerNumber) const {
//	if (playerNumber == PLAYER_ONE)
//		return piecesOnBoard_Player1[FLAG];
//	return piecesOnBoard_Player2[FLAG];
//}

//bool Game::doPlayerHasMovablePieces(int playerNumber) const {
//	if (playerNumber == PLAYER_ONE) {
//		if (piecesOnBoard_Player1[ROCK] != 0 || piecesOnBoard_Player1[PAPER] != 0 || piecesOnBoard_Player1[SCISSORS] != 0 || aremovingJokers(playerNumber))
//			return true;
//	}
//	else if (piecesOnBoard_Player2[ROCK] != 0 || piecesOnBoard_Player2[PAPER] != 0 || piecesOnBoard_Player2[SCISSORS] != 0 || aremovingJokers(playerNumber))
//		return true;
//	return false;
//}

//bool Game::aremovingJokers(int playerNumber) const {
//	if (playerNumber == PLAYER_ONE) {
//		for (int i = 0; i < NUM_OF_JOKERS; ++i) {
//			//if (jokersOnBoard_Player1[i].getJokerRep() == 'R' || jokersOnBoard_Player1[i].getJokerRep() == 'P' || jokersOnBoard_Player1[i].getJokerRep() == 'S')
//				return true;
//		}
//		return false;
//	}
//	for (int i = 0; i < NUM_OF_JOKERS; ++i) {
//		//if (jokersOnBoard_Player2[i].getJokerRep() == 'r' || jokersOnBoard_Player2[i].getJokerRep() == 'p' || jokersOnBoard_Player2[i].getJokerRep() == 's')
//			return true;
//	}
//	return false;
//}

//bool Game::checkWinningConditions() const {
	//if (flagsLeft(PLAYER_ONE) == 0 && flagsLeft(PLAYER_TWO) == 0) {
	//	gameStatus.setGameStatus(PLAYER_ONE, PossibleStatus::All_Flags_Captured);
	//	gameStatus.setGameStatus(PLAYER_TWO, PossibleStatus::All_Flags_Captured);
	//	return true;
	//}
	//else if (doPlayerHasMovablePieces(PLAYER_ONE) == false && doPlayerHasMovablePieces(PLAYER_TWO) == false) {
	//	gameStatus.setGameStatus(PLAYER_ONE, PossibleStatus::Out_Of_Moving_Pieces);
	//	gameStatus.setGameStatus(PLAYER_TWO, PossibleStatus::Out_Of_Moving_Pieces);
	//	return true;
	//}

	//else if (doPlayerHasMovablePieces(PLAYER_ONE) == false) {
	//	gameStatus.setGameStatus(PLAYER_ONE, PossibleStatus::Out_Of_Moving_Pieces);
	//	return true;
	//}
	//else if (flagsLeft(PLAYER_ONE) == 0) {
	//	gameStatus.setGameStatus(PLAYER_ONE, PossibleStatus::All_Flags_Captured);
	//	return true;
	//}
	//else if (doPlayerHasMovablePieces(PLAYER_TWO) == false) {
	//	gameStatus.setGameStatus(PLAYER_TWO, PossibleStatus::Out_Of_Moving_Pieces);
	//	return true;
	//}
	//else if (flagsLeft(PLAYER_TWO) == 0) {
	//	gameStatus.setGameStatus(PLAYER_TWO, PossibleStatus::All_Flags_Captured);
	//	return true;
	//}
//	return false;
//}

void Game::fillBoardWithInitialPositions(vector<unique_ptr<PiecePosition>>& positionsVectorPlayer1, vector<unique_ptr<PiecePosition>>& positionsVectorPlayer2, vector<unique_ptr<FightInfo>>& fightsVector) {

	size_t firstVectorSize = positionsVectorPlayer1.size();
	size_t secondVectorSize = positionsVectorPlayer2.size();
	tuple<int, int> tempTuple;
	map<tuple<int, int>, unique_ptr<PiecePosition>> myMap;

	//fill map with first vector
	for (size_t i = 0; i < firstVectorSize; ++i) {
		tempTuple = make_tuple(positionsVectorPlayer1[i]->getPosition().getX(), positionsVectorPlayer1[i]->getPosition().getY());
		myMap[tempTuple] = move(positionsVectorPlayer1[i]);
	}

	//fill map with second vector while resolving fights
	for (size_t i = 0; i < secondVectorSize; ++i) {
		tempTuple = make_tuple(positionsVectorPlayer2[i]->getPosition().getX(), positionsVectorPlayer2[i]->getPosition().getY());
		auto search = myMap.find(tempTuple);
		//fight occurs
		if (search != myMap.end()) {
			fightsVector.push_back(make_unique<FightInfoImp>(*myMap[tempTuple].release(), *positionsVectorPlayer2[i].release()));
			myMap.erase(tempTuple);
		}
		//no fight - add to map
		else {
			myMap[tempTuple] = move(positionsVectorPlayer2[i]);
		}
	}

	//fill board from fights vector
	for (size_t i = 0; i < fightsVector.size(); ++i) {
		PiecePositionImp piecePositionImp;
		FightInfoImp& fightInfoImpRef = dynamic_cast<FightInfoImp&>(*fightsVector[i]);
		if (fightsVector[i]->getWinner() == PLAYER_1) {
			piecePositionImp.setOwner(PLAYER_1);
			piecePositionImp.setPiece(fightsVector[i]->getPiece(PLAYER_1));
		}
		else {//player 2 is winner
			piecePositionImp.setOwner(PLAYER_2);
			piecePositionImp.setPiece(fightsVector[i]->getPiece(PLAYER_2));
		}
		piecePositionImp.setPosition(fightsVector[i]->getPosition().getX(), fightsVector[i]->getPosition().getY());
		piecePositionImp.setJokerRep(fightInfoImpRef.getJokerRep());
		gameBoard.getBoardReg()[fightsVector[i]->getPosition().getX() - 1][fightsVector[i]->getPosition().getY() - 1] = make_shared<PiecePositionImp>(piecePositionImp);
	}

	//fill board from map
	for (map<tuple<int, int>, unique_ptr<PiecePosition>>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
		PiecePositionImp& piecePositionImpRef = dynamic_cast<PiecePositionImp&>(*(it->second));
		gameBoard.getBoardReg()[get<0>(it->first) - 1][get<1>(it->first) - 1] = make_shared<PiecePositionImp>(piecePositionImpRef);
	}

}

bool Game::placePiece(PiecePositionImp piece) {

	//empty valid cell
	//if (gameBoard.getBoard()[piecePosition.getPosition().getX()][piecePosition.getPosition().getY()].getOwner() == NO_PLAYER) {
	//	if (getNumberOfPiecesLeftToPlace(playerNumber, piece) > 0) {
	//		decreasePieceFromStock(playerNumber, piece);//reduce 1 piece left for player
	//		increasePieceOnBoard(playerNumber, piece, piecePosition);//increase 1 piece on board for player

	//		//update the cell
	//		gameBoard.setCell(piecePosition.getPosition().getX(), piecePosition.getPosition().getY(), piecePosition.getOwner(), piecePosition.getPiece(), piecePosition.getJokerRep());
	//		return true;
	//	}
	//	else {
	//		cout << "Player " << playerNumber << " had no more " << piece << " pieces at line " << lineNumber + 1 << ":" << endl;
	//		gameStatus.setGameStatus(playerNumber, PossibleStatus::input_File_Error, piecePosition.getPosition().getX());
	//		return false;
	//	}


	//}
	////illegal - same place piece
	//else if (gameBoard.getBoard()[piecePosition.getPosition().getX() - 1][piecePosition.getPosition().getY() - 1].getOwner() == playerNumber) {
	//	cout << "Player " << playerNumber << " tried to place a " << piece << " in line " << lineNumber + 1 << ":" << endl \
	//		<< "where he already placed there a  piece before." << endl;
	//	gameStatus.setGameStatus(playerNumber, PossibleStatus::input_File_Error, lineNumber + 1);
	//	return false;
	//}
	////legal place - fight
	//else {
	//	decreasePieceFromStock(playerNumber, piece);//reduce 1 piece from stock
	//	increasePieceOnBoard(playerNumber, piece, piecePosition);//increase 1 piece on board
	//	fight(piecePosition, playerNumber);
	//	return true;
	//}

	return true;
}

//void Game::fight(PiecePositionImp piecePosition, int attackingPlayerNumber) {
//
//	int defendingPlayerNumber = 1 ? 2 : attackingPlayerNumber == 2;
//	int x = piecePosition.getPosition().getX();
//	int y = piecePosition.getPosition().getY();
//
//	char attackingPiece = piecePosition.getPiece();
//	char attackingPieceJokerRep = piecePosition.getJokerRep();
//	//in case joker, actuallAttackingPieceRep holds the "real" representation 
//	char actuallAttackingPieceRep = attackingPiece ? attackingPieceJokerRep : attackingPieceJokerRep == '#';
//	char defendingPiece = gameBoard.getBoard()[x - 1][y - 1].getPiece();
//	char defendingPieceJokerRep = gameBoard.getBoard()[x - 1][y - 1].getJokerRep();
//	char actuallDefendingPieceRep = defendingPiece ? defendingPieceJokerRep : defendingPieceJokerRep == '#';
//	int battleResult = getFightResult(pieceToNumRep(actuallAttackingPieceRep), pieceToNumRep(actuallDefendingPieceRep));
//
//	//case player initiates fight wins
//	if (battleResult == WIN) {
//		decreasePieceFromBoard(defendingPlayerNumber, actuallDefendingPieceRep, gameBoard.getBoard()[x - 1][y - 1]);
//		//uptade cell with the Attacking player's details
//		gameBoard.setCell(x, y, piecePosition.getOwner(), piecePosition.getPiece(), piecePosition.getJokerRep());
//
//	}

	//case player initiates fight loses
//	else if (battleResult == LOSE) {
//		//decrease the number of pieces Attacking player has on board
//		decreasePieceFromBoard(attackingPlayerNumber, actuallAttackingPieceRep, piecePosition);
//	}
//
//	//case of tie
//	else if (battleResult == TIE) {
//		//remove pieces for both players and initialize cell to be empty
//		gameBoard.setCell(x, y, NO_PLAYER, ' ', ' ');
//		decreasePieceFromBoard(attackingPlayerNumber, attackingPiece, piecePosition);
//		decreasePieceFromBoard(defendingPlayerNumber, defendingPiece, gameBoard.getBoard()[x - 1][y - 1]);
//	}
//}

//void Game::decreasePieceFromBoard(int playerNumber, char piece, PiecePositionImp piecePosition) {
//	if (playerNumber == PLAYER_ONE) {
//		if (piece == 'J') {
//			for (int i = 0; i < NUM_OF_JOKERS; ++i)
//				if (jokersOnBoard_Player1[i].get()->getPosition().getX() == piecePosition.getPosition().getX() && jokersOnBoard_Player1[i].get()->getPosition().getY() == piecePosition.getPosition().getY()) {
//					//jokersOnBoard_Player1[i].setJokerRep('#');// same as deleted
//				}
//		}
//		piecesOnBoard_Player1[pieceToNumRep(piece)] -= 1;
//	}
//	else {
//		if (piece == 'j') {
//			for (int i = 0; i < NUM_OF_JOKERS; ++i)
//				if (jokersOnBoard_Player2[i].get()->getPosition().getX() == piecePosition.getPosition().getX() && jokersOnBoard_Player2[i].get()->getPosition().getY() == piecePosition.getPosition().getY()) {
//					//jokersOnBoard_Player2[i].setJokerRep('#');
//				}
//		}
//		piecesOnBoard_Player2[pieceToNumRep(piece)] -= 1;
//	}
//
//}

//int Game::getNumberOfPiecesLeftToPlace(int playerNumber, char Piece) {
//	if (playerNumber == 1)
//		return piecesToPlace_Player1[pieceToNumRep(Piece)];
//	return piecesToPlace_Player2[pieceToNumRep(Piece)];
//
//}
//
//int Game::getFightResult(int x, int y) const {
//	return strengthTable[x][y];
//}
//
//int Game::pieceToNumRep(char Piece) {
//	if (Piece == 'R' || Piece == 'r')
//		return ROCK;
//	else if (Piece == 'P' || Piece == 'p')
//		return PAPER;
//	else if (Piece == 'S' || Piece == 's')
//		return SCISSORS;
//	else if (Piece == 'B' || Piece == 'b')
//		return BOMB;
//	else if (Piece == 'F' || Piece == 'f')
//		return FLAG;
//	return JOKER;
//}
//
//void Game::decreasePieceFromStock(int playerNumber, char piece) {
//	if (playerNumber == PLAYER_ONE)
//		piecesToPlace_Player1[pieceToNumRep(piece)] -= 1;
//	else
//		piecesToPlace_Player2[pieceToNumRep(piece)] -= 1;
//
//}
//
//void Game::increasePieceOnBoard(int playerNumber, char piece, PiecePositionImp piecePosition) {
//
//	if (playerNumber == PLAYER_ONE) {
//		if (piece == 'J') {
//			//jokersOnBoard_Player1.emplace_back(piecePosition);
//		}
//		piecesOnBoard_Player1[pieceToNumRep(piece)] += 1;
//	}
//	else {
//		if (piece == 'j') {
//			//jokersOnBoard_Player2.emplace_back(piecePosition);
//		}
//		piecesOnBoard_Player2[pieceToNumRep(piece)] += 1;
//	}
//}



