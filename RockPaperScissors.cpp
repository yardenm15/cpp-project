/*
* RockPaperScissors.cpp
*
*  Created on:
*  Author: Oleg S.
*/

//todo: #include "stdafx.h" todo:whats this header?
#include "RockPaperScissors.h"
#include "gameStatus.h"

RockPaperScissors::RockPaperScissors() {

	//initialize number of pieces each player has
	for (int i = 0; i < NUM_OF_DIFFERENT_PIECES; ++i) {
		piecesToPlace_Player1[i] = numberOfPieaces[i];
		piecesToPlace_Player2[i] = numberOfPieaces[i];
	}

	//iniitalize board
	board = new Cell*[NUM_OF_ROWS];
	for (int i = 0; i < NUM_OF_ROWS; ++i)
		board[i] = new Cell[NUM_OF_ROWS];

	//initialize joker arrays for both players
	for (int i = 0; i < NUM_OF_JOKERS; ++i) {
		jokersOnBoard_Player1[i] = Piece();
		jokersOnBoard_Player1[i] = Piece();
	}

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

RockPaperScissors::~RockPaperScissors() {
	if (board != NULL) {
		for (int i = 0; i < NUM_OF_ROWS; ++i)
			delete board[i];
		delete[] board;
	}
}

bool isPositionFormatCorrect(vector<string> tokens) {
	//verify single letter in each token
	for (int i = 0; i < tokens.size(); ++i) {
		if (tokens[i].length() != 1)
			return false;
	}
	//verify correct format for <PIECE_CHAR> <X> <Y>
	if (tokens.size() == 3) {
		if (tokens[0].at(0) == 'R' || tokens[0].at(0) == 'P' || tokens[0].at(0) == 'S' || tokens[0].at(0) == 'B' || tokens[0].at(0) == 'F') {
			if (toDigit(tokens[1].at(0)) > 0 && toDigit(tokens[1].at(0)) < NUM_OF_ROWS + 1) {
				if (toDigit(tokens[2].at(0)) > 0 && toDigit(tokens[2].at(0)) < NUM_OF_COLS + 1)
					return true;
			}
		}
	}
	//verify correct format for J <X> <Y> <PIECE_CHAR>
	if (tokens.size() == 4) {
		if (tokens[0].at(0) == 'J') {
			if (tokens[3].at(0) == 'R' || tokens[3].at(0) == 'P' || tokens[3].at(0) == 'S' || tokens[3].at(0) == 'B') {
				if (toDigit(tokens[1].at(0)) > 0 && toDigit(tokens[1].at(0)) < NUM_OF_ROWS + 1) {
					if (toDigit(tokens[2].at(0)) > 0 && toDigit(tokens[2].at(0)) < NUM_OF_COLS + 1)
						return true;
				}
			}
		}
	}
	return false;
}

int RockPaperScissors::getPlayerOwningCell(int row, int col) {
	return board[row][col].getPlayerOwning();
}

bool RockPaperScissors::isMoveFormatCorrect(vector<string> tokens) {

	//verify number of letters in each token
	if (tokens.size() == 4 || tokens.size() == 8) {
		for (int i = 0; i < tokens.size(); ++i) {
			if (i == 4)
				continue;
			if (tokens[i].length() != 1)
				return false;
		}
		if (tokens.size() == 8) {
			if (tokens[4].size() != 2)
				return false;
		}
	}
	//wrong length
	else
		return false;



	//verify correct format for <FROM_X> <FROM_Y> <TO_X> <TO_Y> J: <Joker_X> <Joker_Y> <NEW_REP>
	for (int i = 0; i < tokens.size(); ++i) {
		if (i == 4) {
			if (tokens[i].at(0) != 'J' || tokens[i].at(0) != ':')
				return false;
		}
		else if (i == 0 || i == 2 || i == 5) {
			if (toDigit(tokens[i].at(0)) < 0 || toDigit(tokens[i].at(0)) > NUM_OF_ROWS) {
				return false;
			}
		}
		else {// i == 1 || i == 3 || i == 6
			if (toDigit(tokens[i].at(0)) < 0 || toDigit(tokens[i].at(0)) > NUM_OF_COLS) {
				return false;
			}
		}
	}

	return true;
}

int RockPaperScissors::getNumberOfPiecesLeftToPlace(int playerNumber, Piece p) {
	if (playerNumber == 1)
		return piecesToPlace_Player1[(int)p.getrpc()];
	return piecesToPlace_Player2[(int)p.getrpc()];
}

void RockPaperScissors::setPosition(int lineNumber, string& line, int playerNumber, status& currentStatus) {
	Piece p;
	//split string by white spaces
	istringstream buf(line);
	istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end);

	if (isPositionFormatCorrect(tokens)) {
		//format: <PIECE_CHAR> <X> <Y>
		switch (tokens[0].at(0)) {
			case 'R':
				p.setrpc(RPC::Rock);
				break;
			case 'P':
				p.setrpc(RPC::Paper);
				break;
			case 'S':
				p.setrpc(RPC::Scissors);
				break;
			case 'B':
				p.setrpc(RPC::Bomb);
				break;
			case 'F':
				p.setrpc(RPC::Flag);
				break;
			case 'J':
				p.setJoker(true);
				//format: J <X> <Y> <PIECE_CHAR>
				switch (tokens[3].at(0)) {
					case 'R':
						p.setrpc(RPC::Rock);
						break;
					case 'P':
						p.setrpc(RPC::Paper);
						break;
					case 'S':
						p.setrpc(RPC::Scissors);
						break;
					case 'B':
						p.setrpc(RPC::Bomb);
						break;
				}
				break;
		}
	}
	//illegal line
	else {
		cout << "Player " << playerNumber << " has a faulty format in line " << lineNumber + 1 << " : " << endl \
			<< line << endl \
			<< "Correct format is:" << endl \
			<< "<PIECE_CHAR> <X> <Y> or J <X> <Y> <PIECE_CHAR>" << endl;
		currentStatus.setStatus(playerNumber, PossibleStatus::input_File_Error, lineNumber + 1, line);
		return;
	}
	int row = toDigit(tokens[1].at(0)) - 1;
	int column = toDigit(tokens[2].at(0)) - 1;

	if (!placePiece(playerNumber, p, board, row, column, 0, 0, line, currentStatus))
		return;

}

void RockPaperScissors::decreasePieceFromStock(int playerNumber, Piece p) {
	if (playerNumber == PLAYER_ONE) {
		if (p.getisJoker()) {
			piecesToPlace_Player1[JOKER] -= 1;
			removeJokerFromJokerArray(playerNumber, p);
		}
		else
			piecesToPlace_Player1[(int)p.getrpc()] -= 1;
	}
	else {// player two
		if (p.getisJoker()) {
			piecesToPlace_Player2[JOKER] -= 1;
			removeJokerFromJokerArray(playerNumber, p);
		}
		else
			piecesToPlace_Player2[(int)p.getrpc()] -= 1;
	}
}

void RockPaperScissors::addJokerToJokerArray(int playerNumber, Piece p) {
	for (int i = 0; i < NUM_OF_JOKERS; ++i) {
		if (playerNumber == PLAYER_ONE) {
			if (jokersOnBoard_Player1[i].getrpc() == RPC::None) {
				jokersOnBoard_Player1[i] = p;
				break;
			}
		}
		else { //player 2
			if (jokersOnBoard_Player2[i].getrpc() == RPC::None) {
				jokersOnBoard_Player2[i] = p;
				break;
			}
		}
	}
}

void RockPaperScissors::removeJokerFromJokerArray(int playerNumber, Piece p) {
	for (int i = 0; i < NUM_OF_JOKERS; ++i) {
		if (playerNumber == PLAYER_ONE) {
			if (jokersOnBoard_Player1[i].getrpc() == p.getrpc()) {
				jokersOnBoard_Player1[i].setJoker(false);
				jokersOnBoard_Player1[i].setrpc(RPC::None);
				break;
			}
		}
		else { //player 2
			if (jokersOnBoard_Player2[i].getrpc() == p.getrpc()) {
				jokersOnBoard_Player1[i].setJoker(false);
				jokersOnBoard_Player1[i].setrpc(RPC::None);
				break;
			}
		}
	}
}

void RockPaperScissors::increasePieceOnBoard(int playerNumber, Piece p) {
	if (playerNumber == PLAYER_ONE) {
		if (p.getisJoker()) {
			piecesOnBoard_Player1[JOKER] += 1;
			addJokerToJokerArray(playerNumber, p);
		}
		else
			piecesOnBoard_Player1[(int)p.getrpc()] += 1;
	}
	else//player two
		if (p.getisJoker()) {
			piecesOnBoard_Player2[JOKER] += 1;
			addJokerToJokerArray(playerNumber, p);
		}
		else
			piecesOnBoard_Player2[(int)p.getrpc()] += 1;
}

void RockPaperScissors::decreasePieceFromBoard(int playerNumber, Piece p) {
	if (playerNumber == PLAYER_ONE) {
		if (p.getisJoker()) {
			piecesOnBoard_Player1[JOKER] -= 1;
			removeJokerFromJokerArray(playerNumber, p);
		}
		else
			piecesOnBoard_Player1[(int)p.getrpc()] -= 1;
	}
	else//player two
		if (p.getisJoker()) {
			piecesOnBoard_Player2[JOKER] -= 1;
			removeJokerFromJokerArray(playerNumber, p);
		}
		else
			piecesOnBoard_Player2[(int)p.getrpc()] -= 1;
}

bool RockPaperScissors::placePiece(int playerNumber, Piece p, Cell** board, int fromRow, int fromColumn, int toRow, int toColumn, string line, status& currentStatus) {
	Cell& cel = board[fromRow][fromColumn];

	if (currentStatus.getIsPositioningPhase() == true) {
		//empty valid cell
		if (cel.getPlayerOwning() == NO_PLAYER) {
			//player has pieces left
			if (getNumberOfPiecesLeftToPlace(playerNumber, p) > 0) {
				decreasePieceFromStock(playerNumber, p);//reduce 1 piece left for player
				increasePieceOnBoard(playerNumber, p);//increase 1 piece on board for player
				cel.setCell(p, playerNumber);
				return true;
			}
			//illegal - out of pieces
			else {
				cout << "Player " << playerNumber << " had no more " << p << " pieces at line " << fromRow + 1 << ":" << endl \
					<< line << endl;
				currentStatus.setStatus(playerNumber, PossibleStatus::input_File_Error, fromRow, line);
				return false;
			}
		}
		//illegal - same place piece
		else if (cel.getPlayerOwning() == playerNumber) {
			cout << "Player " << playerNumber << " tried to place a " << p << " in line " << fromRow + 1 << ":" << endl \
			<< line << endl \
			<< "where he already placed there a " << cel.getCellPiece() << " before." << endl;
			currentStatus.setStatus(playerNumber, PossibleStatus::input_File_Error, fromRow, line);
			return false;
		}
		//legal place - fight
		else {
			decreasePieceFromStock(playerNumber, p);//reduce 1 piece from stock
			increasePieceOnBoard(playerNumber, p);//increase 1 piece on board 
			fight(fromRow, fromColumn, p, playerNumber, currentStatus);
			return true;
		}

	}

	else {//moving phase

		//empty cell
		if (cel.getPlayerOwning() == NO_PLAYER) {
			setPieceAt(toRow, toColumn, playerNumber);//remove piece from original cell
			cel.setCell(p, playerNumber);
		}

		//illegal - same place piece
		else if (cel.getPlayerOwning() == playerNumber) {
			cout << "Player " << playerNumber << " already has a piece at " << fromRow + 1 << "," << fromColumn + 1 << " when executing line " << fromRow + 1 << ":" << endl \
				<< line << endl;
			currentStatus.setStatus(playerNumber, PossibleStatus::Move_File_Error, fromRow, line);
			return false;
		}
		//legal place - fight
		else {
			setPieceAt(toRow, toColumn, playerNumber);//remove piece from original cell
			fight(fromRow, fromColumn, p, playerNumber, currentStatus);
		}
	}
	return true;
}

int RockPaperScissors::getFightResult(int x, int y) {
	return strengthTable[x][y];
}

bool RockPaperScissors::checkWinningConditions(status& currentStatus) {
	if (doPlayerHasMovablePieces(PLAYER_ONE) == false) {
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

bool RockPaperScissors::aremovingJokers(int playerNumber) {
	if (playerNumber == PLAYER_ONE) {
		for (int i = 0; i < NUM_OF_JOKERS; ++i) {
			if (jokersOnBoard_Player1[i].getrpc() == RPC::Rock || jokersOnBoard_Player1[i].getrpc() == RPC::Paper || jokersOnBoard_Player1[i].getrpc() == RPC::Scissors)
				return true;
		}
		return false;
	}
	for (int i = 0; i < NUM_OF_JOKERS; ++i) {
		if (jokersOnBoard_Player2[i].getrpc() == RPC::Rock || jokersOnBoard_Player2[i].getrpc() == RPC::Paper || jokersOnBoard_Player2[i].getrpc() == RPC::Scissors)
			return true;
	}
	return false;
}

bool RockPaperScissors::doPlayerHasMovablePieces(int playerNumber) {
	if (playerNumber == PLAYER_ONE) {
		if (piecesOnBoard_Player1[ROCK] != 0 || piecesOnBoard_Player1[PAPER] != 0 || piecesOnBoard_Player1[SCISSORS] != 0 || aremovingJokers(playerNumber))
			return true;
		return false;
	}
	if (piecesOnBoard_Player2[ROCK] != 0 || piecesOnBoard_Player2[PAPER] != 0 || piecesOnBoard_Player2[SCISSORS] != 0 || aremovingJokers(playerNumber))
		return true;
	return false;
}

int RockPaperScissors::flagsLeft(int playerNumber) {
	if (playerNumber == PLAYER_ONE)
		return piecesOnBoard_Player1[FLAG];
	return piecesOnBoard_Player2[FLAG];
}

void RockPaperScissors::fight(int row, int column, Piece p, int attackingPlayerNumber, status& currentStatus) {
	Cell& cel = board[row][column];
	Piece existingPiece = cel.getCellPiece();
	int battleResult = getFightResult((int)p.getrpc(), (int)existingPiece.getrpc());

	//case player initiates fight wins
	if (battleResult == WIN) {
		decreasePieceFromBoard(attackingPlayerNumber == PLAYER_ONE ? PLAYER_TWO : PLAYER_ONE, existingPiece); //remove the losing player piece from the board
		cel.setCell(p, attackingPlayerNumber); // set the cell with the new winning piece
	}

	//case player initiates fight loses
	else if (battleResult == LOSE) {
		decreasePieceFromBoard(attackingPlayerNumber, p); ///remove the losing piece from the board
	}

	//case of tie
	else if (battleResult == TIE) {
		//remove pieces for both players and initialize cell to be empty
		cel.setCell(Piece());
		decreasePieceFromBoard(PLAYER_TWO, p);
		decreasePieceFromBoard(PLAYER_ONE, existingPiece);
	}


}

void RockPaperScissors::startGame(string& firstPlayerInitFile, string& secondPlayerInitFile, string& firstPlayerMoveFile, string& secondPlayerMoveFile, status& currentStatus) {

	//open input files
	ifstream player1PositionFile(firstPlayerInitFile);
	if (!player1PositionFile) {
		currentStatus.setStatus(PLAYER_ONE, PossibleStatus::File_Error);
	}

	ifstream player2PositionFile(secondPlayerInitFile);
	if (!player2PositionFile) {
		currentStatus.setStatus(PLAYER_TWO, PossibleStatus::File_Error);
	}

	ifstream player1MoveFile(firstPlayerMoveFile);
	if (!player1MoveFile) {
		currentStatus.setStatus(PLAYER_ONE, PossibleStatus::File_Error);
	}

	ifstream player2MoveFile(secondPlayerMoveFile);
	if (!player2MoveFile) {
		currentStatus.setStatus(PLAYER_TWO, PossibleStatus::File_Error);
	}

	//verify files exists and open to read
	if (currentStatus.getStatus(PLAYER_ONE) != PossibleStatus::Valid || currentStatus.getStatus(PLAYER_TWO) != PossibleStatus::Valid) {
		cout << "usage: Ex1" << endl << "infiles: player1.rps_board, player2.rps_board, player1.rps_moves, player2.rps_moves" << endl;
		return;
	}

	//at this point the all 4 input files are valid so lets create output file
	ofstream outputFile;
	outputFile.open("rps.output");

	int lineNumber = 0;

	//processing position file for player 1
	for (string line; getline(player1PositionFile, line); ++lineNumber) {
		setPosition(lineNumber, line, PLAYER_ONE, currentStatus);
		if (currentStatus.getStatus(PLAYER_ONE) != PossibleStatus::Valid)
			break;
	}

	lineNumber = 0;

	//processing position file for player 2
	for (string line; getline(player2PositionFile, line); ++lineNumber) {
		setPosition(lineNumber, line, PLAYER_TWO, currentStatus);
		if (currentStatus.getStatus(PLAYER_TWO) != PossibleStatus::Valid)
			break;
	}

	//verify both input files are valid. meaning: valid format of lines, no positioning 2 pieces by the same player at the same cell, no using more pieces than a plyer have,
	//valid coordinates are on board
	if (currentStatus.getStatus(PLAYER_ONE) != PossibleStatus::Valid || currentStatus.getStatus(PLAYER_TWO) != PossibleStatus::Valid) {
		currentStatus.printStatusToFile(outputFile);
		printBoardToFile(outputFile);
		return;
	}

	int flagsLeft = getNumberOfPiecesLeftToPlace(PLAYER_ONE, Piece(RPC::Flag));

	if (flagsLeft > 0) {
		currentStatus.setStatus(PLAYER_ONE, PossibleStatus::input_File_Error);
		cout << "Player " << PLAYER_ONE << " has still " << flagsLeft << " flags to use. Placing all flags is mendatory." << endl;
	}

	flagsLeft = getNumberOfPiecesLeftToPlace(PLAYER_TWO, Piece(RPC::Flag));

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

	//processing move files for both players
	bool moveFile1 = true;
	bool moveFile2 = true;
	lineNumber = 0;
	string line1, line2;
	getline(player1MoveFile, line1);
	getline(player2MoveFile, line2);

	while (moveFile1 == true || moveFile2 == true) {
		if (line1 == "")
			moveFile1 = false;
		else {
			setMove(lineNumber, line1, PLAYER_ONE, currentStatus);
			if (currentStatus.getStatus(PLAYER_ONE) != PossibleStatus::Valid)
				break;
			getline(player1MoveFile, line1);
		}
		if (checkWinningConditions(currentStatus)) {
			currentStatus.printStatusToFile(outputFile);
			printBoardToFile(outputFile);
			break;
		}
		if (line2 == "")
			moveFile2 = false;
		else {
			setMove(lineNumber, line2, PLAYER_TWO, currentStatus);
			if (currentStatus.getStatus(PLAYER_TWO) != PossibleStatus::Valid)
				break;
			getline(player2MoveFile, line2);
		}

		if (checkWinningConditions(currentStatus)) {
			currentStatus.printStatusToFile(outputFile);
			printBoardToFile(outputFile);
			break;
		}
		++lineNumber;
	}


	//game is over in tie after all move files exhausted. print to output file

	currentStatus.printStatusToFile(outputFile);
	printBoardToFile(outputFile);

	//automatic close open files in destructor

}

Piece RockPaperScissors::getPieceAt(int row, int col) {
	return board[row][col].getCellPiece();
}

void RockPaperScissors::setPieceAt(int row, int col, int playerNumber, Piece p) {
	board[row][col].setCell(p, playerNumber);
}

void RockPaperScissors::setMove(int lineNumber, string& line, int playerNumber, status& currentStatus) {
	Piece p;
	//split string by white spaces
	istringstream buf(line);
	istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end);
	int fromRow, fromCol, toRow, toCol;

	if (isMoveFormatCorrect(tokens)) {
		//verify player has a mobile Piece at the source location
		fromRow = tokens[0].at(0);
		fromCol = tokens[1].at(0);
		toRow = tokens[2].at(0);
		toCol = tokens[3].at(0);

		if (getPlayerOwningCell(fromRow, fromCol) != playerNumber) {
			cout << "Player " << playerNumber << " has no pieces to move at " << fromRow + 1 << "," << fromCol + 1 << " when executing line number " << lineNumber + 1 << ":" << endl \
				<< line << endl;
			currentStatus.setStatus(playerNumber, PossibleStatus::Move_File_Error, lineNumber, line);
			return;
		}

		else if (getPieceAt(fromRow, fromCol).getrpc() != RPC::Rock  && \
				 getPieceAt(fromRow, fromCol).getrpc() != RPC::Paper && \
				 getPieceAt(fromRow, fromCol).getrpc() != RPC::Scissors) {
			cout << "Player " << playerNumber << " has no mobile pieces at " << fromRow + 1 << "," << fromCol + 1 << " when executing line " << lineNumber + 1 << ":" << endl \
				<< line << endl;
			currentStatus.setStatus(playerNumber, PossibleStatus::Move_File_Error, lineNumber, line);
			return;
		}
	}

	//illegal format
	else {
		cout << "Player " << playerNumber << " has a faulty format in line " << lineNumber + 1 << " : " << endl \
			<< line << endl \
			<< "Correct format is:" << endl \
			<< "<FROM_X> <FROM_Y> <TO_X> <TO_Y> [J: <Joker_X> <Joker_Y> <NEW_REP>]" << endl;
		currentStatus.setStatus(playerNumber, PossibleStatus::Move_File_Error, lineNumber, line);
		return;
	}

	//move the piece

	//place piece at new cell
	if (!placePiece(playerNumber, p, board, fromRow, fromCol, toRow, toCol, line, currentStatus))
		return;
}


//sanity check 
void RockPaperScissors::printBoardToFile(ofstream& outputFile) {
	char chr;
	for (int i = 0; i < NUM_OF_ROWS; ++i) {
		for (int j = 0; j < NUM_OF_COLS; ++j) {
			Cell& cel = board[i][j];
			Piece p = cel.getCellPiece();
			int playerOwn = cel.getPlayerOwning();
			if (playerOwn == PLAYER_ONE) {
				if (p.getisJoker())
					chr = 'J';
				else {
					switch (p.getrpc()) {
						case RPC::Rock:
							chr = 'R';
							break;
						case RPC::Paper:
							chr = 'P';
							break;
						case RPC::Scissors:
							chr = 'S';
							break;
						case RPC::Bomb:
							chr = 'B';
							break;
						case RPC::Flag:
							chr = 'F';
							break;
					}
				}
			}
			else if (playerOwn == PLAYER_TWO) {
				if (p.getisJoker())
					chr = 'j';
				else {
					switch (p.getrpc()) {
						case RPC::Rock:
							chr = 'r';
							break;
						case RPC::Paper:
							chr = 'p';
							break;
						case RPC::Scissors:
							chr = 's';
							break;
						case RPC::Bomb:
							chr = 'b';
							break;
						case RPC::Flag:
							chr = 'f';
							break;
					}
				}
			}
			else {
				chr = ' ';
			}
			outputFile << chr;
		}
		outputFile << endl;
	}

}