#include "Piece.h"


Piece::Piece() : type(Piece::Type::NONE), color(Piece::Color::UNCOLORED), position(Position(0, 0)), _hasMoved(false) {}

Piece::Piece(Position position) : type(Piece::Type::NONE), color(Piece::Color::UNCOLORED), position(position), _hasMoved(false) {}

Piece::Piece(Piece::Type type, Piece::Color color, Position position, bool hasMoved) : type(type), color(color), position(position), _hasMoved(hasMoved) {}

Position Piece::getPosition() const
{
	return this->position;
}

Piece::Type Piece::getType() const
{
	return this->type;
}

void Piece::setType(const Type newType)
{
	this->type = newType;
}

Piece::Color Piece::getColor() const
{
	return this->color;
}

void Piece::move(Position targetPosition)
{
	this->position = targetPosition;
	this->_hasMoved = true;
}

bool Piece::hasMoved() const
{
	return this->_hasMoved;
}

bool Piece::operator==(const Piece& other) const
{
	return this->position == other.position;
}
