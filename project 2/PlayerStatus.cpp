#include "PlayerStatus.h"

void PlayerStatus::setPlayerStatus(PossibleStatus stat, int lineNum, const string& li ) { 
	status = stat; 
	lineNumber = lineNum; 
	line = li; 
}

PossibleStatus PlayerStatus::getPlayerStatus() const { 
	return status; 
}

int PlayerStatus::getlineNumber() const { 
	return lineNumber; 
}

string PlayerStatus::getline() const { 
	return line; 
}