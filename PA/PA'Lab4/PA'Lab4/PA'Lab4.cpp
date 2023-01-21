#include <iostream>
#include <ctime>
#include "Header.h"
using namespace std;

int main()
{
    srand(time(NULL));

    int graph[200][200];
    double pheromoneGraph[200][200];
    double pheromoneSumGraph[200][200];

    BuildGraph(graph);
    BuildPheromoneGraph(pheromoneGraph);
    BuildPheromoneSumGraph(pheromoneSumGraph);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << graph[i][j] << '\t';
        }
        cout << endl;
    }
    
    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << pheromoneGraph[i][j] << '\t';
        }
        cout << endl;
    }

    cout << endl;

    TSPAlgorithm(graph, pheromoneGraph, pheromoneSumGraph);
}

void BuildGraph(int graph[200][200])
{
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 200; j++)
        {
            if (i == j)
            {
                graph[i][j] = 0;
            }
            else 
            {
                graph[i][j] = rand() % 51;
            }
        }
    }
}

void BuildPheromoneGraph(double pheromoneGraph[200][200])
{
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 200; j++)
        {
            if (i == j)
            {
                pheromoneGraph[i][j] = 0;
            }
            else
            {
                pheromoneGraph[i][j] = 0.1;
            }
        }
    }
}

void BuildPheromoneSumGraph(double pheromoneSumGraph[200][200])
{
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 200; j++)
        {
            pheromoneSumGraph[i][j] = 0;
        }
    }
}
