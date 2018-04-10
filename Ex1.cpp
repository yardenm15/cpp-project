// Ex1.cpp : Defines the entry point for the console application.
//

//todo: #include "stdafx.h" this doesn't compile for me
#include "RockPaperScissors.h"
#include "gameStatus.h"

int main() {
	RockPaperScissors game;
	status* currentStatus = new status();
	string player1InitFile = "player1.rps_board";
	string player2InitFile = "player2.rps_board";
	string player1MoveFile = "player1.rps_moves";
	string player2MoveFile = "player2.rps_moves";
	game.startGame(player1InitFile, player2InitFile, player1MoveFile, player2MoveFile, *currentStatus);
	return 0;
}