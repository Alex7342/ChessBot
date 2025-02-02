#include "Piece.h"

Piece::Piece(Position position, Piece::Color color, bool hasMoved) : position(position), color(color), _hasMoved(hasMoved) {}

Position Piece::getPosition()
{
	return this->position;
}

Piece::Color Piece::getColor()
{
	return this->color;
}

void Piece::move(Position targetPosition)
{
	this->position = targetPosition;
}

bool Piece::hasMoved()
{
	return this->_hasMoved;
}
