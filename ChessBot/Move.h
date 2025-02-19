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
	// Construct an empty move
	Move();
	// Construct a move given an initial position, a target position and a promotion type in case of pawn promotion
	Move(const Position initialPosition, const Position targetPosition, const Piece::Type promotionType = Piece::Type::NONE);
	
	// Get the position from which the piece moves
	Position getInitialPosition() const;
	// Get the position the piece is moving to
	Position getTargetPosition() const;
	
	// Get the type of piece the pawn is promoting to
	Piece::Type getPromotionType() const;
	// Set the type of piece the pawn is promoting to
	void setPromotionType(const Piece::Type newPromotionType);

	// Returns true if positions and promotion type are the same, false otherwise
	bool operator ==(const Move& other) const;

	// Compute a string to describe the current move
	std::string toString() const;
};

