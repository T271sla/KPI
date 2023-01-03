﻿#include <iostream>
#include <cmath>
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
        for (int j = i; j < 200; j++)
        {
            pheromoneGraph[i][j] = 0;
        }
    }
}

void BuildPheromoneSumGraph(double pheromoneSumGraph[200][200])
{
    for (int i = 0; i < 200; i++)
    {
        for (int j = i; j < 200; j++)
        {
            pheromoneSumGraph[i][j] = ((rand() % 3) + 1) / 10;
        }
    }
}

void BuildVisibilityGraph(double visibilityGraph[200][200], int graph[200][200])
{
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 200; j++)
        {
            visibilityGraph[i][j] = 1 / graph[i][j];
        }
    }
}

double RD(double min, double max)
{
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}