/*
* gamegameStatus.cpp
*
*  Created on:
*  Author: Oleg S.
*/

#include "gameStatus.h"
#include <fstream>

PossibleStatus GameStatus::getGameStatus(int playerNumber) const {
	return playerNumber == PLAYER_ONE ? playerOne->getPlayerStatus() : playerTwo->getPlayerStatus();
}

void GameStatus::setGameStatus(int playerNumber, PossibleStatus st) {
	if (playerNumber == PLAYER_ONE)
		playerOne->setPlayerStatus(st);
	else
		playerTwo->setPlayerStatus(st);
}

bool GameStatus::getIsPositioningPhase() const {
	return isPositioningPhase;
}

void GameStatus::setIsPositioningPhase(bool b) {
	isPositioningPhase = b;
}

void GameStatus::printGameStatusToFile(ofstream& outputFile) const {

	//tie - error in both players positioning files
	if (playerOne->getPlayerStatus() == PossibleStatus::Position_Error && playerTwo->getPlayerStatus() == PossibleStatus::Position_Error) {
		outputFile << "Winner: 0" << endl;
		outputFile << "Reason: " << "Bad Positioning input file for both players - player 1: line " << playerOne->getlineNumber() + 1 << ", player 2: line " << playerTwo->getlineNumber() + 1 << endl;
	}

	//tie - both players lost their flags in the positioning phase
	else if (playerOne->getPlayerStatus() == PossibleStatus::All_Flags_Captured && playerTwo->getPlayerStatus() == PossibleStatus::All_Flags_Captured) {
		outputFile << "Winner: 0" << endl;
		outputFile << "Reason: " << "A tie - all flags are eaten by both players in the position files" << endl;
	}

	//tie - both players exhausted their moves with no winner
	else if (playerOne->getPlayerStatus() == PossibleStatus::Valid && playerTwo->getPlayerStatus() == PossibleStatus::Valid) {
		outputFile << "Winner: 0" << endl;
		outputFile << "Reason: " << "A tie - both Moves input files done without a winner" << endl;
	}

	//player one has lost
	else if (playerOne->getPlayerStatus() != PossibleStatus::Valid) {
		outputFile << "Winner: 2" << endl;
		switch (GameStatus::playerOne->getPlayerStatus()) {
		case PossibleStatus::Position_Error:
			outputFile << "Reason: " << "Bad Positioning input file for player " << PLAYER_ONE << " - line " << playerOne->getlineNumber() << endl;
			break;
		case PossibleStatus::Move_Error:
			outputFile << "Reason: " << "Bad Moves input file for player " << PLAYER_ONE << " - line " << playerOne->getlineNumber() << endl;
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
		switch (GameStatus::playerTwo->getPlayerStatus()) {
		case PossibleStatus::Position_Error:
			outputFile << "Reason: " << "Bad Positioning input file for player " << PLAYER_TWO << " - line " << playerTwo->getlineNumber() << endl;
			break;
		case PossibleStatus::Move_Error:
			outputFile << "Reason: " << "Bad Moves input file for player " << PLAYER_TWO << " - line " << playerTwo->getlineNumber() << endl;
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