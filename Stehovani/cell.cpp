#include "cell.h"

Cell::Cell(int r, int c, char symbol)
{
    this->r = r;
    this->c = c;
    this->symbol = symbol;
}

int Cell::GetRow()
{
    return r;
}

int Cell::GetColumn()
{
    return c;
}

char Cell::GetChar()
{
    return symbol;
}

void Cell::SetChar(char toReplace)
{
    this->symbol = toReplace;
}

int Cell::GetCounter()
{
    return counter;
}

void Cell::IncrementCounter()
{
    this->counter++;
}