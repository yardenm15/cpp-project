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
#include <memory>
#include "PlayerStatus.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::unique_ptr;
using std::make_unique;

#define PLAYER_ONE 1
#define PLAYER_TWO 2

class GameStatus {
	unique_ptr<PlayerStatus> playerOne;
	unique_ptr<PlayerStatus> playerTwo;
	bool isPositioningPhase;//divide the game play to positioning phase and moving phase
public:
	explicit GameStatus() : isPositioningPhase(true), playerOne(make_unique<PlayerStatus>()), playerTwo(make_unique<PlayerStatus>()) {};
	void printGameStatusToFile(ofstream& outputFile) const;
	PossibleStatus getGameStatus(int playerNumber) const;
	void setGameStatus(int playerNumber, PossibleStatus status, int lineNumber = -1, const string& line = "");
	bool getIsPositioningPhase() const;
	void setIsPositioningPhase(bool b);
};
#endif