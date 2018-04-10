/*
* gameStatus.cpp
*
*  Created on:
*  Author: Oleg S.
*/

//#include "stdafx.h"
#include "gameStatus.h"
#include "cell.h"
#include <fstream>

status::status() {
	isPositioningPhase = true;
}

PossibleStatus playerStatus::getPlayerStatus() {
	return statt;
}

void playerStatus::setPlayerStatus(PossibleStatus st, int lineNum, string li) {
	statt = st;
	lineNumber = lineNum;
	line = li;
}

int playerStatus::getlineNumber() {
	return lineNumber;
}

string playerStatus::getline() {
	return line;
}

PossibleStatus status::getStatus(int playerNumber) {
	return playerNumber == PLAYER_ONE ? playerOne.getPlayerStatus() : playerTwo.getPlayerStatus();
}

void status::setStatus(int playerNumber, PossibleStatus st, int lineNum, string li) {
	if (playerNumber == PLAYER_ONE)
		playerOne.setPlayerStatus(st, lineNum, li);
	else
		playerTwo.setPlayerStatus(st, lineNum, li);
}

bool status::getIsPositioningPhase() {
	return isPositioningPhase;
}

void status::setIsPositioningPhase(bool b) {
	isPositioningPhase = b;
}

void status::printStatusToFile(ofstream& outputFile) {
	
	//tie - error in both players positioning files
	if (playerOne.getPlayerStatus() == PossibleStatus::input_File_Error && playerTwo.getPlayerStatus() == PossibleStatus::input_File_Error) {
		outputFile << "Winner: 0" << endl;
		outputFile << "Reason: " << "Bad Positioning input file for both players - player 1: line " << playerOne.getlineNumber() + 1 << ", player 2: line " << playerOne.getlineNumber() + 1 << endl;
	}

	//tie - both players lost their flags in the positioning phase
	else if (playerOne.getPlayerStatus() == PossibleStatus::All_Flags_Captured && playerTwo.getPlayerStatus() == PossibleStatus::All_Flags_Captured) {
		outputFile << "Winner: 0" << endl;
		outputFile << "A tie - all flags are eaten by both players in the position files" << endl;
	}

	//tie - both players exhausted their moves with no winner
	else if (playerOne.getPlayerStatus() == PossibleStatus::Valid && playerTwo.getPlayerStatus() == PossibleStatus::Valid) {
		outputFile << "Winner: 0" << endl;
		outputFile << "A tie - both Moves input files done without a winner" << endl;
	}

	//player one has lost
	else if (playerOne.getPlayerStatus() != PossibleStatus::Valid) {
		outputFile << "Winner: 2" << endl;
		switch (status::playerOne.getPlayerStatus()) {
			case PossibleStatus::input_File_Error:
				outputFile << "Bad Positioning input file for player " << PLAYER_ONE << " - line " << playerOne.getlineNumber() + 1 << endl;
				break;
			case PossibleStatus::Move_File_Error:
				outputFile << "Bad Moves input file for player " << PLAYER_ONE << " - line " << playerOne.getlineNumber() + 1 << endl;
				break;
			case PossibleStatus::All_Flags_Captured:
				outputFile << "All flags of the opponent are captured" << endl;
				break;
			case PossibleStatus::Out_Of_Moving_Pieces:
				outputFile << "All moving PIECEs of the opponent are eaten" << endl;
				break;
		}
	}

	//player two has lost
	else {
		outputFile << "Winner: 1" << endl;
		switch (status::playerTwo.getPlayerStatus()) {
			case PossibleStatus::input_File_Error:
				outputFile << "Bad Positioning input file for player " << PLAYER_TWO << " - line " << playerTwo.getlineNumber() + 1 << endl;
				break;
			case PossibleStatus::Move_File_Error:
				outputFile << "Bad Moves input file for player " << PLAYER_TWO << " - line " << playerOne.getlineNumber() + 1 << endl;
				break;
			case PossibleStatus::All_Flags_Captured:
				outputFile << "All flags of the opponent are captured" << endl;
				break;
			case PossibleStatus::Out_Of_Moving_Pieces:
				outputFile << "All moving PIECEs of the opponent are eaten" << endl;
				break;
		}
	}
	outputFile << endl;// 3rd line is empty
}