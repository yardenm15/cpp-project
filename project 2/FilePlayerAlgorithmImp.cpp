#include "FilePlayerAlgorithmImp.h"
#include "helperFunctions.h"

//void FilePlayerAlgorithmImp::parseMovesFile(string MovesFile) {
//
//	////processing move files for both players
//	//bool moveFile = false;
//	//int lineNumber = 0;
//	//string line;;
//
//	//ifstream playerMoveFile(MovesFile);
//	//if (!playerMoveFile) {
//	//	playerStatus.setPlayerStatus(playerNumber, PossibleStatus::File_Error);
//	//}
//
//	////verify files exists and open to read
//	//if (playerStatus.getStatus(PLAYER_ONE) != PossibleStatus::Valid || (*playerStatus).getStatus(PLAYER_TWO) != PossibleStatus::Valid) {
//	//	cout << "usage: Ex1" << endl << "infiles: player1.rps_board, player2.rps_board, player1.rps_moves, player2.rps_moves" << endl;
//	//	return;
//	//}
//
//	//int fromRow, fromCol, toRow, toCol;
//
//	//while (getline(playerMoveFile, line)) {
//
//	//	vector<string> tokens = splitLineBySpaces(line);
//
//	//	if (isMoveFormatCorrect(tokens)) {
//
//	//		fromRow = stoi(tokens[0]);
//	//		fromCol = stoi(tokens[1]);
//	//		toRow = stoi(tokens[2]);
//	//		toCol = stoi(tokens[3]);
//
//	//		PointImp srcPoint;
//	//		PointImp destPoint;
//	//		PointImp jokerChangePoint;
//	//		srcPoint.setX(fromRow);
//	//		srcPoint.setY(fromCol);
//	//		destPoint.setX(toRow);
//	//		destPoint.setY(toRow);
//
//	//		movesVector.push_back(std::make_unique<MoveImp>(srcPoint, destPoint));
//
//	//		if (tokens.size() == 8) {
//	//			jokerChangePoint.setX(stoi(tokens[5]));
//	//			jokerChangePoint.setY(stoi(tokens[6]));
//	//			jokerChangeVector.push_back(std::make_unique<JokerChangeImp>(jokerChangePoint, tokens[7].at(0)));
//
//
//	//		}
//	//		else {
//	//			jokerChangeVector.push_back(nullptr);
//
//	//		}
//
//	//	}
//	//	//illegal format
//	//	else {
//	//		cout << "Player " << playerNumber << " has a faulty format in line " << lineNumber + 1 << " : " << endl \
//	//			<< line << endl \
//	//			<< "Correct format is:" << endl \
//	//			<< "<FROM_X> <FROM_Y> <TO_X> <TO_Y> [J: <Joker_X> <Joker_Y> <NEW_REP>]" << endl;
//	//		(*playerStatus).setStatus(playerNumber, PossibleStatus::Move_File_Error, lineNumber, line);
//	//		return;
//	//	}
//	//
//	//}
//
//}

//FilePlayerAlgorithmImp::FilePlayerAlgorithmImp() {
//	playerBoard = make_shared<BoardImp>();
//}

void FilePlayerAlgorithmImp::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) {
	
	int lineNumber = 0;
	ifstream playerPositionFile;

	//open input file
	if (player == PLAYER_1) {
		playerPositionFile.open("player1.rps_board");
	}
	else
		playerPositionFile.open("player2.rps_board");
	
	//verify file opened
	if (!playerPositionFile) {
		playerStatus->setPlayerStatus(PossibleStatus::File_Error);
		cout << "failed to open player " << player << " position file" << endl;
		return;
	}


	//processing position file
	for (string line; getline(playerPositionFile, line); ++lineNumber) {
		PiecePositionImp Piece;
		parseToPiecePosition(lineNumber, line, player, Piece);
		if (playerStatus->getPlayerStatus() != PossibleStatus::Valid)
			break;
		vectorToFill.emplace_back(make_unique<PiecePositionImp>(Piece));
	}

}

//int FilePlayerAlgorithmImp::getMovesVectorSize() {
//	return movesVector.size();
//}


void FilePlayerAlgorithmImp::parseToPiecePosition(int lineNumber, string line, int player, PiecePositionImp& Piece) {

	//split string by white spaces
	istringstream buf(line);
	istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end);

	if (isPositionFormatCorrect(tokens)) {
		Piece = getPieceFromVector(tokens);
		Piece.setOwner(player);
	}
	//illegal line
	else {
		playerStatus->setPlayerStatus(PossibleStatus::Position_File_Error, lineNumber + 1, line);
		cout << "Player " << player << " has a faulty format in line " << lineNumber + 1 << " : " << endl \
			<< line << endl \
			<< "Correct format is:" << endl \
			<< "<PIECE_CHAR> <X> <Y> or J <X> <Y> <PIECE_CHAR>" << endl;
	}

}

PiecePositionImp FilePlayerAlgorithmImp::getPieceFromVector(const vector<string>& tokens) const {
	PiecePositionImp p;
	//format: <PIECE_CHAR> <X> <Y>
	switch (tokens[0].at(0)) {
	case 'R':
		p.setPiece('R');
		p.setJokerRep('#');
		break;
	case 'P':
		p.setPiece('P');
		p.setJokerRep('#');
		break;
	case 'S':
		p.setPiece('S');
		p.setJokerRep('#');
		break;
	case 'B':
		p.setPiece('B');
		p.setJokerRep('#');
		break;
	case 'F':
		p.setPiece('F');
		p.setJokerRep('#');
		break;
	case 'J':
		p.setPiece('J');
		//format: J <X> <Y> <PIECE_CHAR>
		switch (tokens[3].at(0)) {
		case 'R':
			p.setJokerRep('R');
			break;
		case 'P':
			p.setJokerRep('P');
			break;
		case 'S':
			p.setJokerRep('S');
			break;
		case 'B':
			p.setJokerRep('B');
			break;
		}
		break;
	}
	p.setPosition(stoi(tokens[1]), stoi(tokens[2]));
	return p;
}

//PlayerStatus FilePlayerAlgorithmImp::getPlayerStatus() const {
//	return playerStatus;
//}

void FilePlayerAlgorithmImp::notifyOnOpponentMove(const Move& move) {}
void FilePlayerAlgorithmImp::notifyFightResult(const FightInfo& fightInfo) {}

// to do implement functions
unique_ptr<Move> FilePlayerAlgorithmImp::getMove() {
	unique_ptr<Move> blah = make_unique<MoveImp>();
	return blah;
}
unique_ptr<JokerChange> FilePlayerAlgorithmImp::getJokerChange() {
	unique_ptr<JokerChange> blah = make_unique<JokerChangeImp>();
	return blah;
}
