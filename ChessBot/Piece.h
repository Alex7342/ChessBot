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

	Position getPosition();
	Piece::Color getColor();
	virtual std::vector<Move> getMoves() = 0;
	void move(Position targetPosition);
	bool hasMoved();

private:
	Position position;
	Piece::Color color;
	bool _hasMoved;
};

