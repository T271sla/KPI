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

int State::F2()
{
	int tempBoard[8];

	for (int i = 0; i < 8; i++)
	{
		tempBoard[i] = this->board[i];
	}

	int count = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			if (tempBoard[i] == tempBoard[j])
			{
				count++;
			}
		}
	}

	int p;

	for (int i = 0; i < 8; i++)
	{
		p = 1;
		while ((i + p < 8) & (tempBoard[i] + p < 8))
		{
			if (tempBoard[i + p] == tempBoard[i] + p)
			{
				count++;
			}
			p++;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		p = 1;
		while ((i + p < 8) & (tempBoard[i] - p > -1))
		{
			if (tempBoard[i + p] == tempBoard[i] - p)
			{
				count++;
			}
			p++;
		}
	}

	return count;
}

bool State::CheckSolution()
{
	int tempBoard[8];

	for (int i = 0; i < 8; i++)
	{
		tempBoard[i] = this->board[i];
	}

	int count = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			if (tempBoard[i] == tempBoard[j])
			{
				return false;
			}
		}
	}

	int p;

	for (int i = 0; i < 8; i++)
	{
		p = 1;
		while ((i + p < 8) & (tempBoard[i] + p < 8))
		{
			if (tempBoard[i + p] == tempBoard[i] + p)
			{
				return false;
			}
			p++;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		p = 1;
		while ((i + p < 8) & (tempBoard[i] - p > -1))
		{
			if (tempBoard[i + p] == tempBoard[i] - p)
			{
				return false;
			}
			p++;
		}
	}

	return true;
}


bool State::operator==(State field)
{
	for (int i = 0; i < 8; i++)
	{
		if (this->board[i] != field.board[i])
		{
			return false;
		}
	}
	return true;
}