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

void TSPFindOptimal(int graph[300][300], double pheromoneGraph[300][300], double pheromoneSumGraph[300][300])
{
	int Alpha = 2;
	int Beta = 3;
	double Ro = 0.3;
	double Lmin = GetLmin(graph);
	int M = 45;
	int FirstSP = 152;
	int eliteGen = 0;

	int count = 0;

	/*
	cout << "Enter Alpha: ";
	cin >> Alpha;
	cout << "Enter Beta: ";
	cin >> Beta;
	cout << "Enter Ro: ";
	cin >> Ro;
	cout << "Enter Lmin(Suggested " << Lmin << "): ";
	cin >> Lmin;
	cout << "Enter number of Ants: ";
	cin >> M;
	cout << "Enter starting point for the first Ant: ";
	cin >> FirstSP;
	cout << "Will first Ant be elite? ";
	cin >> eliteGen;*/

	double min = TSPAlgorithm(graph, pheromoneGraph, pheromoneSumGraph, Alpha, Beta, Ro, Lmin, M, FirstSP, eliteGen);
	int tempAlpha = 1;

	while (true)
	{
		if (tempAlpha = 3)
		{
			tempAlpha += 1;
		}
		double tempMin = TSPAlgorithm(graph, pheromoneGraph, pheromoneSumGraph, tempAlpha, Beta, Ro, Lmin, M, FirstSP, eliteGen);
		if (tempMin < min)
		{
			min = tempMin;
			Alpha = tempAlpha;
			tempAlpha++;
		}
		else
		{
			tempAlpha++;
			count++;
			if (count >= 2)
			{
				if (tempAlpha <= Alpha)
				{
					tempAlpha = Alpha + 1;
				}
				else
				{
					break;
				}
			}
		}
	}

	int tempBeta = 1;

	while (true)
	{
		if (tempBeta = 3)
		{
			tempBeta += 1;
		}
		double tempMin = TSPAlgorithm(graph, pheromoneGraph, pheromoneSumGraph, Alpha, tempBeta, Ro, Lmin, M, FirstSP, eliteGen);
		if (tempMin < min)
		{
			min = tempMin;
			Beta = tempBeta;
			tempBeta++;
		}
		else
		{
			tempBeta++;
			count++;
			if (count >= 2)
			{
				if (tempBeta <= Beta)
				{
					tempBeta = Beta + 1;
				}
				else
				{
					break;
				}
			}
		}
	}

	double tempRo = 0.1;

	while (true)
	{
		if (tempRo = 0.3)
		{
			tempRo += 0.1;
		}
		double tempMin = TSPAlgorithm(graph, pheromoneGraph, pheromoneSumGraph, Alpha, Beta, tempRo, Lmin, M, FirstSP, eliteGen);
		if (tempMin < min)
		{
			min = tempMin;
			Ro = tempRo;
			tempBeta++;
		}
		else
		{
			tempBeta++;
			count++;
			if (count >= 2)
			{
				if (tempRo <= Ro)
				{
					tempRo = Ro + 0.1;
				}
				else
				{
					break;
				}
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			int tempL = 1000;
			double tempMin = TSPAlgorithm(graph, pheromoneGraph, pheromoneSumGraph, Alpha, Beta, Ro, tempL, M, FirstSP, eliteGen);
			if (tempMin < min)
			{
				min = tempMin;
				Lmin = tempL;
			}
		}
		if (i == 1)
		{
			int tempL = 3000;
			double tempMin = TSPAlgorithm(graph, pheromoneGraph, pheromoneSumGraph, Alpha, Beta, Ro, tempL, M, FirstSP, eliteGen);
			if (tempMin < min)
			{
				min = tempMin;
				Lmin = tempL;
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			int tempM = 15;
			double tempMin = TSPAlgorithm(graph, pheromoneGraph, pheromoneSumGraph, Alpha, Beta, Ro, Lmin, tempM, FirstSP, eliteGen);
			if (tempMin < min)
			{
				min = tempMin;
				M = tempM;
			}
		}
		if (i == 1)
		{
			int tempM = 75;
			double tempMin = TSPAlgorithm(graph, pheromoneGraph, pheromoneSumGraph, Alpha, Beta, Ro, Lmin, tempM, FirstSP, eliteGen);
			if (tempMin < min)
			{
				min = tempMin;
				M = tempM;
			}
		}
	}

	double tempMin = TSPAlgorithm(graph, pheromoneGraph, pheromoneSumGraph, Alpha, Beta, Ro, Lmin, M, FirstSP, 1);

	if (tempMin < min)
	{
		min = tempMin;
	}

	cout << min;
}

double TSPAlgorithm(int graph[300][300], double pheromoneGraph[300][300], double pheromoneSumGraph[300][300], int alpha, int beta, double ro, double LMin, int m, int FirstSp, int EliteGen)
{
	int Alpha = alpha;
	int Beta = beta;
	double Ro = ro;
	double Lmin = LMin;
	int M = m;
	int FirstSP = FirstSp;
	int eliteGen = EliteGen;

	vector<Ant> Ants;
	vector<Probability> Probabilities;
	int* UsedStartingPoints = new int[M];

	for (int i = 0; i < M; i++)
	{
		UsedStartingPoints[i] = -1;
	}

	for (int i = 0; i < M; i++)
	{
		if (i == 0)
		{
			Ants.push_back(Ant(FirstSP, eliteGen));
		}
		else
		{
			int StartingPoint = GenerateStartingPoint(UsedStartingPoints, i);
			int eliteGenerator = rand() % 2;
			Ants.push_back(Ant(StartingPoint, eliteGenerator));
		}
	}

	int iteration = 0;
	int count = 0;

	while (iteration < 20)
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

				if (Ants.at(i).elite)
				{
					pheromoneSumGraph[Ants.at(i).Path.at(Ants.at(i).Path.size() - 2)][Ants.at(i).Path.at(Ants.at(i).Path.size() - 1)] += 2 * (Lmin / Ants.at(i).getL(graph));
					count++;
				}
				else
				{
					pheromoneSumGraph[Ants.at(i).Path.at(Ants.at(i).Path.size() - 2)][Ants.at(i).Path.at(Ants.at(i).Path.size() - 1)] += Lmin / Ants.at(i).getL(graph);
					count++;
				}
			}
		}

		double temp;

		for (int m = 0; m < 300; m++)
		{
			for (int n = 0; n < 300; n++)
			{
				if (m != n)
				{
					temp = pheromoneGraph[m][n];
					pheromoneGraph[m][n] = (1 - Ro) * temp + pheromoneSumGraph[m][n];
				}
			}
		}

		iteration++;

		/*if ((iteration + 1) % 20 == 0)
		{
			int minIdx = 0;
			int min = Ants.at(0).getL(graph);

			for (int i = 1; i < Ants.size(); i++)
			{
				if (Ants.at(i).getL(graph) < min)
				{
					min = Ants.at(i).getL(graph);
					minIdx = i;
				}
			}
			cout << endl;
			printList(Ants.at(minIdx));
			cout << "L min: " << Lmin << endl;
			cout << "Path L: " << Ants.at(minIdx).getL(graph) << endl;
		}*/

		/*if ((iteration + 1) % 20 == 0)
		{
			int maxIdx = 0;
			int max = Ants.at(0).getL(graph);

			for (int i = 1; i < Ants.size(); i++)
			{
				if (Ants.at(i).getL(graph) > max)
				{
					max = Ants.at(i).getL(graph);
					maxIdx = i;
				}
			}
			cout << endl;
			printList(Ants.at(minIdx));
			cout << "L min: " << Lmin << endl;
			cout << "Path L: " << Ants.at(maxIdx).getL(graph) << endl;
		}*/

		/*if (iteration % 20 == 0)
		{
			double SumL = 0;

			for (int i = 1; i < Ants.size(); i++)
			{
				SumL += Ants.at(i).getL(graph);
			}
			cout << endl;
			printList(Ants.at(minIdx));
			cout << "L min: " << Lmin << endl;
			cout << SumL/Ants.size() << endl;
		}*/

		/*if (iteration % 20 == 0)
		{
			cout << endl;
			printList(Ants.at(0));
			cout << "L min: " << Lmin << endl;
			cout << "Path L: " << Ants.at(0).getL(graph) << endl;
		}*/
	}

	double SumL = 0;

	for (int i = 1; i < Ants.size(); i++)
	{
		SumL += Ants.at(i).getL(graph);
	}
	return SumL / Ants.size();
}

int GenerateStartingPoint(int UsedStartingPoints[], int M)
{
	int StartingPoint = rand() % 300;
	if (!CheckForStartingPoint(UsedStartingPoints, StartingPoint, M))
	{
		StartingPoint = GenerateStartingPoint(UsedStartingPoints, M);
	}

	return StartingPoint;
}

bool CheckForStartingPoint(int UsedStartingPoints[], int StartingPoint, int M)
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

double MoveProbability(int curVertix, int destination, double pheromone, int alpha, int beta, int graph[300][300], double StepTwo)
{
	double StepOne = MoveProbabilityStepOne(curVertix, destination, pheromone, alpha, beta, graph);

	double probability = StepOne / StepTwo;

	return probability;
}

double MoveProbabilityStepOne(int curVertix, int destination, double pheromone, int alpha, int beta, int graph[300][300])
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

double GetLmin(int graph[300][300])
{
	vector<int> Path;
	int UnvisitedVertices[300];

	for (int i = 0; i < 300; i++)
	{
		UnvisitedVertices[i] = -1;
	}

	double Lmin = 0;
	int min = graph[0][1];
	int newVertix = 1;
	int oldVertix = 0;
	UnvisitedVertices[oldVertix] = 1;
	UnvisitedVertices[newVertix] = 1;

	for (int i = 0; i < 300; i++)
	{
		for (int j = 0; j < 300; j++)
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

	while (Path.size() != 300)
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

int GetMin(int graph[300][300], int UnvisitedVertices[300], int currVertix)
{
	int min = 0;
	int nextVertix = 0;

	for (int i = 0; i < 300; i++)
	{
		if ((graph[currVertix][i] != 0) && (UnvisitedVertices[i] == -1))
		{
			min = graph[currVertix][i];
			nextVertix = i;
			UnvisitedVertices[i] = 1;
			break;
		}
	}

	for (int i = 0; i < 300; i++)
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
	for (int i = 0; i < 300; i++)
	{
		cout << Ant.Path.at(i) << "->";
	}
	cout << Ant.Path.at(0);
	cout << endl;
	cout << endl;
}

void printArray(int arr[300])
{
	for (int i = 0; i < 300; i++)
	{
		cout << arr[i] << "->";
	}

	cout << endl;
	cout << endl;
}