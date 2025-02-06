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
	static const int searchDepth = 4;

	class minimaxResult
	{
	private:
		Move move;
		int value;

	public:
		minimaxResult(const Move move, const int value);
		
		Move getMove() const;
		int getValue() const;

		void setMove(const Move move);
		void setValue(const int value);
	};

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

	minimaxResult minimax(int depth, bool whiteToMove);

public:
	Board();

	Piece getPiece(const Position position);

	std::vector<Move> getMoves(const Piece::Color playerColor);

	int evaluate() const;
	Move getBestMove(const Piece::Color playerToMove);

	void makeMove(Move move);
	void undoMove();

	std::string toString();
};

const int pieceValue[7] =
{
	0,		// Empty square
	100,	// Pawn
	330,	// Bishop
	320,	// Knight
	500,	// Rook
	900,	// Queen
	20000   // King
};

const int positionValue[8][8][8] =
{
	// Empty square value table (index 0)
	{
		{  0,   0,   0,   0,   0,   0,   0,   0 },
		{  0,   0,   0,   0,   0,   0,   0,   0 },
		{  0,   0,   0,   0,   0,   0,   0,   0 },
		{  0,   0,   0,   0,   0,   0,   0,   0 },
		{  0,   0,   0,   0,   0,   0,   0,   0 },
		{  0,   0,   0,   0,   0,   0,   0,   0 },
		{  0,   0,   0,   0,   0,   0,   0,   0 },
		{  0,   0,   0,   0,   0,   0,   0,   0 }
	},

	// Pawn value table (index 1)
	{
		{  0,   0,   0,   0,   0,   0,   0,   0 },
		{ 50,  50,  50,  50,  50,  50,  50,  50 },
		{ 10,  10,  20,  30,  30,  20,  10,  10 },
		{  5,   5,  10,  25,  25,  10,   5,   5 },
		{  0,   0,   0,  20,  20,   0,   0,   0 },
		{  5,  -5, -10,   0,   0, -10,  -5,   5 },
		{  5,  10,  10, -20, -20,  10,  10,   5 },
		{  0,   0,   0,   0,   0,   0,   0,   0 }
	},

	// Bishop value table (index 2)
	{
		{-20, -10, -10, -10, -10, -10, -10, -20 },
		{-10,   0,   0,   0,   0,   0,   0, -10 },
		{-10,   0,   5,  10,  10,   5,   0, -10 },
		{-10,   5,   5,  10,  10,   5,   5, -10 },
		{-10,   0,  10,  10,  10,  10,   0, -10 },
		{-10,  10,  10,  10,  10,  10,  10, -10 },
		{-10,   5,   0,   0,   0,   0,   5, -10 },
		{-20, -10, -10, -10, -10, -10, -10, -20 }
	},

	// Knight value table (index 3)
	{
		{-50, -40, -30, -30, -30, -30, -40, -50 },
		{-40, -20,   0,   5,   5,   0, -20, -40 },
		{-30,   5,  10,  15,  15,  10,   5, -30 },
		{-30,   0,  15,  20,  20,  15,   0, -30 },
		{-30,   5,  15,  20,  20,  15,   5, -30 },
		{-30,   0,  10,  15,  15,  10,   0, -30 },
		{-40, -20,   0,   0,   0,   0, -20, -40 },
		{-50, -40, -30, -30, -30, -30, -40, -50 }
	},

	// Rook value table (index 4)
	{
		{  0,   0,   0,   0,   0,   0,   0,   0 },
		{  5,  10,  10,  10,  10,  10,  10,   5 },
		{ -5,   0,   0,   0,   0,   0,   0,  -5 },
		{ -5,   0,   0,   0,   0,   0,   0,  -5 },
		{ -5,   0,   0,   0,   0,   0,   0,  -5 },
		{ -5,   0,   0,   0,   0,   0,   0,  -5 },
		{ -5,   0,   0,   0,   0,   0,   0,  -5 },
		{  0,   0,   0,   5,   5,   0,   0,   0 }
	},

	// Queen value table (index 5)
	{
		{-20, -10, -10,  -5,  -5, -10, -10, -20 },
		{-10,   0,   5,   0,   0,   0,   0, -10 },
		{-10,   0,   5,   5,   5,   5,   0, -10 },
		{ -5,   0,   5,   5,   5,   5,   0,  -5 },
		{  0,   0,   5,   5,   5,   5,   0,  -5 },
		{-10,   0,   5,   5,   5,   5,   0, -10 },
		{-10,   0,   0,   0,   0,   0,   0, -10 },
		{-20, -10, -10,  -5,  -5, -10, -10, -20 }
	},

	// King early and mid game value table
	{
		{ -30, -40, -40, -50, -50, -40, -40, -30 },
		{ -30, -40, -40, -50, -50, -40, -40, -30 },
		{ -30, -40, -40, -50, -50, -40, -40, -30 },
		{ -30, -40, -40, -50, -50, -40, -40, -30 },
		{ -20, -30, -30, -40, -40, -30, -30, -20 },
		{ -10, -20, -20, -20, -20, -20, -20, -10 },
		{  20,  30,  10,   0,   0,  10,  30,  20 },
		{  20,  20,   0,   0,   0,   0,  20,  20 }
	},

	// King end game value table
	{
		{ -50, -30, -30, -30, -30, -30, -30, -50 },
		{ -30, -30,   0,   0,   0,   0, -30, -30 },
		{ -30, -10,  20,  30,  30,  20, -10, -30 },
		{ -30, -10,  30,  40,  40,  30, -10, -30 },
		{ -30, -10,  30,  40,  40,  30, -10, -30 },
		{ -30, -10,  20,  30,  30,  20, -10, -30 },
		{ -30, -20, -10,   0,   0, -10, -20, -30 },
		{ -50, -40, -30, -20, -20, -30, -40, -50 }
	}
};