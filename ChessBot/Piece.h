#pragma once
#include <vector>
#include "Move.h"

class Piece
{
public:
	enum Type
	{
		NONE = 0,
		PAWN = 1,
		BISHOP = 2,
		KNIGHT = 3,
		ROOK = 4,
		QUEEN = 5,
		KING = 6
	};

	enum Color
	{
		UNCOLORED = 0,
		WHITE = 1,
		BLACK = 2
	};

	Piece();
	Piece(Position position);
	Piece(Piece::Type type, Piece::Color color, Position position, bool hasMoved = false);

	Piece::Type getType() const;
	Piece::Color getColor() const;
	Position getPosition() const;
	bool hasMoved() const;
	void move(Position targetPosition);

	bool operator ==(const Piece& other) const;

private:
	Piece::Type type;
	Piece::Color color;
	Position position;
	bool _hasMoved;
};

