#include <fstream>     //ifstream
#include <iostream>     //standard c output modes
#include <iomanip>     //setprecision()
#include <vector>     //vectors, including 2-dimensional
#include <cstdlib>     //system("cls") to clear console
#include <stack>     //stacks
#include <math.h>     //sqrt()
#include <ctime>     //clock in DelayFrame()
#include <vector>
#include <algorithm>
#include <string>

#include "graph.h"
#include "solution.h"


using namespace std;

long int sortArr(vector<pair<int, pair<int, int>>> points, vector<int> p, int K, int R, int S, vector<vector<char>> table, vector<vector<string>> sTable)
{
    // grid that can be analyzed for shortest path
    vector<vector<int>> grid(R, vector<int>(S, 1));
    // create a solution object that can be used to find the shortest path
    Solution s(0, 0, 0, 0);
    // total number of steps needed
    long int steps = 0;
    int a = 0;
    // distance from the start point
    int dist = 0;

    for(int i = 0; i < points.size(); i++)
    {
        grid[points[i].second.first][points[i].second.second] = 0;
    }

    // set the starting point
    s.start_y = p[0];
    s.start_x = p[1];

    // if there is not enough cells for the boxes, exit
    if(points.size() < K)
    {
        return -1;
    }

//******************************************************************************************************************************************
    // // change all the accessible cells into 0s
    // for(int i = 0; i < vp.size(); i++)
    // {
    //     if(table[vp[i].second[0]][vp[i].second[1]] == '.')
    //     {
    //         sTable[vp[i].second[0]][vp[i].second[1]] = to_string(vp[i].first);
    //     }
    //     else if(table[vp[i].second[0]][vp[i].second[1]] == 'D')
    //     {
    //         sTable[vp[i].second[0]][vp[i].second[1]] = to_string(vp[i].first);
    //     }
    //     else
    //     {
    //         printf("\n Error: character error - %c; at position (%i, %i) \n", table[vp[i].second[0]][vp[i].second[1]], vp[i].second[0], vp[i].second[1]);
    //     }
    // }

    // //print the filled grid
    // for(int i = 0; i < grid.size(); i++)
    // {
    //     for(int j = 0; j < grid[i].size(); j++)
    //     {
    //         if(sTable[i][j] == "X")
    //         {
    //             printf(" X ");
    //         }
    //         else if(sTable[i][j] == ".")
    //         {
    //             printf(" . ");
    //         }
    //         else
    //         {
    //             a = std::stoi(sTable[i][j]);
    //             if(a < 10)
    //             {
    //                 printf(" %i ", a);
    //             }
    //             else if(a < 100)
    //             {
    //                 printf("%i ", a);
    //             }
    //             else
    //             {
    //                 printf("%i", a);
    //             }
                
    //         }
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    
    for(int i = 0; i < R; i++)
    {
        for(int j = 0; j < S; j++)
        {
            sTable[i][j] = table[i][j];
        }
    }

    // change all the accessible cells into 0s
    for(int i = 0; i < K; i++)
    {
        if(table[points[i].second.first][points[i].second.second] == '.')
        {
            sTable[points[i].second.first][points[i].second.second] = to_string(points[i].first);
        }
        else if(table[points[i].second.first][points[i].second.second] == 'D')
        {
            sTable[points[i].second.first][points[i].second.second] = to_string(points[i].first);
        }
        else
        {
            printf("\n Error: character error - %c; at position (%i, %i) \n", table[points[i].second.first][points[i].second.second], points[i].second.first, points[i].second.second);
        }
    }

    //print the filled grid
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            if(sTable[i][j] == "X")
            {
                printf(" X ");
            }
            else if(sTable[i][j] == ".")
            {
                printf(" . ");
            }
            else
            {
                a = std::stoi(sTable[i][j]);
                if(a < 10)
                {
                    printf(" %i ", a);
                }
                else if(a < 100)
                {
                    printf("%i ", a);
                }
                else
                {
                    printf("%i", a);
                }
                
            }
        }
        cout << endl;
    }
    cout << endl;

//*****************************************************************************************************************************************    
    // calculate the steps needed to visit the closest K cells
    steps = 0;
    for(int i = 0; i < K; i++)
    {
        steps += (2 * points[i].first);
    }

    // steps = 0;
    // for(int i = K-1; i >= 0; i--)
    // {
    //     // find distance from the begining cell
    //     steps += (2 * s.shortestPathBinaryMatrix(grid, points[i].second.first, points[i].second.second));
    //     grid[points[i].second.first][points[i].second.second] = 1;
    // }
    
    return steps;
}

int main() {
    std::ifstream input("D-lehky.txt");
    std::ofstream output("D-vysledek.txt");

    int T, R, S, K;
    input >> T;  
    vector<pair<int, pair<int, int>>> points;
    vector<int> p(2, 0);

    for (int t = 0; t < T; t++) 
    {
		input >> R >> S >> K;
        vector<vector<char>> tab(R, vector<char>(S, '!'));
        vector<vector<string>> table(R, vector<string>(S, "!"));
        vector<vector<int>> grid(R, vector<int>(S, 1));

        // load the input data into a table
        for(int i = 0; i < R; i++)
        {
            for(int j = 0; j < S; j++)
            {
                input >> tab[i][j];
                if(tab[i][j] == '.')
                {
                    grid[i][j] = 0;
                }
                else if (tab[i][j] == 'D')
                {
                    grid[i][j] = 0;
                    p[0] = i;
                    p[1] = j;
                }
                
            }
        }

        // // create and load the graph from input
        // Graph graph(R, S);
        // graph.LoadGraph(tab);
        // // find all the points that are accessible
        // graph.DFS(graph.start_y, graph.start_x);
        // // get rid of any duplicates
        //points = graph.points;

        Solution s(0, 0, 0, 0);
        s.start_y = p[0];
        s.start_x = p[1];

        points = s.allPaths(grid);
        std::sort(points.begin(), points.end());
        points.erase( std::unique(points.begin(), points.end()), points.end());

        // // define starting position, which can be passed to processing function
        // p[0] = graph.start_y;
        // p[1] = graph.start_x;

        for(int i = 0; i < R; i++)
        {
            for(int j = 0; j < S; j++)
            {
                table[i][j] = tab[i][j];
            }
        }

        // process the data and return the sum of the steps that need to be taken
        long int sum = sortArr(points, p, K, R, S, tab, table);

        // output the sum
        output << to_string(sum) << std::endl;
    }
    return 0;
}