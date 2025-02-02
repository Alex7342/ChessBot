#pragma once
#include <utility>
#include "Position.h"

class Move
{
private:
	Position initialPosition;
	Position targetPosition;

public:
	Position getInitialPosition();
	Position getTargetPosition();
};

