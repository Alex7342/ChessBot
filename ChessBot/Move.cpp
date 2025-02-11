#include "Move.h"

Move::Move() : initialPosition(Position()), targetPosition(Position()) {}

Move::Move(const Position initialPosition, const Position targetPosition, const Piece::Type promotionType) : initialPosition(initialPosition), targetPosition(targetPosition), promotionType(promotionType) {}

Position Move::getInitialPosition()
{
	return this->initialPosition;
}

Position Move::getTargetPosition()
{
	return this->targetPosition;
}

Piece::Type Move::getPromotionType()
{
	return this->promotionType;
}

void Move::setPromotionType(const Piece::Type newPromotionType)
{
	this->promotionType = newPromotionType;
}

std::string Move::toString() const
{
	return "(" + std::to_string(this->initialPosition.row()) + ", " + std::to_string(this->initialPosition.column()) + ") -> " +
		"(" + std::to_string(this->targetPosition.row()) + ", " + std::to_string(this->targetPosition.column()) + ")";
}
