#include "helperFunctions.h"

//verify correct user input
bool verifyCommandLineArguments(int argc, char* argv[]) {

	if (argc != 2) {
		cout << "usage: ./Game  object-vs-object where object is auto or file" << endl;
		return false;
	}

	string str = argv[1];
	size_t found = str.find("-vs-");
	int stringLength = 4;

	if (found == std::string::npos || (str.substr(0, found) != "auto" && str.substr(0, found) != "file") || (str.substr(found+ stringLength, str.length()) != "auto" && str.substr(found + stringLength, str.length()) != "file")) {
		cout << "usage: ./Game  object-vs-object where object is auto or file" << endl;
		return false;
	}

	return true;
}

bool isANumber(const string str) {
	for (string::size_type i = 0; i < str.length(); ++i) {
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

bool isPositionFormatCorrect(const vector<string>& tokens) {

	//verify correct format for <PIECE_CHAR> <X> <Y>
	if (tokens.size() == 3) {
		if (tokens[0].size() == 1) {
			if (tokens[0].at(0) == 'R' || tokens[0].at(0) == 'P' || tokens[0].at(0) == 'S' || tokens[0].at(0) == 'B' || tokens[0].at(0) == 'F') {
				if (isANumber(tokens[1])) {
					if (stoi(tokens[1]) > 0 && stoi(tokens[1]) < NUM_OF_ROWS + 1) {
						if (isANumber(tokens[2])) {
							if (stoi(tokens[2]) > 0 && stoi(tokens[2]) < NUM_OF_COLS + 1)
								return true;
						}
					}
				}
			}
		}
	}

	//verify correct format for J <X> <Y> <PIECE_CHAR>
	if (tokens.size() == 4) {
		if (tokens[0].size() == 1) {
			if (tokens[0].at(0) == 'J') {
				if (tokens[3].size() == 1) {
					if (tokens[3].at(0) == 'R' || tokens[3].at(0) == 'P' || tokens[3].at(0) == 'S' || tokens[3].at(0) == 'B') {
						if (isANumber(tokens[1])) {
							if (stoi(tokens[1]) > 0 && stoi(tokens[1]) < NUM_OF_ROWS + 1) {
								if (isANumber(tokens[2])) {
									if (stoi(tokens[2]) > 0 && stoi(tokens[2]) < NUM_OF_COLS + 1)
										return true;
								}
							}
						}
					}
				}
			}
		}
	}

	return false;
}

bool isMoveFormatCorrect(const vector<string>& tokens) {

	//verify correct format for <FROM_X> <FROM_Y> <TO_X> <TO_Y> J: <Joker_X> <Joker_Y> <NEW_REP>
	if (tokens.size() == 4 || tokens.size() == 8) {
		for (vector<string>::size_type i = 0; i < tokens.size(); ++i) {
			if (i == 4) {
				if (tokens[i].size() != 2)
					return false;
				if (tokens[i].at(0) != 'J' || tokens[i].at(1) != ':')
					return false;
			}
			else if (i == 0 || i == 2 || i == 5) {//verify rows within range
				if (!isANumber(tokens[i]))
					return false;
				if (stoi(tokens[i]) < 1 || stoi(tokens[i]) > NUM_OF_ROWS) {
					return false;
				}
			}
			else if (i == 1 || i == 3 || i == 6) {
				if (!isANumber(tokens[i]))
					return false;
				if (stoi(tokens[i]) < 1 || stoi(tokens[i]) > NUM_OF_COLS) {
					return false;
				}
			}
			else {//i = 7
				if (tokens[i].size() != 1)
					return false;
				if (tokens[i].at(0) != 'R' && tokens[i].at(0) != 'P' && tokens[i].at(0) != 'S' && tokens[i].at(0) != 'B') {
					return false;
				}
			}
		}
	}
	return true;
}

vector<string> splitLineBySpaces(string line) {
	//split string by white spaces
	istringstream buf(line);
	istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end);
	return tokens;
}

bool isArrayEmpty(int arr[STRENGTH_TABLE_SIZE][STRENGTH_TABLE_SIZE]) {
	for (int i = 0; i < STRENGTH_TABLE_SIZE; ++i) {
		for (int j = 0; j < STRENGTH_TABLE_SIZE; ++j) {
			if (arr[i][j] != 0)
				return false;
		}
	}
	return true;
}

void initializeStrengthArray(int (&strengthTable)[STRENGTH_TABLE_SIZE][STRENGTH_TABLE_SIZE]) {
	//rock:
	strengthTable[ROCK][ROCK] = TIE;
	strengthTable[ROCK][PAPER] = LOSE;
	strengthTable[ROCK][SCISSORS] = WIN;
	strengthTable[ROCK][BOMB] = TIE;
	strengthTable[ROCK][FLAG] = WIN;

	//Paper:
	strengthTable[PAPER][ROCK] = WIN;
	strengthTable[PAPER][PAPER] = TIE;
	strengthTable[PAPER][SCISSORS] = LOSE;
	strengthTable[PAPER][BOMB] = TIE;
	strengthTable[PAPER][FLAG] = WIN;

	//Scissors:
	strengthTable[SCISSORS][ROCK] = LOSE;
	strengthTable[SCISSORS][PAPER] = WIN;
	strengthTable[SCISSORS][SCISSORS] = TIE;
	strengthTable[SCISSORS][BOMB] = TIE;
	strengthTable[SCISSORS][FLAG] = WIN;

	//Bomb:
	strengthTable[BOMB][ROCK] = TIE;
	strengthTable[BOMB][PAPER] = TIE;
	strengthTable[BOMB][SCISSORS] = TIE;
	strengthTable[BOMB][BOMB] = TIE;
	strengthTable[BOMB][FLAG] = TIE;

	//Flag:
	strengthTable[FLAG][ROCK] = LOSE;
	strengthTable[FLAG][PAPER] = LOSE;
	strengthTable[FLAG][SCISSORS] = LOSE;
	strengthTable[FLAG][BOMB] = TIE;
	strengthTable[FLAG][FLAG] = TIE;
}