#pragma once

class Position
{
private:
	int _row, _column;

public:
	Position(const int row, const int column);
	int row();
	int column();
};

