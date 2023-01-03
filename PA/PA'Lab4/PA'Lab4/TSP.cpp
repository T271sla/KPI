#include "Header.h"

void TSPAlgorithm(int graph[200][200], double pheromoneGraph[200][200], double pheromoneSumGraph[200][200])
{
	int Alpha = 3;
	int Beta = 2;
	double Ro = 0.3;
	int Lmin = GetLmin(graph);
	List<Ant> Ants;
	int UsedStartingPoints[45];

	for (int i = 0; i < 45; i++)
	{
		UsedStartingPoints[i] = -1;
	}

	for (int i = 0; i < 45; i++)
	{
		int StartingPoint = GenerateStartingPoint(UsedStartingPoints, i);
		Ants.Push(Ant(StartingPoint));
	}

	int iteration = 0;

	while (iteration < 20)
	{
		for (int i = 0; i < 200; i++)
		{
			Ants.GetAt(i).Reset();
		}

		for (int i = 0; i < 45; i++)
		{
			while (Ants.GetAt(i).UnvisitedVertices.Length() != 0)
			{
				double* Probabilities = new double[Ants.GetAt(i).UnvisitedVertices.Length()];
				int noPath = 0;

				for (int j = 0; j < Ants.GetAt(i).UnvisitedVertices.Length(); j++)
				{
					if (graph[Ants.GetAt(i).Path.GetAt(Ants.GetAt(i).Path.Length() - 1)][Ants.GetAt(i).UnvisitedVertices.GetAt(i)] != 0)
					{
						Probabilities[i] = MoveProbability(Ants.GetAt(i).Path.GetAt(Ants.GetAt(i).Path.Length() - 1), Ants.GetAt(i).UnvisitedVertices.GetAt(j), pheromoneGraph[Ants.GetAt(i).Path.GetAt(Ants.GetAt(i).Path.Length() - 1)][Ants.GetAt(i).UnvisitedVertices.GetAt(j)], Alpha, Beta, graph, Ants.GetAt(i).UnvisitedVertices.Length());
					}
					else
					{
						noPath++;
					}
				}

				Ants.GetAt(i).ChooseDestination(Probabilities, noPath);

				pheromoneSumGraph[Ants.GetAt(i).Path.GetAt(Ants.GetAt(i).Path.Length() - 2)][Ants.GetAt(i).Path.GetAt(Ants.GetAt(i).Path.Length() - 1)] += Lmin / Ants.GetAt(i).getL(graph);

				delete[] Probabilities;
			}
		}

		double temp;

		for (int m = 0; m < 200; m++)
		{
			for (int n = 0; n < 200; n++)
			{
				if (m != n)
				{
					temp = pheromoneGraph[m][n];
					pheromoneGraph[m][n] = (1 - Ro) * temp + pheromoneSumGraph[m][n];
				}
			}
		}

		iteration++;
	}

	printList(Ants.GetAt(199));
}

int GenerateStartingPoint(int UsedStartingPoints[45], int M)
{
	int StartingPoint = rand() % 200;
	if (!CheckForStartingPoint(UsedStartingPoints, StartingPoint, M))
	{
		StartingPoint = GenerateStartingPoint(UsedStartingPoints, M);
	}

	return StartingPoint;
}

bool CheckForStartingPoint(int UsedStartingPoints[45], int StartingPoint, int M)
{
	for (int i = 0; i < M; i++)
	{
		if (StartingPoint == UsedStartingPoints[i])
		{
			return false;
		}
	}

	return true;
}

double MoveProbability(int curVertix, int destination, int pheromone, int alpha, int beta, int graph[200][200], int UnvisitedVerticesCount)
{
	double StepOne = MoveProbabilityStepOne(curVertix, destination, pheromone, alpha, beta, graph);
	double StepTwo = 0;

	for (int i = 0; i < UnvisitedVerticesCount; i++)
	{
		StepTwo += MoveProbabilityStepOne(curVertix, i, pheromone, alpha, beta, graph);
	}

	double probability = StepOne / StepTwo;

	return probability;
}

double MoveProbabilityStepOne(int curVertix, int destination, int pheromone, int alpha, int beta, int graph[200][200])
{
	double StepOne = (pow(pheromone, alpha) * pow((1 / graph[curVertix][destination]), beta));
	return StepOne;
}

int GetLmin(int graph[200][200])
{
	int Lmin = 0;
	int min = graph[0][1];
	int newVertix = 1;

	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			if ((graph[i][j] < min) && (graph[i][j] != 0))
			{
				min = graph[i][j];
				newVertix = j;
			}
		}
	}

	int visited[200];

	for (int i = 0; i < 200; i++)
	{
		visited[i] = 0;
	}

	visited[newVertix] = min;
	int iteration = 1;
	GetMin(graph, visited, newVertix, iteration);

	for (int i = 0; i < 200; i++)
	{
		Lmin += visited[i];
	}

	printArray(visited);

	return Lmin;
}

void GetMin(int graph[200][200], int visited[200], int Vertix, int& iteration)
{
	int min = 0;
	int newVertix = 0;

	for (int j = 0; j < 200; j++)
	{
		if ((min == 0) && (graph[Vertix][j] != 0))
		{
			min = graph[Vertix][j];
			newVertix = j;
		}

		if ((graph[Vertix][j] < min) && (graph[Vertix][j] != 0))
		{
			min = graph[Vertix][j];
			newVertix = j;
		}
	}

	visited[newVertix] = min;
	iteration++;

	if (iteration < 200)
	{
		GetMin(graph, visited, newVertix, iteration);
	}

	return;
}