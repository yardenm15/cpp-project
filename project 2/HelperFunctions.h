#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

#define NUM_OF_ROWS 10 
#define NUM_OF_COLS 10 
#define STRENGTH_TABLE_SIZE 5
#define ROCK 0
#define PAPER 1
#define SCISSORS 2
#define BOMB 3
#define FLAG 4
#define JOKER 5
#define TIE 0
#define WIN 1
#define LOSE 2

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::istringstream;
using std::istream_iterator;

bool verifyCommandLineArguments(int argc, char* argv[]);
bool isANumber(const string str);
bool isPositionFormatCorrect(const vector<string>& tokens);
bool isMoveFormatCorrect(const vector<string>& tokens);
void initializeStrengthArray(int (&strengthTable) [STRENGTH_TABLE_SIZE][STRENGTH_TABLE_SIZE]);
vector<string> splitLineBySpaces(string line);
bool isArrayEmpty( int arr [STRENGTH_TABLE_SIZE][STRENGTH_TABLE_SIZE]);

#endif