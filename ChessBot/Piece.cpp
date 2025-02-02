#include "Piece.h"


Piece::Piece(Piece::Type type, Piece::Color color, Position position, bool hasMoved) : type(type), color(color), position(position), _hasMoved(hasMoved) {}

Position Piece::getPosition()
{
	return this->position;
}

Piece::Type Piece::getType()
{
	return this->type;
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
