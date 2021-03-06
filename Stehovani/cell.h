#ifndef CELL_H
#define CELL_H

class Cell
{
    public:
        Cell(int r, int c, char symbol);
        int GetRow();
        int GetColumn();
        char GetChar();
        void SetChar(char toReplace);
        int GetCounter();
        void IncrementCounter();
    protected:
        int r;      //Row of cell
        int c;      //Column of cell
        char symbol;        //Symbol of cell
        int counter;        //Number of visits; initialized to be 1 in cell constructor
};

#endif // CELL_H