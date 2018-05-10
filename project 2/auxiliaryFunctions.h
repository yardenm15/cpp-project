#ifndef AUXILIARYFUNCTIONS_H_
#define AUXILIARYFUNCTIONS_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

#define NUM_OF_ROWS 10 
#define NUM_OF_COLS 10 

bool isANumber(const string str);
bool isPositionFormatCorrect(const vector<string>& tokens);
bool isMoveFormatCorrect(const vector<string>& tokens);
#endif