#include "Move.h"

Move::Move(const Position initialPosition, const Position targetPosition) : initialPosition(initialPosition), targetPosition(targetPosition) {}

Position Move::getInitialPosition()
{
	return this->initialPosition;
}

Position Move::getTargetPosition()
{
	return this->targetPosition;
}
