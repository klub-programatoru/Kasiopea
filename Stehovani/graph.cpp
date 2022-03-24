#include "graph.h"
#include "cell.h"
#include <iostream>
#include <string>
#include <algorithm>

Graph::Graph(int height, int width)
{
    this->height = height;
    this->width = width;
}

//Loads in the maze from an external text-file
//Gets # rows, # columns and all symbols for all elements in maze
void Graph::LoadGraph(std::vector<std::vector<char>> tab)
{
    maze.clear();
    //Adds elements from external text-file to one row of the maze
    for (int row = 0; row < tab.size(); row++)
    {
        for (int col = 0; col < tab[row].size(); col++)
        {
            buffer = tab[row][col];

            cells.push_back(new Cell(row, col, buffer));

            //If there is a new path position, increment the counter
            if (buffer == path)
            {
                numPaths++;
            }
            else if(buffer == start)
            {
                start_x = col;
                start_y = row;
            }

        }

        //Pushes the row into a 2-dimensional vector
        maze.push_back(cells);
        cells.clear();
    }
}

/*Depth First Search
Maze search starts at r = 1, c = 1
*/
void Graph::DFS(int r, int c)
{
    //Displays state of maze as it is being solved

    //If goal is reached, stop
    if (maze[r][c] -> GetChar() == goal){
        //Declare array to hold 'solution set' for valid path
        solutions.push_back(cellSequence.size());
        int stackSize = cellSequence.size();
        Cell** solutionSet = new Cell*[stackSize];

        //Fill array with path positions
        for (int i = 0; i < stackSize; i++)
        {
            solutionSet[i] = cellSequence.top();
            //Remove the topmost cell once it has been added to array
            cellSequence.pop();
        }

        //Delete dynamically allocated array
        delete solutionSet;

        //Total distance of path is the stack size + 1 for the goal cell
        pathDistance = stackSize + 1;
    }
    else {
        //Otherwise, push current cell to stack
        if (maze[r][c] -> GetChar() == path || maze[r][c] -> GetChar() == start)
        {
            points.push_back(std::make_pair(r, c));
         cellSequence.push(maze[r][c]);
         cellsVisited++;
        }

        //Set current cell as visited and mark it with #times visited - 1 (know how many repeats)
        maze[r][c] -> SetChar(maze[r][c] -> GetCounter());

        //Increment the number of times visited (prior)
        maze[r][c] -> IncrementCounter();


        //Goes through all 4 adjacent cells and checks conditions

        //Down
        if (r+1 < maze.size() && ((maze[r+1][c] -> GetChar() == path) || (maze[r+1][c] -> GetChar() == goal)))
        {
            r++;
            DFS(r, c);
        }
        //Up
        else if ((r-1 >= 0) && ((maze[r-1][c] -> GetChar() == path) || (maze[r-1][c] -> GetChar() == goal)))
        {
            r--;
            DFS(r, c);
        }
        //Right
        else if (c+1 < maze[0].size() && ((maze[r][c+1] -> GetChar() == path) || (maze[r][c+1] -> GetChar() == goal)))
        {
            c++;
            DFS(r, c);
        }
        //Left
        else if (c-1 >= 0 && ((maze[r][c-1] -> GetChar() == path) || (maze[r][c-1] -> GetChar() == goal)))
        {
            c--;
            DFS(r, c);
        }
        else
        {
            //No neighboring cells are free and unvisited, so we need to backtrack

            //Sets current cell to obstacle
            maze[r][c] -> SetChar(obstacle);

            //Remove current (top) cell from stack
            cellSequence.pop();

            if (cellSequence.empty())
            {
                // std::cout << std::endl << "Finished!";
                
            }
            else
            {
                //Get row and column of last valid cell in stack and use those to resume search
                r = cellSequence.top() -> GetRow();
                c = cellSequence.top() -> GetColumn();

                DFS(r, c);
            }
        }
    }
}

// int Graph::ShortestPath(int r, int c)
// {
//     //Displays state of maze as it is being solved

//     //If goal is reached, stop
//     if (maze[r][c] -> GetChar() == goal){
//         //Declare array to hold 'solution set' for valid path
//         int stackSize = cellSequence.size();

//         while (!cellSequence.empty())
//         {
//             cellSequence.pop();
//         }

//         return stackSize;
        
//         Cell** solutionSet = new Cell*[stackSize];

//         //Fill array with path positions
//         for (int i = 0; i < stackSize; i++)
//         {
//             solutionSet[i] = cellSequence.top();
//             //Remove the topmost cell once it has been added to array
//             cellSequence.pop();
//         }

//         //Delete dynamically allocated array
//         delete solutionSet;

//         //Total distance of path is the stack size + 1 for the goal cell
//         pathDistance = stackSize + 1;
//     }
//     else {
//         //Otherwise, push current cell to stack
//         if (maze[r][c] -> GetChar() == path || maze[r][c] -> GetChar() == start)
//         {
//             points.push_back(std::make_pair(r, c));
//             cellSequence.push(maze[r][c]);
//             cellsVisited++;
//         }

//         //Set current cell as visited and mark it with #times visited - 1 (know how many repeats)
//         maze[r][c] -> SetChar(maze[r][c] -> GetCounter());

//         //Increment the number of times visited (prior)
//         maze[r][c] -> IncrementCounter();


//         //Goes through all 4 adjacent cells and checks conditions

//         int a = INT_MAX, b = INT_MAX, d = INT_MAX, e = INT_MAX;

//         //Down
//         if (r+1 < maze.size() && ((maze[r+1][c] -> GetChar() == path) || (maze[r+1][c] -> GetChar() == goal)))
//         {
//             a = ShortestPath(r+1, c);
//         }
//         //Up
//         if ((r-1 > 0) && ((maze[r-1][c] -> GetChar() == path) || (maze[r-1][c] -> GetChar() == goal)))
//         {
//             b = ShortestPath(r-1, c);
//         }
//         //Right
//         if (c+1 < maze[0].size() && ((maze[r][c+1] -> GetChar() == path) || (maze[r][c+1] -> GetChar() == goal)))
//         {
//             d = ShortestPath(r, c+1);
//         }
//         //Left
//         if (c-1 > 0 && ((maze[r][c-1] -> GetChar() == path) || (maze[r][c-1] -> GetChar() == goal)))
//         {
//             e = ShortestPath(r, c-1);
//         }

//         int min_ab, min_cd, min;

//         if(a != INT_MAX || b != INT_MAX || d != INT_MAX || e != INT_MAX)
//         {
//             min_ab = a < b ? a : b;
//             min_cd = d < e ? d : e;
//             min = min_ab < min_cd ? min_ab : min_cd;
//             solutions.push_back(min);
//             return min;
//             a = INT_MAX, b = INT_MAX, d = INT_MAX, e = INT_MAX;
//         }
//         else
//         {
//             //No neighboring cells are free and unvisited, so we need to backtrack

//             //Sets current cell to obstacle
//             maze[r][c] -> SetChar(obstacle);

//             //Remove current (top) cell from stack
//             cellSequence.pop();

//             return INT_MAX;
//         }
//     }
// }