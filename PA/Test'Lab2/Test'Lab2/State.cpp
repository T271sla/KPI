#include "State.h"

State::State()
{
	for (int i = 0; i < 8; i++)
	{
		board[i] = 0;
	}
}

void State::randomState()
{
	for (int i = 0; i < 8; i++)
	{
		board[i] = rand() % 8;
	}
}

void State::makeState()
{
	int temp;

	for (int i = 0; i < 8; i++)
	{
		cin >> temp;
		board[i] = temp;
	}
}


void State::moveQueen(int index, int position)
{
	this->board[index] = position;
}

void State::print()
{
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (this->board[j] == i)
			{
				cout << "Q" << " ";
			}
			else
			{
				cout << "-" << " ";
			}
		}
		cout << endl;
	}
}

bool State::CheckForSolution()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((this->board[i] == this->board[j]) && (i != j))
			{
				return false;
			}
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = this->board[i]; j < 8 - i; i++)
		{
			if (this->board[j] == this->board[i] + j)
			{
				return false;
			}
		}
	}

	return true;
}

int F2(State state)
{
	int countPairs = 0;

	int arr1[8] = { 0,0,0,0,0,0,0,0 };

	for (int i = 0; i < 8; i++)
	{
		arr1[state.board[i]]++;
	}

	countPairs += countPairsInArr(arr1, 8);

	int arr2[15] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	for (int i = 0; i < 8; i++)
	{
		arr2[7 + (i - state.board[i])]++;
	}

	countPairs += countPairsInArr(arr2, 15);

	int arr3[15] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	for (int i = 0; i < 8; i++)
	{
		arr3[i + state.board[i]]++;
	}

	countPairs += countPairsInArr(arr3, 15);

	return countPairs;
}

int countPairsInArr(int arr[], int n)
{
	int countPairsInArr = 0;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > 1)
		{
			countPairsInArr += Combination(arr[i], 2);
		}
	}
	return countPairsInArr;
}

int Combination(int n, int m)
{
	if (m == 0 || n == m)
	{
		return 1;
	}
	else
	{
		return Combination(n - 1, m - 1) + Combination(n - 1, m);
	}
}

bool State::operator==(State state)
{
	for (int i = 0; i < 8; i++)
	{
		if (this->board[i] != state.board[i])
		{
			return false;
		}
	}

	return true;
}