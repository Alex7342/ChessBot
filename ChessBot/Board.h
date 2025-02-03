#pragma once
#include <vector>
#include "Piece.h"
#include "Move.h"

class Board
{
private:
	struct Square
	{
		Piece::Type type;
		Piece::Color color;
	} board[8][8];

	std::vector<Piece> whitePieces;
	std::vector<Piece> blackPieces;

	// Helper functions that need access to the board
	bool availableSquare(Piece::Color color, const int row, const int column);
	void addAllMovesInDirection(std::vector<Move>& moves, Piece piece, const int rowChange, const int columnChange);
	void addPawnMoves(std::vector<Move>& moves, Piece piece);
	void addBishopMoves(std::vector<Move>& moves, Piece piece);
	void addKnightMoves(std::vector<Move>& moves, Piece piece);
	void addRookMoves(std::vector<Move>& moves, Piece piece);
	void addQueenMoves(std::vector<Move>& moves, Piece piece);
	void addKingMoves(std::vector<Move>& moves, Piece piece);

public:
	Board();
	std::vector<Move> getWhiteMoves();
	std::vector<Move> getBlackMoves();
};

