#include "solution.h"
#include <vector>

using namespace std;

Solution::Solution(int start_x, int start_y, int end_x, int end_y)
{
    this->start_x = start_x;
    this->start_y = start_y;
    this->end_x = end_x;
    this->end_y = end_y;
}

bool Solution::isValid(std::vector<std::vector<int>>& grid, int i, int j)
{
    if(i < 0 || i >= grid.size() || j < 0 || j >= grid[i].size() || grid[i][j] != 0)
        return false;
    return true;
}

int Solution::shortestPathBinaryMatrix(std::vector<std::vector<int>> &grid, int end_y, int end_x)
{
    if(grid.empty())
        return 0;

    if(grid[start_y][start_x] == 1 || grid[end_y][end_x] == 1) 
        return -1;

    int m = grid.size(), n = grid[0].size();
    pair<int, int> start = {start_y, start_x};
    pair<int, int> end = {end_y, end_x};
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    // no priority queue needed: the graph is not weighted
    vector<std::pair<int,int>> q;
    q.push_back(start);
    visited[start.first][start.second] = true;
    int count = 0;

    while(!q.empty())
    {
        // just iterate the vector and populate a new one
        vector<std::pair<int,int>> q2;
        for(auto const& cur: q) {
            if(cur.first == end.first && cur.second == end.second)
                return count;
            for(auto dir : dirs)
            {
                int x = cur.first, y = cur.second;

                if(isValid(grid, x + dir[0], y + dir[1]))
                    x += dir[0], y += dir[1];

                if(!visited[x][y])
                {
                    visited[x][y] = true;
                    q2.push_back({x,y});
                }
            }
        }
        count++;
        q = q2; // prepare for next iteration
    }
    return -1;
}

vector<pair<int, pair<int, int>>> Solution::allPaths(std::vector<std::vector<int>> &grid)
{
    if(grid.empty())
        return {make_pair(0, make_pair(0, 0))};

    if(grid[start_y][start_x] == 1) 
        return {make_pair(-1, make_pair(-1, -1))};

    int m = grid.size(), n = grid[0].size();
    pair<int, int> start = {start_y, start_x};
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    // no priority queue needed: the graph is not weighted
    vector<std::pair<int,int>> q;
    q.push_back(start);
    visited[start.first][start.second] = true;
    int count = 0;
    vector<pair<int, pair<int, int>>> paths;

    while(!q.empty())
    {
        // just iterate the vector and populate a new one
        vector<std::pair<int,int>> q2;
        for(auto const& cur: q) {
            paths.push_back(make_pair(count, make_pair(cur.first, cur.second)));
            for(auto dir : dirs)
            {
                int x = cur.first, y = cur.second;

                if(isValid(grid, x + dir[0], y + dir[1]))
                    x += dir[0], y += dir[1];

                if(!visited[x][y])
                {
                    visited[x][y] = true;
                    q2.push_back({x,y});
                }
            }
        }
        count++;
        q = q2; // prepare for next iteration
    }

    // // push_back and return all visited cells
    // for(int i = 0; i < visited.size(); i++)
    // {
    //     for(int j = 0; j < visited[i].size(); j++)
    //     {
    //         if(visited[i][j])
    //         {
    //             paths.push_back(make_pair(i, j));   
    //         }
    //     }
    // }
    return paths;
}