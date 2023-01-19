#include <iostream>
#include <ctime>
#include "Header.h"
using namespace std;

int main()
{

    int graph[300][300];
    auto pheromoneGraph = new double[300][300];
    auto pheromoneSumGraph = new double[300][300];

    BuildGraph(graph);
    BuildPheromoneGraph(pheromoneGraph);
    BuildPheromoneSumGraph(pheromoneSumGraph);

    /*
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
    }*/

    TSPFindOptimal(graph, pheromoneGraph, pheromoneSumGraph);
}

void BuildGraph(int graph[300][300])
{
    for (int i = 0; i < 300; i++)
    {
        for (int j = 0; j < 300; j++)
        {
            if (i == j)
            {
                graph[i][j] = 0;
            }
            else
            {
                graph[i][j] = (rand() % 146) + 5;
            }
        }
    }

    for (int i = 0; i < 300; i++)
    {
        for (int j = i; j < 300; j++)
        {
            if (i != j)
            {
                int randNum = rand() % 2;

                if (randNum == 1)
                {
                    graph[j][i] = graph[i][j];
                }
            }
        }
    }
}

void BuildPheromoneGraph(double pheromoneGraph[300][300])
{
    for (int i = 0; i < 300; i++)
    {
        for (int j = 0; j < 300; j++)
        {
            if (i == j)
            {
                pheromoneGraph[i][j] = 0;
            }
            else
            {
                pheromoneGraph[i][j] = rand() % 9 + 1;
                pheromoneGraph[i][j] = pheromoneGraph[i][j] / 10;
            }
        }
    }
}

void BuildPheromoneSumGraph(double pheromoneSumGraph[300][300])
{
    for (int i = 0; i < 300; i++)
    {
        for (int j = 0; j < 300; j++)
        {
            pheromoneSumGraph[i][j] = 0;
        }
    }
}

void BuildVisibilityGraph(double visibilityGraph[300][300], int graph[300][300])
{
    for (int i = 0; i < 300; i++)
    {
        for (int j = 0; j < 300; j++)
        {
            visibilityGraph[i][j] = 1 / graph[i][j];
        }
    }
}

