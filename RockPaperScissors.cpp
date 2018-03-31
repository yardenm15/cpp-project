/*
* RockPaperScissors.cpp
*
*  Created on:
*  Author: Oleg S.
*/


#include "stdafx.h"
#include "RockPaperScissors.h"





RockPaperScissors::RockPaperScissors() {
	piecesLeft_Player1 = piecesLeft_Player2 =0;
	numOfFlagsPositioned_Player1 = numOfFlagsPositioned_Player2 = 0;
	winner = 0;
	board = new cell*[NUM_OF_ROWS];
	for (int i = 0; i < NUM_OF_ROWS; ++i)
		board[i] = new cell[NUM_OF_ROWS];

	//init strength Table
	strengthTable = new int*[9];
	for (int i = 0; i < 9; ++i)
		strengthTable[i] = new int[9];

	//fill strength Table: 
	//for example: row-0 col-2 means: i am rock and i win fighting Scissors
	//VICTORY means i eat Flag, DEFEAT means i am flag that got eaten
	//rock:
	strengthTable[0][0] = TIE;
	strengthTable[0][1] = LOSE;
	strengthTable[0][2] = WIN;
	strengthTable[0][3] = LOSE;
	strengthTable[0][4] = TIE;
	strengthTable[0][5] = LOSE;
	strengthTable[0][6] = WIN;
	strengthTable[0][7] = LOSE;
	strengthTable[0][8] = VICTORY;

	//Paper:
	strengthTable[1][0] = WIN;
	strengthTable[1][1] = TIE;
	strengthTable[1][2] = LOSE;
	strengthTable[1][3] = LOSE;
	strengthTable[1][4] = WIN;
	strengthTable[1][5] = TIE;
	strengthTable[1][6] = LOSE;
	strengthTable[1][7] = LOSE;
	strengthTable[1][8] = VICTORY;

	//Scissors:
	strengthTable[2][0] = LOSE;
	strengthTable[2][1] = WIN;
	strengthTable[2][2] = TIE;
	strengthTable[2][3] = LOSE;
	strengthTable[2][4] = LOSE;
	strengthTable[2][5] = WIN;
	strengthTable[2][6] = TIE;
	strengthTable[2][7] = LOSE;
	strengthTable[2][8] = VICTORY;

	//Bomb:
	strengthTable[3][0] = WIN;
	strengthTable[3][1] = WIN;
	strengthTable[3][2] = WIN;
	strengthTable[3][3] = TIE;
	strengthTable[3][4] = WIN;
	strengthTable[3][5] = WIN;
	strengthTable[3][6] = WIN;
	strengthTable[3][7] = TIE;
	strengthTable[3][8] = VICTORY;

	//Joker_Rock:
	strengthTable[4][0] = TIE;
	strengthTable[4][1] = LOSE;
	strengthTable[4][2] = WIN;
	strengthTable[4][3] = LOSE;
	strengthTable[4][4] = TIE;
	strengthTable[4][5] = LOSE;
	strengthTable[4][6] = WIN;
	strengthTable[4][7] = LOSE;
	strengthTable[4][8] = VICTORY;

	//Joker_Paper:
	strengthTable[5][0] = WIN;
	strengthTable[5][1] = TIE;
	strengthTable[5][2] = LOSE;
	strengthTable[5][3] = LOSE;
	strengthTable[5][4] = WIN;
	strengthTable[5][5] = TIE;
	strengthTable[5][6] = LOSE;
	strengthTable[5][7] = LOSE;
	strengthTable[5][8] = VICTORY;

	//Joker_Scissors:
	strengthTable[6][0] = LOSE;
	strengthTable[6][1] = WIN;
	strengthTable[6][2] = TIE;
	strengthTable[6][3] = LOSE;
	strengthTable[6][4] = LOSE;
	strengthTable[6][5] = WIN;
	strengthTable[6][6] = TIE;
	strengthTable[6][7] = LOSE;
	strengthTable[6][8] = VICTORY;

	//Joker_Bomb:
	strengthTable[7][0] = WIN;
	strengthTable[7][1] = WIN;
	strengthTable[7][2] = WIN;
	strengthTable[7][3] = TIE;
	strengthTable[7][4] = WIN;
	strengthTable[7][5] = WIN;
	strengthTable[7][6] = WIN;
	strengthTable[7][7] = TIE;
	strengthTable[7][8] = VICTORY;

	//Flag:
	strengthTable[8][0] = DEFEAT;
	strengthTable[8][1] = DEFEAT;
	strengthTable[8][2] = DEFEAT;
	strengthTable[8][3] = DEFEAT;
	strengthTable[8][4] = DEFEAT;
	strengthTable[8][5] = DEFEAT;
	strengthTable[8][6] = DEFEAT;
	strengthTable[8][7] = DEFEAT;
	strengthTable[8][8] = TIE;
}

RockPaperScissors::~RockPaperScissors() {
	if (board != NULL) {
		for (int i = 0; i < NUM_OF_ROWS; ++i)
			delete[] board[i];
		delete[] board;

	}
}


void RockPaperScissors::setFirstPlayerPosition(string& line) {
	Piece p;
	//split string by space
	istringstream buf(line);
	istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end);

	/*for (auto i = tokens.begin(); i != tokens.end(); ++i)
	cout << *i << ' ';
	cout << endl;*/

	//format: J <X> <Y> <PIECE_CHAR>
	if (tokens[0] == "J") {

		switch (tokens[3].at(1)) {
		case 'R':
			p = Piece::Joker_Rock;
			//advance the num of player1's pieces
			++piecesLeft_Player1;
			break;
		case 'P':
			p = Piece::Joker_Paper;
			++piecesLeft_Player1;
			break;
		case 'S':
			p = Piece::Joker_Scissors;
			++piecesLeft_Player1;
			break;
		case 'B':
			p = Piece::Joker_Bomb;
			++piecesLeft_Player1;
			break;
		default:
			//to do...illegal cases
			cout << "Error" << endl;
			break;
		}

	}
	//format: <PIECE_CHAR> <X> <Y>
	else {
		switch (tokens[0].at(1)) {
		case 'R':
			p = Piece::Rock;
			++piecesLeft_Player1;
			break;
		case 'P':
			p = Piece::Paper;
			++piecesLeft_Player1;
			break;
		case 'S':
			p = Piece::Scissors;
			++piecesLeft_Player1;
			break;
		case 'B':
			p = Piece::Bomb;
			++piecesLeft_Player1;
			break;
		case 'F':
			p = Piece::Flag;
			++numOfFlagsPositioned_Player1;
			break;
		default:
			//to do...illegal cases
			cout << "Error" << endl;
			break;
		}

	}

	//board[x][Y]=PIECE
	board[stoi(tokens[1].substr(1, 1)) - 1][stoi(tokens[2].substr(1, 1)) - 1].updateCell(p, FIRST_PLAYER);
}

void RockPaperScissors::setSecondPlayerPosition(string& line) {
	Piece p;
	int x;
	int y;
	//split string by space
	istringstream buf(line);
	istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end);

	/*for (auto i = tokens.begin(); i != tokens.end(); ++i)
	cout << *i << ' ';
	cout << endl;*/

	//format: J <X> <Y> <PIECE_CHAR>
	if (tokens[0] == "J") {
		switch (tokens[3].at(1)) {
		case 'R':
			p = Piece::Joker_Rock;
			++piecesLeft_Player2;
			break;
		case 'P':
			p = Piece::Joker_Paper;
			++piecesLeft_Player2;
			break;
		case 'S':
			p = Piece::Joker_Scissors;
			++piecesLeft_Player2;
			break;
		case 'B':
			p = Piece::Joker_Bomb;
			++piecesLeft_Player2;
			break;
		default:
			//to do...illegal cases
			cout << "Error" << endl;
			break;
		}

	}
	//format: <PIECE_CHAR> <X> <Y>
	else {
		switch (tokens[0].at(1)) {
		case 'R':
			p = Piece::Rock;
			++piecesLeft_Player2;
			break;
		case 'P':
			p = Piece::Paper;
			++piecesLeft_Player2;
			break;
		case 'S':
			p = Piece::Scissors;
			++piecesLeft_Player2;
			break;
		case 'B':
			p = Piece::Bomb;
			++piecesLeft_Player2;
			break;
		case 'F':
			p = Piece::Flag;
			++numOfFlagsPositioned_Player2;
			break;
		default:
			//to do...illegal cases
			cout << "Error" << endl;
			break;
		}

	}

	x = stoi(tokens[1].substr(1, 1)) - 1;
	y = stoi(tokens[2].substr(1, 1)) - 1;
	
	
	

	if (board[x][y].getPlayer1Piece() != Piece::None) {
		makeFight(x, y, p);
	}
	else {
		//board[x][Y]=PIECE
		board[stoi(tokens[1].substr(1, 1)) - 1][stoi(tokens[2].substr(1, 1)) - 1].updateCell(p, FIRST_PLAYER);
	}

}

int RockPaperScissors::getIndexInStrengthTable(Piece piece) {
	int result;
	switch (piece) {
	case Piece::Rock:
		result = 0;
		break;
	case Piece::Paper:
		result = 1;
		break;
	case Piece::Scissors:
		result = 2;
		break;
	case Piece::Bomb:
		result = 3;
		break;
	case Piece::Joker_Rock:
		result = 4;
		break;
	case Piece::Joker_Paper:
		result = 5;
		break;
	case Piece::Joker_Scissors:
		result = 6;
		break;
	case Piece::Joker_Bomb:
		result = 7;
		break;
	case Piece::Flag:
		result = 8;
		break;
	default:
		cout << "Error" << endl;
		break;
	}

	return result;
}


int RockPaperScissors::getFightResult(int x, int y) {
	return strengthTable[x][y];
}

void RockPaperScissors::makeFight(int x, int y, Piece secondPlayerPiece) {
	Piece firstPlayerPiece = board[x][y].getPlayer1Piece();
	int player1Index = getIndexInStrengthTable(firstPlayerPiece);
	int player2Index = getIndexInStrengthTable(secondPlayerPiece);
	int result = getFightResult(player2Index, player1Index);
	
	//case second player wins
	if (result == WIN) {
		//eat  player1's piece by setting None
		board[x][y].updateCell(Piece::None, FIRST_PLAYER);
		//decrease player1's number of available pieces
		--piecesLeft_Player1;
		//update Player2's piece
		board[x][y].updateCell(secondPlayerPiece, SECOND_PLAYER);
	}
	//case first player wins
	else if (result == LOSE) {
		//decrease player2's number of available pieces
		--piecesLeft_Player2;
	}
	//case Player2 eats opponent's Flag
	else if(result == VICTORY) {
		--numOfFlagsPositioned_Player1;
		board[x][y].updateCell(Piece::None, FIRST_PLAYER);
	}
	//case player1 eats opponent's Flag
	else if (result == DEFEAT) {
		--numOfFlagsPositioned_Player2;
	}
	//case tie
	else if (result == TIE) {
		//update player2's piece
		board[x][y].updateCell(secondPlayerPiece, SECOND_PLAYER);
	}


}



void RockPaperScissors::startGame(string& firstPlayerFile, string& secondPlayerFile) {

	ifstream fin1(firstPlayerFile);
	if (!fin1) {
		cout << "Cannot open input file1" << endl; 
		
	}
	ifstream fin2(secondPlayerFile);
	if (!fin2) {
		cout << "Cannot open input file2" << endl;
	}

	//processing first file
	for (string line; getline(fin1, line);) {
		setFirstPlayerPosition(line);
	}
	
	//processing second file
	for (string ln; getline(fin2, ln);) {
		setSecondPlayerPosition(ln);
	}

	//to do: 
	//check that numOfFlagsPositioned_Player1 == NUM_OF_FLAGS,
	//numOfFlagsPositioned_Player2 == NUM_OF_FLAGS and act correspondingly
	//case of error determine the winner  and the reason
	//possible something else

	fin1.close();
	fin2.close();
}

//to do..
void RockPaperScissors::movePieces(string firstPlayerFile, string secondPlayerFile) {

}


//sanity check 
void RockPaperScissors::printBoard() {

	string p1;
	string p2;
	for (int i = 0; i < NUM_OF_ROWS; ++i) {
		for (int j = 0; j < NUM_OF_ROWS; ++j) {
			Piece t = board[i][j].getPlayer1Piece();
			if(t == Piece::None)
				p1 = "None";
			else if (t == Piece::Rock)
				p1 = "Rock";
			else if (t == Piece::Paper)
				p1 = "Paper";
			else if (t == Piece::Scissors)
				p1 = "Scissors";
			else if (t == Piece::Bomb)
				p1 = "Bomb";
			else if (t == Piece::Joker_Rock)
				p1 = "Joker_Rock";
			else if (t == Piece::Joker_Paper)
				p1 = "Joker_Paper";
			else if (t == Piece::Joker_Scissors)
				p1 = "Joker_Scissors";
			else if (t == Piece::Joker_Bomb)
				p1 = "Joker_Bomb";
			else if(t == Piece::Flag)
				p1 = "Flag";
	

			Piece f = board[i][j].getPlayer2Piece();
			if (f == Piece::None)
				p2 = "None";
			else if (f == Piece::Rock)
				p2 = "Rock";
			else if (f == Piece::Paper)
				p2 = "Paper";
			else if (f == Piece::Scissors)
				p2 = "Scissors";
			else if (f == Piece::Bomb)
				p2 = "Bomb";
			else if (f == Piece::Joker_Rock)
				p2 = "Joker_Rock";
			else if (f == Piece::Joker_Paper)
				p2 = "Joker_Paper";
			else if (f == Piece::Joker_Scissors)
				p2 = "Joker_Scissors";
			else if (f == Piece::Joker_Bomb)
				p2 = "Joker_Bomb";
			else if (f == Piece::Flag)
				p2 = "Flag";
			cout << "(" << i+1 << "," << j+1 << "):" << "P1: " << p1 << " P2: " << p2 << " | ";

		}
		cout << endl;
	}
		
}


