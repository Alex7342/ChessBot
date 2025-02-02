#pragma once
#include <utility>
#include "Position.h"

class Move
{
private:
	Position initialPosition;
	Position targetPosition;

public:
	Move(const Position initialPosition, const Position targetPosition);
	Position getInitialPosition();
	Position getTargetPosition();
};

