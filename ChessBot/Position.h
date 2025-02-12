#pragma once

class Position
{
private:
	int _row, _column;

public:
	// Construct an empty position (row = 0, column = 0)
	Position();
	// Construct a position given a row and a column
	Position(const int row, const int column);
	
	// Get the row of the position
	int row() const;

	// Get the column of the position
	int column() const;
	
	// Get the position one square up from the current one
	Position Up() const;
	// Get the position one square down from the current one
	Position Down() const;
	// Get the position one square to the left from the current one
	Position Left() const;
	// Get the position one square to the right from the current one
	Position Right() const;
	// Get the position one square up and one square to the left from the current one
	Position UpLeft() const;
	// Get the position one square up and one square to the right from the current one
	Position UpRight() const;
	// Get the position one square down and one square to the left from the current one
	Position DownLeft() const;
	// Get the position one square down and one square to the right from the current one
	Position DownRight() const;

	// Change the current position with the given offsets
	void GoTowards(const int rowChange, const int columnChange);

	// Check if the position have the same row and the same column
	bool operator ==(const Position& other) const;

	// Check if this position has a smaller row than the other or if it has the same row and a smaller column
	bool operator <(const Position& other) const;
};

