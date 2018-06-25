#ifndef _EX4_HEADER_H_
#define _EX4_HEADER_H_

#include <memory>
#include <vector>
#include <tuple>

using std::unique_ptr;
using std::pair;
using std::vector;
using std::make_unique;
using std::make_pair;
using std::iterator;
using std::tuple;
using std::make_tuple;

template<typename GAME_PIECE>
using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;
template<typename GAME_PIECE>
using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;

template<int ROWS, int COLUMNS, typename GAME_PIECE, int NUMBEROFPLAYERS = 2>
class GameBoard {

	int rows, columns, numberOfPlayers;
	vector<vector<PieceInfo<GAME_PIECE>>> board;

public:

	//iterator a
	class iterator {
		typename vector<vector<PieceInfo<GAME_PIECE>>>::const_iterator rowsIterator;
		typename vector<PieceInfo<GAME_PIECE>>::const_iterator columnsIterator;
		int row, column, currentRow, currentColumn;
	public:
		iterator(typename vector<vector<PieceInfo<GAME_PIECE>>>::const_iterator rowsItr,
				 typename vector<PieceInfo<GAME_PIECE>>::const_iterator columnsItr,
				 int r, int c) : rowsIterator(rowsItr), columnsIterator(columnsItr), row(r), column(c), currentRow(0), currentColumn(0) {};

		iterator operator++() {
			do {
				if (currentColumn == column - 1) {
					currentRow++;
					currentColumn = 0;
					++rowsIterator;
					if (currentRow < row) {
						columnsIterator = rowsIterator->begin();
					}
				}

				else {
					++currentColumn;
					++columnsIterator;
				}
			} while (!*columnsIterator);
			return *this;
		}

		bool operator!=(iterator other) {
			return (rowsIterator != other.rowsIterator);
		}

		tuple<int, int, GAME_PIECE, int> operator*() {
			return make_tuple(currentRow, currentColumn, get<1>(*(*columnsIterator)), get<0>(*(*columnsIterator)));
		}
	};

	//end of iterator a

	//iterator b
	class allPiecesOfCertainPlayer {

		vector<vector<PieceInfo<GAME_PIECE>>>& board;
		int player;

	public:

		allPiecesOfCertainPlayer(vector<vector<PieceInfo<GAME_PIECE>>>& b, int p) : board(b), player(p){}

		class allPiecesOfCertainIterator {

			typename vector<vector<PieceInfo<GAME_PIECE>>>::const_iterator rowsIterator;
			typename vector<PieceInfo<GAME_PIECE>>::const_iterator columnsIterator;
			int row, column, currentRow, currentColumn, playerNumber;

		public:
			allPiecesOfCertainIterator(typename vector<vector<PieceInfo<GAME_PIECE>>>::const_iterator rowsItr,
									  typename vector<PieceInfo<GAME_PIECE>>::const_iterator columnsItr,
									  int r, int c, int p) : rowsIterator(rowsItr), columnsIterator(columnsItr), row(r), column(c), currentRow(0), currentColumn(0), playerNumber(p) {};

			allPiecesOfCertainIterator operator++() {
				do {
					if (currentColumn == column - 1) {
						currentRow++;
						currentColumn = 0;
						++rowsIterator;
						if (currentRow < row) {
							columnsIterator = rowsIterator->begin();
						}
					}

					else {
						++currentColumn;
						++columnsIterator;
					}
				} while ((!*columnsIterator || get<0>(*(*columnsIterator)) != playerNumber) && currentRow < row);
				return *this;
			}

			bool operator!=(allPiecesOfCertainIterator other) {
				return (rowsIterator != other.rowsIterator);
			}

			tuple<int, int, GAME_PIECE, int> operator*() {
				return make_tuple(currentRow, currentColumn, get<1>(*(*columnsIterator)), get<0>(*(*columnsIterator)));
			}
		};

		allPiecesOfCertainIterator begin() const {
			return allPiecesOfCertainIterator(board.cbegin(), board.cbegin()->cbegin(), board.size(), board[0].size(), player);
		}

		allPiecesOfCertainIterator end() const {
			return allPiecesOfCertainIterator(board.cend(), (board.cbegin() + board.size() - 1)->cend(), board.size(), board[0].size(), player);
		}

	};

	allPiecesOfCertainPlayer allPiecesOfPlayer(int player) {
		return allPiecesOfCertainPlayer(board, player);
	}

	//end of iterator b

	//iterator c
	class certainPieceForAllPlayers {

		vector<vector<PieceInfo<GAME_PIECE>>>& board;
		char piece;

	public:

		certainPieceForAllPlayers(vector<vector<PieceInfo<GAME_PIECE>>>& b, char p) : board(b), piece(p) {}

		class certainPieceForAllPlayersIterator {

			typename vector<vector<PieceInfo<GAME_PIECE>>>::const_iterator rowsIterator;
			typename vector<PieceInfo<GAME_PIECE>>::const_iterator columnsIterator;
			int row, column, currentRow, currentColumn;
			char pie;

		public:
			certainPieceForAllPlayersIterator(typename vector<vector<PieceInfo<GAME_PIECE>>>::const_iterator rowsItr,
									  typename vector<PieceInfo<GAME_PIECE>>::const_iterator columnsItr,
									  int r, int c, char p) : rowsIterator(rowsItr), columnsIterator(columnsItr), row(r), column(c), currentRow(0), currentColumn(0), pie(p) {};

			certainPieceForAllPlayersIterator operator++() {
				do {
					if (currentColumn == column - 1) {
						currentRow++;
						currentColumn = 0;
						++rowsIterator;
						if (currentRow < row) {
							columnsIterator = rowsIterator->begin();
						}
					}

					else {
						++currentColumn;
						++columnsIterator;
					}
				} while ((!*columnsIterator || get<1>(*(*columnsIterator)) != pie) && currentRow < row);
				return *this;
			}

			bool operator!=(certainPieceForAllPlayersIterator other) {
				return (rowsIterator != other.rowsIterator);
			}

			tuple<int, int, GAME_PIECE, int> operator*() {
				return make_tuple(currentRow, currentColumn, get<1>(*(*columnsIterator)), get<0>(*(*columnsIterator)));
			}
		};

		certainPieceForAllPlayersIterator begin() const {
			return certainPieceForAllPlayersIterator(board.cbegin(), board.cbegin()->cbegin(), board.size(), board[0].size(), piece);
		}

		certainPieceForAllPlayersIterator end() const {
			return certainPieceForAllPlayersIterator(board.cend(), (board.cbegin() + board.size() - 1)->cend(), board.size(), board[0].size(), piece);
		}

	};

	certainPieceForAllPlayers allOccureneceOfPiece(char piece) {
		return certainPieceForAllPlayers(board, piece);
	}

	//end of iterator c

	//iterator d
	class certainPieceForCertainPlayer {

		vector<vector<PieceInfo<GAME_PIECE>>>& board;
		char piece;
		int playerNumber;

	public:

		certainPieceForCertainPlayer(vector<vector<PieceInfo<GAME_PIECE>>>& b, char p, int pl) : board(b), piece(p), playerNumber(pl) {}

		class certainPieceForCertainPlayerIterator {

			typename vector<vector<PieceInfo<GAME_PIECE>>>::const_iterator rowsIterator;
			typename vector<PieceInfo<GAME_PIECE>>::const_iterator columnsIterator;
			int row, column, currentRow, currentColumn, player;
			char pie;

		public:
			certainPieceForCertainPlayerIterator(typename vector<vector<PieceInfo<GAME_PIECE>>>::const_iterator rowsItr,
											  typename vector<PieceInfo<GAME_PIECE>>::const_iterator columnsItr,
											  int r, int c, char p, int pl) : rowsIterator(rowsItr), columnsIterator(columnsItr), row(r), column(c), currentRow(0), currentColumn(0), pie(p), player(pl) {};

			certainPieceForCertainPlayerIterator operator++() {
				do {
					if (currentColumn == column - 1) {
						currentRow++;
						currentColumn = 0;
						++rowsIterator;
						if (currentRow < row) {
							columnsIterator = rowsIterator->begin();
						}
					}

					else {
						++currentColumn;
						++columnsIterator;
					}
				} while ((!*columnsIterator || get<1>(*(*columnsIterator)) != pie || get<0>(*(*columnsIterator)) != player) && currentRow < row);
				return *this;
			}

			bool operator!=(certainPieceForCertainPlayerIterator other) {
				return (rowsIterator != other.rowsIterator);
			}

			tuple<int, int, GAME_PIECE, int> operator*() {
				return make_tuple(currentRow, currentColumn, get<1>(*(*columnsIterator)), get<0>(*(*columnsIterator)));
			}
		};

		certainPieceForCertainPlayerIterator begin() const {
			return certainPieceForCertainPlayerIterator(board.cbegin(), board.cbegin()->cbegin(), board.size(), board[0].size(), piece, playerNumber);
		}

		certainPieceForCertainPlayerIterator end() const {
			return certainPieceForCertainPlayerIterator(board.cend(), (board.cbegin() + board.size() - 1)->cend(), board.size(), board[0].size(), piece, playerNumber);
		}

	};

	certainPieceForCertainPlayer allOccureneceOfPieceForPlayer(char piece, int playerNum) {
		return certainPieceForCertainPlayer(board, piece, playerNum);
	}

	//end of iterator d

	GameBoard() : rows(ROWS), columns(COLUMNS), numberOfPlayers(NUMBEROFPLAYERS) {

		board.resize(ROWS);

		for (size_t i = 0; i < ROWS; ++i) {
			board[i].resize(COLUMNS);
		}

	};

	PieceInfo<GAME_PIECE> getPiece(int row, int col) {
		if (board[row][col])
			return make_unique<const pair<int, GAME_PIECE>>(*board[row][col].get());
		return nullptr;
	}

	PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player) {
		if (board[row][col]) {
			PieceInfo<GAME_PIECE> newPiece = make_unique<const pair<int, GAME_PIECE>>(make_pair(player, piece));
			newPiece.swap(board[row][col]);
			return newPiece;
		}
		board[row][col] = make_unique<const pair<int, GAME_PIECE>>(make_pair(player, piece));
		return nullptr;
	}

	iterator begin() const {
		return iterator(board.cbegin(), board.cbegin()->cbegin(), rows, columns);
	}

	iterator end() const {
		return iterator(board.cend(), (board.cbegin() + rows - 1)->cend(), rows, columns);
	}

};

#endif