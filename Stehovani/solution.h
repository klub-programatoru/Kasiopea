#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>

class Solution 
{
    public:
        Solution(int start_x, int start_y, int end_x, int end_y);
        bool isValid(std::vector<std::vector<int>>& grid, int i, int j);
        int shortestPathBinaryMatrix(std::vector<std::vector<int>> &grid, int end_y, int end_x);
        std::vector<std::pair<int, std::pair<int, int>>> allPaths(std::vector<std::vector<int>> &grid);
        int start_x = 0,  start_y = 0, end_y = 0, end_x = 0;

        std::vector<std::vector<int>> dirs = {{0,1},{1,0},{-1,0},{0,-1}};
};

#endif // SOLUTION_H