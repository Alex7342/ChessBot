#include "Piece.h"

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
