/*
* gameStatus.cpp
*
*  Created on:
*  Author: Oleg S.
*/


#include "gameStatus.h"
#include <fstream>
#define PLAYER_ONE 1
#define PLAYER_TWO 2

PossibleStatus playerStatus::getPlayerStatus() const {
	return status;
}

void playerStatus::setPlayerStatus(const PossibleStatus st, int lineNum, const string li) {
	status = st;
	lineNumber = lineNum;
	line = li;
}

int playerStatus::getlineNumber() const {
	return lineNumber;
}

string playerStatus::getline() const {
	return line;
}

Status::Status() {
	isPositioningPhase = true;
}

PossibleStatus Status::getStatus(int playerNumber) const {
	return playerNumber == PLAYER_ONE ? playerOne.getPlayerStatus() : playerTwo.getPlayerStatus();
}

void Status::setStatus(int playerNumber, PossibleStatus st, int lineNum, string li) {
	if (playerNumber == PLAYER_ONE)
		playerOne.setPlayerStatus(st, lineNum, li);
	else
		playerTwo.setPlayerStatus(st, lineNum, li);
}

bool Status::getIsPositioningPhase() const {
	return isPositioningPhase;
}

void Status::setIsPositioningPhase(bool b) {
	isPositioningPhase = b;
}

void Status::printStatusToFile(ofstream& outputFile) const {

	//tie - error in both players positioning files
	if (playerOne.getPlayerStatus() == PossibleStatus::input_File_Error && playerTwo.getPlayerStatus() == PossibleStatus::input_File_Error) {
		outputFile << "Winner: 0" << endl;
		outputFile << "Reason: " << "Bad Positioning input file for both players - player 1: line " << playerOne.getlineNumber() + 1 << ", player 2: line " << playerTwo.getlineNumber() + 1 << endl;
	}

	//tie - both players lost their flags in the positioning phase
	else if (playerOne.getPlayerStatus() == PossibleStatus::All_Flags_Captured && playerTwo.getPlayerStatus() == PossibleStatus::All_Flags_Captured) {
		outputFile << "Winner: 0" << endl;
		outputFile << "Reason: " << "A tie - all flags are eaten by both players in the position files" << endl;
	}

	//tie - both players exhausted their moves with no winner
	else if (playerOne.getPlayerStatus() == PossibleStatus::Valid && playerTwo.getPlayerStatus() == PossibleStatus::Valid) {
		outputFile << "Winner: 0" << endl;
		outputFile << "Reason: " << "A tie - both Moves input files done without a winner" << endl;
	}

	//player one has lost
	else if (playerOne.getPlayerStatus() != PossibleStatus::Valid) {
		outputFile << "Winner: 2" << endl;
		switch (Status::playerOne.getPlayerStatus()) {
		case PossibleStatus::input_File_Error:
			outputFile << "Reason: " << "Bad Positioning input file for player " << PLAYER_ONE << " - line " << playerOne.getlineNumber() << endl;
			break;
		case PossibleStatus::Move_File_Error:
			outputFile << "Reason: " << "Bad Moves input file for player " << PLAYER_ONE << " - line " << playerOne.getlineNumber() << endl;
			break;
		case PossibleStatus::All_Flags_Captured:
			outputFile << "Reason: " << "All flags of the opponent are captured" << endl;
			break;
		case PossibleStatus::Out_Of_Moving_Pieces:
			outputFile << "Reason: " << "All moving PIECEs of the opponent are eaten" << endl;
			break;
		default:
			break;
		}
	}

	//player two has lost
	else {
		outputFile << "Winner: 1" << endl;
		switch (Status::playerTwo.getPlayerStatus()) {
		case PossibleStatus::input_File_Error:
			outputFile << "Reason: " << "Bad Positioning input file for player " << PLAYER_TWO << " - line " << playerTwo.getlineNumber() << endl;
			break;
		case PossibleStatus::Move_File_Error:
			outputFile << "Reason: " << "Bad Moves input file for player " << PLAYER_TWO << " - line " << playerTwo.getlineNumber() << endl;
			break;
		case PossibleStatus::All_Flags_Captured:
			outputFile << "Reason: " << "All flags of the opponent are captured" << endl;
			break;
		case PossibleStatus::Out_Of_Moving_Pieces:
			outputFile << "Reason: " << "All moving PIECEs of the opponent are eaten" << endl;
			break;
		default:
			break;
		}
	}
	outputFile << endl;// 3rd line is empty
}