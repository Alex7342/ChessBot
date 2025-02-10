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
	static const int searchDepth = 5;

	class minimaxResult
	{
	public:
		Move move;
		int value;
		minimaxResult(const Move move, const int value);
	};

	enum Action
	{
		SEPARATOR = 0,
		REMOVE_PIECE = 1,
		ADD_PIECE = 2,
	};

	Piece board[8][8];

	// Two sets that contain the occupied squares of each color (index 0 for white, index 1 for black)
	std::set<Position> occupiedSquares[2];

	// Stack that keeps track of all actions made (used for reverting them)
	std::stack<Action> actionsMade;

	// Helper stack that keeps track of added pieces
	std::stack<Piece> addedPieces;
	// Helper stack that keeps track of removed pieces
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
	void addPiece(const Piece piece, const bool silent = false);
	void removePiece(const Piece piece, const bool silent = false);

	// The position of the white king
	Position whiteKingPosition;
	// The position of the black king
	Position blackKingPosition;

	// Returns true if the given position is attacked by a piece of the other color, false otherwise
	bool isAttackedBy(Position position, const Piece::Color attackingColor);
	// Returns true if the king of given color is in check, false otherwise
	bool isInCheck(const Piece::Color color);
	//Returns true if the player of the given color is checkmated, false otherwise
	bool checkmate(const Piece::Color color);

	minimaxResult minimax(int depth, int alpha, int beta, bool whiteToMove);

public:
	Board();

	Piece getPiece(const Position position);

	std::vector<Move> getMoves(const Piece::Color playerColor);

	int evaluate() const;
	Move getBestMove(const Piece::Color playerToMove);

	// Special case of makeMove for handling castles
	void castle(Move move);
	// Makes the given move on the board
	void makeMove(Move move);
	// Undoes the last move that was made
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