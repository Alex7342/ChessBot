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
