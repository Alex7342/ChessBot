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
	class minimaxResult
	{
	public:
		// The move returned by the minimax algorithm
		Move move;
		// The evaluation value return by the minimax algorithm
		int value;
		// Construct a minimax result given a move and an evaluation value
		minimaxResult(const Move move, const int value);
	};

	// Enum for all possible actions performed on the board
	enum Action
	{
		SEPARATOR = 0,
		REMOVE_PIECE = 1,
		ADD_PIECE = 2,
	};

	// Array that represents the current state of the board
	Piece board[8][8];

	// Two sets that contain the occupied squares of each color (index 0 for white, index 1 for black)
	std::set<Position> occupiedSquares[2];


	// Stack that keeps track of all actions made (used for reverting them)
	std::stack<Action> actionsMade;

	// Helper stack that keeps track of added pieces
	std::stack<Piece> addedPieces;

	// Helper stack that keeps track of removed pieces
	std::stack<Piece> removedPieces;


	// The position of the white king
	Position whiteKingPosition;

	// The position of the black king
	Position blackKingPosition;


	// Check if any piece of the given color can move to the given square assuming it has access to it (NOT SUITABLE FOR PAWNS)
	bool availableSquare(const Piece::Color color, const int row, const int column) const;

	// Add all possible moves of a piece in a direction to a container reference given as a parameter
	void addAllMovesInDirection(std::vector<Move>& moves, const Piece piece, const int rowChange, const int columnChange) const;

	// Add all possible moves of a given pawn to a container reference given as a parameter
	void addPawnMoves(std::vector<Move>& moves, const Piece piece) const;

	// Add all possible moves of a given bishop to a container reference given as a parameter
	void addBishopMoves(std::vector<Move>& moves, const Piece piece) const;

	// Add all possible moves of a given knight to a container reference given as a parameter
	void addKnightMoves(std::vector<Move>& moves, const Piece piece) const;

	// Add all possible moves of a given rook to a container reference given as a parameter
	void addRookMoves(std::vector<Move>& moves, const Piece piece) const;

	// Add all possible moves of a given queen to a container reference given as a parameter
	void addQueenMoves(std::vector<Move>& moves, const Piece piece) const;

	// Add all possible moves of a given king to a container reference given as a parameter
	void addKingMoves(std::vector<Move>& moves, const Piece piece) const;

	// Adds a given piece on the current board table, if silent = true then it does not update the addedPieces stack (useful for undo)
	void addPiece(const Piece piece, const bool silent = false);

	// Removes a piece from the current board table, if silent = true then it does not update the removedPieces stack (useful for undo)
	void removePiece(const Piece piece, const bool silent = false);

	
	// Returns true if the given position is attacked by a piece of the other color, false otherwise
	bool isAttackedBy(const Position position, const Piece::Color attackingColor) const;

	// Returns true if the king of given color is in check, false otherwise
	bool isInCheck(const Piece::Color color) const;

	//Returns true if the player of the given color is checkmated, false otherwise
	bool checkmate(const Piece::Color color);


	// Special case of makeMove for handling castles
	void castle(const Move move);

	// Special case of makeMove for handling en passant
	void enPassant(const Move move);

	// Value used for board evaluation
	int evaluation;

	// The depth of the move search
	static const int searchDepth = 5;

	// Minimax algorithm that searches for the best possible move
	minimaxResult minimax(int depth, int alpha, int beta, const bool whiteToMove);

public:
	// Construct a board with the default chess setup
	Board();

	// Returns the piece at the given position
	Piece getPiece(const Position position) const;

	// Gets all pseudo legal moves of the given color
	std::vector<Move> getMoves(const Piece::Color playerColor) const;

	// Compute an evaluation of the current state of the board (positive values favour white and negative values favour black)
	int evaluate() const;

	// Search and retrieve the best possible move for the given color considering the current state of the board
	Move getBestMove(const Piece::Color playerToMove);

	// Makes the given move on the board
	void makeMove(const Move move);

	// Undoes the last move that was made
	void undoMove();

	// Compute a string describing the current state of the board
	std::string toString() const;

	// Compute a string that shows the attacked positions by the given color
	std::string attackedSquaresToString(const Piece::Color color) const;
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

// Table describing positional value of each piece type
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