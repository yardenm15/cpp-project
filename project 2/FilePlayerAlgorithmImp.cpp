#include "stdafx.h"
#include "FilePlayerAlgorithmImp.h"
#include "auxiliaryFunctions.h"


FilePlayerAlgorithmImp::FilePlayerAlgorithmImp(string positionsFile, string MovesFile) {
	positionsFile = positionsFile;
	MovesFile = MovesFile;

}

void FilePlayerAlgorithmImp::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) {
	
	int lineNumber;

	//open input file
	ifstream playerPositionFile(positionsFile);
	if (!playerPositionFile) {
		status.setPlayerStatus(PossibleStatus::File_Error);
		cout << "failed to open" << player << "'s positions file" << endl;
	}

	lineNumber = 0;
	//processing position file for player 1
	for (string line; getline(playerPositionFile, line); ++lineNumber) {
		PiecePositionImp Piece;
		parseToPiecePosition(lineNumber, line, player, status, Piece);
		vectorToFill.push_back(std::make_unique<PiecePositionImp>(Piece));
		if (status.getPlayerStatus() != PossibleStatus::Valid)
			break;
	}



}

void FilePlayerAlgorithmImp::parseToPiecePosition(int lineNumber, string line, int player, playerStatus& status, PiecePositionImp& Piece) {

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
		status.setPlayerStatus(PossibleStatus::input_File_Error, lineNumber + 1, line);
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
unique_ptr<Move> FilePlayerAlgorithmImp::getMove() { }
unique_ptr<JokerChange> FilePlayerAlgorithmImp::getJokerChange() { }
