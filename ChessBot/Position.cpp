#include "Position.h"

Position::Position() : _row(0), _column(0) {}

Position::Position(const int row, const int column) : _row(row), _column(column) {}

int Position::row() const
{
    return this->_row;
}

int Position::column() const
{
    return this->_column;
}

Position Position::Up() const
{
    return Position(this->_row - 1, this->_column);
}

Position Position::Down() const
{
    return Position(this->_row + 1, this->_column);
}

Position Position::Left() const
{
    return Position(this->_row, this->_column - 1);
}

Position Position::Right() const
{
    return Position(this->_row, this->_column + 1);
}

Position Position::UpLeft() const
{
    return Position(this->_row - 1, this->_column - 1);
}

Position Position::UpRight() const
{
    return Position(this->_row - 1, this->_column + 1);
}

Position Position::DownLeft() const
{
    return Position(this->_row + 1, this->_column - 1);
}

Position Position::DownRight() const
{
    return Position(this->_row + 1, this->_column + 1);
}

void Position::GoTowards(const int rowChange, const int columnChange)
{
    this->_row += rowChange;
    this->_column += columnChange;
}

bool Position::operator==(const Position& other) const
{
    return this->_row == other._row && this->_column == other._column;
}

bool Position::operator!=(const Position& other) const
{
    return this->_row != other._row || this->_column != other._column;
}

Position Position::operator+(const Position& other)
{
    return Position(this->_row + other._row, this->_column + other._column);
}

bool Position::operator<(const Position& other) const
{
    return this->_row < other._row || (this->_row == other._row && this->_column < other._column);
}
