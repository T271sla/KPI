#pragma once
#include <iostream>
#include "Set.h"
#include "Queue.h"
#include "State.h"
using namespace std;

void Algorithm(State state, int row, int maxIteration, int& currIteration, int& check);

void LDFS(State state)
{
	long long int maxIteration = 0;

	int check = 0;
	int currIteration = 0;
	
	Algorithm(state, 1, maxIteration, currIteration, check);
}

void Algorithm(State state, int row, int maxIteration, int& currIteration, int& check)
{
	if (row >= 8)
	{
		return;
	}

	if (check == 1)
	{
		return;
	}

	if (state.CheckForSolution())
	{
		check = 1;
		cout << "Solution is found!" << endl;
		state.print();
		return;
	}

	for (int i = 0; i < 8; i++)
	{
		state.moveQueen(row, i);
		currIteration++;
		Algorithm(state, row + 1, maxIteration, currIteration, check);
	}
}

void Astar(State firstStep)
{
	Set<State> closed;
	PreorityQueue<State> open;
	int g = 0;
	int h = F2(firstStep);
	int f = g + h;
	open.push(firstStep, f);

	int counter = 0;
	while (true)
	{

		State current = open.pop();

		if (!closed.contains(current))
		{
			g++;
			h = F2(current);
			if (h == 0)
			{
				cout << "Solution is found!" << endl;
				current.print();
				cout << "\nState " << counter + 1 << ":" << endl;
				int amount = closed.getLength() + open.GetLength();
				cout << "States in memory - " << amount << endl;
				cout << "Total states - " << amount << endl;
				break;
			}
			else
			{
				closed.insert(current);

				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						State childStep = current;
						if (j != childStep.GetQueenPosition(i))
						{
							childStep.moveQueen(i, j);
						}
						h = F2(childStep);
						f = g + h;
						open.push(childStep, f);
					}
				}
			}
		}
		counter++;
	}
}