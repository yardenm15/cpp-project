// Ex1.cpp : Defines the entry point for the console application.

#include "RockPaperScissors.h"

int main() {
	RockPaperScissors game;
	Status currentStatus;
	string player1InitFile = "player1.rps_board";
	string player2InitFile = "player2.rps_board";
	string player1MoveFile = "player1.rps_moves";
	string player2MoveFile = "player2.rps_moves";
	game.startGame(player1InitFile, player2InitFile, player1MoveFile, player2MoveFile, currentStatus);
	return 0;
}