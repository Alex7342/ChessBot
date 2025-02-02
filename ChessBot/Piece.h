#pragma once
#include <vector>
#include "Move.h"

class Piece
{
public:
	enum Color
	{
		WHITE,
		BLACK
	};

	Piece(Position position, Piece::Color color, bool hasMoved = false);

	Position getPosition();
	Piece::Color getColor();
	void move(Position targetPosition);
	bool hasMoved();

private:
	Position position;
	Piece::Color color;
	bool _hasMoved;
};

