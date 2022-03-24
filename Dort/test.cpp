#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> get_num_elements(vector<int> row)
{
    int count = 0;
    vector<int> v;

    v.clear();
    for (int i = 0; i < row.size(); i++)
    {
        if (row[i] != -1)
        {
            v.push_back(row[i]);
        }
    }
    return v;
}

void fillTable(vector<vector<int>> &table, int R, int S, int K)
{
    vector<vector<int>> num_elements(R, vector<int>());

    // find number of color in each row of the table
    for (int i = 0; i < table.size(); i++)
    {
        num_elements[i] = get_num_elements(table[i]);
    }

    if(num_elements[0].empty())
    {
        return;
    }

    for (int i = 0; i < table.size(); i++)
    {
        // if there is only one element in the row
         if (num_elements[i].size() == 1)
        {
            // store the color of the one cell
            int color = num_elements[i][0];

            // fill all the elements except the one that is already filled
            // with the given color values
            for (int cell = 0; cell < table[i].size(); cell++)
            {
                if (table[i][cell] == -1)
                {
                    table[i][cell] = color;
                }
            }

            // fill all the other consecutive rows that are empty
            while (num_elements[i + 1].empty() && i + 1 < R)
            {
                for (int cell = 0; cell < table[i + 1].size(); cell++)
                {
                    table[i + 1][cell] = color;
                }
                // switch to next row
                i++;
            }
        }
        // if the table is neither full nor empty
        else if (!num_elements[i].empty() && num_elements[i].size() != S)
        {
            // cell represents the n-th element in a row
            int cell = 0, current_row = i;

            // for each color in a row fill wiht that color all the cell in front
            for (int c = 0; c < num_elements[i].size(); c++)
            {
                while (table[i][cell] == -1)
                {
                    table[i][cell] = num_elements[i][c];
                    cell++;
                }
                cell++;

                //if there are some cells remaining after hitting the last color, fill them
                while (c == num_elements[i].size() - 1 && cell < S)
                {
                    table[i][cell] = num_elements[i][c];
                    cell++;
                }
            }

            // fill all the other consecutive rows that are empty
            while (num_elements[i + 1].empty() && i + 1 < R)
            {
                cell = 0;
                // for each color in a row fill wiht that color all the cell in front
                for (int c = 0; c < num_elements[current_row].size(); c++)
                {
                    while (table[current_row][cell] == num_elements[current_row][c])
                    {
                        table[i + 1][cell] = num_elements[current_row][c];
                        cell++;
                    }

                    //if there are some cells remaining after hitting the last color, fill them
                    while (c == num_elements[current_row].size() - 1 && cell < S)
                    {
                        table[i + 1][cell] = num_elements[current_row][c];
                        cell++;
                    }
                }
                // switch to next row
                i++;
            }
        }
    }
}

int main()
{
    ifstream input("C-tezky.txt");
    ofstream output("C-vysledek.txt");

    int T = 0, R = 0, S = 0, K = 0;

    input >> T;
    for (int i = 0; i < T; i++)
    {
        // load row column and number of colors respectively
        input >> R >> S >> K;
        // vector to store the cells of the table
        vector<vector<int>> table(R, vector<int>(S, 0));

        // load the initial state of the table
        for (int row = 0; row < R; row++)
        {
            for (int col = 0; col < S; col++)
            {
                input >> table[row][col];
            }
        }

        if(K <= R*S || K != 0)
        {
            // fill in the table
            fillTable(table, R, S, K);
        }

        // output the filled table
        for (int row = 0; row < R; row++)
        {
            for (int col = 0; col < S; col++)
            {
                output << to_string(table[row][col]) + ' ';
            }
            output << endl;
        }
    }
}