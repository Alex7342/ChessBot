#pragma once
#include <utility>
#include <string>
#include "Position.h"


class Move
{
private:
	Position initialPosition;
	Position targetPosition;

public:
	Move();
	Move(const Position initialPosition, const Position targetPosition);
	
	Position getInitialPosition();
	Position getTargetPosition();

	std::string toString() const;
};

