#pragma once

class Position
{
private:
	int _row, _column;

public:
	Position(const int row, const int column);
	
	int row() const;
	int column() const;
	
	Position Up();
	Position Down();
	Position Left();
	Position Right();
	Position UpLeft();
	Position UpRight();
	Position DownLeft();
	Position DownRight();

	void GoTowards(const int rowChange, const int columnChange);

	bool operator ==(const Position& other) const;
};

