#include "Header.h"
#include "Ant.h"

void printList(Ant Ant);

bool CheckOrig(vector<int> Path)
{
	for (int i = 0; i < Path.size() - 1; i++)
	{
		for (int j = i + 1; j < Path.size() - 1; j++)
		{
			if (Path.at(i) == Path.at(j))
			{
				return false;
			}
		}
	}

	return true;
}

void TSPAlgorithm(int graph[200][200], double pheromoneGraph[200][200], double pheromoneSumGraph[200][200])
{
	int Alpha = 3;
	int Beta = 2;
	double Ro = 0.3;
	double Lmin = GetLmin(graph);
	vector<Ant> Ants;
	vector<Probability> Probabilities;
	int UsedStartingPoints[45];

	for (int i = 0; i < 45; i++)
	{
		UsedStartingPoints[i] = -1;
	}

	for (int i = 0; i < 45; i++)
	{
		int StartingPoint = GenerateStartingPoint(UsedStartingPoints, i);
		Ants.push_back(Ant(StartingPoint));
	}

	int iteration = 0;
	int count = 0;

	while (iteration < 1000)
	{
		for (int i = 0; i < Ants.size(); i++)
		{
			Ants.at(i).Reset();
		}

		for (int i = 0; i < Ants.size(); i++)
		{
			while (Ants.at(i).UnvisitedVertices.size() != 0)
			{
				Probabilities.clear();

				double StepTwo = 0;

				for (int p = 0; p < Ants.at(i).UnvisitedVertices.size(); p++)
				{
					StepTwo += MoveProbabilityStepOne(Ants.at(i).Path.at(Ants.at(i).Path.size() - 1), Ants.at(i).UnvisitedVertices.at(p), pheromoneGraph[Ants.at(i).Path.at(Ants.at(i).Path.size() - 1)][Ants.at(i).UnvisitedVertices.at(p)], Alpha, Beta, graph);
				}

				for (int j = 0; j < Ants.at(i).UnvisitedVertices.size(); j++)
				{
					if (graph[Ants.at(i).Path.at(Ants.at(i).Path.size() - 1)][Ants.at(i).UnvisitedVertices.at(j)] != 0)
					{
						Probability prob;
						prob.chance = MoveProbability(Ants.at(i).Path.at(Ants.at(i).Path.size() - 1), Ants.at(i).UnvisitedVertices.at(j), pheromoneGraph[Ants.at(i).Path.at(Ants.at(i).Path.size() - 1)][Ants.at(i).UnvisitedVertices.at(j)], Alpha, Beta, graph, StepTwo);
						prob.vertix = Ants.at(i).UnvisitedVertices.at(j);
						Probabilities.push_back(prob);
					}
					else
					{
						Probability prob;
						prob.chance = -1;
						prob.vertix = Ants.at(i).UnvisitedVertices.at(j);
						Probabilities.push_back(prob);
					}
				}

				Ants.at(i).ChooseDestination(Probabilities);

				count++;
			}
			Ants.at(i).Path.push_back(Ants.at(i).StartingPoint);
			for (int m = 0; m < Ants.at(i).Path.size() - 1; m++)
			{
				pheromoneSumGraph[Ants.at(i).Path.at(m)][Ants.at(i).Path.at(m + 1)] += Lmin / Ants.at(i).getL(graph);
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

		BuildPheromoneSumGraph(pheromoneSumGraph);

		iteration++;

		if ((iteration + 1) % 20 == 0)
		{
			int minIdx = 0;
			int min = Ants.at(0).getL(graph);
			int maxIdx = 0;
			int max = Ants.at(0).getL(graph);
			double SumL = 0;

			for (int i = 1; i < Ants.size(); i++)
			{
				if (Ants.at(i).getL(graph) < min)
				{
					min = Ants.at(i).getL(graph);
					minIdx = i;
				}

				if (Ants.at(i).getL(graph) > max)
				{
					max = Ants.at(i).getL(graph);
					maxIdx = i;
				}

				SumL += Ants.at(i).getL(graph);
			}
			cout << Ants.at(minIdx).getL(graph) << " " << Ants.at(maxIdx).getL(graph) << " " << (SumL / Ants.size()) << endl;
		}
	}
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

double MoveProbability(int curVertix, int destination, double pheromone, int alpha, int beta, int graph[200][200], double StepTwo)
{
	double StepOne = MoveProbabilityStepOne(curVertix, destination, pheromone, alpha, beta, graph);

	double probability = StepOne / StepTwo;

	return probability;
}

double MoveProbabilityStepOne(int curVertix, int destination, double pheromone, int alpha, int beta, int graph[200][200])
{
	if (graph[curVertix][destination] != 0)
	{
		double edge = graph[curVertix][destination];
		double visibility = 1 / edge;
		double StepOne = (pow(pheromone, alpha) * pow(visibility, beta));
		return StepOne;
	}
	else
	{
		return 0;
	}
}

double GetLmin(int graph[200][200])
{
	vector<int> Path;
	int UnvisitedVertices[200];

	for (int i = 0; i < 200; i++)
	{
		UnvisitedVertices[i] = -1;
	}

	double Lmin = 0;
	int min = graph[0][1];
	int newVertix = 1;
	int oldVertix = 0;
	UnvisitedVertices[oldVertix] = 1;
	UnvisitedVertices[newVertix] = 1;

	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			if ((graph[i][j] < min) && (graph[i][j] != 0))
			{
				min = graph[i][j];
				UnvisitedVertices[oldVertix] = -1;
				UnvisitedVertices[newVertix] = -1;
				oldVertix = i;
				newVertix = j;
				UnvisitedVertices[oldVertix] = 1;
				UnvisitedVertices[newVertix] = 1;
			}
		}
	}

	int first = oldVertix;

	Path.push_back(oldVertix);
	Path.push_back(newVertix);

	while (Path.size() != 200)
	{
		int next = GetMin(graph, UnvisitedVertices, Path.back());
		UnvisitedVertices[next] = 1;
		Path.push_back(next);
	}

	Path.push_back(first);

	bool check = CheckOrig(Path);

	for (int i = 0; i < Path.size() - 1; i++)
	{
		Lmin += graph[Path.at(i)][Path.at(i + 1)];
	}

	return Lmin;
}

int GetMin(int graph[200][200], int UnvisitedVertices[200], int currVertix)
{
	int min = 0;
	int nextVertix = 0;

	for (int i = 0; i < 200; i++)
	{
		if ((graph[currVertix][i] != 0) && (UnvisitedVertices[i] == -1))
		{
			min = graph[currVertix][i];
			nextVertix = i;
			UnvisitedVertices[i] = 1;
			break;
		}
	}

	for (int i = 0; i < 200; i++)
	{
		if ((graph[currVertix][i] != 0) && (graph[currVertix][i] < min) && (UnvisitedVertices[i] == -1))
		{
			min = graph[currVertix][i];
			UnvisitedVertices[nextVertix] = -1;
			nextVertix = i;
			UnvisitedVertices[i] == 1;
		}
	}

	return nextVertix;
}

void printList(Ant Ant)
{
	cout << Ant.Path.size() << endl;
	for (int i = 0; i < 200; i++)
	{
		cout << Ant.Path.at(i) << "->";
	}
	cout << Ant.Path.at(0);
	cout << endl;
	cout << endl;
}

void printArray(int arr[200])
{
	for (int i = 0; i < 200; i++)
	{
		cout << arr[i] << "->";
	}

	cout << endl;
	cout << endl;
}