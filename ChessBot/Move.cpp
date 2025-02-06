#include "Move.h"

Move::Move() : initialPosition(Position()), targetPosition(Position()) {}

Move::Move(const Position initialPosition, const Position targetPosition) : initialPosition(initialPosition), targetPosition(targetPosition) {}

Position Move::getInitialPosition()
{
	return this->initialPosition;
}

Position Move::getTargetPosition()
{
	return this->targetPosition;
}

std::string Move::toString() const
{
	return "(" + std::to_string(this->initialPosition.row()) + ", " + std::to_string(this->initialPosition.column()) + ") -> " +
		"(" + std::to_string(this->targetPosition.row()) + ", " + std::to_string(this->targetPosition.column()) + ")";
}
