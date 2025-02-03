#pragma once
#include <vector>
#include <stack>
#include "Piece.h"
#include "Move.h"

class Board
{
private:
	enum Actions
	{
		SEPARATOR = 0,
		REMOVE_PIECE = 1,
		MOVE_PIECE = 2,
		MODIFY_SQUARE = 3
	};

	Piece board[8][8];

	std::vector<Position> whiteSquares;
	std::vector<Position> blackSquares;

	// Stack that keeps track of all actions made (used for reverting them)
	std::stack<Actions> actionsMade;

	// Helper functions that need access to the board
	bool availableSquare(const Piece::Color color, const int row, const int column);
	void addAllMovesInDirection(std::vector<Move>& moves, const Piece piece, const int rowChange, const int columnChange);
	void addPawnMoves(std::vector<Move>& moves, Piece piece);
	void addBishopMoves(std::vector<Move>& moves, Piece piece);
	void addKnightMoves(std::vector<Move>& moves, Piece piece);
	void addRookMoves(std::vector<Move>& moves, Piece piece);
	void addQueenMoves(std::vector<Move>& moves, Piece piece);
	void addKingMoves(std::vector<Move>& moves, Piece piece);

public:
	Board();

	Piece getPiece(const Position position);

	std::vector<Move> getWhiteMoves();
	std::vector<Move> getBlackMoves();

	//void makeMove(Move move);
};

