#include "AutoPlayerAlgorithmImp.h"

AutoPlayerAlgorithmImp::AutoPlayerAlgorithmImp(int playerNum) {
	myPlayerNumber = playerNum;
	numberOfToolsLeftForOpponent = 0;
	numberOfRocksOwning = NUM_OF_ROCKS;
	numberOfPapersOwning = NUM_OF_PAPERS;
	numberOfScissorsOwning = NUM_OF_SCISSORS;
	numberOfBombsOwning = NUM_OF_BOMBS;
	numberOfJokersOwning = NUM_OF_JOKERS;
	numberOfFlagsOwning = NUM_OF_FLAGS;

	acuredJokerChange = false;

	numOfRocksDestroyedByMe=0;
	numOfPapersDestroyedByMe=0;
	numOfScissorsDestroyedByMe=0;
	numOfBombsDestroyedByMe=0;
	numOfFlagsDestroyedByMe=0;
	numberOfJokersDestroyedByMe=0;

	int x, y;

	for (int i = 0; i < NUM_OF_ROWS; ++i) {
		for (int j = 0; j < NUM_OF_COLS; ++j) {
			x = i + 1;
			y = j + 1;
			myGameBoard.setCell(x, y, NO_PLAYER, '#', '#');
		}
	}

}

void AutoPlayerAlgorithmImp::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){
	

	//Positioning flags
	for (int i = 0; i < NUM_OF_FLAGS; ++i) {
		int x, y;
		PiecePositionImp Piece;
		Piece.setOwner(player);
		Piece.setJokerRep('#');
		if (player == PLAYER_ONE)
			Piece.setPiece('F');
		else
			Piece.setPiece('f');
		x = getRandomPosition();
		y = getRandomPosition();
		pairs p;
		p.first = x;
		p.second = y;
		const bool is_in = s.find(p) != s.end();
		//loop until we get empty Position( have not placed Piece at this point) 
		while (is_in) {
			x = getRandomPosition();
			y = getRandomPosition();
			pairs p;
			p.first = x;
			p.second = y;
			const bool is_in = s.find(p) != s.end();

		}
		s.insert(p);
		Piece.setPosition(x, y);
		vectorToFill.push_back(std::make_unique<PiecePositionImp>(Piece));
		//update algo's board
		myGameBoard.setCell(x, y, player, Piece.getPiece(), '#');
		PointImp point;
		point.setX(x);
		point.setX(y);
		//update Occupied Points
		myOccupiedPoints.push_back(point);
	}

	//Positioning BOMBS
	for (int i = 0; i < NUM_OF_BOMBS; ++i) {
		int x, y;
		PiecePositionImp Piece;
		Piece.setOwner(player);
		Piece.setJokerRep('#');
		if (player == PLAYER_ONE)
			Piece.setPiece('B');
		else
			Piece.setPiece('b');
		x = getRandomPosition();
		y = getRandomPosition();
		pairs p;
		p.first = x;
		p.second = y;
		const bool is_in = s.find(p) != s.end();
		//loop until we get empty Position( have not placed Piece at this point) 
		while (is_in) {
			x = getRandomPosition();
			y = getRandomPosition();
			pairs p;
			p.first = x;
			p.second = y;
			const bool is_in = s.find(p) != s.end();

		}
		s.insert(p);
		Piece.setPosition(x, y);
		vectorToFill.push_back(std::make_unique<PiecePositionImp>(Piece));
		myGameBoard.setCell(x, y, player, Piece.getPiece(), '#');
		PointImp point;
		point.setX(x);
		point.setX(y);
		//update Occupied Points
		myOccupiedPoints.push_back(point);
	}

	//Positioning SCISSORS
	for (int i = 0; i < NUM_OF_SCISSORS; ++i) {
		int x, y;
		PiecePositionImp Piece;
		Piece.setOwner(player);
		Piece.setJokerRep('#');
		if (player == PLAYER_ONE)
			Piece.setPiece('S');
		else
			Piece.setPiece('s');
		x = getRandomPosition();
		y = getRandomPosition();
		pairs p;
		p.first = x;
		p.second = y;
		const bool is_in = s.find(p) != s.end();
		//loop until we get empty Position( have not placed Piece at this point) 
		while (is_in) {
			x = getRandomPosition();
			y = getRandomPosition();
			pairs p;
			p.first = x;
			p.second = y;
			const bool is_in = s.find(p) != s.end();

		}
		s.insert(p);
		Piece.setPosition(x, y);
		vectorToFill.push_back(std::make_unique<PiecePositionImp>(Piece));
		myGameBoard.setCell(x, y, player, Piece.getPiece(), '#');
		PointImp point;
		point.setX(x);
		point.setX(y);
		//update Occupied Points
		myOccupiedPoints.push_back(point);
	}

	//Positioning PAPERS
	for (int i = 0; i < NUM_OF_PAPERS; ++i) {
		int x, y;
		PiecePositionImp Piece;
		Piece.setOwner(player);
		Piece.setJokerRep('#');
		if (player == PLAYER_ONE)
			Piece.setPiece('P');
		else
			Piece.setPiece('p');
		x = getRandomPosition();
		y = getRandomPosition();
		pairs p;
		p.first = x;
		p.second = y;
		const bool is_in = s.find(p) != s.end();
		//loop until we get empty Position( have not placed Piece at this point) 
		while (is_in) {
			x = getRandomPosition();
			y = getRandomPosition();
			pairs p;
			p.first = x;
			p.second = y;
			const bool is_in = s.find(p) != s.end();

		}
		s.insert(p);
		Piece.setPosition(x, y);
		vectorToFill.push_back(std::make_unique<PiecePositionImp>(Piece));
		myGameBoard.setCell(x, y, player, Piece.getPiece(), '#');
		PointImp point;
		point.setX(x);
		point.setX(y);
		//update Occupied Points
		myOccupiedPoints.push_back(point);
	}

	//Positioning ROCKS
	for (int i = 0; i < NUM_OF_ROCKS; ++i) {
		int x, y;
		PiecePositionImp Piece;
		Piece.setOwner(player);
		Piece.setJokerRep('#');
		if (player == PLAYER_ONE)
			Piece.setPiece('R');
		else
			Piece.setPiece('r');
		x = getRandomPosition();
		y = getRandomPosition();
		pairs p;
		p.first = x;
		p.second = y;
		const bool is_in = s.find(p) != s.end();
		//loop until we get empty Position( have not placed Piece at this point) 
		while (is_in) {
			x = getRandomPosition();
			y = getRandomPosition();
			pairs p;
			p.first = x;
			p.second = y;
			const bool is_in = s.find(p) != s.end();

		}
		s.insert(p);
		Piece.setPosition(x, y);
		vectorToFill.push_back(std::make_unique<PiecePositionImp>(Piece));
		myGameBoard.setCell(x, y, player, Piece.getPiece(), '#');
		PointImp point;
		point.setX(x);
		point.setX(y);
		//update Occupied Points
		myOccupiedPoints.push_back(point);
	}

	//Positioning JOKERS
	for (int i = 0; i < NUM_OF_JOKERS; ++i) {
		int x, y;
		PiecePositionImp Piece;
		Piece.setOwner(player);
		if (player == PLAYER_ONE)
			Piece.setPiece('J');
		else
			Piece.setPiece('j');
		x = getRandomPosition();
		y = getRandomPosition();
		pairs p;
		p.first = x;
		p.second = y;
		const bool is_in = s.find(p) != s.end();
		//loop until we get empty Position( have not placed Piece at this point) 
		while (is_in) {
			x = getRandomPosition();
			y = getRandomPosition();
			pairs p;
			p.first = x;
			p.second = y;
			const bool is_in = s.find(p) != s.end();

		}
		s.insert(p);
		Piece.setPosition(x, y);
		char randomRep = getRandomJokerRep(player);
		Piece.setJokerRep(randomRep);
		vectorToFill.push_back(std::make_unique<PiecePositionImp>(Piece));
		myGameBoard.setCell(x, y, player, Piece.getPiece(), randomRep);
		PointImp point;
		point.setX(x);
		point.setX(y);
		//update Occupied Points
		myOccupiedPoints.push_back(point);
	}

}

int AutoPlayerAlgorithmImp::getRandomPosition() {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 10); // distribution in range [1, 10]

	return dist6(rng);
}

char AutoPlayerAlgorithmImp::getRandomJokerRep(int player) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 4); // distribution in range [1, 4]

	int num = dist6(rng);
	if (player == PLAYER_ONE) {
		if (num == 1)
			return 'S';
		else if (num == 2)
			return 'R';
		else if (num == 3)
			return 'P';
		else
			return 'B';

	}
	else {
		if (num == 1)
			return 's';
		else if (num == 2)
			return 'r';
		else if (num == 3)
			return 'p';
		else
			return 'b';

	}

}

int AutoPlayerAlgorithmImp::getRandomNumInRange(int size) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, size-1); 

	return dist6(rng);
}

void AutoPlayerAlgorithmImp::decreaseToolFromMyStock(char Piece) {
	if (Piece == 'R' || Piece == 'r')
		--numberOfRocksOwning;
	else if (Piece == 'P' || Piece == 'p')
		--numberOfPapersOwning;
	else if (Piece == 'S' || Piece == 's')
		--numberOfScissorsOwning;
	else if (Piece == 'B' || Piece == 'b')
		--numberOfBombsOwning;
	else if (Piece == 'F' || Piece == 'f')
		--numberOfFlagsOwning;
	else if (Piece == 'J' || Piece == 'j')
		--numberOfJokersOwning;
	
}

void AutoPlayerAlgorithmImp::increaseDestroyedPieces(char Piece) {
	if (Piece == 'R' || Piece == 'r') {
		++numOfRocksDestroyedByMe;
		if (numOfRocksDestroyedByMe > NUM_OF_ROCKS)
			++numberOfJokersDestroyedByMe;
	}
	else if (Piece == 'P' || Piece == 'p') {
		++numOfPapersDestroyedByMe;
		if (numOfPapersDestroyedByMe > NUM_OF_PAPERS)
			++numberOfJokersDestroyedByMe;
	}
	else if (Piece == 'S' || Piece == 's') {
		++numOfScissorsDestroyedByMe;
		if (numOfScissorsDestroyedByMe > NUM_OF_SCISSORS)
			++numberOfJokersDestroyedByMe;
	}
	else if (Piece == 'B' || Piece == 'b') {
		++numOfBombsDestroyedByMe;
		if (numOfBombsDestroyedByMe > NUM_OF_BOMBS)
			++numberOfJokersDestroyedByMe;
	}
	else if (Piece == 'F' || Piece == 'f') {
		++numOfFlagsDestroyedByMe;
	}

}

void AutoPlayerAlgorithmImp::removePointFromOccupiedPoints(PointImp point) {
	int size = myOccupiedPoints.size();
	for (int i = 0; i < size; ++i) {
		if (myOccupiedPoints[i].getX() == point.getX() && myOccupiedPoints[i].getY() == point.getY())
			myOccupiedPoints.erase(myOccupiedPoints.begin() + i);
	} 
}

void AutoPlayerAlgorithmImp::removePointFromOpponentOccupiedPoints(PointImp point) {
	int size = opponentOccupiedPoints.size();
	for (int i = 0; i < size; ++i) {
		if (opponentOccupiedPoints[i].getX() == point.getX() && opponentOccupiedPoints[i].getY() == point.getY())
			opponentOccupiedPoints.erase(opponentOccupiedPoints.begin() + i);
	}
}


void AutoPlayerAlgorithmImp::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){
	int x,y;
	int size = fights.size();
	int opponentNumber = 1 ? 2 : myPlayerNumber == 2;
	int owningPlayer;

	//update number Of Tools Opponent has
	for (int i = 0; i < NUM_OF_ROWS; ++i) {
		for (int j = 0; j < NUM_OF_COLS; ++j) {
			PointImp p;
			x = i + 1;
			y = j + 1;
			p.setX(x);
			p.setY(y);
			owningPlayer = b.getPlayer(p);
			if (owningPlayer == opponentNumber)
				++numberOfToolsLeftForOpponent;

		}
	}

	for (int i = 0; i < size; ++i) {

		PointImp point;


		x = fights.at(i).get()->getPosition().getX();
		y = fights.at(i).get()->getPosition().getY();
		point.setX(x);
		point.setX(y);
		char OpponentPiece = fights.at(i).get()->getPiece(opponentNumber);
		//char myPiece = myGameBoard.getBoard()[x-1][y-1].getPiece();
		char myPiece = myGameBoard[x - 1][y - 1]->getPiece();
		int winner = fights.at(i).get()->getWinner();
		//I win
		if (winner == myPlayerNumber) {
			--numberOfToolsLeftForOpponent;
			increaseDestroyedPieces(OpponentPiece);

		}
		//oponnent wins
		else if (winner == opponentNumber) {
			decreaseToolFromMyStock(myPiece);
			//update Occupied Points
			removePointFromOccupiedPoints(point);

			if (OpponentPiece == 'B' || OpponentPiece == 'b') {
				increaseDestroyedPieces(OpponentPiece);
				--numberOfToolsLeftForOpponent;
				myGameBoard.setCell(x, y, NO_PLAYER, '#', '#');
			}
			else
				//using oponnents jokerRep of the Cell to mark which tool his piece abale to eat  
				myGameBoard.setCell(x, y, fights.at(i).get()->getWinner(), '#', myPiece);
		}
		//tie
		else {
			decreaseToolFromMyStock(myPiece);
			increaseDestroyedPieces(OpponentPiece);
			removePointFromOccupiedPoints(point);
			myGameBoard.setCell(x, y, NO_PLAYER, '#', '#');
			--numberOfToolsLeftForOpponent;
		}
	}




	//update game board
	for (int i = 0; i < NUM_OF_ROWS; ++i) {
		for (int j = 0; j < NUM_OF_COLS; ++j) {
			PointImp p;
			x = i + 1;
			y = j + 1;
			p.setX(x);
			p.setY(y);
			int owningPlayer = b.getPlayer(p);
			if (owningPlayer == opponentNumber) {
				opponentOccupiedPoints.push_back(p);
				if(myGameBoard[x - 1][y - 1]->getJokerRep() == '#')
					myGameBoard.setCell(x, y, owningPlayer, '#', '#');
			}

		}

	}
}
void AutoPlayerAlgorithmImp::notifyOnOpponentMove(const Move& move){
	int fromX = move.getFrom().getX();
	int fromY = move.getFrom().getY();
	int toX = move.getTo().getX();
	int toY = move.getTo().getY();
	int opponentNumber = 1 ? 2 : myPlayerNumber == 2;
	PointImp point;
	point.setX(fromX);
	point.setY(fromY);

	char rep = myGameBoard[fromX - 1][fromY - 1]->getJokerRep();
	
	removePointFromOpponentOccupiedPoints(point);
	myGameBoard.setCell(fromX, fromY, NO_PLAYER, '#', '#');

	
	PiecePositionImp& Piece = dynamic_cast<PiecePositionImp&>(*myGameBoard[toX - 1][toY - 1]);
	//case no fight move him in my board
	if ( Piece.getOwner() != myPlayerNumber ) {
		myGameBoard.setCell(toX, toY, opponentNumber, '#', rep);
		point.setX(toX);
		point.setY(toY);
		opponentOccupiedPoints.push_back(point);
	}


}
void AutoPlayerAlgorithmImp::notifyFightResult(const FightInfo& fightInfo){
	
	int opponentNumber = 1 ? 2 : myPlayerNumber == 2;
	int X = fightInfo.getPosition().getX();
	int Y = fightInfo.getPosition().getY();
	char myTool = fightInfo.getPiece(myPlayerNumber);
	char oponnentTool = fightInfo.getPiece(opponentNumber);
	int winner = fightInfo.getWinner();
	PointImp point;
	point.setX(X);
	point.setY(Y);

	//I win
	if (winner == myPlayerNumber) {
		--numberOfToolsLeftForOpponent;
		increaseDestroyedPieces(oponnentTool);
		if (!doIOccupiePoint(X, Y)) {
			myOccupiedPoints.push_back(point);
			myGameBoard.setCell(X, Y, myPlayerNumber, myTool, auxPiece.getJokerRep());
		}
	}
	//oponnent wins
	else if (winner == opponentNumber) {
		decreaseToolFromMyStock(myTool);
		if(!doOpponentOccupiePoint(X, Y))
			opponentOccupiedPoints.push_back(point);
		removePointFromOccupiedPoints(point);
		if (oponnentTool == 'B' || oponnentTool == 'b') {
			increaseDestroyedPieces(oponnentTool);
			--numberOfToolsLeftForOpponent;
			removePointFromOpponentOccupiedPoints(point);
			myGameBoard.setCell(X, Y, NO_PLAYER, '#', '#');
		}
		else
			//using oponnents jokerRep of the Cell to mark which tool his piece abale to eat  
			myGameBoard.setCell(X, Y, opponentNumber, '#', myTool);
	}
	//tie
	else {
		decreaseToolFromMyStock(myTool);
		increaseDestroyedPieces(oponnentTool);
		removePointFromOccupiedPoints(point);
		removePointFromOpponentOccupiedPoints(point);
		myGameBoard.setCell(X, Y, NO_PLAYER, '#', '#');
		--numberOfToolsLeftForOpponent;
	}

}

bool AutoPlayerAlgorithmImp::hasMovingPieces() {
	if (numberOfRocksOwning > 0 || numberOfPapersOwning > 0 || numberOfScissorsOwning > 0 || numberOfJokersOwning > 0)
		return true;
	return false;
}

unique_ptr<Move> AutoPlayerAlgorithmImp::getMove(){


	
	PointImp point;
	PointImp src, dest;
	int coin = getRandomNumInRange(10);
	int mySize = myOccupiedPoints.size();
	int oponnentSize = opponentOccupiedPoints.size();
	if (!hasMovingPieces()) {
		return nullptr;
	}
	int whichPointToMove;
	int whichPointToFight;
	int fromX,fromY,toX,toY;
	//move randomly
	if (coin <= 4) {
		whichPointToMove = getRandomNumInRange(mySize);
		fromX = myOccupiedPoints.at(whichPointToMove).getX();
		fromY = myOccupiedPoints.at(whichPointToMove).getY();
		while (myGameBoard[fromX - 1][fromY - 1]->getPiece() == 'F' || myGameBoard[fromX - 1][fromY - 1]->getPiece() == 'f'
			|| myGameBoard[fromX - 1][fromY - 1]->getPiece() == 'B' || myGameBoard[fromX - 1][fromY - 1]->getPiece() == 'b') {
				
			whichPointToMove = getRandomNumInRange(mySize);
			fromX = myOccupiedPoints.at(whichPointToMove).getX();
			fromY = myOccupiedPoints.at(whichPointToMove).getY();
		}
		toX = getRandomPosition();
		toY = getRandomPosition();
		while (doIOccupiePoint(toX, toY)) {
			toX = getRandomPosition();
			toY = getRandomPosition();
		}
		src.setX(fromX);
		src.setY(fromY);
		dest.setX(toX);
		dest.setY(toY);
		MoveImp move(src, dest);
		unique_ptr<Move> m = make_unique<MoveImp>(move);

		//in case no fight
		if (!doOpponentOccupiePoint(toX, toY)) {
			myOccupiedPoints.push_back(dest);
			myGameBoard.setCell(toX, toY, myPlayerNumber, myGameBoard[fromX][fromY]->getPiece(), myGameBoard[fromX][fromY]->getJokerRep());
			removePointFromOccupiedPoints(src);
			myGameBoard.setCell(fromX, fromY, NO_PLAYER, '#', '#');
		}
		//fight gonna happen
		else {
			//save data
			auxPiece.setPosition(fromX, fromY);
			auxPiece.setPiece(myGameBoard[fromX - 1][fromY - 1]->getPiece());
			auxPiece.setOwner(myPlayerNumber);
			auxPiece.setJokerRep(myGameBoard[fromX - 1][fromY - 1]->getJokerRep());

			removePointFromOccupiedPoints(src);
			myGameBoard.setCell(fromX, fromY, NO_PLAYER, '#', '#');

		}

		acuredJokerChange = false;
		return m;
	}
	//move to cell Occupied by oponnent 
	else {
		whichPointToMove = getRandomNumInRange(mySize);
		whichPointToFight = getRandomNumInRange(oponnentSize);
		char toolThatOponnentAte;
		for (int i = 0; i < oponnentSize; ++i) {
			if ((toolThatOponnentAte = myGameBoard[opponentOccupiedPoints[i].getX() - 1][opponentOccupiedPoints[i].getY() - 1]->getJokerRep()) != '#') {
				for (int j = 0; j < mySize; ++j) {
					if (myGameBoard[myOccupiedPoints[j].getX() - 1][myOccupiedPoints[j].getY() - 1]->getPiece() != toolThatOponnentAte
						&& myGameBoard[myOccupiedPoints[j].getX() - 1][myOccupiedPoints[j].getY() - 1]->getPiece() != 'F'
						&& myGameBoard[myOccupiedPoints[j].getX() - 1][myOccupiedPoints[j].getY() - 1]->getPiece() != 'f'
						&& myGameBoard[myOccupiedPoints[j].getX() - 1][myOccupiedPoints[j].getY() - 1]->getPiece() != 'B'
						&& myGameBoard[myOccupiedPoints[j].getX() - 1][myOccupiedPoints[j].getY() - 1]->getPiece() != 'b'
						&& myGameBoard[myOccupiedPoints[j].getX() - 1][myOccupiedPoints[j].getY() - 1]->getPiece() != 'J'
						&& myGameBoard[myOccupiedPoints[j].getX() - 1][myOccupiedPoints[j].getY() - 1]->getPiece() != 'j') {

						fromX = myOccupiedPoints.at(j).getX();
						fromY = myOccupiedPoints.at(j).getY();
						toX = opponentOccupiedPoints[i].getX();
						toY = opponentOccupiedPoints[i].getY();

						src.setX(fromX);
						src.setY(fromY);
						dest.setX(toX);
						dest.setY(toY);
						MoveImp move(src, dest);
						unique_ptr<Move> m = make_unique<MoveImp>(move);

						//save data
						auxPiece.setPosition(fromX, fromY);
						auxPiece.setPiece(myGameBoard[fromX - 1][fromY - 1]->getPiece());
						auxPiece.setOwner(myPlayerNumber);
						auxPiece.setJokerRep(myGameBoard[fromX - 1][fromY - 1]->getJokerRep());

						removePointFromOccupiedPoints(src);
						myGameBoard.setCell(fromX, fromY, NO_PLAYER, '#', '#');

						acuredJokerChange = false;
						return m;
					}


				}
			}
				
		}


		for (int i = 0; i < oponnentSize; ++i) {
			if ((toolThatOponnentAte = myGameBoard[opponentOccupiedPoints[i].getX() - 1][opponentOccupiedPoints[i].getY() - 1]->getJokerRep()) != '#') {
				for (int j = 0; j < mySize; ++j) {
					if ( myGameBoard[myOccupiedPoints[j].getX() - 1][myOccupiedPoints[j].getY() - 1]->getPiece() != toolThatOponnentAte
						&& (myGameBoard[myOccupiedPoints[j].getX() - 1][myOccupiedPoints[j].getY() - 1]->getPiece() == 'J'
						|| myGameBoard[myOccupiedPoints[j].getX() - 1][myOccupiedPoints[j].getY() - 1]->getPiece() == 'j')) {

						fromX = myOccupiedPoints.at(j).getX();
						fromY = myOccupiedPoints.at(j).getY();
						toX = opponentOccupiedPoints[i].getX();
						toY = opponentOccupiedPoints[i].getY();

						src.setX(fromX);
						src.setY(fromY);
						dest.setX(toX);
						dest.setY(toY);
						MoveImp move(src, dest);
						unique_ptr<Move> m = make_unique<MoveImp>(move);


						char jokerCh = getStrongJokerRep(myPlayerNumber, toolThatOponnentAte);						
						jokerChange = std::make_unique<JokerChangeImp>(dest, jokerCh);
						acuredJokerChange = true;
						//save data
						auxPiece.setPosition(fromX, fromY);
						auxPiece.setPiece(myGameBoard[fromX - 1][fromY - 1]->getPiece());
						auxPiece.setOwner(myPlayerNumber);
						auxPiece.setJokerRep(myGameBoard[fromX - 1][fromY - 1]->getJokerRep());

						removePointFromOccupiedPoints(src);
						myGameBoard.setCell(fromX, fromY, NO_PLAYER, '#', '#');

						return m;
					}


				}
			}

		}


		whichPointToMove = getRandomNumInRange(mySize);
		fromX = myOccupiedPoints.at(whichPointToMove).getX();
		fromY = myOccupiedPoints.at(whichPointToMove).getY();
		while (myGameBoard[fromX - 1][fromY - 1]->getPiece() == 'F' || myGameBoard[fromX - 1][fromY - 1]->getPiece() == 'f'
			|| myGameBoard[fromX - 1][fromY - 1]->getPiece() == 'B' || myGameBoard[fromX - 1][fromY - 1]->getPiece() == 'b') {
			whichPointToMove = getRandomNumInRange(mySize);
			fromX = myOccupiedPoints.at(whichPointToMove).getX();
			fromY = myOccupiedPoints.at(whichPointToMove).getY();
		}

		if (oponnentSize > 0) {
			toX = opponentOccupiedPoints[0].getX();
			toY = opponentOccupiedPoints[0].getY();
		}
		else{
			toX = getRandomPosition();
			toY = getRandomPosition();
			while (doIOccupiePoint(toX, toY)) {
				toX = getRandomPosition();
				toY = getRandomPosition();
			}

		}

		src.setX(fromX);
		src.setY(fromY);
		dest.setX(toX);
		dest.setY(toY);
		MoveImp move(src, dest);
		unique_ptr<Move> m = make_unique<MoveImp>(move);

		//save data
		auxPiece.setPosition(fromX, fromY);
		auxPiece.setPiece(myGameBoard[fromX - 1][fromY - 1]->getPiece());
		auxPiece.setOwner(myPlayerNumber);
		auxPiece.setJokerRep(myGameBoard[fromX - 1][fromY - 1]->getJokerRep());

		removePointFromOccupiedPoints(src);
		myGameBoard.setCell(fromX, fromY, NO_PLAYER, '#', '#');

		acuredJokerChange = false;
		return m;

	}

	

}

char AutoPlayerAlgorithmImp::getStrongJokerRep(int playerNumber, char toolThatOponnentAte) {
	if (playerNumber == PLAYER_ONE) {
		if (toolThatOponnentAte == 'R' ) {
			return  'S';
		}
		else if (toolThatOponnentAte == 'P') {
			return 'R';
		}
		else if (toolThatOponnentAte == 'S') {
			return 'P';
		}
		else {
		return 'R';
		}

	}

	else {
		if (toolThatOponnentAte == 'R') {
			return  's';
		}
		else if (toolThatOponnentAte == 'P') {
			return 'r';
		}
		else if (toolThatOponnentAte == 'S') {
			return 'p';
		}
		else {
			return 'r';
		}

	}

}

bool AutoPlayerAlgorithmImp::doIOccupiePoint(int X, int Y) {
	int size = myOccupiedPoints.size();
	for (int i = 0; i < size; ++i) {
		if (myOccupiedPoints[i].getX() == X && myOccupiedPoints[i].getY() == Y)
			return true;
	}
	return false;
}

bool AutoPlayerAlgorithmImp::doOpponentOccupiePoint(int X, int Y) {
	int size = opponentOccupiedPoints.size();
	for (int i = 0; i < size; ++i) {
		if (opponentOccupiedPoints[i].getX() == X && opponentOccupiedPoints[i].getY() == Y)
			return true;
	}
	return false;
}

unique_ptr<JokerChange> AutoPlayerAlgorithmImp::getJokerChange() {
	if (acuredJokerChange) {
		PointImp p;
		p.setX(jokerChange.get()->getJokerChangePosition().getX());
		p.setY(jokerChange.get()->getJokerChangePosition().getY());

		return make_unique<JokerChangeImp>(p, jokerChange.get()->getJokerNewRep());
	}
	return nullptr;
}