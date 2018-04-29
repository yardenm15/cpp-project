#include "Game.h"

using std::make_unique;

int main() {
	Game game;
	PlayerAlgorithmImp player1Algorithm;
	PlayerAlgorithmImp  player2Algorithm;
	//unique_ptr<PlayerAlgorithm> player1Algorithmptr (&player1Algorithm);
	vector<unique_ptr<PiecePosition>> positionsVectorPlayer1;
	vector<unique_ptr<PiecePosition>> positionsVectorPlayer2;
	vector<unique_ptr<FightInfo>> fightsVector;
	player1Algorithm.getInitialPositions(PLAYER_1, positionsVectorPlayer1);
	player2Algorithm.getInitialPositions(PLAYER_2, positionsVectorPlayer2);
	game.performInitialPositionsFights(positionsVectorPlayer1, positionsVectorPlayer2);
	game.isGameOver();
	player1Algorithm.notifyOnInitialBoard(game.getBoard, fightsVector);
	player2Algorithm.notifyOnInitialBoard(game.getBoard, fightsVector);
	while (!game.isGameOver()) {
		player1Algorithm.getMove();
		//todo: keep filling MoveImp data members and methods to continue iwth check if there was a fight
	}
	return EXIT_SUCCESS;
}

bool Game::isGameOver() {
	return false;
}

void Game::performInitialPositionsFights(vector<unique_ptr<PiecePosition>>& player1InitialBoard, vector<unique_ptr<PiecePosition>>& player2InitialBoard) {

}
