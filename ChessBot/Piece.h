#pragma once
#include <vector>
#include "Move.h"

class Piece
{
public:
	enum Type
	{
		PAWN,
		BISHOP,
		KNIGHT,
		ROOK,
		QUEEN,
		KING
	};

	enum Color
	{
		WHITE,
		BLACK
	};

	Piece(Piece::Type type, Piece::Color color, Position position, bool hasMoved = false);

	Position getPosition();
	Piece::Color getColor();
	void move(Position targetPosition);
	bool hasMoved();

private:
	Piece::Type type;
	Piece::Color color;
	Position position;
	bool _hasMoved;
};

