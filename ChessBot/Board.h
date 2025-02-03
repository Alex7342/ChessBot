#pragma once
#include <vector>
#include <stack>
#include <unordered_set>
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
	};

	Piece board[8][8];

	// TODO Hash function for Position
	std::unordered_set<Position> whiteSquares;
	std::unordered_set<Position> blackSquares;

	// Stack that keeps track of all actions made (used for reverting them)
	std::stack<Actions> actionsMade;

	std::stack<Piece> removedPieces;

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

	void makeMove(Move move);
};

