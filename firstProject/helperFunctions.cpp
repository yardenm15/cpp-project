#include "helperFunctions.h"

bool isANumber(const string str) {
	for (int i = 0; i < str.length(); ++i) {
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
		for (int i = 0; i < tokens.size(); ++i) {
			if (i == 4) {
				if (tokens[i].size() != 2)
					return false;
				if (tokens[i].at(0) != 'J' || tokens[i].at(1) != ':')
					return false;
			}
			else if (i == 0 || i == 2 || i == 5) {//verify rows within range
				if (!isANumber(tokens[i]))
					return false;
				if (stoi(tokens[i]) < 0 || stoi(tokens[i]) > NUM_OF_ROWS) {
					return false;
				}
			}
			else if (i == 1 || i == 3 || i == 6) {
				if (!isANumber(tokens[i]))
					return false;
				if (stoi(tokens[i]) < 0 || stoi(tokens[i]) > NUM_OF_COLS) {
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