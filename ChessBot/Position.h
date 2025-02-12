#pragma once

class Position
{
private:
	int _row, _column;

public:
	Position();
	Position(const int row, const int column);
	
	int row() const;
	int column() const;
	
	Position Up() const;
	Position Down() const;
	Position Left() const;
	Position Right() const;
	Position UpLeft() const;
	Position UpRight() const;
	Position DownLeft() const;
	Position DownRight() const;

	void GoTowards(const int rowChange, const int columnChange);

	bool operator ==(const Position& other) const;

	bool operator <(const Position& other) const;
};

