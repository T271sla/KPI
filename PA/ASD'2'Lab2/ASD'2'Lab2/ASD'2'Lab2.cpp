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
void Algorithm(State state, int row, int maxIteration, int& currIteration, int& check);

int main()
{
	srand(time(NULL));

	FindLDFS();

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
	parent.makeState();

	cout << "First step:" << endl;

	parent.print();

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

	open.push(parent, 0);

	while (open.GetLength() != 0)
	{
		State current = open.pop();
		g++;

		if (current.F2() == 0)
		{
			cout << "Solution is found!" << std::endl;
			current.print();
			break;
		}

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				State child = current;
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
	}
}

void LDFS(State parent)
{
	long long int maxDepth = 0;
	int check = 0;
	int currIDepth = 1;
	cout << "Enter max iteration: ";
	cin >> maxDepth;
	Algorithm(parent, 1, maxDepth, currIDepth, check);
}

void Algorithm(State state, int row, int maxDepth, int& currIDepth, int& check)
{
	if (check == 1)
	{
		return;
	}

	if (currIDepth + 1 > maxDepth)
	{
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
				cout << "Iterations: " << currIDepth << endl;
				return;
			}
			state.moveQueen(row, i);
			currIDepth++;
			Algorithm(state, row + 1, maxDepth, currIDepth, check);
			currIDepth -= 1;
		}
	}
}
