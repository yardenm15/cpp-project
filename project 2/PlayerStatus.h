#ifndef PLAYERSTATUS_H_
#define PLAYERSTATUS_H_

#include <string>

using std::string;

enum class PossibleStatus {
	Valid, File_Error, Position_File_Error, Move_File_Error, All_Flags_Captured, Out_Of_Moving_Pieces
};

class PlayerStatus {
	PossibleStatus status;
	int lineNumber;
	string line;
public:
	explicit PlayerStatus() : status(PossibleStatus::Valid), lineNumber(-1), line("") {};
	void setPlayerStatus(PossibleStatus stat, int lineNum = -1, const string& li = "");
	PossibleStatus getPlayerStatus() const;
	int getlineNumber() const;
	string getline() const;
};

#endif