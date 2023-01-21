#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Probability
{
	double chance;
	int vertix;
};

void BuildGraph(int graph[200][200]);
void BuildPheromoneGraph(double pheromoneGraph[200][200]);
void BuildPheromoneSumGraph(double pheromoneSumGraph[200][200]);
void BuildVisibilityGraph(double visibilityGraph[200][200], int graph[200][200]);
void TSPAlgorithm(int graph[200][200], double pheromoneGraph[200][200], double pheromoneSumGraph[200][200]);
int GenerateStartingPoint(int UsedStartingPoints[45], int M);
bool CheckForStartingPoint(int UsedStartingPoints[45], int StartingPoint, int M);
double MoveProbability(int curVertix, int destination, double pheromone, int alpha, int beta, int graph[200][200], double StepTwo);
double MoveProbabilityStepOne(int curVertix, int destination, double pheromone, int alpha, int beta, int graph[200][200]);
double GetLmin(int graph[200][200]);
int GetMin(int graph[200][200], int UnvisitedVertices[200], int currVertix);
bool CheckVisited(int visited[200]);
void printArray(int arr[200]);