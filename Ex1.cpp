// Ex1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RockPaperScissors.h"

int main()
{
	RockPaperScissors *game = new RockPaperScissors();
	string  player1File = "player1.rps_board.txt";
	string player2File = "player2.rps_board.txt";
	game->startGame(player1File, player2File);
	game->printBoard();
    return 0;
}

