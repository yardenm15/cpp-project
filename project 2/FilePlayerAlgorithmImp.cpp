#include "stdafx.h"
#include "FilePlayerAlgorithmImp.h"
#include "auxiliaryFunctions.h"


FilePlayerAlgorithmImp::FilePlayerAlgorithmImp(string positionsFile, string MovesFile, Status *curStatus, int PlayerNumber) {
	positionsFile = positionsFile;
	MovesFile = MovesFile;
	currentStatus = curStatus;
	parseMovesFile(MovesFile);
	playerNumber = PlayerNumber;
	counter = -1;

}

void FilePlayerAlgorithmImp::parseMovesFile(string MovesFile) {

	//processing move files for both players
	bool moveFile = false;
	int lineNumber = 0;
	string line;;

	ifstream playerMoveFile(MovesFile);
	if (!playerMoveFile) {
		(*currentStatus).setStatus(playerNumber, PossibleStatus::File_Error);
	}

	//verify files exists and open to read
	if ((*currentStatus).getStatus(PLAYER_ONE) != PossibleStatus::Valid || (*currentStatus).getStatus(PLAYER_TWO) != PossibleStatus::Valid) {
		cout << "usage: Ex1" << endl << "infiles: player1.rps_board, player2.rps_board, player1.rps_moves, player2.rps_moves" << endl;
		return;
	}

	int fromRow, fromCol, toRow, toCol;

	while (getline(playerMoveFile, line)) {

		vector<string> tokens = splitLineBySpaces(line);

		if (isMoveFormatCorrect(tokens)) {

			fromRow = stoi(tokens[0]);
			fromCol = stoi(tokens[1]);
			toRow = stoi(tokens[2]);
			toCol = stoi(tokens[3]);

			PointImp srcPoint;
			PointImp destPoint;
			PointImp jokerChangePoint;
			srcPoint.setX(fromRow);
			srcPoint.setY(fromCol);
			destPoint.setX(toRow);
			destPoint.setY(toRow);

			movesVector.push_back(std::make_unique<MoveImp>(srcPoint, destPoint));

			if (tokens.size() == 8) {
				jokerChangePoint.setX(stoi(tokens[5]));
				jokerChangePoint.setY(stoi(tokens[6]));
				jokerChangeVector.push_back(std::make_unique<JokerChangeImp>(jokerChangePoint, tokens[7].at(0)));


			}
			else {
				jokerChangeVector.push_back(nullptr);

			}

		}
		//illegal format
		else {
			cout << "Player " << playerNumber << " has a faulty format in line " << lineNumber + 1 << " : " << endl \
				<< line << endl \
				<< "Correct format is:" << endl \
				<< "<FROM_X> <FROM_Y> <TO_X> <TO_Y> [J: <Joker_X> <Joker_Y> <NEW_REP>]" << endl;
			(*currentStatus).setStatus(playerNumber, PossibleStatus::Move_File_Error, lineNumber, line);
			return;
		}
	
	}

}

vector<string> FilePlayerAlgorithmImp::splitLineBySpaces(string line) {
	//split string by white spaces
	istringstream buf(line);
	istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end);
	return tokens;
}





void FilePlayerAlgorithmImp::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) {
	
	int lineNumber;

	//open input file
	ifstream playerPositionFile(positionsFile);
	if (!playerPositionFile) {
		(*currentStatus).setStatus(player, PossibleStatus::File_Error);
		cout << "failed to open" << player << "'s positions file" << endl;
	}

	lineNumber = 0;
	//processing position file 
	for (string line; getline(playerPositionFile, line); ++lineNumber) {
		PiecePositionImp Piece;
		parseToPiecePosition(lineNumber, line, player, (*currentStatus), Piece);
		vectorToFill.push_back(std::make_unique<PiecePositionImp>(Piece));
		if ((*currentStatus).getStatus(player) != PossibleStatus::Valid)
			break;
	}



}

int FilePlayerAlgorithmImp::getMovesVectorSize() {
	return movesVector.size();
}


void FilePlayerAlgorithmImp::parseToPiecePosition(int lineNumber, string line, int player, Status& status, PiecePositionImp& Piece) {

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
		cout << "Player " << player << " has a faulty format in line " << lineNumber + 1 << " : " << endl \
			<< line << endl \
			<< "Correct format is:" << endl \
			<< "<PIECE_CHAR> <X> <Y> or J <X> <Y> <PIECE_CHAR>" << endl;
		(*currentStatus).setStatus(player, PossibleStatus::input_File_Error, lineNumber + 1, line);

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



void FilePlayerAlgorithmImp::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){}
void FilePlayerAlgorithmImp::notifyOnOpponentMove(const Move& move) {}
void FilePlayerAlgorithmImp::notifyFightResult(const FightInfo& fightInfo) {}

// to do implement functions
unique_ptr<Move> FilePlayerAlgorithmImp::getMove() {}
unique_ptr<JokerChange> FilePlayerAlgorithmImp::getJokerChange() { }
