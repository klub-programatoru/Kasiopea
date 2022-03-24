#ifndef GRAPH_H
#define GRAPH_H

#include "cell.h"
#include <vector>
#include <stack>

class Graph
{
    public:
        Graph(int height, int width);
        void LoadGraph(std::vector<std::vector<char>> tab);
        // void DisplayGraph();
        void DFS(int r, int c);
        int ShortestPath(int r, int c);
        // void DelayFrame(clock_t millisec);
        int start_x = 0, start_y = 0;
        std::vector<std::pair<int, int>> points;
        std::vector<int> solutions;
    private:
        int height;     //# of rows of maze
        int width;     //# of columns of maze
        int numPaths;     //# of possible path positions in maze
        int pathDistance;     //Total distance of correct position sequence
        char buffer;     //To store char elements from external text-file
        const char obstacle = 'X';
        const char start = 'D';
        const char path = '.'; 
        const char goal = '$';    //Constant chars to represent elements of maze
        double cellsVisited;     //# of cells visited; does not contain duplications of cells


        std::vector <std::vector<Cell*> > maze;     //Stores maze
        std::vector <Cell*> cells;     //Stores individual rows of maze to be allocated into maze 2-dimensional vector
        std::stack <Cell*> cellSequence;     //Stack of cells to store sequence of positions in use
        
};

#endif // GRAPH_H