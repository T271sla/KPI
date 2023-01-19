#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Probability
{
	double chance;
	int vertix;
};

void BuildGraph(int graph[300][300]);
void BuildPheromoneGraph(double pheromoneGraph[300][300]);
void BuildPheromoneSumGraph(double pheromoneSumGraph[300][300]);
void BuildVisibilityGraph(double visibilityGraph[300][300], int graph[300][300]);
void TSPFindOptimal(int graph[300][300], double pheromoneGraph[300][300], double pheromoneSumGraph[300][300]);
double TSPAlgorithm(int graph[300][300], double pheromoneGraph[300][300], double pheromoneSumGraph[300][300], int alpha, int beta, double ro, double LMin, int m, int FirstSp, int EliteGen);
int GenerateStartingPoint(int UsedStartingPoints[], int M);
bool CheckForStartingPoint(int UsedStartingPoints[], int StartingPoint, int M);
double MoveProbability(int curVertix, int destination, double pheromone, int alpha, int beta, int graph[300][300], double StepTwo);
double MoveProbabilityStepOne(int curVertix, int destination, double pheromone, int alpha, int beta, int graph[300][300]);
double GetLmin(int graph[300][300]);
int GetMin(int graph[300][300], int UnvisitedVertices[300], int currVertix);
bool CheckVisited(int visited[300]);
void printArray(int arr[300]);
