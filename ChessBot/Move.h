#pragma once
#include <utility>
#include <string>
#include "Position.h"
#include "Piece.h"


class Move
{
private:
	Position initialPosition;
	Position targetPosition;
	Piece::Type promotionType;

public:
	Move();
	Move(const Position initialPosition, const Position targetPosition, const Piece::Type promotionType = Piece::Type::NONE);
	
	Position getInitialPosition();
	Position getTargetPosition();

	Piece::Type getPromotionType();
	void setPromotionType(const Piece::Type newPromotionType);

	std::string toString() const;
};

