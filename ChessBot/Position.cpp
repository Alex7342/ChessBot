#include "Position.h"

Position::Position(const int row, const int column) : _row(row), _column(column) {}

int Position::row()
{
    return this->_row;
}

int Position::column()
{
    return this->_column;
}

Position Position::Up()
{
    return Position(this->_row - 1, this->_column);
}

Position Position::Down()
{
    return Position(this->_row + 1, this->_column);
}

Position Position::Left()
{
    return Position(this->_row, this->_column - 1);
}

Position Position::Right()
{
    return Position(this->_row, this->_column + 1);
}

Position Position::UpLeft()
{
    return Position(this->_row - 1, this->_column - 1);
}

Position Position::UpRight()
{
    return Position(this->_row - 1, this->_column + 1);
}

Position Position::DownLeft()
{
    return Position(this->_row + 1, this->_column - 1);
}

Position Position::DownRight()
{
    return Position(this->_row + 1, this->_column + 1);
}

Position Position::GoTowards(const int rowChange, const int columnChange)
{
    return Position(this->_row + rowChange, this->_column + columnChange);
}
