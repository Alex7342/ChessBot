#pragma once
#include <vector>
#include "Position.h"

class Piece
{
public:
	// Enum of all possible piece types
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

	// Enum of all possible piece colors
	enum Color
	{
		UNCOLORED = 0,
		WHITE = 1,
		BLACK = 2
	};

	// Construct an empty piece
	Piece();
	// Construct an empty piece with a given position
	Piece(Position position);
	// Construct a piece given a type, a color, a position and a hasMoved value
	Piece(Piece::Type type, Piece::Color color, Position position, bool hasMoved = false);

	// Get the type of the piece
	Piece::Type getType() const;
	// Set the type of the piece
	void setType(const Type newType);
	
	// Get the color of the piece
	Piece::Color getColor() const;

	// Get the position of the piece
	Position getPosition() const;

	// Check if the piece has moved before (true if it did, false otherwise)
	bool hasMoved() const;

	// Set the hasMoved value of the piece
	void setHasMoved(const bool newHasMoved);

	// Move the piece to a given position
	void move(Position targetPosition);

	// Check if this piece has the same position as the other
	bool operator ==(const Piece& other) const;

private:
	Piece::Type type;
	Piece::Color color;
	Position position;
	bool _hasMoved;
};

