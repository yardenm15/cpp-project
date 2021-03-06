// ex2.cpp : Defines the entry point for the console application.
//
#include "helperFunctions.h"
#include "Game.h"

int main(int argc, char* argv[])
{

	if (!verifyCommandLineArguments(argc, argv))
		return EXIT_FAILURE;
	string firstAlgoType = argv[1];
	firstAlgoType = firstAlgoType.substr(0, 4);
	string secondAlgoType = argv[1];
	secondAlgoType = secondAlgoType.substr(8, 12);
	Game game(firstAlgoType, secondAlgoType);
	game.startGame();
	return EXIT_SUCCESS;

}

