#include "PlayerAlgorithmImp.h"
#include "AutoPlayerAlgorithmImp.h"
#include "FilePlayerAlgorithmImp.h"

class Game {
	BoardImp board;
public:
	BoardImp getBoard() const { return board; };
	bool isGameOver();
	void performInitialPositionsFights(vector<unique_ptr<PiecePosition>> & player1InitialBoard, vector<unique_ptr<PiecePosition>> & player2InitialBoard);
};
