#include <iostream>
#include <vector>
#include "Queue.h"
#include "Set.h"
#include "State.h"
#include "Open.h"
using namespace std;

void FindAstar();
void FindLDFS();
void Astar(State parent);
void CheckF2();
void LDFS(State parent);
void Algorithm(State state, int row, int maxIteration, int& currIteration, int& iterations, int& check, int& deadEnds);

int main()
{
	srand(time(NULL));

	//FindLDFS();

	FindAstar();

    return 0;
}

void CheckF2()
{
	State field;
	field.makeState();
	cout << field.F2() << endl;
}

void FindLDFS()
{
	State parent;
	parent.randomState();

	cout << "First step:" << endl;

	parent.print();

	for (int i = 0; i < 8; i++)
	{
		cout << parent.GetQueenPosition(i) << " ";
	}

	cout << endl;

	long int start = clock();
	LDFS(parent);
	long int end = clock();

	cout << "LDFS time - " << end - start << "ms" << endl;
}

void FindAstar()
{
	State parent;
	parent.randomState();

	cout << "First step:" << endl;

	parent.print();

	for (int i = 0; i < 8; i++)
	{
		cout << parent.GetQueenPosition(i) << " ";
	}

	cout << endl;

	cout << "Searching for solution..." << endl;

	long int start = clock();
	Astar(parent);
	long int end = clock();

	cout << "A* time - " << end - start << "ms" << endl;
}

void Astar(State parent)
{
	PriorityQueue<State> open;
	Set<State> closed;

	int g = 0;
	int h;
	int f;
	int iterations = 1;
	int states = 1;

	open.push(parent, 0);

	while (open.GetLength() != 0)
	{
		State current = open.pop();
		g++;

		if (current.F2() == 0)
		{
			cout << "Solution is found!" << endl;
			current.print();
			cout << "Iterations: " << iterations << endl;
			cout << "States: " << states << endl;
			break;
		}

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				State child = current;
				states++;
				if (j != child.GetQueenPosition(i))
				{
					child.moveQueen(i, j);
					if (!closed.contains(child))
					{
						h = child.F2();
						f = g + h;
						open.push(child, f);
					}
				}
			}
		}

		closed.insert(current);

		iterations++;
	}
}

void LDFS(State parent)
{
	int maxDepth = 0;
	int check = 0;
	int currIDepth = 1;
	int iterations = 0;
	int deadEnds = 0;
	cout << "Enter max depth: ";
	cin >> maxDepth;
	Algorithm(parent, 1, maxDepth, currIDepth, iterations, check, deadEnds);
}

void Algorithm(State state, int row, int maxDepth, int& currIDepth, int& iterations, int& check, int& deadEnds)
{
	if (check == 1)
	{
		return;
	}

	if (currIDepth + 1 > maxDepth)
	{
		deadEnds++;
		return;
	}

	if (row < 8)
	{
		for (int i = 0; i < 8; i++)
		{
			if (state.CheckSolution())
			{
				check = 1;
				cout << "Solution is found!" << endl;
				state.print();
				cout << "Depth: " << currIDepth << endl;
				cout << "Iterations: " << iterations << endl;
				cout << "Dead-ends: " << deadEnds << endl;
				return;
			}
			state.moveQueen(row, i);
			iterations++;
			currIDepth++;
			Algorithm(state, row + 1, maxDepth, currIDepth, iterations, check, deadEnds);
			currIDepth -= 1;
		}
	}
	else
	{
		deadEnds++;
	}
}
