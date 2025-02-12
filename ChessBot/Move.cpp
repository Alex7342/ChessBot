#include "Move.h"

Move::Move() : initialPosition(Position()), targetPosition(Position()), promotionType(Piece::Type::NONE) {}

Move::Move(const Position initialPosition, const Position targetPosition, const Piece::Type promotionType) : initialPosition(initialPosition), targetPosition(targetPosition), promotionType(promotionType) {}

Position Move::getInitialPosition() const
{
	return this->initialPosition;
}

Position Move::getTargetPosition() const
{
	return this->targetPosition;
}

Piece::Type Move::getPromotionType() const
{
	return this->promotionType;
}

void Move::setPromotionType(const Piece::Type newPromotionType)
{
	this->promotionType = newPromotionType;
}

bool Move::operator==(const Move& other) const
{
	return this->initialPosition == other.initialPosition && this->targetPosition == other.targetPosition && this->promotionType == other.promotionType;
}

std::string Move::toString() const
{
	std::string moveString = "(" + std::to_string(this->initialPosition.row()) + ", " + std::to_string(this->initialPosition.column()) + ") -> " +
		"(" + std::to_string(this->targetPosition.row()) + ", " + std::to_string(this->targetPosition.column()) + ")";
	
	switch (this->promotionType)
	{
	case Piece::QUEEN:
		moveString += " Promote to Queen";
		break;
	case Piece::ROOK:
		moveString += " Promote to Rook";
		break;
	case Piece::BISHOP:
		moveString += " Promote to Bishop";
		break;
	case Piece::KNIGHT:
		moveString += " Promote to Knight";
		break;
	default:
		break;
	}
	
	return moveString;
}
