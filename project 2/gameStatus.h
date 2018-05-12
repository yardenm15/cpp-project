/*
* gameStatus.h
*
*  Created on:
*  Author:
*/

#ifndef GAMESTATUS_H_
#define GAMESTATUS_H_

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

enum class PossibleStatus {
	Valid, File_Error, input_File_Error, Move_File_Error, All_Flags_Captured, Out_Of_Moving_Pieces
};

class playerStatus {
	PossibleStatus status;
	int lineNumber;
	string line;
public:
	explicit playerStatus() : status(PossibleStatus::Valid) {}
	playerStatus(const playerStatus&) = delete;
	//playerStatus& operator=(const playerStatus&) = delete;
	void setPlayerStatus(const PossibleStatus stat, const int lineNumber = -1, const string line = "");
	PossibleStatus getPlayerStatus() const;
	int getlineNumber() const;
	string getline() const;
};

class Status {
	playerStatus playerOne;
	playerStatus playerTwo;
	bool isPositioningPhase;//divide the game play to positioning phase and moving phase
public:
	explicit Status();
	Status(const Status&) = delete;
	//Status& operator=(const Status&) = delete;
	void printStatusToFile(ofstream& outputFile) const;
	PossibleStatus getStatus(int playerNumber) const;
	void setStatus(int playerNumber, const PossibleStatus status, int lineNumber = -1, const string line = "");
	bool getIsPositioningPhase() const;
	void setIsPositioningPhase(bool b);
};

#endif