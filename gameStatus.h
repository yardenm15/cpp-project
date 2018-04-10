/*
* gameStatus.h
*
*  Created on:
*  Author: Oleg S.
*/

#ifndef GAMESTATUS_H_
#define GAMESTATUS_H_

#include <iostream>
#include <string>
#include "cell.h"

using namespace std;

enum class PossibleStatus {
	Valid, File_Error, input_File_Error, Move_File_Error, All_Flags_Captured, Out_Of_Moving_Pieces
};

class playerStatus {
	PossibleStatus statt;
	int lineNumber;
	string line;
public:
	explicit playerStatus() : statt(PossibleStatus::Valid) {}
	playerStatus(const playerStatus&) = delete;
	playerStatus& operator=(const playerStatus&) = delete;
	PossibleStatus getPlayerStatus();
	void setPlayerStatus(PossibleStatus stat, int lineNumber = -1, string line = "");
	int getlineNumber();
	string getline();
};

class status {
	playerStatus playerOne;
	playerStatus playerTwo;
	bool isPositioningPhase;//divide the game play to positioning phase and moving phase
public:
	explicit status();
	status(const status&) = delete;
	status& operator=(const status&) = delete;
	void printStatusToFile(ofstream& outputFile);
	PossibleStatus getStatus(int playerNumber);
	void setStatus(int playerNumber, PossibleStatus status, int lineNumber = -1, string line = "");
	bool getIsPositioningPhase();
	void setIsPositioningPhase(bool b);
};

#endif