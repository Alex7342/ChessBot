#pragma once
#include <vector>
#include <stack>
#include <set>
#include <string>
#include "Piece.h"
#include "Move.h"

class Board
{
private:
	enum Action
	{
		SEPARATOR = 0,
		REMOVE_PIECE = 1,
		MOVE_PIECE = 2,
	};

	Piece board[8][8];

	// Two sets that contain the occupied squares of each color (index 0 for white, index 1 for black)
	std::set<Position> occupiedSquares[2];

	// Stack that keeps track of all actions made (used for reverting them)
	std::stack<Action> actionsMade;

	// Helper stacks that keeps track of removed pieces and moves made
	std::stack<Piece> removedPieces;
	std::stack<Move> movesMade;

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

	std::vector<Move> getMoves(const Piece::Color playerColor);

	void makeMove(Move move);
	void undoMove();

	std::string toString();
};
